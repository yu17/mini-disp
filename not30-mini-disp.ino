#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define INT_SIZE 16
#define INT_MSB 16384

#define HDD_PIN 9

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

//#define NUMFLAKES     10 // Number of snowflakes in the animation example
//#define XPOS   0 // Indexes into the 'icons' array in function below
//#define YPOS   1
//#define DELTAY 2
//
//void testanimate(const uint8_t *bitmap, uint8_t w, uint8_t h) {
//	int8_t f, icons[NUMFLAKES][3];
//
//	// Initialize 'snowflake' positions
//	for(f=0; f< NUMFLAKES; f++) {
//		icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
//		icons[f][YPOS]   = -LOGO_HEIGHT;
//		icons[f][DELTAY] = random(1, 6);
//		Serial.print(F("x: "));
//		Serial.print(icons[f][XPOS], DEC);
//		Serial.print(F(" y: "));
//		Serial.print(icons[f][YPOS], DEC);
//		Serial.print(F(" dy: "));
//		Serial.println(icons[f][DELTAY], DEC);
//	}
//
//	for(;;) { // Loop forever...
//		display.clearDisplay(); // Clear the display buffer
//
//		// Draw each snowflake:
//		for(f=0; f< NUMFLAKES; f++) {
//			display.drawBitmap(icons[f][XPOS], icons[f][YPOS], bitmap, w, h, SSD1306_WHITE);
//		}
//
//		display.display(); // Show the display buffer on the screen
//		delay(200);        // Pause for 1/10 second
//
//		// Then update coordinates of each flake...
//		for(f=0; f< NUMFLAKES; f++) {
//			icons[f][YPOS] += icons[f][DELTAY];
//			// If snowflake is off the bottom of the screen...
//			if (icons[f][YPOS] >= display.height()) {
//				// Reinitialize to a random position, just off the top
//				icons[f][XPOS]   = random(1 - LOGO_WIDTH, display.width());
//				icons[f][YPOS]   = -LOGO_HEIGHT;
//				icons[f][DELTAY] = random(1, 6);
//			}
//		}
//	}
//}

	// Show the display buffer on the screen. You MUST call display() after
	// drawing commands to make them visible on screen!
//	display.display();
	// display.display() is NOT necessary after every single drawing command,
	// unless that's what you want...rather, you can batch up a bunch of
	// drawing operations and then update the screen all at once by calling
	// display.display(). These examples demonstrate both approaches...

	// Invert and restore display, pausing in-between
//	display.invertDisplay(true);
//	delay(1000);
//	display.invertDisplay(false);
//	delay(1000);

	// Show initial display buffer contents on the screen --
	// the library initializes this with an Adafruit splash screen.
//	display.display();

	// Draw a single pixel in white
//	display.drawPixel(10, 10, SSD1306_WHITE);

//Splash Logo BMP binary
#define ICON_HEIGHT 32
#define ICON_WIDTH 64
static const unsigned char PROGMEM icon_bmp[] =
	{0, 0, 60, 0, 0, 0, 0, 0,
	0, 3, 196, 0, 0, 0, 0, 0,
	0, 12, 4, 0, 0, 0, 0, 0,
	0, 48, 4, 0, 16, 0, 0, 0,
	0, 192, 4, 0, 32, 0, 0, 1,
	1, 0, 4, 0, 32, 0, 0, 3,
	2, 0, 4, 0, 64, 8, 0, 3,
	4, 0, 4, 0, 128, 16, 0, 5,
	8, 7, 4, 0, 128, 16, 0, 9,
	16, 7, 4, 1, 0, 32, 16, 17,
	32, 7, 4, 2, 0, 64, 32, 17,
	32, 0, 4, 2, 0, 128, 64, 33,
	64, 0, 4, 4, 0, 128, 64, 65,
	64, 0, 4, 8, 1, 0, 128, 129,
	128, 0, 4, 8, 2, 1, 0, 129,
	128, 0, 7, 255, 255, 255, 255, 1,
	128, 0, 4, 8, 2, 1, 0, 129,
	128, 0, 4, 4, 1, 0, 128, 65,
	64, 0, 4, 4, 0, 128, 64, 65,
	64, 0, 4, 2, 0, 128, 64, 33,
	32, 12, 4, 1, 0, 64, 32, 17,
	32, 56, 4, 1, 0, 32, 16, 17,
	19, 224, 4, 0, 128, 16, 0, 9,
	14, 0, 4, 0, 128, 16, 0, 9,
	4, 0, 4, 0, 64, 8, 0, 5,
	3, 0, 4, 0, 32, 0, 0, 3,
	0, 128, 4, 0, 32, 0, 0, 3,
	0, 96, 4, 0, 16, 0, 0, 1,
	0, 24, 4, 0, 0, 0, 0, 0,
	0, 6, 4, 0, 0, 0, 0, 0,
	0, 1, 196, 0, 0, 0, 0, 0,
	0, 0, 60, 0, 0, 0, 0, 0};

