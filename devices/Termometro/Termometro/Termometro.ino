#include "Arduino.h"
#include "DebugManager.h"
#include "TemperatureSensorManager.h"
#include "NTPManager.h"
#include "DisplayManager.h"
#include "WiFiManager.h"
#include "DisplayWiFiManager.h"
#include "PubSubClient.h"
#include "WiFiClient.h"
#include "ArduinoJson.h"

//defines - mapeamento de pinos do NodeMCU
#define D0    16
#define D1    5
#define D2    4
#define D3    0
#define D4    2
#define D5    14
#define D6    12
#define D7    13
#define D8    15
#define D9    3
#define D10   1

#define ID_MQTT  "294700e3-b9a7-e711-9bef-707781d470bc" // HardwareBaseId

#define TOPIC_SUB_SET_RESOLUTION "DSFamilyTempSensor.SetResolution"
#define TOPIC_SUB_SET_HIGH_ALARM "DSFamilyTempSensor.SetHighAlarm"
#define TOPIC_SUB_SET_LOW_ALARM "DSFamilyTempSensor.SetLowAlarm"

#define TOPICO_PUBLISH   "ARTPUBTEMP"    //tópico MQTT de envio de informações para Broker

#define MESSAGE_INTERVAL 4000
uint64_t messageTimestamp = 0;

#define READTEMP_INTERVAL 2000
uint64_t readTempTimestamp = 0;

DebugManager debugManager(D6);
NTPManager ntpManager(debugManager);
DisplayManager displayManager(debugManager);
WiFiManager wifiManager(D5, debugManager);
DisplayWiFiManager displayWiFiManager(displayManager, wifiManager, debugManager);
TemperatureSensorManager temperatureSensorManager(debugManager, ntpManager);

//const char* BROKER_MQTT = "broker.hivemq.com"; //URL do broker MQTT que se deseja utilizar
const char* BROKER_MQTT = "file-server.rthomaz.local"; //URL do broker MQTT que se deseja utilizar
int BROKER_PORT = 1883; // Porta do Broker MQTT

WiFiClient espClient;
PubSubClient MQTT(espClient);

void setup() {
		
	Serial.begin(9600);

  // Buzzer
  pinMode(D6,OUTPUT);

  pinMode(D4, INPUT);
  pinMode(D5, INPUT);  

	debugManager.update();

	displayManager.begin();

	temperatureSensorManager.begin();

	if (debugManager.isDebug()) Serial.println("Iniciando...");

	// text display tests
	displayManager.display.clearDisplay();
	displayManager.display.setTextSize(1);
	displayManager.display.setTextColor(WHITE);
	displayManager.display.setCursor(0, 0);	
	displayManager.display.display();

  //TODO: Gambeta, no displayWiFiManager.begin(); está comentado o código que deveria funcionar no lugar destes handlers abaixo
  displayWiFiManager.begin();	
	wifiManager.setStartConfigPortalCallback(handleStartConfigPortalCallback);
  wifiManager.setCaptivePortalCallback(handleCaptivePortalCallback);
  wifiManager.setSuccessConfigPortalCallback(handleSuccessConfigPortalCallback);    
  wifiManager.setFailedConfigPortalCallback(handleFailedConfigPortalCallback);    
  wifiManager.setConnectingConfigPortalCallback(handleConnectingConfigPortalCallback); 
  
  wifiManager.autoConnect();
  
  initMQTT();

	ntpManager.begin();
}

//TODO: Gambeta, no displayWiFiManager.begin(); está comentado o código que deveria funcionar no lugar destes handlers abaixo
void handleStartConfigPortalCallback () {  displayWiFiManager.startConfigPortalCallback(); }
void handleCaptivePortalCallback (String ip) {  displayWiFiManager.captivePortalCallback(ip); }
void handleSuccessConfigPortalCallback () {  displayWiFiManager.successConfigPortalCallback(); }
void handleFailedConfigPortalCallback (int connectionResult) {  displayWiFiManager.failedConfigPortalCallback(connectionResult); }
void handleConnectingConfigPortalCallback () {  displayWiFiManager.connectingConfigPortalCallback(); }

void initMQTT() 
{
    MQTT.setServer(BROKER_MQTT, BROKER_PORT);   //informa qual broker e porta deve ser conectado
    MQTT.setCallback(mqtt_callback);            //atribui função de callback (função chamada quando qualquer informação de um dos tópicos subescritos chega)
}
 
