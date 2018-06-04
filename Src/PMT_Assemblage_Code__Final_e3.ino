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

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
 // Création de la liste des points d'accès pour réaliser la connexion wifi au signal le plus puissant
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
  // Connexion réussi affichage de l'adresse IP ainsi que démarrage du server qui permettra de réaliser le test de d'une demande d'aide 
  if(wifiMulti.run() == WL_CONNECTED) {
     display.clearDisplay();
     display.setTextSize(1);
     display.setTextColor(WHITE);
     display.setCursor(0,0);
     display.println("Connecter au réseau WiFi");
     display.println(WiFi.localIP());
     display.display();
  }
}

void loop() {

  demanderAssistance();
  informerSuperviseur();
  
}

void demanderAssistance(){
  
  String agentId = WiFi.macAddress();
  const int boutonAide = 5;
  const char * host = "172.20.10.1";
  const uint16_t port = 1026;
  WiFiClient client;
  boolean etatBouton;

   pinMode(boutonAide, INPUT);
   etatBouton = digitalRead(boutonAide);
   
   if (!client.connect(host,port)) // Connexion au serveur si la connexion n'est pas encore établie
  
     client.connect(host,port);
     else { //Affichage de l'agent connecté
     client.print("Agent n° ");
      client.print(agentId);
      client.println(" connecté"); 
     }
 
      if(etatBouton == HIGH){   // On regarde si le bouton a eu un changement d'état et est passeé à l'état "HIGH" on fabrique ensuite la demande d'assistance et on l'envoie au superviseur
          
          client.print("Je suis l'agent n° ");
          client.print(agentId);
          client.print(" et je me situe au ");
          client.println(WiFi.SSID());
          delay(5000);
          String c = client.readString();
          display.setCursor(0,0);
          display.setTextColor(WHITE);
          display.println(c);
          display.display();
      }
  
}

void informerSuperviseur() {

  unsigned int tension= analogRead(A0); 
  float volts= (tension/1024.0) * 4.2;

  if (volts <= 3.70){
    client.print("La charge de l'agent n°");
    client.print(agentId);
    client.println(" est en dessous des 20% ");
    display.println("Mode économie activée.");
    ESP.deepSleep(20e6);
  }
}

