#include "DisplayDevice.h"
#include "Arduino.h"
#include "SPI.h"
#include "Wire.h"
#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

#define LOGO_GLCD_X 0
#define LOGO_GLCD_Y 0 
#define LOGO_GLCD_HEIGHT 64 
#define LOGO_GLCD_WIDTH 128 
static const unsigned char PROGMEM logo16_glcd_bmp[] =
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7E, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x7E, 0x70, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x3C, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x10, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x0C, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x1E, 0x00, 0x00,
0x00, 0x01, 0x80, 0x00, 0x00, 0x00, 0x00, 0x7C, 0x00, 0x00, 0x0F, 0x80, 0x00, 0x1E, 0x00, 0x00,
0x00, 0x03, 0xC0, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x12, 0x00, 0x00,
0x00, 0x03, 0xE0, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x33, 0x00, 0x00,
0x00, 0x01, 0xE0, 0x00, 0x00, 0x00, 0x7F, 0xF0, 0x00, 0x00, 0x3F, 0x00, 0x00, 0x23, 0x00, 0x00,
0x00, 0x00, 0xC0, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x61, 0x80, 0x00,
0x00, 0x18, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xF8, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7F, 0x80, 0x00,
0x00, 0x1C, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x7F, 0x80, 0x00,
0x00, 0x10, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xC0, 0xC0, 0x00,
0x00, 0x10, 0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7E, 0x00, 0x00, 0xC0, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xE0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xF0, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x7C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x01, 0xE0, 0x08, 0x20, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x18, 0x01, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3C, 0x01, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x7E, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0xFF, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x30, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x78, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x38, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x70, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x70, 0x00, 0x00, 0x7F, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0xF0, 0x00, 0x00, 0x7F, 0x80, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x00, 0x61, 0x80, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x61, 0x80, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x00, 0x7F, 0x80, 0x00,
0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x78, 0x00, 0x00, 0x7E, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x78, 0x00, 0x00, 0x63, 0x00, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x38, 0x00, 0x00, 0x63, 0x80, 0x00,
0x00, 0x00, 0x01, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x38, 0x00, 0x00, 0x61, 0x80, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFE, 0x00, 0x3C, 0x00, 0x00, 0x61, 0xC0, 0x00,
0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFC, 0x00, 0x3C, 0x00, 0x00, 0x60, 0xC0, 0x00,
0x00, 0x00, 0x00, 0x7F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF8, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0xFF, 0xF0, 0x00, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x0F, 0xFF, 0xFF, 0xFF, 0xFF, 0xE0, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x7E, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x07, 0xFF, 0xFF, 0xFC, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xFF, 0xF0, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xFF, 0x80, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0x80, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xC0, 0x00, 0x00, 0x7F, 0x00, 0x00, 0xFF, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xE0, 0x00, 0x00, 0x3F, 0x80, 0x00, 0xFF, 0x80, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF0, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xFF, 0xF0, 0x00, 0x00, 0x1F, 0x80, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x00, 0x07, 0xC0, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xF8, 0x00, 0x00, 0x03, 0xC0, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0xF8, 0x00, 0x00, 0x00, 0xE0, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1F, 0xF8, 0x00, 0x00, 0x00, 0x38, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x08, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

namespace ART
{
	DisplayDevice::DisplayDevice()
	{
		DisplayDeviceBinary::create(_displayDeviceBinary, this);
	}

	DisplayDevice::~DisplayDevice()
	{
		delete (_displayDeviceBinary);
	}

	void DisplayDevice::begin()
	{
		// Display
		// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
		display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
													// init done

													// Show image buffer on the display hardware.
													// Since the buffer is intialized with an Adafruit splashscreen

		display.clearDisplay();
		display.drawBitmap(LOGO_GLCD_X, LOGO_GLCD_Y, logo16_glcd_bmp, LOGO_GLCD_WIDTH, LOGO_GLCD_HEIGHT, 1);						// internally, this will display the splashscreen.
		display.display();
		delay(3000);

		// Clear the buffer.
		display.clearDisplay();
	}

	DisplayDeviceBinary * DisplayDevice::getDisplayDeviceBinary()
	{
		return _displayDeviceBinary;
	}
	
}