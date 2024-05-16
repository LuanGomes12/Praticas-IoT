# Thing Speak
Descrição: Utilizar um sensor de temperatura concetado ao esp32 e enviar essas informações para um servidro online hospedado no thinkspeak

Passo1) Ferramentas → Gerenciador de bibliotecas → "'DHT sensor library' by Adafruit" (essa biblioteca inclui o Adafruit Unified Sensor)

OBS1: lembre de selecionar a placa correta, vá em Ferramentas → Placa → esp32 → ESP32 Dev Module

Passo2) Comente o código "#include <ESP8266WiFi.h>" e adicione a biblioteca "#include <WiFi.h>"

Passo3) Crie uma conta no site www.thingspeak.com e crie um novo canal, preenchendo as informações necessárias

Passo4) Ajuste o código modificando:
- Escreva seu Write API key do site ThingSpeak
- Substitua com o ssid e senha da rede Wifi
- Ao final do trecho "Serial.println("%. Send to Thingspeak.");" adcione um delay ("delay(1000);")
- Verifique a montagem do circuito

Passo5) Verificar o código cliando "Verify" e depois fazer o upload no esp32 clicando em "Upload"

OBS2: em algumas placas esp32 tem o problema de gravação do código, apresentado o erro "exit status 2" no arduino, para solucionar isso, enquanto o programa estiver
sendo baixado no esp32 segure o botão de BOOT/FLASH até que o upload termine por completo

Pressionado -> 0
SEm ser pressionado -> 1