from __future__ import print_function
import logging
import logging.handlers
import sys
import time
import subprocess
import psutil
import serial
import serial.tools.list_ports as lspt

MAGIC_handshake = 0x77
MAGIC_INFO_cpu_prct = 0x10
MAGIC_INFO_cpu_fqar = 0x11
MAGIC_INFO_cpu_fqmx = 0x12
MAGIC_INFO_cpu_load = 0x13
MAGIC_INFO_gpu_prct = 0x20
MAGIC_INFO_gpu_freq = 0x21
MAGIC_INFO_gpu_temp = 0x22
MAGIC_INFO_gpu_mem = 0x23
MAGIC_INFO_gpu_fan = 0x24
MAGIC_INFO_gpu_pwr = 0x25
MAGIC_INFO_mem_prct = 0x30
MAGIC_INFO_mem_aval = 0x31
MAGIC_INFO_net_up = 0x40
MAGIC_INFO_net_down = 0x41
MAGIC_INFO_rot_fan = 0x50
MAGIC_INFO_rot_pump = 0x51
MAGIC_INFO_tmp_cpu = 0x52
MAGIC_INFO_tmp_ssd = 0x53
MAGIC_INFO_tmp_wifi = 0x54
MAGIC_INFO_weather = 0x60

GPU_MAXRPM = 2600

