#include <ESP8266WiFi.h>
#include <PubSubClient.h> // tem na ide (2.6)
#include <ArduinoJson.h> //arduino json (5.13.2)
#include <DNSServer.h> // baixar do git -> sketch ->incluir biblioteca -> adicionar bibioteca .zip
#include <ESP8266WebServer.h> // do git -> sketch ->incluir biblioteca -> adicionar bibioteca .zip
#include <WiFiManager.h> // do git -> sketch ->incluir biblioteca -> adicionar bibioteca .zip


const String ORG = "nyvrst";
const String DEVICE_TYPE = "ESP32";
const String DEVICE_ID = "001";
#define DEVICE_TOKEN "e@KaNKbP_e8eGuc@Sn"

//da maq estados
#include "definicoes_sistema.h"
int codigoEvento = NENHUM_EVENTO;
int eventoInterno = NENHUM_EVENTO;
int estado = ESPERA;
int codigoAcao;
int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
//

//////
int IN1 = D4;
int IN2 = D3;
int ENA=D2;

/////


const String CLIENT_ID = "d:" + ORG + ":" + DEVICE_TYPE + ":" + DEVICE_ID; //The MQTT client ID is in the format d:orgId:deviceType:deviceId.
const String MQTT_SERVER = ORG + ".messaging.internetofthings.ibmcloud.com";

#define COMMAND_TOPIC_1 "iot-2/cmd/comandoVoz/fmt/json" // formato de subscrição :iot-2/cmd/command_id/fmt/format_string, no caso  commandR1 é id o passado em msg.eventOrCommandType (id do tópico) e json é o formato
#define COMMAND_TOPIC_2 "iot-2/cmd/comandoManual/fmt/json"  
#define COMMAND_TOPIC_3 "iot-2/cmd/horarioProgramado/fmt/json"  
#define COMMAND_TOPIC_4 "iot-2/cmd/automatico/fmt/json"  

WiFiClient wifiClient;
PubSubClient client(MQTT_SERVER.c_str(), 1883, wifiClient);




//maq de estados
void executarAcao(int codigoAcao,int porcentual)
{
    Serial.println(porcentual);


    switch(codigoAcao)
    {
    case A0:
        // abre_persiana(true);
            Serial.println(" Acao: A0 ");
            Serial.println(codigoAcao);
             //Gira o Motor A no sentido horario
            digitalWrite(ENA, HIGH);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            delay(3000);
             //Para o motor A
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
            break;
    case A1:
        // fecha_persiana(true);
            Serial.println(" Acao: A1");
            Serial.println(codigoAcao);
             //Gira o Motor A no sentido anti-horario
          digitalWrite(ENA, HIGH);
          digitalWrite(IN1, LOW);
          digitalWrite(IN2, HIGH);
          delay(3000);
            //Para o motor A
          digitalWrite(IN1, HIGH);
          digitalWrite(IN2, HIGH);
        break;
    case A2:
        // abre_persiana_toda(true);
            Serial.println(" Acao: A2 ");
            Serial.println(codigoAcao);
                        Serial.println(" Acao: A0 ");
            Serial.println(codigoAcao);
             //Gira o Motor A no sentido horario
            digitalWrite(ENA, HIGH);
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, LOW);
            delay(3000);
             //Para o motor A
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
        break;
    case A3:
        // fecha_persiana_toda(true);
            Serial.println(" Acao: A3");
            Serial.println(codigoAcao);
             //Gira o Motor A no sentido anti-horario
            digitalWrite(ENA, HIGH);
            digitalWrite(IN1, LOW);
            digitalWrite(IN2, HIGH);
            delay(3000);
             //Para o motor A
            digitalWrite(IN1, HIGH);
            digitalWrite(IN2, HIGH);
        break;
    } // switch


} // executarAcao