//HDD activity icon BMP binary
#define HDD_HEIGHT 16
#define HDD_WIDTH 10
static const unsigned char PROGMEM hdd_bmp[] =
	{B00001100, B00000000,
	B01110011, B10000000,
	B01111111, B10000000,
	B01110011, B10000000,
	B10001100, B01000000,
	B11110011, B11000000,
	B10001100, B01000000,
	B10000000, B01000000,
	B10000000, B01000000,
	B10000000, B01000000,
	B10000000, B01000000,
	B10000000, B01000000,
	B10000000, B01000000,
	B10000000, B01000000,
	B01110011, B10000000,
	B00001100, B00000000};

static const unsigned char PROGMEM hdd_fill[] =
	{B00001100, B00000000,
	B01110011, B10000000,
	B01111111, B10000000,
	B01110011, B10000000,
	B10001100, B01000000,
	B11110011, B11000000,
	B10001100, B01000000,
	B10110011, B01000000,
	B10111111, B01000000,
	B10111111, B01000000,
	B10111111, B01000000,
	B10111111, B01000000,
	B10111111, B01000000,
	B10001100, B01000000,
	B01110011, B10000000,
	B00001100, B00000000};
// sysinfo icons
#define CPU_HEIGHT 16
#define CPU_WIDTH 16
static const unsigned char PROGMEM cpu_bmp[] =
	{B00001010,B01010000,
	B00001010,B01010000,
	B00001010,B01010000,
	B00011111,B11111000,
	B11110000,B00001111,
	B00010000,B00001000,
	B11110011,B11001111,
	B00010011,B11001000,
	B00010011,B11001000,
	B11110011,B11001111,
	B00010000,B00001000,
	B11110000,B00001111,
	B00011111,B11111000,
	B00001010,B01010000,
	B00001010,B01010000,
	B00001010,B01010000};
#define GPU_HEIGHT 16
#define GPU_WIDTH 16
static const unsigned char PROGMEM gpu_bmp[] =
	{B00001010,B01010000,
	B00001010,B01010000,
	B00001010,B01010000,
	B00011111,B11111000,
	B11110000,B00001111,
	B00010011,B11001000,
	B11110100,B00101111,
	B00010100,B00001000,
	B00010100,B11101000,
	B11110100,B00101111,
	B00010011,B11001000,
	B11110000,B00001111,
	B00011111,B11111000,
	B00001010,B01010000,
	B00001010,B01010000,
	B00001010,B01010000};

#define MEM_HEIGHT 9
#define MEM_WIDTH 9
static const unsigned char PROGMEM mem_bmp[] =
	{B01010101,B00000000,
	B01010101,B00000000,
	B11111111,B10000000,
	B10000000,B10000000,
	B10000000,B10000000,
	B10000000,B10000000,
	B11111111,B10000000,
	B01010101,B00000000,
	B01010101,B00000000};
