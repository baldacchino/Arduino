//Switch - Clipsal  
const int ClipsalPBL = 10;     // the number of the pushbutton pin
int buttonState = 0;  
int VarHomvisionRollerShedDoor1 = 0;

int buttonPushCounter = 0;   // counter for the number of button presses
int lastButtonState = 0;     // previous state of the button

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xAE, 0xFE, 0xDE, 0xEF, 0xFD, 0xFD };


byte gateway[] = { 10, 0, 0, 1 }; //            
byte subnet[] = { 255, 255, 255, 0 }; //                
IPAddress ip(10,0,0,49);

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
  
   // initialize the pushbutton pin as an input:
        pinMode(ClipsalPBL, INPUT);
  
        pinMode(RELAY_CH1, OUTPUT); 
   digitalWrite(RELAY_CH1, HIGH);  // switch on LED1
 
   
  
  
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
  // read the state of the pushbutton value:
  buttonState = digitalRead(ClipsalPBL);

      // compare the buttonState to its previous state
    if (buttonState != lastButtonState) {
      // if the state has changed, increment the counter
      if (buttonState == HIGH) {
        // if the current state is HIGH then the button went from off to on:
        buttonPushCounter++;
        Serial.println("on");
        Serial.print("Number of button pushes: ");
        Serial.println(buttonPushCounter);
      } else {
        // if the current state is LOW then the button went from on to off:
        Serial.println("off");
      }
   
     
    }
    // save the current state as the last state, for next time through the loop
    lastButtonState = buttonState;
  
  
    // turns on the LED every four button pushes by checking the modulo of the
    // button push counter. the modulo function gives you the remainder of the
    // division of two numbers:
    if (buttonPushCounter == 2) {
      
       if (VarHomvisionRollerShedDoor1 == 0){
                HomvisionRollerShedDoor1();
                VarHomvisionRollerShedDoor1 = 1;
                digitalWrite(RELAY_CH1, HIGH);    // set pin 4 high
                Serial.println("Toggle Relay 1 High");
                buttonPushCounter = 0;
        } else {
              digitalWrite(RELAY_CH1, LOW);    // set pin 4 high
              Serial.println("Toggle Relay 1 Low");
              HomvisionRollerShedDoor2();
              VarHomvisionRollerShedDoor1 = 0;
              buttonPushCounter = 0; 
        }
        
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

        if(readString.indexOf("?relay1off") >0)//checks for on
        {
            digitalWrite(RELAY_CH1, HIGH);    // set pin 4 high
            Serial.println("Relay 1 On");
          }
        else{
          if(readString.indexOf("?relay1on") >0)//checks for off
          {
            digitalWrite(RELAY_CH1, LOW);    // set pin 4 low          
            Serial.println("Relay 1 Off");
          }
        }
          
      
                   
           readString="";
           
         
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


void HomvisionRollerShedDoor1(){
  IPAddress server(10,0,0,202);
  EthernetClient client2;
  if(client2.connect(server,11080)) {
    client2.println("GET /?var+44+%3D=111");
    client2.println(" HTTP/1.0");
    client2.println("User-Agent: Arduino 1.0");
    client2.println();
    Serial.println("Connect ok");
  }
  client2.stop();
  client2.flush();
}


void HomvisionRollerShedDoor2(){
  IPAddress server(10,0,0,202);
  EthernetClient client2;
  if(client2.connect(server,11080)) {
    client2.println("GET /?var+44+%3D=222");
    client2.println(" HTTP/1.0");
    client2.println("User-Agent: Arduino 1.0");
    client2.println();
    Serial.println("Connect ok");
  }
  client2.stop();
  client2.flush();
}
