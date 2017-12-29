//Switch - Clipsal  
const int ClipsalPBL = 10;     // the number of the pushbutton pin
int buttonState = 0;  

//Timer Code
unsigned long interval=500; // the time we need to wait
unsigned long previousMillis=0; // millis() returns an unsigned long.
bool ClipsalPBLState = false; // state variable for the switch
 

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0xAE, 0xFE, 0xDE, 0xEF, 0xFD, 0xFD };


byte gateway[] = { 10, 0, 0, 1 }; //               <------- PUT YOUR ROUTERS IP Address to which your shield is connected Here
byte subnet[] = { 255, 255, 255, 0 }; //                <------- It will be as it is in most of the cases
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
 
        pinMode(RELAY_CH2, OUTPUT); 
  digitalWrite(RELAY_CH2, HIGH);  // switch on LED2
 
        pinMode(RELAY_CH3, OUTPUT); 
  digitalWrite(RELAY_CH3, HIGH);  // switch on LED3
 
        pinMode(RELAY_CH4, OUTPUT); 
  digitalWrite(RELAY_CH4, HIGH);  // switch on LED4
 
        pinMode(RELAY_CH5, OUTPUT); 
  digitalWrite(RELAY_CH5, HIGH);  // switch on LED5
 
        pinMode(RELAY_CH6, OUTPUT); 
  digitalWrite(RELAY_CH6, HIGH);  // switch on LED6
 
        pinMode(RELAY_CH7, OUTPUT); 
  digitalWrite(RELAY_CH7, HIGH);  // switch on LED7
 
        pinMode(RELAY_CH8, OUTPUT); 
  digitalWrite(RELAY_CH8, HIGH);  // switch on LED8
  
  
  
 // Open serial communications and wait for port to open:
  Serial.begin(9600);
   while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }


  // start the Ethernet connection and the server:
  Ethernet.begin(mac, ip);
  
  server.begin();
  Serial.print("HTTP Server has started and is running on IPV4 : ");
  Serial.println(Ethernet.localIP()); 
  
}


void loop() {

  // grab current time
  unsigned long currentMillis = millis(); 



  
  // read the state of the pushbutton value:
  buttonState = digitalRead(ClipsalPBL);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
        // check if "interval" time has passed (1000 milliseconds)
     if ((unsigned long)(currentMillis - previousMillis) >= interval) {
        ClipsalPBLState = !ClipsalPBLState; // "toggles" the state
        digitalWrite(RELAY_CH1, HIGH);    // set pin 4 high
        Serial.println("Relay 1 On");
     }
  } else {
     if ((unsigned long)(currentMillis - previousMillis) >= interval) {
        ClipsalPBLState = !ClipsalPBLState; // "toggles" the state
        digitalWrite(RELAY_CH1, LOW);    // set pin 4 high
        Serial.println("Relay 1 Off");
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
          
          
         if(readString.indexOf("?relay2off") >0)//checks for on
        {
            digitalWrite(RELAY_CH2, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay2on") >0)//checks for off
          {
            digitalWrite(RELAY_CH2, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
          
          
          if(readString.indexOf("?relay3off") >0)//checks for on
        {
            digitalWrite(RELAY_CH3, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay3on") >0)//checks for off
          {
            digitalWrite(RELAY_CH3, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
        
        if(readString.indexOf("?relay4off") >0)//checks for on
        {
            digitalWrite(RELAY_CH4, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay4on") >0)//checks for off
          {
            digitalWrite(RELAY_CH4, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
        
         if(readString.indexOf("?relay5off") >0)//checks for on
        {
            digitalWrite(RELAY_CH5, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay5on") >0)//checks for off
          {
            digitalWrite(RELAY_CH5, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
          
          
         if(readString.indexOf("?relay6off") >0)//checks for on
        {
            digitalWrite(RELAY_CH6, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay6on") >0)//checks for off
          {
            digitalWrite(RELAY_CH6, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
          
          
          if(readString.indexOf("?relay7off") >0)//checks for on
        {
            digitalWrite(RELAY_CH7, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay7on") >0)//checks for off
          {
            digitalWrite(RELAY_CH7, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
        
        if(readString.indexOf("?relay8off") >0)//checks for on
        {
            digitalWrite(RELAY_CH8, HIGH);    // set pin 4 high
            //Serial.println("Led On");
      
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/on.png' />");
            //client.println("Light 1 Is On");
            client.println("<br />");
  }
        else{
          if(readString.indexOf("?relay8on") >0)//checks for off
          {
            digitalWrite(RELAY_CH8, LOW);    // set pin 4 low
            //Serial.println("Led Off");
            client.println("<link rel='apple-touch-icon' href='http://chriscosma.co.cc/off.png' />");

      //client.println("Light 1 Is Off");
            client.println("<br />");
          }
        }
                    
        // INPUT
          
          
          // output the value of each analog input pin
          //for (int analogChannel = 0; analogChannel < 6; analogChannel++) {
          //  int sensorReading = analogRead(analogChannel);
          //  client.print("analog input ");
          //  client.print(analogChannel);
          //  client.print(" is ");
          //  client.print(sensorReading);
          //  client.println("<br />");       
          //}
                   
           readString="";
           client.println("</body>");         
           client.println("</html>");
         
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
    //client.println("<meta http-equiv=\"refresh\" content=\"10;url=http://192.168.0.199/\"/>" );
    
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
    
  }//if(Client)
  
}//Loop

