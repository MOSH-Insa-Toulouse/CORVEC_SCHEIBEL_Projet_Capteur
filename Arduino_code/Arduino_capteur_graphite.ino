#include <SoftwareSerial.h>


/***LIBRAIRIE OLED***/

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h> 
#include <string.h>



/***DEFINITION BLUETOOTH***/

#define rxPin 11 //Broche 11 en tant que RX, à raccorder sur TX du HC-05
#define txPin 10 //Broche 10 en tant que TX, à raccorder sur RX du HC-05
SoftwareSerial mySerial(rxPin,txPin);
#define baudrate 9600



/***DEFINITION OLED***/

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#if (SSD1306_LCDHEIGHT != 32) // Vérification de la présene de la bibliothèque
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif



/***DECLARATION***/

int Pin_ADC = 0;
unsigned long previousMillis = 0; // Variable pour compter le nombre de milliseconde
const long interval = 1000; // Intervalle de temps entre deux mesures
byte tension_capteur = 0;
float R0 = 0.0; 
const int speed_serial = 9600; // Vitesse de communication Bluetooth 




/***INITIALISATION***/

void setup()
{  
  Serial.begin(baudrate);
  mySerial.begin(baudrate);
 
  pinMode(rxPin,INPUT); //Initialisation port RX du module Bluetooth
  pinMode(txPin,OUTPUT); //Initialisation port TX du module Bluetooth

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //Initialisation OLED
  delay(2000); // Délai d'initialisation OLED
  display.clearDisplay();
}



/***PROGRAMME PRINCIPAL***/

/*** Ce programme permet de lire la valeur de la tension au borne du capteur via l'Arduino. Cette valeur est 
envoyée par bluetooth à l'APK. Il convertit la valeur de tension en résistance pour l'afficher directement sur l'OLED.***/

void loop()                    
{
unsigned long currentMillis = millis();   

  /*Lecture de la valeur de la tension toutes les secondes*/
  if (currentMillis - previousMillis >= interval) {     
    previousMillis = currentMillis; //Lecture de la valeur de la tension toutes les secondes
    
    /* Récupération de la valeur de la tension lue sur 10 bits, conversion sur 8 bits */
    tension_capteur = map(analogRead(Pin_ADC),0,1024,0,255); 
 
    /* Envoi, sur un 1 byte (8bits), de la valeur de la tension_capteur vers l'APK via Bluetooth */
    mySerial.write(tension_capteur);

    /* Calcul de la valeur de résistance (en Méga) puis affichage sur l'OLED */
    float temp  = (float)(tension_capteur) * (5.0/256.0);
    R0 = (float)((1.0+100000.0/1000.0)*100000.0*(5.0/temp)-100000.0-10000.0)/1000000.0 ;  
    R0 = R0;
    Serial.println( R0, DEC); 
    display.clearDisplay();
    display.setTextSize(1.5); 
    display.setTextColor(WHITE);
    display.setCursor(0, 0);
    display.println(F("Resistance"));
    display.setCursor(0,10);
    display.println(R0,1);
    display.setCursor(65, 17);
    display.display();
  } 
}


// Lien vers le GIT de la bibliothèque Adafruit
//https://github.com/adafruit/Adafruit_SSD1306/blob/master/examples/ssd1306_128x64_i2c/ssd1306_128x64_i2c.ino
