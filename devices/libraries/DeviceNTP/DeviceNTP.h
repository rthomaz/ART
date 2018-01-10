#ifndef DeviceNTP_h
#define DeviceNTP_h

#include "Arduino.h"
#include "ArduinoJson.h"
#include "RemoteDebug.h"
#include "Udp.h"
#include "WiFiUdp.h"

#define SEVENZYYEARS 2208988800UL
#define NTP_PACKET_SIZE 48

#define DEVICE_NTP_SET_UPDATE_CALLBACK_SIGNATURE std::function<void(bool, bool)>

namespace ART
{
	class ESPDevice;

	class DeviceNTP
	{

	public:

		DeviceNTP(ESPDevice* espDevice);
		~DeviceNTP();

		void											load(JsonObject& jsonObject);

		char*											getHost();
		int												getPort();

		int												getUtcTimeOffsetInSecond();
		void											setUtcTimeOffsetInSecond(String json);

		int												getUpdateIntervalInMilliSecond();
		void											setUpdateIntervalInMilliSecond(String json);

		/**
		* Starts the underlying UDP client with the default local port
		*/
		bool begin();

		/**
		* This should be called in the main loop of your application. By default an update from the NTP Server is only
		* made every 60 seconds. This can be configured in the DeviceNTP constructor.
		*
		* @return true on success, false on failure
		*/
		bool update();

		/**
		* This will force the update from the NTP Server.
		*
		* @return true on success, false on failure
		*/
		bool forceUpdate();

		int getDay();
		int getHours();
		int getMinutes();
		int getSeconds();

		/**
		* @return time formatted like `hh:mm:ss`
		*/
		String getFormattedTimeOld();

		String getFormattedTime();

		/**
		* @return time in seconds since Jan. 1, 1970
		*/
		unsigned long getEpochTime();
		unsigned long getEpochTimeUTC();

		/**
		* Stops the underlying UDP client
		*/
		void end();

		DeviceNTP& setUpdateCallback(DEVICE_NTP_SET_UPDATE_CALLBACK_SIGNATURE callback);

		static void createDeviceNTP(DeviceNTP* (&deviceNTP), ESPDevice* espDevice)
		{
			deviceNTP = new DeviceNTP(espDevice);
		}

	private:

		ESPDevice * _espDevice;

		char*											_host;
		int												_port;
		int												_utcTimeOffsetInSecond;
		int												_updateIntervalInMilliSecond;

		UDP*          									_udp;
		bool          									_udpSetup = false;

		unsigned long 									_currentEpoc = 0;      // In s
		unsigned long 									_lastUpdate = 0;      // In ms

		byte          									_packetBuffer[NTP_PACKET_SIZE];

		void          									sendNTPPacket();

		DEVICE_NTP_SET_UPDATE_CALLBACK_SIGNATURE		_updateCallback;

		bool 											_initialized = false;
	};
}

#endif