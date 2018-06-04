#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Définir les broches de l'écran permettant l'affichage des messages 
#define OLED_MOSI   D4         
#define OLED_CLK    D3
#define OLED_DC     D2
#define OLED_CS     D1
#define OLED_RESET  D0
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


// Déclaration des variables necessaire au fonctionnement du serveur de test ainsi que du bouton qui permettra l'envoie de la demande d'aide 
ESP8266WiFiMulti wifiMulti;
String agentId = WiFi.macAddress(); 
const int boutonAide = 5;
const char * host = "172.20.10.4";
const uint16_t port = 1024;
WiFiClient client;
boolean etatBouton;

void setup() {
  // Initialisation des composant utilisés (l'écran OLED et le bouton poussoir )
  pinMode(boutonAide, INPUT);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
  
 // Création de la liste des points d'accès pour réaliser la connection wifi au signal le plus puissant
  WiFi.mode(WIFI_STA);
    wifiMulti.addAP("iPhone de Junior", "pluriels2");
    wifiMulti.addAP("iPhone de Jonathan", "fgwk9u5hgggs7");
    wifiMulti.addAP("NETGEAR", "v13btsiris");
    
  // Début de la connexion 
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Connection au WiFi..");
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(1000);
    display.print(".");
    display.display();
  }
  // Connexion réussi affichage de l'adresse IP ainsi que démarrage du server qui permettera de réaliser le test de d'une demande d'aide
  if(wifiMulti.run() == WL_CONNECTED) {
     display.clearDisplay();
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0,0);
     display.println("Connecter au réseau WiFi");
     display.println(WiFi.localIP());
     display.display();
     delay(2000);
     
  }
  
 
void loop() {
  
  etatBouton = digitalRead(boutonAide);
  
  if (!client.connect(host,port))
  
     client.connect(host,port);
     else {
     client.print("Agent n° ");
      client.print(agentId);
      client.println(" connecte"); 
     }
}
  
       if(etatBouton == HIGH){   // On régarde si le bouton a eu un changement d'état et est passer à l'état "HIGH" on fabrique ensuite la demande d'assistance et on l'envoie au superviseur
          client.print("Je suis l'agent n° ");
          client.print(agentId);
          client.print(" et je me situe au ");
          client.println(WiFi.SSID()); 
          delay(5000);
          String c = client.readString();
           // Une fois le message afficher on récupère la confirmation du superviseur à l'agent et on l'affiche sur l'écran de l'agent
              display.clearDisplay();
              display.setCursor(0,0);
              display.setTextColor(WHITE);
              display.println(c);
              display.display();
        }
}
