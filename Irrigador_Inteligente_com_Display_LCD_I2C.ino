#include "arduino_secrets.h"

// Projeto Irrigador Inteligente                                                //
// ProgramaÃ§Ã£o usando um MÃ³dulo RelÃ© 5V e um Display LCD (20x4) com MÃ³dulo I2C  //

// Inclui as bibliotecas para funcionamento do display
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define o nome para o pino A0 como "pinoAnalog"
#define pinoAnalog A0
// Define o nome para pino 8 como "pinoRele"
#define pinoRele 8

// Inicializa o LCD com o endereÃ§o do mÃ³dulo e as dimensÃµes
LiquidCrystal_I2C lcd(0x27, 20, 4);

void setup() {
  Serial.begin(9600);              // Define a conexÃ£o serial em 9600 bits por segundo
  pinMode(pinoRele, OUTPUT);       // Define o pinoRele como saÃ­da
  lcd.init();                      // Inicializa o LCD
  lcd.backlight();                 // Liga a retroiluminaÃ§Ã£o do LCD
}

void loop() {
  // Armazena a leitura do sensor na variÃ¡vel.
  int Dados_sensor = analogRead(pinoAnalog);
  // Mapeia os dados do sensor para definir os valores de umidade em porcentagem.
 int Umid = map(Dados_sensor, 1023, 0, 0, 100);

Serial.println("-------------------------");
Serial.print("Umidade:  ");                 // Imprime no monitor serial a Umidade
Serial.print(Umid);                         // Imprime o valor da umidade no monitor serial
Serial.print("%");                          // Imprime no monitor serial "%."
Serial.println();                           // Quebra uma linha no monitor serial

  lcd.clear();                     // Apaga as informaÃ§Ãµes do LCD
  lcd.setCursor(0, 1);             // Define o cursor no inÃ­cio da segunda linha do LCD
  lcd.print("Umidade: ");          // Digita o texto "Umidade: "
  lcd.setCursor(9, 1);             // Define o cursor na nona coluna, segunda linha
  lcd.print(Umid);                 // Digita o valor de umidade
 
  if (Umid <= 45) {                // Se a umidade for menor ou igual Ã  45% faz...

    digitalWrite(pinoRele, LOW);   // Define a saÃ­da do pinoRele para nÃ­vel = LOW (Baixo), ligando a bomba

Serial.println("Irrigando...");               // Imprime no monitor serial "Irrigando..."
Serial.println("-------------------------");
Serial.println();                             // Quebra uma linha no monitor serial
    
  lcd.setCursor(0, 2);           // Define o cursor no inÃ­cio da terceira linha
  lcd.print("Irrigando...");     // Digita "Irrigando..." se a umidade for baixa
  } 

    else {
      
    digitalWrite(pinoRele, HIGH);  // Define a saÃ­da do pinoRele para nÃ­vel = HIGH (Alto), desligando a bomba

Serial.println("Pronto para irrigar.");       // Imprime no monitor serial "Pronto para irrigar."
Serial.println("-------------------------");
Serial.println();                             // Quebra uma linha no monitor serial
      
  lcd.setCursor(0, 2);                   // Define o cursor no inÃ­cio da terceira linha
  lcd.print("Pronto para irrigar");      // Digita "Pronto para irrigar"
  
  }

  delay(1000);                   // Espera 1 segundo e repete o processo
}