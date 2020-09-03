//#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Ethernet.h>
float lat = 0,lon = 0;
//TinyGPS gps; 
int speedV;
//float lat, lon;
byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
IPAddress ip(192,168,137,1);
//SoftwareSerial gpsSerial(3,4);//rx,tx 
EthernetClient client;
char server[] = "10.20.12.42";
size_t maxSize = 512;
char response[512];

void setup(){ 
    Serial.begin(9600);
    Serial.println("--- Start ---");
    delay(1000);
    Ethernet.begin(mac, ip); 
    Serial.print("My IP address: ");
    Serial.println(Ethernet.localIP());
    //gpsSerial.begin(9600);
    ///lcd.begin(16,2);
}

void loop(){
    speedV = httpRequest(lat, lon);
    Serial.println(speedV);
}
int httpRequest(float latitude, float longitude) {
    client.stop();
    if (client.connect(server, 80)) {
        String s = "GET /index.php?lat=";
        s.concat(String(latitude));
        s.concat("&lon=");
        s.concat(longitude);
        client.println(s);
        client.println("Host: 10.20.12.42");
        delay(1000);
        size_t len = client.readBytes(response, maxSize);
        response[len] = 0;
        //client.println("Connection: close");
        client.println();
        //Serial.println(response);
        int Limit = atoi(response);
        return(Limit);
    }
    else
        Serial.println("connection failed");
    delay(1000);
}