#define NET_HEIGHT 10
#define NET_WIDTH 10
static const unsigned char PROGMEM net_bmp[] =
	{B00010000,B00000000,
	B00110000,B00000000,
	B01010010,B00000000,
	B10010010,B00000000,
	B00010010,B00000000,
	B00010010,B00000000,
	B00010010,B01000000,
	B00010010,B10000000,
	B00000011,B00000000,
	B00000010,B00000000};
#define FAN_HEIGHT 10
#define FAN_WIDTH 10
static const unsigned char PROGMEM fan_bmp[] =
	{B00011111,B00000000,
	B00011110,B00000000,
	B10011000,B00000000,
	B11010011,B11000000,
	B11001101,B11000000,
	B11101100,B11000000,
	B11110010,B11000000,
	B00000110,B01000000,
	B00011110,B00000000,
	B00111110,B00000000};
#define PUMP_HEIGHT 10
#define PUMP_WIDTH 10
static const unsigned char PROGMEM pump_bmp[] =
	{B11111111,B11000000,
	B10000000,B01000000,
	B10100111,B01000000,
	B10101100,B01000000,
	B10110010,B01000000,
	B10010011,B01000000,
	B10001101,B01000000,
	B10111001,B01000000,
	B10000000,B01000000,
	B11111111,B11000000};
#define TEMP_HEIGHT 10
#define TEMP_WIDTH 4
static const unsigned char PROGMEM temp_bmp[] =
	{B01100000,
	B01000000,
	B01100000,
	B01000000,
	B01100000,
	B01000000,
	B01100000,
	B11110000,
	B11110000,
	B01100000};

#define MAGIC_handshake 0x77
#define MAGIC_INFO_cpu_prct 0x10
#define MAGIC_INFO_cpu_fqar 0x11
#define MAGIC_INFO_cpu_fqmx 0x12
#define MAGIC_INFO_cpu_load 0x13
#define MAGIC_INFO_gpu_prct 0x20
#define MAGIC_INFO_gpu_freq 0x21
#define MAGIC_INFO_gpu_temp 0x22
#define MAGIC_INFO_gpu_mem 0x23
#define MAGIC_INFO_gpu_fan 0x24
#define MAGIC_INFO_gpu_pwr 0x25
#define MAGIC_INFO_mem_prct 0x30
#define MAGIC_INFO_mem_aval 0x31
#define MAGIC_INFO_net_up 0x40
#define MAGIC_INFO_net_down 0x41
#define MAGIC_INFO_rot_fan 0x50
#define MAGIC_INFO_rot_pump 0x51
#define MAGIC_INFO_tmp_cpu 0x52
#define MAGIC_INFO_tmp_ssd 0x53
#define MAGIC_INFO_tmp_wifi 0x54
#define MAGIC_INFO_weather 0x60

//Setup global variables
//int hdd_occ[4] = {0,0,0,0};
//char hdd_string[5];
//char hdd_status = HIGH; //active on low
//char hdd_last = HIGH;

char cpu_prct[8];
char cpu_fqar[8];
char cpu_fqmx[8];
char cpu_load[8];
char gpu_prct[8];
char gpu_freq[8];
char gpu_temp[8];
char gpu_mem[8];
char gpu_fan[8];
char gpu_pwr[8];
char mem_prct[8];
char mem_aval[10];
char net_up[10];
char net_down[10];
char rot_fan[10];
char rot_pump[10];
char tmp_cpu[10];
char tmp_ssd[10];
char tmp_wifi[10];
char weather[15];

int inactive_count_sys;//, inactive_count_hdd;
int loop_count;
char inactive_flag;

int disp_status_update(){
	if (inactive_count_sys&&inactive_flag) {
		display.ssd1306_command(SSD1306_DISPLAYON);
		inactive_flag = 0;
	}
	else if (!inactive_count_sys&&!inactive_flag) {
		display.ssd1306_command(SSD1306_DISPLAYOFF);
		inactive_flag = 1;
	}
	return inactive_flag;
}

