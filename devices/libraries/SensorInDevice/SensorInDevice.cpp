#include "SensorInDevice.h"
#include "DeviceSensors.h"
#include "ESPDevice.h"
#include "DeviceDebug.h"

namespace ART
{
	SensorInDevice::SensorInDevice(DeviceSensors* deviceSensors, JsonObject& jsonObject)
	{
		_deviceSensors = deviceSensors;
		DeviceDebug* deviceDebug = _deviceSensors->getESPDevice()->getDeviceDebug();

		deviceDebug->printlnLevel(DeviceDebug::DEBUG, "SensorInDevice", "constructor", "begin");
		
		_ordination = jsonObject["ordination"];

		Sensor::create(_sensor, this, jsonObject["sensor"]);

		deviceDebug->printlnLevel(DeviceDebug::DEBUG, "SensorInDevice", "constructor", "end");
	}

	SensorInDevice::~SensorInDevice()
	{
		_deviceSensors->getESPDevice()->getDeviceDebug()->printlnLevel(DeviceDebug::DEBUG, "SensorInDevice", "destructor");
	}

	SensorInDevice SensorInDevice::create(DeviceSensors * deviceSensors, JsonObject & jsonObject)
	{
		return SensorInDevice(deviceSensors, jsonObject);
	}

	void SensorInDevice::begin()
	{
		_deviceSensors->getESPDevice()->getDeviceMQ()->addSubscribeDeviceInApplicationCallback([=]() { return onDeviceMQSubscribeDeviceInApplication(); });
		_deviceSensors->getESPDevice()->getDeviceMQ()->addUnSubscribeDeviceInApplicationCallback([=]() { return onDeviceMQUnSubscribeDeviceInApplication(); });
		//_deviceSensors->getESPDevice()->getDeviceMQ()->addSubscriptionCallback([=](char* topicKey, char* json) { return onDeviceMQSubscription(topicKey, json); });
	}

	Sensor * SensorInDevice::getSensor()
	{
		return _sensor;
	}

	DeviceSensors * SensorInDevice::getDeviceSensors()
	{
		return _deviceSensors;
	}

	short SensorInDevice::getOrdination()
	{
		return _ordination;
	}

	void SensorInDevice::setOrdination(short value)
	{
		_ordination = value;
	}

	bool SensorInDevice::operator<(const SensorInDevice & val) const
	{
		return _ordination < val._ordination;
	}

	void SensorInDevice::onDeviceMQSubscribeDeviceInApplication()
	{

	}

	void SensorInDevice::onDeviceMQUnSubscribeDeviceInApplication()
	{

	}

	void SensorInDevice::onDeviceMQSubscription(char* topicKey, char* json)
	{

	}
}