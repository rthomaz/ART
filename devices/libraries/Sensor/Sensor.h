#ifndef Sensor_h
#define Sensor_h

#include "Arduino.h"
#include "ArduinoJson.h"
#include "vector"
#include "OneWire.h"
#include "DallasTemperature.h"

#include "SensorDatasheet.h"
#include "SensorTempDSFamily.h"
#include "SensorUnitMeasurementScale.h"
#include "SensorTrigger.h"
#include "PositionEnum.h"

#define SENSOR_SET_LABEL_TOPIC_SUB "Sensor/SetLabelIoT"

namespace ART
{
	class SensorInDevice;	

	class Sensor
	{

	public:
		Sensor(SensorInDevice* sensorInDevice, JsonObject& jsonObject);
		~Sensor();

		static void							create(Sensor* (&sensor), SensorInDevice* sensorInDevice, JsonObject& jsonObject);

		char*								getSensorId() const;
		SensorTypeEnum						getSensorTypeId();
		SensorDatasheetEnum					getSensorDatasheetId();

		const uint8_t*		 				getDeviceAddress();

		char*								getFamily() const;
		bool								getValidFamily();

		char* 								getLabel() const;
		void 								setLabel(char* value);	

		bool 								getConnected();
		void 								setConnected(bool value);

		float 								getValue();
		void 								setValue(float value);

		bool 								hasAlarm();
		bool 								hasAlarmBuzzer();		

		void								insertTrigger(JsonObject& root);
		void								deleteTrigger(char* sensorTriggerId);

		SensorTempDSFamily *				getSensorTempDSFamily();
		SensorUnitMeasurementScale *		getSensorUnitMeasurementScale();
		SensorTrigger *						getSensorTriggers();

	private:

		SensorInDevice *					_sensorInDevice;
		SensorDatasheet *					_sensorDatasheet;

		SensorTempDSFamily *				_sensorTempDSFamily;
		SensorUnitMeasurementScale *		_sensorUnitMeasurementScale;

		char* 								_sensorId;
		SensorTypeEnum						_sensorTypeId;
		SensorDatasheetEnum					_sensorDatasheetId;

		std::vector<uint8_t> 				_deviceAddress;

		char* 								_family;
		bool 								_validFamily;

		char* 								_label;	

		std::vector<SensorTrigger> 			_sensorTriggers;

		bool 								_connected;

		float 								_value;

		long 								_epochTimeUtc;	

		void								onDeviceMQSubscribeDeviceInApplication();
		void								onDeviceMQUnSubscribeDeviceInApplication();
		void								onDeviceMQSubscription(char* topicKey, char* json);

	};
}

#endif