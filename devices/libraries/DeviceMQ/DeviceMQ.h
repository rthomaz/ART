#ifndef DeviceMQ_h
#define DeviceMQ_h

#include "functional"
#include "vector"
#include "../ArduinoJson/ArduinoJson.h"
#include "RemoteDebug.h"
#include "PubSubClient.h"

#define DEVICE_MQ_GET_BY_KEY_TOPIC_PUB   						"DeviceMQ/GetAllByKeyIoT" 
#define DEVICE_MQ_GET_BY_KEY_COMPLETED_TOPIC_SUB				"DeviceMQ/GetAllByKeyCompletedIoT"

namespace ART
{
	class ESPDevice;

	class DeviceMQ
	{

	public:

		DeviceMQ(ESPDevice* espDevice);
		~DeviceMQ();

		void														load(JsonObject& jsonObject);

		void														loop();

		char*														getHost() const;
		int															getPort();
		char*														getUser() const;
		char*														getPassword() const;
		char*														getClientId() const;
		char*														getDeviceTopic() const;

		void														begin();

		bool														autoConnect();

		bool														connected();

		void														getByKeyPub();
		void														getByKeySub(const char* json);

		void														publishInApplication(const char* topic, const char* payload);

		void														subscribeDeviceInApplication(const char* topic);
		void														subscribeDevice(const char* topic);

		void														unSubscribeDeviceInApplication(const char* topic);
		void														unSubscribeDevice(const char* topic);

		template<typename Function>
		void														addSubscribeDeviceCallback(Function && fn)
		{
			_subscribeDeviceCallbacks.push_back(std::forward<Function>(fn));
		}

		template<typename Function>
		void														addSubscribeDeviceInApplicationCallback(Function && fn)
		{
			_subscribeDeviceInApplicationCallbacks.push_back(std::forward<Function>(fn));
		}

		template<typename Function>
		void														addUnSubscribeDeviceCallback(Function && fn)
		{
			_unSubscribeDeviceCallbacks.push_back(std::forward<Function>(fn));
		}

		template<typename Function>
		void														addUnSubscribeDeviceInApplicationCallback(Function && fn)
		{
			_unSubscribeDeviceInApplicationCallbacks.push_back(std::forward<Function>(fn));
		}

		template<typename Function>
		void														addSubscriptionCallback(Function && fn)
		{
			_subscriptionCallbacks.push_back(std::forward<Function>(fn));
		}

	private:

		ESPDevice *													_espDevice;

		char*														_host;
		int															_port;
		char*														_user;
		char*														_password;
		char*														_clientId;
		char*														_deviceTopic;

		bool														_loaded;

		WiFiClient	 												_espClient;
		PubSubClient* 												_mqqt;

		String 														getApplicationRoutingKey(const char* topic);
		String 														getDeviceRoutingKey(const char* topic);
		char*														getTopicKey(const char* routingKey);

		typedef std::function<void()>								subscribeSignature;
		typedef std::function<bool(const char*, const char*)>		subscriptionSignature;

		void														onMQQTCallback(char* topic, uint8_t* payload, unsigned int length);

		std::vector<subscribeSignature>								_subscribeDeviceCallbacks;
		std::vector<subscribeSignature>								_subscribeDeviceInApplicationCallbacks;

		std::vector<subscribeSignature>								_unSubscribeDeviceCallbacks;
		std::vector<subscribeSignature>								_unSubscribeDeviceInApplicationCallbacks;

		std::vector<subscriptionSignature>							_subscriptionCallbacks;

		void														onDeviceInApplicationInsert();
		void														onDeviceInApplicationRemove();

		void														onDeviceMQSubscribeDeviceInApplication();
		void														onDeviceMQUnSubscribeDeviceInApplication();
	};
}

#endif