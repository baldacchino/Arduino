//Push button switches
const int GarageDoor_Rear_ClipsalPBL = 51;
const int GarageDoor_Front_ClipsalPBL = 53;

int GarageDoor_Rear_buttonState = 0;
int GarageDoor_Front_buttonState = 0;

unsigned long GarageDoor_Rear_startMillis;
unsigned long GarageDoor_Front_startMillis;

//Door Movement Protection (eg 3 clicks within 2 seconds causing two state changes)
unsigned long GarageDoor_Rear_Protection_startMillis;
unsigned long GarageDoor_Front_Protection_startMillis;

unsigned long GarageDoor_Rear_currentMillis;
unsigned long GarageDoor_Front_currentMillis;
const unsigned long period = 1000;  //the value is a number of milliseconds


int GarageDoor_Rear_buttonPushCounter = 0;   // counter for the number of button presses
int GarageDoor_Rear_lastButtonState = 0;     // previous state of the button

int GarageDoor_Front_buttonPushCounter = 0;   // counter for the number of button presses
int GarageDoor_Front_lastButtonState = 0;     // previous state of the button

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xAE, 0xFE, 0xDE, 0xEF, 0xFD, 0xFD };


byte gateway[] = { 10, 0, 0, 1 }; //
byte subnet[] = { 255, 255, 255, 0 }; //
IPAddress ip(10, 0, 0, 49);

// Initialize the Ethernet server library
// with the IP address and port you want to use
// (port 80 is default for HTTP):
EthernetServer server(80);


#define RELAY_CH1  2
#define RELAY_CH2  3
#define RELAY_CH3  4
#define RELAY_CH4  5
#define RELAY_CH5  6
#define RELAY_CH6  7
#define RELAY_CH7  8
#define RELAY_CH8  9

String readString;

void setup() {

  //Garage Door Rear
  pinMode(GarageDoor_Rear_ClipsalPBL, INPUT);
  digitalWrite(GarageDoor_Rear_ClipsalPBL, HIGH);       // turn on pullup resistors
  pinMode(RELAY_CH1, OUTPUT);
  pinMode(RELAY_CH2, OUTPUT);
  digitalWrite(RELAY_CH1, LOW);
  digitalWrite(RELAY_CH2, LOW);
  GarageDoor_Rear_currentMillis = millis();


  //Garage Door Front
  pinMode(GarageDoor_Front_ClipsalPBL, INPUT);
  digitalWrite(GarageDoor_Front_ClipsalPBL, HIGH);       // turn on pullup resistors
  pinMode(RELAY_CH3, OUTPUT);
  pinMode(RELAY_CH4, OUTPUT);
  digitalWrite(RELAY_CH3, LOW);
  digitalWrite(RELAY_CH4, LOW);
  GarageDoor_Front_currentMillis = millis();


  //initial start time
  GarageDoor_Rear_startMillis = millis();
  GarageDoor_Front_startMillis = millis();




  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  while (!Serial) {
    ;
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);

  server.begin();
  Serial.print("HTTP Server has started and is running on IPV4 : ");
  Serial.println(Ethernet.localIP());

}