//int HDDCountBit(){
//	int n=0;
//	int p;
//	for(int i=0;i<4;i++){
//		p=hdd_occ[i];
//		while (p){
//			p &= (p-1);
//			n++;
//		}
//	}
//	return n;
//}
//
//int HDDActivity(){
//	int t=HDDCountBit();
//	if (t > 33) return 100;
//	else return t*3;
//}
//
//int HDDUpdate(int value){
//	for(int i=0;i<3;i++){
//		hdd_occ[i] = (hdd_occ[i] << 1) + (hdd_occ[i+1]<0);
//	}
//	hdd_occ[3] = (hdd_occ[3] << 1) + value;
//}

void SerialHandler(){
	char flag = Serial.read();
	if (flag==-1) return;
	inactive_count_sys = 30000;
	char buffer[16];
	int i = 0;
	char c = flag;
	for(;c!='\0'&&i<16;){
		c = Serial.read();
		if (c!=-1) buffer[i++] = c;
		else delay(1);
	}
	buffer[i+1] = '\0';
	if (flag==MAGIC_handshake){
		Serial.write(MAGIC_handshake);
	}
	else if (flag==MAGIC_INFO_cpu_prct){
		strcpy(cpu_prct,buffer);
		strcat(cpu_prct,"%");
	}
	else if (flag==MAGIC_INFO_cpu_fqar){
		strcpy(cpu_fqar,buffer);
		strcat(cpu_fqar,"MHz");
	}
	else if (flag==MAGIC_INFO_cpu_fqmx){
		strcpy(cpu_fqmx,buffer);
		strcat(cpu_fqmx,"MHz");
	}
	else if (flag==MAGIC_INFO_cpu_load){
		strcpy(cpu_load,buffer);
	}
	else if (flag==MAGIC_INFO_gpu_prct){
		strcpy(gpu_prct,buffer);
		strcat(gpu_prct,"%");
	}
	else if (flag==MAGIC_INFO_gpu_freq){
		strcpy(gpu_freq,buffer);
	}
	else if (flag==MAGIC_INFO_gpu_temp){
		strcpy(gpu_temp,buffer);
		strcat(gpu_temp,"\370C");
	}
	else if (flag==MAGIC_INFO_gpu_mem){
		strcpy(gpu_mem,buffer);
	}
	else if (flag==MAGIC_INFO_gpu_fan){
		strcpy(gpu_fan,buffer);
		strcat(gpu_fan,"RPM");
	}
	else if (flag==MAGIC_INFO_gpu_pwr){
		strcpy(gpu_pwr,buffer);
	}
	else if (flag==MAGIC_INFO_mem_prct){
		strcpy(mem_prct,buffer);
		strcat(mem_prct,"%");
	}
	else if (flag==MAGIC_INFO_mem_aval){
		strcpy(mem_aval,buffer);
	}
	else if (flag==MAGIC_INFO_net_up){
		strcpy(net_up,buffer);
	}
	else if (flag==MAGIC_INFO_net_down){
		strcpy(net_down,buffer);
	}
	else if (flag==MAGIC_INFO_rot_fan){
		strcpy(rot_fan,buffer);
	}
	else if (flag==MAGIC_INFO_rot_pump){
		strcpy(rot_pump,buffer);
	}
	else if (flag==MAGIC_INFO_tmp_cpu){
		strcpy(tmp_cpu,buffer);
		strcat(tmp_cpu,"\370C");
	}
	else if (flag==MAGIC_INFO_tmp_ssd){
		strcpy(tmp_ssd,buffer);
		strcat(tmp_ssd,"\370C");
	}
	else if (flag==MAGIC_INFO_tmp_wifi){
		strcpy(tmp_wifi,buffer);
		strcat(tmp_wifi,"\370C");
	}
	else if (flag==MAGIC_INFO_weather){
		strcpy(weather,buffer);
	}
}