void mqtt_callback(char* topic, byte* payload, unsigned int length) 
{
    printMQTTReceived(86, 0);
    
    String json;
    
    //obtem a string do payload recebido
    for(int i = 0; i < length; i++) 
    {
       char c = (char)payload[i];
       json += c;
    }

    Serial.print("payload: ");
    Serial.println(json);

    StaticJsonBuffer<300> jsonBuffer;
    
    JsonObject& root = jsonBuffer.parseObject(json);
  
    if (!root.success()) {
      Serial.print("parse payload failed: ");
      Serial.println(json);
      return;
    }

    String payloadTopic = root["topic"];
    String payloadContract = root["contract"];

    Serial.print("payloadTopic: ");
    Serial.println(payloadTopic);

    Serial.print("payloadContract: ");
    Serial.println(payloadContract);

    if(payloadTopic == String(TOPIC_SUB_SET_RESOLUTION)){
      temperatureSensorManager.setResolution(payloadContract);
    }
    if(payloadTopic == String(TOPIC_SUB_SET_HIGH_ALARM)){
      temperatureSensorManager.setHighAlarm(payloadContract);
    }
    if(payloadTopic == String(TOPIC_SUB_SET_LOW_ALARM)){
      temperatureSensorManager.setLowAlarm(payloadContract);
    }
}
 
void reconnectMQTT() 
{
    if (wifiManager.isConnected() && !MQTT.connected()) 
    {
        Serial.print("* Tentando se conectar ao Broker MQTT: ");
        Serial.println(BROKER_MQTT);
        if (MQTT.connect(ID_MQTT, "test", "test")) 
        {
            Serial.println("Conectado com sucesso ao broker MQTT!");

            MQTT.subscribe(TOPIC_SUB_SET_RESOLUTION); 
            MQTT.subscribe(TOPIC_SUB_SET_HIGH_ALARM); 
            MQTT.subscribe(TOPIC_SUB_SET_LOW_ALARM);         
        } 
        else 
        {
            Serial.println("Falha ao reconectar no broker.");
            Serial.println("Havera nova tentatica de conexao em 2s");
            delay(2000);
        }
    }
}

void VerificaConexoesWiFIEMQTT(void)
{    
     reconnectMQTT(); //se não há conexão com o Broker, a conexão é refeita
     wifiManager.autoConnect(); //se não há conexão com o WiFI, a conexão é refeita
}

void printDataDisplay(){    
  
    // Formatted Time   
    
    displayManager.display.setFont();
    displayManager.display.setTextSize(2);
    displayManager.display.setTextColor(WHITE);
    displayManager.display.setCursor(0, 0);       
        
    String formattedTime = ntpManager.getFormattedTime();
    displayManager.display.println(formattedTime);

    // Wifi
    int quality = wifiManager.getQuality();
    int barSignal = wifiManager.convertQualitytToBarsSignal(quality);
    if(wifiManager.isConnected())
      displayWiFiManager.printSignal(106, 1, 4, 2, barSignal);
    else
      displayWiFiManager.printNoSignal(106, 0, 4, 2);
    
    // Sensor
    
    displayManager.display.setFont();
    displayManager.display.setTextSize(2);
    displayManager.display.setTextColor(WHITE);
    displayManager.display.setCursor(0, 16);       
    
    if(sizeof(temperatureSensorManager.Sensors)/sizeof(int) > 0){
      
      displayManager.display.print(temperatureSensorManager.Sensors[0].tempCelsius);
      displayManager.display.println(" C");
      
      //displayManager.display.print(temperatureSensorManager.Sensors[0].tempFahrenheit);
      //displayManager.display.println(" F");
    }    

    // MQTT
    if(MQTT.connected()){
      printMQTTConnected(74, 9);  
    }   
}

void printMQTTConnected(int x, int y){
  
  displayManager.display.setTextSize(1);
  displayManager.display.setTextColor(WHITE, BLACK);  

  displayManager.display.setCursor(x, y);

  displayManager.display.println("ART");
}

void printMQTTSent(int x, int y) {  
    
  displayManager.display.setTextSize(1);
  displayManager.display.setTextColor(WHITE, BLACK);

  displayManager.display.setCursor(x, y);
  displayManager.display.write(24); // ↑
}

void printMQTTReceived(int x, int y) {  
    
  displayManager.display.setTextSize(1);
  displayManager.display.setTextColor(WHITE, BLACK);

  displayManager.display.setCursor(x, y);
  displayManager.display.write(25); // ↓
}

void loop() {	

  debugManager.update();    
  
  //garante funcionamento das conexões WiFi e ao broker MQTT
  VerificaConexoesWiFIEMQTT(); 

  displayManager.display.clearDisplay();

  uint64_t now = millis();   

  if(now - readTempTimestamp > READTEMP_INTERVAL) {
    readTempTimestamp = now;
    temperatureSensorManager.refresh();
  }

  if(now - messageTimestamp > MESSAGE_INTERVAL) {
    messageTimestamp = now;
    printMQTTSent(74, 0);
    char *sensorsJson = temperatureSensorManager.convertSensorsToJson();
    Serial.print("enviando para o servidor => ");
    Serial.println(sensorsJson);
    MQTT.publish(TOPICO_PUBLISH, sensorsJson);      
  }      

  printDataDisplay(); 

  displayManager.display.display();

  
  // Buzzer
  //tone(D7,900,300); //aqui sai o som   
  /*   
   o número D7 indica que o pino positivo do buzzer está na porta 10   
   o número 300 é a frequência que será tocado   
   o número 300 é a duração do som   
  */    
  
  //keep-alive da comunicação com broker MQTT
  MQTT.loop();
}
