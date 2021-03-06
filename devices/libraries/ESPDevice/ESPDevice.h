#ifndef ESPDevice_h
#define ESPDevice_h

#include "DeviceTypeEnum.h"
#include "DeviceInApplication.h"
#include "DeviceSerial.h"
#include "DeviceDebug.h"
#include "DeviceWiFi.h"
#include "DeviceMQ.h"
#include "DeviceNTP.h"
#include "DeviceBinary.h"
#include "DeviceBuzzer.h"
#include "DeviceSensor.h"
#include "DeviceDisplay.h"

#include "functional"
#include "vector"
#include "Arduino.h"
#include "../ArduinoJson/ArduinoJson.h"
#include "ESP8266HTTPClient.h"

#define ESP_DEVICE_UPDATE_PIN_TOPIC_SUB "ESPDevice/UpdatePinIoT"
#define ESP_DEVICE_SET_LABEL_TOPIC_SUB "ESPDevice/SetLabelIoT"

namespace ART
{
	class ESPDevice
	{
	public:

		ESPDevice(const char* webApiHost, uint16_t webApiPort, const char* webApiUri = "/");
		~ESPDevice();

		void								begin();
		void								loop();

		bool								loaded();

		DeviceTypeEnum						getDeviceTypeId();
		char *								getDeviceId() const;
		char *								getDeviceDatasheetId() const;

		int									getChipId();
		int									getFlashChipId();
		long								getChipSize();

		char *								getLabel() const;
		
		char *								getWebApiHost() const;
		uint16_t							getWebApiPort();
		char * 								getWebApiUri() const;

		DeviceInApplication*				getDeviceInApplication();		
		DeviceDebug*						getDeviceDebug();
		DeviceWiFi*							getDeviceWiFi();
		DeviceMQ*							getDeviceMQ();
		DeviceNTP*							getDeviceNTP();
		DeviceBinary*						getDeviceBinary();
		DeviceBuzzer*						getDeviceBuzzer();		
		DeviceDisplay*						getDeviceDisplay();
		DeviceSensor*						getDeviceSensor();
		DeviceSerial*						getDeviceSerial();

		bool								hasDeviceSensor();
		bool								hasDeviceSerial();
		bool								hasDeviceWiFi();
		bool								hasDeviceNTP();
		bool								hasDeviceMQ();
		bool								hasDeviceDebug();
		bool								hasDeviceDisplay();
		bool								hasDeviceBinary();

		char*								getDeviceKeyAsJson();		

	private:

		DeviceTypeEnum						_deviceTypeId;
		char *								_deviceId;
		char *								_deviceDatasheetId;

		int									_chipId;
		int									_flashChipId;
		long								_chipSize;

		char *								_label;

		bool 								_hasDeviceSerial;
		bool 								_hasDeviceSensor;
		bool 								_hasDeviceWiFi;
		bool 								_hasDeviceNTP;
		bool 								_hasDeviceMQ;
		bool 								_hasDeviceDebug;
		bool 								_hasDeviceDisplay;
		bool 								_hasDeviceBinary;

		char *								_webApiHost;
		uint16_t							_webApiPort;
		char * 								_webApiUri;

		DeviceInApplication*				_deviceInApplication;
		DeviceSerial*						_deviceSerial;
		DeviceDebug*						_deviceDebug;
		DeviceWiFi*							_deviceWiFi;
		DeviceMQ*							_deviceMQ;
		DeviceNTP*							_deviceNTP;
		DeviceBinary*						_deviceBinary;
		DeviceBuzzer*						_deviceBuzzer;
		DeviceSensor*						_deviceSensor;
		DeviceDisplay*						_deviceDisplay;

		void								autoLoad();
		void								load(String json);
		bool 								_loaded = false;

		void								setLabel(const char* json);

		void								onDeviceMQSubscribeDevice();
		void								onDeviceMQUnSubscribeDevice();
		void								onDeviceMQSubscribeDeviceInApplication();		
		void								onDeviceMQUnSubscribeDeviceInApplication();
		bool								onDeviceMQSubscription(const char* topicKey, const char* json);
	};
}

#endif