//void RenderHDDinfo(){
//	// HDD icon
//	if (hdd_status) display.drawBitmap(SCREEN_WIDTH-HDD_WIDTH, 0,hdd_bmp,HDD_WIDTH, HDD_HEIGHT, 1);
//	else display.drawBitmap(SCREEN_WIDTH-HDD_WIDTH, 0,hdd_fill,HDD_WIDTH, HDD_HEIGHT, 1);
//	// HDD active percentage counter
//	sprintf(hdd_string,"%02d%%",HDDActivity());
//	if (strlen(hdd_string)>3) display.setCursor(SCREEN_WIDTH-24,HDD_HEIGHT+2);
//	else display.setCursor(SCREEN_WIDTH-18,HDD_HEIGHT+2);
//	display.print(hdd_string);
//}

void RenderSysinfo(){
	display.drawBitmap(0,0,cpu_bmp,CPU_WIDTH,CPU_HEIGHT,1);
	display.setCursor(18,0);
	display.print(cpu_prct);
	display.setCursor(56,0);
	display.print(cpu_fqar);
	display.setCursor(18,8);
	display.print(cpu_load);
	display.setCursor(56,8);
	display.print(cpu_fqmx);
	display.drawBitmap(2,17,mem_bmp,MEM_WIDTH,MEM_HEIGHT,1);
	display.setCursor(12,18);
	display.print(mem_prct);
	display.setCursor(56,18);
	display.print(mem_aval);
	display.drawBitmap(2,27,fan_bmp,FAN_WIDTH,FAN_HEIGHT,1);
	display.setCursor(14,28);
	display.print(rot_fan);
	display.drawBitmap(42,27,pump_bmp,PUMP_WIDTH,PUMP_HEIGHT,1);
	display.setCursor(54,28);
	display.print(rot_pump);
	display.drawBitmap(82,27,temp_bmp,TEMP_WIDTH,TEMP_HEIGHT,1);
	display.setCursor(90,28);
	display.print(tmp_cpu);
	display.drawBitmap(0,38,gpu_bmp,GPU_WIDTH,GPU_HEIGHT,1);
	display.setCursor(40-6*strlen(gpu_prct),38);
	display.print(gpu_prct);
	display.setCursor(84-6*strlen(gpu_freq),38);
	display.print(gpu_freq);
	display.setCursor(128-6*strlen(gpu_mem),38);
	display.print(gpu_mem);
	display.setCursor(16,46);
	display.print(gpu_temp);
	display.setCursor(84-6*strlen(gpu_fan),46);
	display.print(gpu_fan);
	display.setCursor(128-6*strlen(gpu_pwr),46);
	display.print(gpu_pwr);
	display.drawBitmap(0,54,net_bmp,NET_WIDTH,NET_HEIGHT,1);
	display.setCursor(66-6*strlen(net_up),55);
	display.print(net_up);
	display.setCursor(67,55);
	display.print("/");
	display.setCursor(128-6*strlen(net_down),55);
	display.print(net_down);
	
	
//	/display.print(" ");
//	display.print(tmp_ssd);
//	display.print(" ");
//	display.print(tmp_wifi);
}

