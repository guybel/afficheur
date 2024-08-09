
#include <M5Core2.h>
#include <WiFi.h> 
#include <NMEAParser.h> 

const char* ssid = "NMEA2000-Gateway";
const char* password = "password";
const char * serverAddress = "192.168.4.1";
const int serverPort = 2222; // Port série 2222

WiFiClient client;

float depthBelowKeel;
float speedOverWater = -1;

NMEAParser<2> parser;


void errorHandler()
{
  Serial.print("*** Error : ");
  Serial.println(parser.error()); 
}

void unknownCommand()
{
  Serial.print("*** Unkown command : ");
  char buf[6];
  parser.getType(buf);
  Serial.println(buf);
}
/****************** */
// argument 0 = en pied
// argument 2 = en metre 
/**************** */
void handleDepthSounder()
{
  float depth;
  if (parser.getArg(0, depth))
  {
    depthBelowKeel = depth;
  }
}

/********************/
// 
/*******************/
void handleSpeed()
{
  float speed;
  if (parser.getArg(2, speed)){
    speedOverWater = speed ;
  }
}

void setup() {
  M5.begin();
  Serial.begin(9600);
  M5.Lcd.setTextSize(2);
  parser.setErrorHandler(errorHandler);
  parser.addHandler("IIDBK", handleDepthSounder);
  parser.addHandler("VWVHW", handleSpeed);
  

  WiFi.begin(ssid, password);
  M5.Lcd.println("Connexion au WiFi...");
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    M5.Lcd.print(".");
  }
  M5.Lcd.clear();
  M5.Lcd.setCursor(0, 0);
  M5.Lcd.println("Connecté au WiFi!");
  M5.Lcd.print("Adresse IP: ");
  M5.Lcd.println(serverAddress);

}

void affichage_de_connexion(){
    M5.Lcd.clear();
    M5.Lcd.setCursor(0, 0);
    
    M5.Lcd.setTextFont(7);
   
    M5.Lcd.setTextSize(2);
    M5.Lcd.println("Connecté au serveur");
    M5.Lcd.clear();
}

void display_data(){
        M5.Lcd.drawString("Speed", 0, 89, 1);
        M5.Lcd.drawString( String(speedOverWater,1), 100, 17, 7);
        M5.lcd.drawFastHLine(0,115,300,WHITE);
        M5.Lcd.drawString("Depth", 0, 189, 1);
        M5.Lcd.drawString(String(depthBelowKeel,1), 100, 120, 7);
}

void loop() {

 if (client.connect(serverAddress, serverPort)) {
    affichage_de_connexion();

    float old;
    String str;
    char singlechar;
    // Lecture des données du flux série
    while (client.connected()) {
        
        if (client.available()) {
            singlechar = client.read();        
            parser << singlechar;
            str += singlechar;
         }

        if (old != depthBelowKeel || speedOverWater > 0){
          Serial.println(str);
          str = "";
          display_data();
          old = depthBelowKeel;
       }
    }
    
    client.stop();
    M5.Lcd.println("Déconnecté du serveur");
  } else {
   
    M5.Lcd.setCursor(0, 0);
    M5.Lcd.println("Échec de connexion au serveur");
  }
  
  delay(5000); // Attendre 5 secondes avant de réessayer
}
       



