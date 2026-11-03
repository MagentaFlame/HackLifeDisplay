#include <WiFi.h>
#include <WiFiAP.h>
#include <WiFiClient.h>
#include <WiFiGeneric.h>
#include <WiFiMulti.h>
#include <WiFiSTA.h>
#include <WiFiScan.h>
#include <WiFiServer.h>
#include <WiFiType.h>
#include <WiFiUdp.h>

#include <HTTPClient.h>
#include <Adafruit_NeoPixel.h>
#include <ArduinoJson.h>

#define PIN D11         // ESP32 C3
#define NUM_PIXELS 8    

Adafruit_NeoPixel strip(NUM_PIXELS, PIN, NEO_GRB + NEO_KHZ800); // set strip up

// wifi, specific sensitive info
char ssid[] = "putlater";
char password[] = "putlater";
int serial = "putlater";
String lat = "putlater";
String lon = "putlater";
String api = "012af975319ae1fe0292a8b252031fc5";

// getWeather things
String currentWeather;
String currentID; // a next step could be to make this integer so can be gradient of colors depending on more specific reports

// millis
unsigned long prevPause = 0;

// switch states
int currentSwitch; 
int prevSwitch;

void setup() { // runs once after start
  Serial.begin(serial); // init serial, wifi
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) { // check wifi status
    delay(500);
    Serial.print(".");
  }
  Serial.print("Connected.");

  strip.begin();            // set up the data pin
  strip.setBrightness(40);  // about 15%, call this once here

  pinMode(8, INPUT_PULLUP); // init switch
  currentSwitch = digitalRead(8);

  getWeather(); // initial showing
}

void loop() { // continuously running
  unsigned long pause = millis();
  if ((pause - prevPause) >= 1860000) { // 30 min intervals so don't use up api
    prevPause = pause; // reset loop, not change millis but the prev
    getWeather();
  }
  currentSwitch = digitalRead(8); // pin 8
  if (currentSwitch != prevSwitch) { // check if flipped
    updateLED(currentWeather, currentID); // immediately update
    prevSwitch = currentSwitch; // reset
  }
}

void getWeather() { // gets api and the info needed, calls LED update
  WiFiClient client;
  HTTPClient http;
  
  JsonDocument doc;

  String endpoint = "https://api.openweathermap.org/data/4.0/onecall/timeline/1h?lat=" + lat + "&lon=" + lon + "&appid=" + api; 

  http.begin(client, endpoint.c_str()); // .c_str b/c of some old compatibility?
  int httpCode = http.GET(); // gets it

  if (httpCode > 0) { // if there is a httpCode
    String payload = http.getString(); // got the json string info
    DeserializationError error = deserializationJson(doc, payload);

    if (!error) { // if no error, then update LEDs
      currentWeather = doc["weather"][0]["main"].as<String>();
      currentID = doc["weather"][0]["id"].as<String>();

      updateLED(currentWeather, currentID);
    }
  }
  http.end();
}

void updateLED(currentWeather, currentID) { // changes LED color
  // ooooo colorssss fun
  int r;
  int g;
  int b;
  if (currentSwitch == LOW) { // cool tones
    if (currentWeather == "Thunderstorm") { // dark blue grey
      g = 91;
      r = 80;
      b = 117;
    } else if (currentWeather == "Drizzle") { // grey white hint of blue
      g = 205;
      r = 188;
      b = 245;
    } else if (currentWeather == "Rain") {
      if (currentID == "500") || (currentID == "501") || (currentID == "520") || (currentID == "521") { // light rain (pastel blue)
        g = 175;
        r = 151;
        b = 247;
      } else { // heavyish rain (saturated darker blue)
        g = 105;
        r = 57;
        b = 247;
      }
    } else if (currentWeather == "Snow") { // grey white hint of bright blue
      g = 227;
      r = 205;
      b = 250;
    } else if (currentWeather == "Clear") { // bright pastel blue
      g = 217;
      r = 161;
      b = 255;
    } else if (currentWeather == "Clouds") {
      if (currentID == "803") || (currentID == "804") { // dark clouds (grey blue)
        g = 143;
        r = 116;
        b = 161;
      } else { // light clouds (light blue)
        g = 174;
        r = 139;
        b = 196;
      }
    } else { // dusty, etc (light green)
      g = 242;
      r = 218;
      b = 231;
    }
  } else { // warm tones
    if (currentWeather == "Thunderstorm") { // dark purple
      g = 36;
      r = 82;
      b = 166;
    } else if (currentWeather == "Drizzle") { // brighter lavender
      g = 180;
      r = 225;
      b = 237;
    } else if (currentWeather == "Rain") { // medium pink
      if (currentID == "500") || (currentID == "501") || (currentID == "520") || (currentID == "521") { // light rain
        g = 152;
        r = 227;
        b = 227;
      } else { // heavyish rain (dark pink)
        g = 43;
        r = 179;
        b = 179;
      }
    } else if (currentWeather == "Snow") { // pale pink
      g = 232;
      r = 255;
      b = 244;
    } else if (currentWeather == "Clear") { // pale yellow
      g = 255;
      r = 249;
      b = 186;
    } else if (currentWeather == "Clouds") {
      if (currentID == "803") || (currentID == "804") { // dark clouds (dark red)
        g = 76;
        r = 230;
        b = 76;
      } else { // light clouds (medium red)
        g = 152;
        r = 237;
        b = 152;
      }
    } else { // dusty, etc (light orange)
      g = 218;
      r = 250;
      b = 190;
    }
  }

  for (int i = 0; i < NUM_PIXELS; i++) { // check if want it to be flickering
    strip.clear();                                     // all off (in memory)
    strip.setPixelColor(i, strip.Color(g, r, b));  // pixel i sky blue
    strip.show();                                      // send it to the LEDs
    delay(100);
  }
} 