class disp_server:
    def __init__(self):
        self.baud = 115200
        self.net_nic_eth = 'enp6s0'
        self.net_nic_wl = 'wlp5s0'
        #preload net stats
        net_eth = psutil.net_io_counters(pernic=True)[self.net_nic_eth]
        self.net_eth_sent = net_eth[0]
        self.net_eth_recv = net_eth[1]
        self.net_timestamp = time.time()

    def eprint(self,*args, **kwargs):
        print(*args, file=sys.stderr, **kwargs)

    def get_gpustats(self):
        try:
            return subprocess.check_output(['/usr/bin/nvidia-smi', '--query-gpu=utilization.gpu,clocks.gr,memory.free,temperature.gpu,fan.speed,power.draw', '--format=csv,noheader']).decode().strip().replace(' ','').replace('%','').replace('iB','B').split(',')
        except:
            return []


    def wait_online(self):
        self.eprint("Waiting for arduino online...")
        while True:
            ports = [tuple(p) for p in lspt.comports()]
            for p in ports:
                if '0182CFD6' in p[2]:
                    self.port_path = p[0]
                    self.eprint("Found target Arduino device at "+p[0]+". Opening connection...")
                    self.arduino = serial.Serial(self.port_path, self.baud, timeout = 1)
                    time.sleep(3)
                    return
            time.sleep(60)

    def wait_handshake(self):
        while True:
            self.arduino.write(MAGIC_handshake.to_bytes(1,'little') + '\0'.encode())
            rep = self.arduino.read(1)
            if rep==MAGIC_handshake.to_bytes(1,'little'):
                self.eprint("Connected to Arduino at "+self.port_path+".")
                return True
            else:
                self.eprint("Waiting for Arduino at "+self.port_path+" to be connected...")
                time.sleep(30)

    def to_hrunit(self, size, digits=3, trailers=1, divider=1024.0, till = 1024.0, suffix=''):
        for unit in ['','K','M','G','T','P','E','Z']:
            if abs(size) < till:
                return '{0:{d}.{t}f}{1}{2}'.format(size, unit, suffix, d=digits, t=trailers)
            size /= divider
        return '{0:{d}.{t}f}{1}{2}'.format(size, 'Y', suffix, d=digits, t=trailers)

    def send_sysinfo(self, command = 0):
        byte_count = 0
        if command==0:
            #cpu
            byte_count += self.arduino.write(MAGIC_INFO_cpu_prct.to_bytes(1,'little') + (str(psutil.cpu_percent())+'\0').encode())
            freq = [i[0] for i in psutil.cpu_freq(percpu=True)]
            byte_count += self.arduino.write(MAGIC_INFO_cpu_fqar.to_bytes(1,'little') + (str(int(sum(freq)/len(freq)))+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_cpu_fqmx.to_bytes(1,'little') + (str(int(max(freq)))+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_cpu_load.to_bytes(1,'little') + (str(psutil.getloadavg()[0])+'\0').encode())
            return byte_count
        elif command==1:
            #mem
            mem = psutil.virtual_memory()
            byte_count += self.arduino.write(MAGIC_INFO_mem_prct.to_bytes(1,'little') + (str(mem[2])+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_mem_aval.to_bytes(1,'little') + (self.to_hrunit(mem[1],digits=2,trailers=0,till=70000,suffix='B')+'\0').encode())
            return byte_count
        elif command==2:
            #fan
            fan = psutil.sensors_fans()['nct6798']
            byte_count += self.arduino.write(MAGIC_INFO_rot_fan.to_bytes(1,'little') + (str(fan[1][1])+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_rot_pump.to_bytes(1,'little') + (str(fan[2][1])+'\0').encode())
            #Since switched to watercooling, GPU fan is not read from/controlled by the chassis fan connector
            byte_count += self.arduino.write(MAGIC_INFO_gpu_fan.to_bytes(1,'little') + (str(fan[0][1])+'\0').encode())
            return byte_count
        elif command==3:
            #gpu
            gpu = self.get_gpustats()
            byte_count += self.arduino.write(MAGIC_INFO_gpu_prct.to_bytes(1,'little') + (str(gpu[0])+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_gpu_freq.to_bytes(1,'little') + (str(gpu[1])+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_gpu_temp.to_bytes(1,'little') + (str(gpu[3])+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_gpu_mem.to_bytes(1,'little') + (str(gpu[2])+'\0').encode())
            #byte_count += self.arduino.write(MAGIC_INFO_gpu_fan.to_bytes(1,'little') + (str(int(int(gpu[4])*GPU_MAXRPM/100))+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_gpu_pwr.to_bytes(1,'little') + (str(gpu[5])+'\0').encode())
            return byte_count
        elif command==4:
            #temperature
            temp = psutil.sensors_temperatures()
            byte_count += self.arduino.write(MAGIC_INFO_tmp_cpu.to_bytes(1,'little') + ('{0:.1f}'.format(temp['k10temp'][0][1])+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_tmp_ssd.to_bytes(1,'little') + ('{0:.1f}'.format(max([t[1] for t in temp['nvme']]))+'\0').encode())
            #byte_count += self.arduino.write(MAGIC_INFO_tmp_wifi.to_bytes(1,'little') + ('{0:.1f}'.format(temp['iwlwifi_1'][0][1])+'\0').encode())
            return byte_count
        elif command==5:
            #net
            new_sent,new_recv = psutil.net_io_counters(pernic=True)[self.net_nic_eth][0:2]
            new_time = time.time()
            byte_count += self.arduino.write(MAGIC_INFO_net_up.to_bytes(1,'little') + (self.to_hrunit((new_sent - self.net_eth_sent)/(new_time - self.net_timestamp), suffix='Bps')+'\0').encode())
            byte_count += self.arduino.write(MAGIC_INFO_net_down.to_bytes(1,'little') + (self.to_hrunit((new_recv - self.net_eth_recv)/(new_time - self.net_timestamp), suffix='Bps')+'\0').encode())
            self.net_eth_sent = new_sent
            self.net_eth_recv = new_recv
            self.net_timestamp = new_time
            return byte_count

    def run(self):
        self.wait_online()
        self.wait_handshake()
        while True:
            byte_count = 0
            for i in range(6):
                byte_count += self.send_sysinfo(command = i)
                time.sleep(0.1)
                byte_count = 0
            time.sleep(1)
        self.arduino.close()

if __name__=='__main__':
    disp =  disp_server()
    while True:
        disp.run()
