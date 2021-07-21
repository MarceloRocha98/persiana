#include <ESP8266WiFi.h>
#include <PubSubClient.h> // tem na ide (2.6)
#include <ArduinoJson.h> //arduino json (5.13.2)
#include <DNSServer.h> // baixar do git -> sketch ->incluir biblioteca -> adicionar bibioteca .zip
#include <ESP8266WebServer.h> // do git -> sketch ->incluir biblioteca -> adicionar bibioteca .zip
#include <WiFiManager.h> // do git -> sketch ->incluir biblioteca -> adicionar bibioteca .zip

#include <Ticker.h>
Ticker blinker;

#include <SimplyAtomic.h>

const String ORG = "nyvrst";
const String DEVICE_TYPE = "ESP32";
const String DEVICE_ID = "001";
#define DEVICE_TOKEN "e@KaNKbP_e8eGuc@Sn"

//

#include "ponte_h.h"
#include "ldr.h"
#include "motor.h"


ponte_h ponte_h;
ldr ldr;
motor motor;

//da maq estados
#include "definicoes_sistema.h"
volatile int codigoEvento = NENHUM_EVENTO;
volatile int eventoInterno = NENHUM_EVENTO;
volatile int estado = ESPERA;
volatile int codigoAcao=NENHUMA_ACAO;
volatile int acao_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
volatile int proximo_estado_matrizTransicaoEstados[NUM_ESTADOS][NUM_EVENTOS];
volatile int porcentual = 0;
volatile int horario1 = 0;
volatile int horario2 = 0;
volatile int horario_atual = 0;
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
void executarAcao(int codigo_Acao,int porcentual)
{
    Serial.print(porcentual);
    
   
    switch(codigo_Acao)
    {
    case AZERO:
      // abre_persiana(true);
      Serial.println("Acao 0");
      //ponte_h.horario();
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);


      break;
    case A1:
      Serial.println("Acao 1");
      // fecha_persiana(true);
      //ponte_h.ant_horario();
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      break;
    case A2:
      Serial.println("Acao 2");
      // abre_persiana_toda(true);
      //ponte_h.horario();
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    
    

      break;
    case A3:
      Serial.println("Acao 3");
      // fecha_persiana_toda(true);
     // ponte_h.ant_horario();
      digitalWrite(ENA, HIGH);
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);

      break;
    } // switch
  //  codigoEvento = NENHUM_EVENTO;

 

    // codigoAcao = NENHUMA_ACAO;

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
  acao_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S02] = AZERO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S03] = OPERACAO_AUTOMATICA;
  acao_matrizTransicaoEstados[OPERACAO_AUTOMATICA][S03] = A1;
  
  
  
  
  proximo_estado_matrizTransicaoEstados[ESPERA][S10] = OPERACAO_MANUAL;
  acao_matrizTransicaoEstados[ESPERA][S10] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_MANUAL][S11] = ESPERA;
  acao_matrizTransicaoEstados[OPERACAO_MANUAL][S11] = NENHUMA_ACAO;
  
  proximo_estado_matrizTransicaoEstados[OPERACAO_MANUAL][S12] = OPERACAO_MANUAL;
  acao_matrizTransicaoEstados[OPERACAO_MANUAL][S12] = AZERO;
  
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

void IRAM_ATTR check_acao(void)
{

    if(codigoEvento!=NENHUM_EVENTO)
      estado = obterProximoEstado(estado, codigoEvento);
    

    if(estado==OPERACAO_AUTOMATICA)
    {
      // codigo pra operacao automatica que gera codigo evento pra abrir ou fechar
      int val = ldr.obtem_luminosidade(); //leitura do LDR, A0 pino
      Serial.println(String(val));
    
      if(val>528) //ALTA LUZ->FECHAMENTO
      {
        codigoEvento = S03; //S32
      }else{ //BAIXA LUZ->ABERTURA
        codigoEvento = S02; //S31
      }
    }

    else if(estado==OPERACAO_HORARIOS)
    {
    // codigo operacao manual que gera codigo_evento pra abrir ou fechar
      if(horario_atual<horario1) // fechamento se for antes do horario programado
      {
        codigoEvento = S32;
      }
      else if(horario_atual>=horario1) // abertura se esta no horario programado
      {
        codigoEvento = S31;
      }
      else if(horario_atual>=horario2) // fechamento se passou do horario para fechar
      {
        codigoEvento = S32;
      }
    }

    if(codigoEvento!=NENHUM_EVENTO)
         codigoAcao = obterAcao(estado, codigoEvento);

    if (codigoAcao != NENHUMA_ACAO && codigoEvento!=NENHUM_EVENTO && (estado==OPERACAO_AUTOMATICA or estado==OPERACAO_HORARIOS))
         executarAcao(codigoAcao,porcentual);
    
  
  

   timer1_write(500000); //500000 us =0.5s
  
  
} 


void setup() {
  
  //
  ldr.setup(A0);
  //
  motor.setup(ENA);
  ponte_h.setup(IN1,IN2);
  ponte_h.para();
 //////

  Serial.begin(115200);
  iniciaSistema();
  WiFiManager wifiManager;
  wifiManager.setAPCallback(configModeCallback);
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //wifiManager.resetSettings();
  wifiManager.autoConnect("Persiana"); // (par1,par2) par1=Nome, par2=senha do ponto de acesso

  connectMQTTServer();
  //////
 timer1_attachInterrupt(check_acao); //Use attach_ms if you need time in
 timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
 timer1_write(500000); //500000 us =0.5s

  //////
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
  ATOMIC() {
  // código com interrupções bloqueadas (operações atômicas consecutivas não irão ser interrompidas)

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
    porcentual=doc["volume"];
    codigoEvento=doc["codigo_evento"];
    
    if(codigoEvento==S30) //horarios programados com sucesso
    {
      horario1 = doc["abertura"];
      horario2 = doc["fechamento"];
      horario_atual = doc["hora_atual"];
    }

    // Serial.print(" Evento: ");
    // Serial.print(String(codigoEvento));

    codigoAcao = obterAcao(estado, codigoEvento);
    estado = obterProximoEstado(estado, codigoEvento);
    executarAcao(codigoAcao,porcentual);
    Serial.print("Estado: ");
    Serial.print(String(estado));


 //////////
  }
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