void loop() {
  //GARAGE REAR DOOR

  //Read digital input switch
  GarageDoor_Rear_buttonState = digitalRead(GarageDoor_Rear_ClipsalPBL);

  // compare the GarageDoor_Rear_ClipsalPBL to its previous state
  if (GarageDoor_Rear_buttonState != GarageDoor_Rear_lastButtonState) {
    // if the state has changed, increment the counter
    GarageDoor_Rear_currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if (GarageDoor_Rear_currentMillis - GarageDoor_Rear_startMillis < period && GarageDoor_Rear_currentMillis > 10000 )  //test whether the period has elapsed
    {
      GarageDoor_Rear_currentMillis = millis(); // get the  current milliseconds from arduino
      Serial.println(GarageDoor_Rear_currentMillis);
      // Increment counter
      GarageDoor_Rear_buttonPushCounter++;
      Serial.print("Number of button pushes: ");
      Serial.println(GarageDoor_Rear_buttonPushCounter);
    } else {
      GarageDoor_Rear_buttonPushCounter = 0;
      Serial.print("Number of button pushes: ");
      Serial.println(GarageDoor_Rear_buttonPushCounter);
    }
    GarageDoor_Rear_startMillis = GarageDoor_Rear_currentMillis;  //IMPORTANT to save the start time of the current cycle
  }
  // save the current state as the last state, for next time through the loop
  GarageDoor_Rear_lastButtonState = GarageDoor_Rear_buttonState;


  // Require a count of 1 in order to open garage door
  
  
  
  if (GarageDoor_Rear_buttonPushCounter == 1) {
     if (millis() - GarageDoor_Rear_Protection_startMillis > 10000)  //10 seconds to door opentest whether the period has elapsed
    {
      //HTTP Get to Homevision
      HomvisionRollerShedDoor1();
      digitalWrite(RELAY_CH1, HIGH);
      digitalWrite(RELAY_CH2, LOW);
      delay(50);
      digitalWrite(RELAY_CH1, LOW);
      digitalWrite(RELAY_CH2, HIGH);
      Serial.println("Toggle Relay 1 High");
      Serial.println("Toggle Relay 2 Low");
      GarageDoor_Rear_buttonPushCounter = 0;
      GarageDoor_Rear_Protection_startMillis = millis();
    } else {
     
      Serial.print("Needs to be 10 seconds between cycles"); 
      GarageDoor_Rear_buttonPushCounter = 0; 
    }   

  
   
  }


  //GARAGE FRONT DOOR

  //Read digital input switch
  GarageDoor_Front_buttonState = digitalRead(GarageDoor_Front_ClipsalPBL);
  
  // compare the GarageDoor_Front_ClipsalPBL to its previous state
  if (GarageDoor_Front_buttonState != GarageDoor_Front_lastButtonState) {
 
    // if the state has changed, increment the counter
    GarageDoor_Front_currentMillis = millis();  //get the current "time" (actually the number of milliseconds since the program started)
    if (GarageDoor_Front_currentMillis - GarageDoor_Front_startMillis < period && GarageDoor_Front_currentMillis > 10000 )  //test whether the period has elapsed
    {
      GarageDoor_Front_currentMillis = millis(); // get the  current milliseconds from arduino
      Serial.println(GarageDoor_Front_currentMillis);
      // Increment counter
      GarageDoor_Front_buttonPushCounter++;
      Serial.print("Number of button pushes: ");
      Serial.println(GarageDoor_Front_buttonPushCounter);
    } else {
      GarageDoor_Front_buttonPushCounter = 0;
      Serial.print("Number of button pushes: ");
      Serial.println(GarageDoor_Front_buttonPushCounter);
    }
    GarageDoor_Front_startMillis = GarageDoor_Front_currentMillis;  //IMPORTANT to save the start time of the current cycle
  }
  // save the current state as the last state, for next time through the loop
  GarageDoor_Front_lastButtonState = GarageDoor_Front_buttonState;



 if (GarageDoor_Front_buttonPushCounter == 1) {
     if (millis() - GarageDoor_Front_Protection_startMillis > 10000)  //10 seconds to door opentest whether the period has elapsed
    {
      //HTTP Get to Homevision
      HomvisionRollerShedDoor1();
      digitalWrite(RELAY_CH3, HIGH);
      digitalWrite(RELAY_CH4, LOW);
      delay(50);
      digitalWrite(RELAY_CH3, LOW);
      digitalWrite(RELAY_CH4, HIGH);
      Serial.println("Toggle Relay 3 High");
      Serial.println("Toggle Relay 4 Low");
      GarageDoor_Front_buttonPushCounter = 0;
      GarageDoor_Front_Protection_startMillis = millis();
    } else {
     
      Serial.print("Needs to be 10 seconds between cycles"); 
      GarageDoor_Front_buttonPushCounter = 0; 
    }   

  
   
  }


  
  
  // Require a count of 1 in order to open garage door
  if (GarageDoor_Front_buttonPushCounter == 1) {
    //HTTP Get to Homevision
    HomvisionRollerShedDoor1();
    digitalWrite(RELAY_CH3, HIGH);
    digitalWrite(RELAY_CH4, LOW);
    delay(50);
    digitalWrite(RELAY_CH3, LOW);
    digitalWrite(RELAY_CH4, HIGH);
    Serial.println("Toggle Relay 3 High");
    Serial.println("Toggle Relay 4 Low");
    GarageDoor_Front_buttonPushCounter = 0;
    GarageDoor_Front_Protection_startMillis = millis();
    
  }








  // listen for incoming clients
  EthernetClient client = server.available();

  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {

      if (client.available()) {

        char c = client.read();

        if (readString.length() < 100) {
          //store characters to string
          readString += c;      //Serial.print(c);
        }

        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply

        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          //client.println("Connection: close");  // the connection will be closed after completion of the response
          //client.println("Refresh: 20");  // refresh the page automatically every 5 sec







          // control arduino pin via ethernet Start //

          if (readString.indexOf("?relay1off") > 0) //checks for on
          {
            digitalWrite(RELAY_CH1, HIGH);    // set pin 4 high
            Serial.println("Relay 1 On");
          }
          else {
            if (readString.indexOf("?relay1on") > 0) //checks for off
            {
              digitalWrite(RELAY_CH1, LOW);    // set pin 4 low
              Serial.println("Relay 1 Off");
            }
          }



          readString = "";


          break;
        }// if ( c == \n )


        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }

      }
    }

    // give the web browser time to receive the data
    delay(1);


    // close the connection:
    client.stop();
    Serial.println("client disonnected");

  }//if(Client)

}//Loop


void HomvisionRollerShedDoor1() {
  IPAddress server(10, 0, 0, 202);
  EthernetClient client2;
  if (client2.connect(server, 11080)) {
    client2.println("GET /?var+44+%3D=111");
    client2.println(" HTTP/1.0");
    client2.println("User-Agent: Arduino 1.0");
    client2.println();
    Serial.println("Connect ok");
  }
  client2.stop();
  client2.flush();
}


void HomvisionRollerShedDoor2() {
  IPAddress server(10, 0, 0, 202);
  EthernetClient client2;
  if (client2.connect(server, 11080)) {
    client2.println("GET /?var+44+%3D=222");
    client2.println(" HTTP/1.0");
    client2.println("User-Agent: Arduino 1.0");
    client2.println();
    Serial.println("Connect ok");
  }
  client2.stop();
  client2.flush();
}


