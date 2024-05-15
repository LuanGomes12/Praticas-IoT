#include <WiFi.h>

String apiKey = "0G79EXXPERXOW3RT"; // Chave de escrita do ThingSpeak
const char *ssid =  "WALDEMYR_WIFI"; // SSID da sua rede WiFi
const char *pass =  "waldemyr18";         // Senha da sua rede WiFi
const char* server = "api.thingspeak.com";
const int buttonpin = 4;             // Pino onde o botão está conectado

WiFiClient client;

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(buttonpin, INPUT_PULLUP);   // Configura o pino do botão como entrada com pull-up interno

  Serial.println("Conectando à rede WiFi...");
  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
}

void loop() {
  // Lê o estado do botão
  int buttonState = digitalRead(buttonpin);

  if (client.connect(server, 80)) {
    String postStr = apiKey;
    postStr += "&field1=";
    postStr += String(buttonState);
    postStr += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + apiKey + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(postStr.length());
    client.print("\n\n");
    client.print(postStr);

    Serial.print("Estado do botão: ");
    Serial.print(buttonState);
    Serial.println("%. Enviado para o ThingSpeak.");

    // Aguarde até que o cliente tenha enviado os dados
    delay(1000);
  } else {
    Serial.println("Falha ao conectar-se ao servidor ThingSpeak");
  }
  client.stop();

  Serial.println("Aguardando...");
  
  // O ThingSpeak requer um intervalo mínimo de 15 segundos entre atualizações, então definimos para 20 segundos
  delay(20000);
}