void iniciaMaquinaEstados()
{
  int i;
  int j;

  for (i=0; i < NUM_ESTADOS; i++) {
    for (j=0; j < NUM_EVENTOS; j++) {
       acao_matrizTransicaoEstados[i][j] = NENHUMA_ACAO;
       proximo_estado_matrizTransicaoEstados[i][j] = i;
    }
  }
  proximo_estado_matrizTransicaoEstados[ESPERA][S00] = OPERACAO_AUTOMATICA;
  acao_matrizTransicaoEstados[ESPERA][S00] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S01] = ESPERA;
  acao_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S01] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S02] = OPERACAO_AUTOMATICA;
  acao_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S02] = A0;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S03] = OPERACAO_AUTOMATICA;
  acao_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S03] = A1;
  
  
  
  
  proximo_estado_matrizTransicaoEstados[ESPERA][S10] = OPERACAO_MANUAL;
  acao_matrizTransicaoEstados[ESPERA][S10] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_MANUAL][S11] = ESPERA;
  acao_matrizTransicaoEstados[OPERACAO_MANUAL][S11] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_MANUAL][S12] = OPERACAO_MANUAL;
  acao_matrizTransicaoEstados[OPERACAO_MANUAL][S12] = A0;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_MANUAL][S13] = OPERACAO_MANUAL;
  acao_matrizTransicaoEstados[OPERACAO_MANUAL][S13] = A1;
  
  
  
  
  proximo_estado_matrizTransicaoEstados[ESPERA][S20] = CONFIGURACAO_HORARIOS;
  acao_matrizTransicaoEstados[ESPERA][S20] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[CONFIGURACAO_HORARIOS][S21] = ESPERA;
  acao_matrizTransicaoEstados[CONFIGURACAO_HORARIOS][S21] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[CONFIGURACAO_HORARIOS][S22] = ESPERA;
  acao_matrizTransicaoEstados[CONFIGURACAO_HORARIOS][S22] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[CONFIGURACAO_HORARIOS][S30] = OPERACAO_HORARIOS;
  acao_matrizTransicaoEstados[CONFIGURACAO_HORARIOS][S30] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_HORARIOS][S31] = OPERACAO_HORARIOS;
  acao_matrizTransicaoEstados[OPERACAO_HORARIOS][S31] = A2;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_HORARIOS][S32] = OPERACAO_HORARIOS;
  acao_matrizTransicaoEstados[OPERACAO_HORARIOS][S32] = A3;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_HORARIOS][S33] = ESPERA;
  acao_matrizTransicaoEstados[OPERACAO_HORARIOS][S33] = A2;



} // initStateMachine

void iniciaSistema()
{
   iniciaMaquinaEstados();
} // initSystem


int obterAcao(int estado, int codigoEvento) {
  return acao_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao

int obterProximoEstado(int estado, int codigoEvento) {
  return proximo_estado_matrizTransicaoEstados[estado][codigoEvento];
} // obterAcao



void setup() {
  
  //////
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
 //////

  Serial.begin(115200);
  iniciaSistema();
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //wifiManager.resetSettings();
  wifiManager.autoConnect("Persiana"); // (par1,par2) par1=Nome, par2=senha do ponto de acesso

  connectMQTTServer();
}

void loop() {
  client.loop();
}

//Função responsável pela conexão ao servidor MQTT
void connectMQTTServer() {
  Serial.println("Conectando ao servidor MQTT...");

  if (client.connect(CLIENT_ID.c_str(), "use-token-auth", DEVICE_TOKEN)) {
     Serial.println("Conectado ao Broker MQTT...");
     client.setCallback(callback);

     client.subscribe(COMMAND_TOPIC_1); // se inscreve nos tópicos
     client.subscribe(COMMAND_TOPIC_2);
     client.subscribe(COMMAND_TOPIC_3);
     client.subscribe(COMMAND_TOPIC_4);

  } else {
     Serial.print("erro = ");
     Serial.println(client.state());
     connectMQTTServer();
  }
}

//void callback(char* topic, byte* payload, unsigned int length) {
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("topico ");
  Serial.println(topic);

  //StaticJsonBuffer<30> jsonBuffer;
  StaticJsonDocument<256> doc;
  //JsonObject root = jsonBuffer.parseObject(payload);
 // deserializeJson(doc, payload, length);
  deserializeJson(doc, (const byte*)payload, length);

auto error = deserializeJson(doc, payload);
if (error) {
    Serial.print(F("deserializeJson() failed with code "));
    Serial.println(error.c_str());
    return;
}



////////// loop - codigo aqui

//   int value = doc["on"];
//   int horario = doc["horario"];
    int porcentual=doc["volume"];
    codigoEvento=doc["codigo_evento"];
    Serial.print(" Evento: ");
    Serial.print(String(codigoEvento));

    codigoAcao = obterAcao(estado, codigoEvento);
    estado = obterProximoEstado(estado, codigoEvento);
    executarAcao(codigoAcao,porcentual);
    Serial.print("Estado: ");
    Serial.print(String(estado));

//   if ( (strcmp(topic, COMMAND_TOPIC_1) == 0) || ((strcmp(topic,COMMAND_TOPIC_2)==0) )  //1-topico de acionamento manual por voz
//   {                                                                                    //2-topico de acionamento manual pelo google home
//      //digitalWrite(pinTeste1, value);
//      int porcentual = doc["volume"];
//      Serial.println("Chegou acionamento voz"); 
//   } 

//   else if(strcmp(topic,COMMAND_TOPIC_3)==0) //topico de acionamento por horario pelo google home
//   {
//     // digitalWrite(pinTeste2, value);
//      Serial.println("Chegou acionamento por horario");
//   }
//   else if(strcmp(topic,COMMAND_TOPIC_4)==0) //topico de acionamento por automatico pelo google home
//   {
//     // digitalWrite(pinTeste2, value);
//      Serial.println("Chegou acionamento automatico");
//   }






 //////////
}

void configModeCallback( WiFiManager *myWiFiManager) {
  Serial.println("Entrou no modo de configuração");
  Serial.println(WiFi.softAPIP());
  Serial.println(myWiFiManager->getConfigPortalSSID());
}

void saveConfigCallback() {
  Serial.println("Configuração salva");
  Serial.println(WiFi.softAPIP());
}
