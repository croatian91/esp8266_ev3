/**
 * @Date 26/06/17
 * @Description ESP8266 server controlling the EV3 device. Before uploading to the ESP8266 device, change wifi credentials.
 * @Author Ivan HANZEK
 */

// Import required libraries
#include "ESP8266WiFi.h"
#include <aREST.h>

// The port to listen for incoming TCP connections
#define LISTEN_PORT           80

// WiFi parameters
const char* ssid = "MECATEAM2";
const char* password = "mecateam";

// Create aREST instance
aREST rest = aREST();

// Create an instance of the server
WiFiServer server(LISTEN_PORT);

// Functions
int stop(String message);
int move(String message);

void setup(void)
{
  // Start Serial
  Serial.begin(115200);

  // Functions
  rest.function("stop", stop);
  rest.function("move", move);

  // Give name and ID to device
  rest.set_id("1");
  rest.set_name("EV3");

  // Connect to WiFi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());
}

void loop() {

  // Handle REST calls
  WiFiClient client = server.available();

  if (!client) {
    return;
  }

  while(!client.available()){
    delay(1);
  }

  rest.handle(client);
}

int stop(String command) {
  Serial.println("Stop");
  return 0;
}

int move(String command) {
  Serial.println(command);
  return 0;
}