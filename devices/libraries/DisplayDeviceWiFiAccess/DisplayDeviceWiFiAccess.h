#ifndef DisplayDeviceWiFiAccess_h
#define DisplayDeviceWiFiAccess_h

#include "Arduino.h"
#include "ArduinoJson.h"

#define MESSAGE_INTERVAL 1000

namespace ART
{
	class DisplayDevice;

	class DisplayDeviceWiFiAccess
	{
	public:

		DisplayDeviceWiFiAccess(DisplayDevice* displayDevice);
		~DisplayDeviceWiFiAccess();

		static void					create(DisplayDeviceWiFiAccess* (&displayDeviceWiFiAccess), DisplayDevice* displayDevice);

		void						updatePin(char* json);
		void						loop();

	private:

		DisplayDevice *				_displayDevice;

		String 						_pin;
		int 						_nextFireTimeInSeconds = -1;

		uint64_t 					_messageTimestamp = 0;
	};
}

#endif
