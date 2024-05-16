// Bibliotecas 
#include <WiFi.h>

// Dados da Rede
const char* ssid     = "WifiLuan";
const char* password = "123456789";

// Seta Porta 80 para o Servidor Web
WiFiServer server(80);

// Variável que guarda requisição HTTP
String header;

// Varáveis Auxiliares: Guarda Estado de Saída
String outputD2State = "off";
String outputD4State = "off";
String outputD5State = "off";
String outputD18State = "off";

// Mapeamento de Pinos do Node a serem utilizados
const int outputD2 = 2;
const int outputD4 = 4;
const int outputD5 = 5;
const int outputD18 = 18;

void setup() {
  Serial.begin(115200);
  // Inicializa variáveis de saída como saídas no Node
  pinMode(outputD2, OUTPUT);
  pinMode(outputD4, OUTPUT);
  pinMode(outputD5, OUTPUT);
  pinMode(outputD18, OUTPUT);
  // Seta saídas como LOW
  digitalWrite(outputD2, LOW);
  digitalWrite(outputD4, LOW);
  digitalWrite(outputD5, LOW);
  digitalWrite(outputD18, LOW);

  // Conecta ao Wi-Fi com SSID e Senha
  Serial.print("Conectando-se a ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print do endereço de IP local e inicializa o Servidor Web
  Serial.println("");
  Serial.println("Wi-Fi conectado.");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

//Informações sobre o Servidor Web
void loop(){
  WiFiClient client = server.available();   // Listen for incoming clients

  if (client) {                             // Se um novo Cliente se conecta,
    Serial.println("Novo Cliente.");        // imprime uma mensagem no Serial
    String currentLine = "";                // cria uma String que guarda dados do Cliente ingressante
    while (client.connected()) {            // loop enquanto o Cliente está conectado
      if (client.available()) {             // se há bytes a serem lidos do cliente,
        char c = client.read();             // lê-se um byte e
        Serial.write(c);                    // o imprime no Serial
        header += c;
        if (c == '\n') {                    // se o byte é um caractere de nova linha
          // e se a linha atual está em branco, você terá duas novas linhas de caracteres em seguida.
          // fim da requisição Cliente HTTP, enviando a resposta:
          if (currentLine.length() == 0) {
            // headers HTTP sempre começar com um código de resposta (e.g. HTTP/1.1 200 OK)
            // e o tipo de conteúdo, assim o Cliente saberá o que está por vir. Depois, uma linha em branco:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
            // Liga/Desliga as Portas
            if (header.indexOf("GET /D2/on") >= 0) {
              Serial.println("Porta D2 on");
              outputD2State = "on";
              digitalWrite(outputD2, HIGH);
            } else if (header.indexOf("GET /D2/off") >= 0) {
              Serial.println("Porta D2 off");
              outputD2State = "off";
              digitalWrite(outputD2, LOW);


            } else if (header.indexOf("GET /D4/on") >= 0) {
              Serial.println("Porta D4 on");
              outputD4State = "on";
              digitalWrite(outputD4, HIGH);
            } else if (header.indexOf("GET /D4/off") >= 0) {
              Serial.println("Porta D4 off");
              outputD4State = "off";
              digitalWrite(outputD4, LOW);
            }
            
            else if (header.indexOf("GET /D5/on") >= 0) {
              Serial.println("Porta D5 on");
              outputD5State = "on";
              digitalWrite(outputD5, HIGH);
            } else if (header.indexOf("GET /D5/off") >= 0) {
              Serial.println("Porta D5 off");
              outputD5State = "off";
              digitalWrite(outputD5, LOW);
            }

            else if (header.indexOf("GET /D18/on") >= 0) {
              Serial.println("Porta D18 on");
              outputD18State = "on";
              digitalWrite(outputD18, HIGH);
            } else if (header.indexOf("GET /D18/off") >= 0) {
              Serial.println("Porta D18 off");
              outputD18State = "off";
              digitalWrite(outputD18, LOW);
            }
            
            // Mostra a página HTML
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            // CSS usado para o estilo dos botões de ON e OFF. Pode ser mudado para alterar o visual da página.
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #a018a0; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            // Título da Página Web
            client.println("<body><h1>Servidor WEB - ESP32</h1>");
            
            // Mostra os estados atuais e dos botões ON/OFF da Porta D2  
            client.println("<p>Estado - Porta D2 " + outputD2State + "</p>");
            // Se ooutput26Stat está off, mostra o botão ON.        
            if (outputD2State=="off") {
              client.println("<p><a href=\"/D2/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/D2/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
               
            // Mostra os estados atuais e dos botões ON/OFF da Porta D4  
            client.println("<p>Estado - Porta D4 " + outputD4State + "</p>");
            // Se output27State está off, mostra o botão ON.       
            if (outputD4State=="off") {
              client.println("<p><a href=\"/D4/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/D4/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // Mostra os estados atuais e dos botões ON/OFF da Porta D5  
            client.println("<p>Estado - Porta D5 " + outputD5State + "</p>");
            // Se output27State está off, mostra o botão ON.       
            if (outputD5State=="off") {
              client.println("<p><a href=\"/D5/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/D5/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");

            // Mostra os estados atuais e dos botões ON/OFF da Porta D18  
            client.println("<p>Estado - Porta D18 " + outputD18State + "</p>");
            // Se output27State está off, mostra o botão ON.       
            if (outputD18State=="off") {
              client.println("<p><a href=\"/D18/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/D18/off\"><button class=\"button button2\">OFF</button></a></p>");
            }
            client.println("</body></html>");
            
            // A resposta HTTP termina com outra linha em branco
            client.println();
            // Sai do loop
            break;
          } else { // se há uma nova linha, limpa a linha atual
            currentLine = "";
          }
        } else if (c != '\r') {  // se há retorno de qualquer coisa que não seja caractere,
          currentLine += c;      // adiciona-o ao fim da linha atual.
        }
      }
    }
    // Limpa a variável header
    header = "";
    // Termina conexão.
    client.stop();
    Serial.println("Cliente desconectado.");
    Serial.println("");
  }
}

// ***CRÉDITOS*** > Código baseado no original feito por Rui Santos, 
//em randomnerdtutorials.com
