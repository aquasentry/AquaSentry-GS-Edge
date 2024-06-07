#include <DHT.h>
#include <LiquidCrystal_I2C.h>
#include <RTClib.h> // Biblioteca para Relógio em Tempo Real
#include <Wire.h>   // Biblioteca para comunicação I2C
#include <EEPROM.h>

#define LOG_OPTION 1     // Opção para ativar a leitura do log
#define SERIAL_OPTION 0  // Opção de comunicação serial: 0 para desligado, 1 para ligado
#define UTC_OFFSET -3    // Ajuste de fuso horário para UTC-3

// Definindo pinos e tipo do sensor
#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal_I2C lcd(0x27, 16, 2); // Endereço de acesso: 0x27, 16 colunas, 2 linhas
RTC_DS1307 RTC;

// Definindo pino do LDR e identificador do dispositivo
const int ldrPin = A1;
const int potPin = A0;
#define ID_SIZE 16
char deviceID[ID_SIZE] = "AS1GS-001";

// Configurações da EEPROM
const int maxRecords = 100;
const int recordSize = 8; // Tamanho de cada registro em bytes (timestamp + dado)
int startAddress = 0;
int endAddress = maxRecords * recordSize;
int currentAddress = 0;

float batteryLevel = 100.0; // Nível inicial da bateria (em %)

// Função para escrever o ID na EEPROM
void writeIDToEEPROM(const char* id) {
  for (int i = 0; i < ID_SIZE; i++) {
    EEPROM.write(i, id[i]); // Escreve o ID na EEPROM a partir da posição 0
  }
}

// Função para ler o ID da EEPROM
void readIDFromEEPROM(char* id) {
  for (int i = 0; i < ID_SIZE; i++) {
    id[i] = EEPROM.read(i); // Lê o ID da EEPROM a partir da posição 0
  }
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.begin(16, 2);
  RTC.begin();    // Inicialização do Relógio em Tempo Real
  // RTC.adjust(DateTime(2024,5,6,08,15,00));  // Ajustar a data e hora apropriadas uma vez inicialmente, depois comentar
  EEPROM.begin();

  // Escreve o ID na EEPROM na primeira execução
  writeIDToEEPROM(deviceID);

  // Lê o ID da EEPROM
  readIDFromEEPROM(deviceID);

  lcd.init();   // Inicialização do LCD
  lcd.backlight();  // Ligando o backlight do LCD
  delay(1000);

  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Iniciando");
  lcd.setCursor(3,1);
  lcd.print("o sistema");
  delay(5000);
  lcd.clear();

  lcd.setCursor(6,0);
  lcd.print("AQUA");
  lcd.setCursor(5,1);
  lcd.print("SENTRY");
  delay(5000);
  lcd.clear();

  lcd.setCursor(2, 0);
  lcd.print("Dispositivo");
  lcd.setCursor(1,1);
  lcd.print("ID: ");
  lcd.setCursor(5,1);
  lcd.print(deviceID);
  delay(3000);
  lcd.clear();
}

void loop() {
  DateTime now = RTC.now();

  // Exibe data e hora no formato DD/MM/YYYY HH:MM:SS
  char buffer[20];
  snprintf(buffer, sizeof(buffer), "%02d/%02d/%04d %02d:%02d:%02d",
           now.day(), now.month(), now.year(), now.hour(), now.minute(), now.second());

  // Leitura do sensor de temperatura e umidade
  float temperature = dht.readTemperature();

  // Leitura do potenciômetro para simular o nível de oxigênio
  int oxygenLevelRaw = analogRead(potPin);
  float oxygenLevel = map(oxygenLevelRaw, 0, 1023, 0, 100); // Mapeia para 0-100%

  // Leitura do LDR para detectar luz solar
  int ldrValueRaw = analogRead(ldrPin);
  int ldrValue = map(ldrValueRaw, 0, 1023, 0, 100);
  bool isCharging = ldrValue >= 1; // Supondo que > 512 indica luz solar suficiente para carregar

  // Atualização do nível da bateria
  if (ldrValue >= 1 && ldrValue <= 9) {
    batteryLevel +=0.1; // Carregamento normal
  } else if (ldrValue > 30) {
    batteryLevel += 0.2; // Carregamento rápido
  } else {
    batteryLevel -= 0.05; // Descarga lenta quando não há luz solar
  }

  if (batteryLevel > 100) batteryLevel = 100; // Limite superior de 100%
  if (batteryLevel < 0) batteryLevel = 0; // Limite inferior de 0%

  // Verifica se as leituras são válidas
  if (isnan(temperature)) {
    Serial.println("Falha ao ler o sensor DHT!");
    return;
  }

  // Exibe os valores no display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("LUZ SOLAR: ");
  lcd.print(isCharging ? "SIM" : "NAO");

  lcd.setCursor(0, 1);
  lcd.print("BATERIA: ");
  lcd.print(batteryLevel);
  lcd.print("%");

  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(buffer); // Exibe data e hora
  lcd.setCursor(0, 1);
  lcd.print("TEMP: ");
  lcd.print(temperature);
  lcd.print((char)223);
  lcd.print("C");

  delay(5000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(buffer); // Exibe data e hora
  lcd.setCursor(0, 1);
  lcd.print("OXIGENIO: ");
  lcd.print(oxygenLevel);
  lcd.print("%");

  delay(5000);

  // Armazena os valores na EEPROM
  if (temperature < 20 || temperature > 25) {
    writeLogToEEPROM(buffer, temperature);
    Serial.println("Dados de temperatura armazenados na EEPROM.");
  }
  
  if (oxygenLevel < 95) {
    writeLogToEEPROM(buffer, oxygenLevel);
    Serial.println("Dados de oxigênio armazenados na EEPROM.");
  }
}

// Função para escrever os valores na EEPROM
void writeLogToEEPROM(const char* timestamp, float data) {
  int address = currentAddress;

  // Escrever o timestamp
  for (int i = 0; i < sizeof(timestamp); i++) {
    EEPROM.write(address++, timestamp[i]);
  }

  // Escrever o dado
  EEPROM.put(address, data);
  address += sizeof(data);

  // Atualiza o endereço para o próximo registro
  currentAddress += recordSize;
  if (currentAddress >= endAddress) {
    currentAddress = startAddress; // Volta para o começo se atingir o limite
  }
}

// Função para ler e imprimir os logs armazenados na EEPROM
void readLogsFromEEPROM() {
  Serial.println("Logs armazenados na EEPROM:");
  Serial.println("Timestamp\tDados");

  int address = startAddress;
  while (address < currentAddress) {
    char timestamp[20];
    float data;

    // Ler timestamp
    for (int i = 0; i < sizeof(timestamp); i++) {
      timestamp[i] = EEPROM.read(address++);
    }

    // Ler dado
    EEPROM.get(address, data);
    address += sizeof(data);

    // Imprimir os valores lidos
    Serial.print(timestamp);
    Serial.print("\t");
    Serial.println(data);
  }
}