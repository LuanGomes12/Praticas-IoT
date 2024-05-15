## Wi-Fi Scan
**Descrição:** Verificar todas as redes Wi-Fi disponíveis no ambiente utilizando o esp32.

**Passo 1)** Para selecionar o exemplo vá em Arquivo → Exemplos → WiFi → WiFiScan
 
**Passo 2)** Conecte o NodeMCU ao seu computador utilizando um cabo de transferência de dados

**Passo 3)** Verificar o código cliando *Verify*, para compilar o script, e depois para baixar o código compilado na placa esp32 clique em "*Upload*"

❗ **OBS: em algumas placas esp32 tem o problema de gravação do código, apresentado o erro "*exit status 2*" no arduino, para solucionar isso, enquanto o programa estiver
sendo baixado no esp32 segure o botão de **BOOT/FLASH** do micro até que o upload termine por completo**

**Passo 4)** Abra o terminal serial e veja as redes Wi-Fi disponíveis, caso não apareça pressione **RESET** no esp32, lembre-se de configurar a taxa de transmissão de dados (*Baud rate*) do terminal serial, de maneira semelhante a utilizada no código 

## Wi-Fi Access Point
**Descrição:** criar uma rede Wi-Fi utilizando o esp32.

**Passo 1)** Com o ambiente já cofigurado, Vá em Arquivo → Exemplos → WiFi → WiFiAccessPoint

**Passo 2)** Altere os campos *SSID* e *PASSWORD* no código (crie a sua rede Wi-Fi)

**Passo 3)** Conecte o NodeMCU ao seu computador utilizando um cabo de transferência de dados

**Passo 4)** Verificar o código cliando "Verify" e depois fazer o upload no esp32 clicando em "Upload" (a **OBS** mostrada no exemplo anterior continua válida)

**Passo 5)** Verifique a rede Wi-Fi criada e acesse-a utilizando algum dispositivo que tenha acesso a rede Wi-Fi