void setup() {
	//HW connection setup
	Serial.begin(115200);
	//pinMode(11,INPUT);
	//pinMode(12,INPUT);

	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//	if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
//		Serial.println(F("SSD1306 allocation failed"));
//		for(;;); // Don't proceed, loop forever
//	}
//	else Serial.println("SSD1306 init succeeded.");

	while (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) delay(2000);

	// global var init
	//inactive_count_hdd = 30000;
	inactive_count_sys = 30000;
	inactive_flag = 0;
	loop_count = 0;

	// Clear the buffer
	display.clearDisplay();

	// Boot splash screen
	display.drawBitmap((SCREEN_WIDTH-ICON_WIDTH)/2, (SCREEN_HEIGHT-ICON_HEIGHT)/2, icon_bmp, ICON_WIDTH, ICON_HEIGHT, 1);
	display.display();

	display.setTextSize(1);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(0, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font

	delay(2000);
}

void loop() {
	// Per loop routines
	loop_count++;
	loop_count%=1000;
	// Reduce inactive counter towards 0
	if (inactive_count_sys) inactive_count_sys--;
	//if (inactive_count_hdd) inactive_count_hdd--;
	// Check serial port for sys info update
	while (Serial.available()) SerialHandler();

	// Update HDD ststus every 10 cycles
	//if (!(loop_count%10)) {
	//	if (hdd_status = digitalRead(HDD_PIN)) HDDUpdate(0);
	//	else HDDUpdate(1);
	//	if (hdd_status!=hdd_last) {
	//		inactive_count_hdd = 30000;
	//		hdd_last = hdd_status;
	//	}
	//}

	// Turn on/off display according to inactive counter
	if (disp_status_update()) {
		// When the display is off, check for updates every 1 second and skip the display rendering process.
		delay(1000);
		return;
	}

	// Refresh display every 20 cycles
	if (!(loop_count%20)) {
		display.clearDisplay();

		// HDD status
		//if (inactive_count_hdd) RenderHDDinfo();

		// system status
		if (inactive_count_sys) RenderSysinfo();

		// Flush display
		display.display();
	}

	// 1ms per cycle
	delay(1);
}

void chartable(void) {
	display.clearDisplay();

	display.setTextSize(1);      // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE); // Draw white text
	display.setCursor(0, 0);     // Start at top-left corner
	display.cp437(true);         // Use full 256 char 'Code Page 437' font

	// Not all the characters will fit on the display. This is normal.
	// Library will draw what it can and the rest will be clipped.
	for(int16_t i=1; i<=168; i++) {
		if(i == '\n') display.write(' ');
		else          display.write(i);
	}
	display.display();
	delay(2000);

	display.clearDisplay();
	// Not all the characters will fit on the display. This is normal.
	// Library will draw what it can and the rest will be clipped.
	for(int16_t i=169; i<=255; i++) {
		if(i == '\n') display.write(' ');
		else          display.write(i);
	}
	display.display();
	delay(2000);
}

void i2c_scanner(){
	byte error, address;
	int nDevices;
 
	Serial.println("Scanning...");
 
	nDevices = 0;
	for(address = 1; address < 127; address++ )
	{
		// The i2c_scanner uses the return value of
		// the Write.endTransmisstion to see if
		// a device did acknowledge to the address.
		Wire.beginTransmission(address);
		error = Wire.endTransmission();
 
		if (error == 0)
		{
			Serial.print("I2C device found at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.print(address,HEX);
			Serial.println("  !");
			nDevices++;
		}
		else if (error==4)
		{
			Serial.print("Unknown error at address 0x");
			if (address<16)
				Serial.print("0");
			Serial.println(address,HEX);
		}    
	}
	if (nDevices == 0)
		Serial.println("No I2C devices found\n");
	else
		Serial.println("done\n");
}

void testdrawline() {
	int16_t i;

	display.clearDisplay(); // Clear display buffer

	for(i=0; i<display.width(); i+=4) {
		display.drawLine(0, 0, i, display.height()-1, SSD1306_WHITE);
		display.display(); // Update screen with each newly-drawn line
		delay(1);
	}
	for(i=0; i<display.height(); i+=4) {
		display.drawLine(0, 0, display.width()-1, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for(i=0; i<display.width(); i+=4) {
		display.drawLine(0, display.height()-1, i, 0, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for(i=display.height()-1; i>=0; i-=4) {
		display.drawLine(0, display.height()-1, display.width()-1, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for(i=display.width()-1; i>=0; i-=4) {
		display.drawLine(display.width()-1, display.height()-1, i, 0, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for(i=display.height()-1; i>=0; i-=4) {
		display.drawLine(display.width()-1, display.height()-1, 0, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	delay(250);

	display.clearDisplay();

	for(i=0; i<display.height(); i+=4) {
		display.drawLine(display.width()-1, 0, 0, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}
	for(i=0; i<display.width(); i+=4) {
		display.drawLine(display.width()-1, 0, i, display.height()-1, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000); // Pause for 2 seconds
}

void testdrawrect(void) {
	display.clearDisplay();

	for(int16_t i=0; i<display.height()/2; i+=2) {
		display.drawRect(i, i, display.width()-2*i, display.height()-2*i, SSD1306_WHITE);
		display.display(); // Update screen with each newly-drawn rectangle
		delay(1);
	}

	delay(2000);
}

void testfillrect(void) {
	display.clearDisplay();

	for(int16_t i=0; i<display.height()/2; i+=3) {
		// The INVERSE color is used so rectangles alternate white/black
		display.fillRect(i, i, display.width()-i*2, display.height()-i*2, SSD1306_INVERSE);
		display.display(); // Update screen with each newly-drawn rectangle
		delay(1);
	}

	delay(2000);
}

void testdrawcircle(void) {
	display.clearDisplay();

	for(int16_t i=0; i<max(display.width(),display.height())/2; i+=2) {
		display.drawCircle(display.width()/2, display.height()/2, i, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testfillcircle(void) {
	display.clearDisplay();

	for(int16_t i=max(display.width(),display.height())/2; i>0; i-=3) {
		// The INVERSE color is used so circles alternate white/black
		display.fillCircle(display.width() / 2, display.height() / 2, i, SSD1306_INVERSE);
		display.display(); // Update screen with each newly-drawn circle
		delay(1);
	}

	delay(2000);
}

void testdrawroundrect(void) {
	display.clearDisplay();

	for(int16_t i=0; i<display.height()/2-2; i+=2) {
		display.drawRoundRect(i, i, display.width()-2*i, display.height()-2*i,
			display.height()/4, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testfillroundrect(void) {
	display.clearDisplay();

	for(int16_t i=0; i<display.height()/2-2; i+=2) {
		// The INVERSE color is used so round-rects alternate white/black
		display.fillRoundRect(i, i, display.width()-2*i, display.height()-2*i,
			display.height()/4, SSD1306_INVERSE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testdrawtriangle(void) {
	display.clearDisplay();

	for(int16_t i=0; i<max(display.width(),display.height())/2; i+=5) {
		display.drawTriangle(
			display.width()/2  , display.height()/2-i,
			display.width()/2-i, display.height()/2+i,
			display.width()/2+i, display.height()/2+i, SSD1306_WHITE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testfilltriangle(void) {
	display.clearDisplay();

	for(int16_t i=max(display.width(),display.height())/2; i>0; i-=5) {
		// The INVERSE color is used so triangles alternate white/black
		display.fillTriangle(
			display.width()/2  , display.height()/2-i,
			display.width()/2-i, display.height()/2+i,
			display.width()/2+i, display.height()/2+i, SSD1306_INVERSE);
		display.display();
		delay(1);
	}

	delay(2000);
}

void testdrawstyles(void) {
	display.clearDisplay();

	display.setTextSize(1);             // Normal 1:1 pixel scale
	display.setTextColor(SSD1306_WHITE);        // Draw white text
	display.setCursor(0,0);             // Start at top-left corner
	display.println(F("Hello, world!"));

	display.setTextColor(SSD1306_BLACK, SSD1306_WHITE); // Draw 'inverse' text
	display.println(3.141592);

	display.setTextSize(2);             // Draw 2X-scale text
	display.setTextColor(SSD1306_WHITE);
	display.print(F("0x")); display.println(0xDEADBEEF, HEX);

	display.display();
	delay(2000);
}

void testscrolltext(void) {
	display.clearDisplay();

	display.setTextSize(2); // Draw 2X-scale text
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(10, 0);
	display.println(F("scroll"));
	display.display();      // Show initial text
	delay(100);

	// Scroll in various directions, pausing in-between:
	display.startscrollright(0x00, 0x0F);
	delay(2000);
	display.stopscroll();
	delay(1000);
	display.startscrollleft(0x00, 0x0F);
	delay(2000);
	display.stopscroll();
	delay(1000);
	display.startscrolldiagright(0x00, 0x07);
	delay(2000);
	display.startscrolldiagleft(0x00, 0x07);
	delay(2000);
	display.stopscroll();
	delay(1000);
}
