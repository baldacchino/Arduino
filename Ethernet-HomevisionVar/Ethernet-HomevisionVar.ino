

#include <U8glib.h>


#include <SPI.h>
#include <Ethernet.h>
String DownstairsTemp = "";
String currentLine = "";            // string for incoming serial data
String currRates = "";
boolean readingRates = false;       // is reading?
//const int requestInterval = 600000; // milliseconds delay between requests



U8GLIB_SH1106_128X64 display1(13, 11, 10, 9, 8);
U8GLIB_SSD1306_128X64 display2(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);  // I2C / TWI 

boolean requested;                  // whether you've made a request since connecting
long lastAttemptTime = 0;           // last time you connected to the server, in milliseconds

byte mac[] = { 0x84, 0x42, 0x8B, 0xBA, 0xB2, 0x31 }; //mac address of ethernet shield
char server[] = "10.0.0.202";    // name address for Google (using DNS)
// Set the static IP address to use if the DHCP fails to assign
IPAddress ip(10, 0, 0, 40);

// Initialize the Ethernet client library
// with the IP address and port of the server
// that you want to connect to (port 80 is default for HTTP):
EthernetClient client;

void setup() {
  display1.setColorIndex(1);
  display2.setColorIndex(1);
  pinMode(8, OUTPUT);

  
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // start the Ethernet connection:
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }

   // Connect to server  
  connectToServer();
  
}



void draw1(void)
{
  display1.setFont(u8g_font_unifont);
  display1.drawStr(0, 22, "Downstairs Temp");
  
 // display1.setPrintPos(44, 30);  // set position
   display1.setFont(u8g_font_fur14);
   display1.setPrintPos(44, 50);  // set position
   display1.print(DownstairsTemp + "C");  // dis
   //display1.drawStr(44, 50,DownstairsTemp);
   Serial.println(DownstairsTemp);
 
}
void draw2(void)
{
  display2.setFont(u8g_font_unifont);
  display2.drawStr(0, 22, "Display 2");
}

void connectToServer() {
  // give the Ethernet shield a second to initialize:
  //delay(1000);
  Serial.println("connecting...");

  // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.println("connected");
    // Make a HTTP request:
    client.println("GET /temp.txt HTTP/1.1");
    client.println("Host: 10.0.0.202");
    client.println("Connection: close");
    client.println();
    
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }
  
  
  // note the time of this connect attempt:
  lastAttemptTime = millis();
}



void loop(){
  

 // EthernetClient client = server.available();
  if (client) {
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        //store characters to string
        currentLine += c;

           
        // if you get a newline, clear the line:
        if (c == '\n') {
          currentLine = "";
        }
        
      if (currentLine.endsWith("</Upstairs>")) {
          Serial.println(currentLine);
          int Temperature = currentLine.indexOf('/');
          Serial.println (currentLine.substring(10, 12));
          DownstairsTemp =  (currentLine.substring(10, 12));

  
     
      } 
      
        
        }      
      }
    }
 client.stop();
 delay(5000);
  display1.firstPage();
  do
  {
    draw1();
  } while ( display1.nextPage() );

  display2.firstPage();
  do
  {
    draw2();
  } while ( display2.nextPage() );


 
 connectToServer();

    
  }

