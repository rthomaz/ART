#include "Arduino.h"
#include "DisplayManager.h"

//#include <SPI.h>
//#include <Wire.h>
//#include <Adafruit_GFX.h>
//#include <Adafruit_SSD1306.h>

//#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
//#endif

DisplayManager::DisplayManager(Adafruit_SSD1306& display)
{
	this->_display = &display;
}

void DisplayManager::begin()
{
	// Display
	// by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
	// this->_display->begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
												// init done

												// Show image buffer on the display hardware.
												// Since the buffer is intialized with an Adafruit splashscreen
												// internally, this will display the splashscreen.
	//this->_display->display();
	//delay(2000);

	// Clear the buffer.
	//this->_display->clearDisplay();
}