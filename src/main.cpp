#include <Arduino.h>
#include <MotorService.h>
#include <ESP8266WiFi.h>
#include <Secrets.h>
#include <WiFiUdp.h>

// Variables WiFi:
WiFiUDP Udp;
unsigned int localUdpPort = 4210;  // local port to listen on
char incomingPacket[255];  // buffer for incoming packets
char replyPacket[] = "OK";  // a reply string to send back

/**
 * @brief Parpadea el LED de la placa NodeMCU.
 * 
 * @param period En milisegundos.
 * @param iters Número de parpadeos.
 */
void blink(int period, int iters){
  for(int i=0; i<iters; i++){
    digitalWrite(LED_BUILTIN, LOW);
    delay(period/2);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(period/2);
  }
}

void setup() {
  Serial.begin(9600);

  // Motor setup
  setupMotor();

  // WiFi setup
  Serial.println("Connecting to " + String(SSID) + "...");
  WiFi.config(IPAddress(LOCAL_IP), IPAddress(GATEWAY), IPAddress(SUBNET));
  WiFi.begin(SSID, PASSWORD);

  // Starting connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
    blink(10, 1);
  }
  Serial.println(" Connected!");
  blink(150, 2);

  // Starts listening UDP Port to receive data
  Udp.begin(localUdpPort);
  Serial.printf("Now listening at IP %s, UDP port %d\n", WiFi.localIP().toString().c_str(), localUdpPort);
}

void loop() {
  String payload;
  
  // Data reading
  int packetSize = Udp.parsePacket();
  if (packetSize) // New data available
  {
    int len = Udp.read(incomingPacket, 255);
    if (len > 0)  // Correct data received
    {
      incomingPacket[len] = 0;  // Deletes the termination character.
    }

    payload = String(incomingPacket); // Stores data as a String
    //Serial.println("Payload: " + payload);

    // Send back a reply, to the IP address and port we got the packet from
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write(replyPacket);
    Udp.endPacket();
  }

  // Decission
  if      (payload.compareTo("UP"))     { moveMotor( SPEED); }
  else if (payload.compareTo("DOWN"))   { moveMotor(-SPEED); }
  else if (payload.compareTo("STOP"))   { moveMotor(0); }
  else if (payload.compareTo("GRAB"))   {}
  else if (payload.compareTo("RELEASE")){}
  else { moveMotor(0); }
}