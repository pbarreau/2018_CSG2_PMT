#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


#define OLED_MOSI   D4
#define OLED_CLK    D3
#define OLED_DC     D2
#define OLED_CS     D1
#define OLED_RESET  D0
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // put your setup code here, to run once:
   display.begin(SSD1306_SWITCHCAPVCC);
  display.display();
  delay(2000);
  display.clearDisplay();
}

void loop() {
  // put your main code here, to run repeatedly:
 unsigned int tension= analogRead(A0); 
int volts= (tension/1024) * 4200;

  switch (volts) {
    
    case 3700: 
    client.print("La batterie de l'agent n°");
    client.print(agentId);
    client.println(" est de 20% et est décharger ");
    display.println("Mode économie activée.");
    ESP.deepSleep(60e6);
    break;
  }
}
