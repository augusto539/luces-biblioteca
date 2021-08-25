/*--------------------------------------------------------------
  Program:      web_server_hw_button_pg_button

  Description:  Arduino web server that allows two LEDs to be
                controlled by a checkbox, HTML button and two
                hardware push buttons.
                The web page is stored on the micro SD card.
  
  Hardware:     Arduino Uno and official Arduino Ethernet
                shield. Should work with other Arduinos and
                compatible Ethernet shields.
                2Gb micro SD card formatted FAT16.
                LEDs on pins 6 and 7.
                Switches on pins 2 and 3.
                
  Software:     Developed using Arduino 1.6.1 software
                Should be compatible with Arduino 1.0 +
                SD card contains web page called index.htm
  
  References:   - Based on Ajax I/O example from Starting
                  Electronics:
                  http://startingelectronics.org/tutorials/arduino/ethernet-shield-web-server-tutorial/SD-card-IO/
                  
                - Switch debouncing from Arduino IDE example code
                  File --> Examples --> 02.Digital --> Debounce
                  http://www.arduino.cc/en/Tutorial/Debounce

  Date:         13 April 2015
 
  Author:       W.A. Smith, http://startingelectronics.org
--------------------------------------------------------------*/

#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
// size of buffer used to capture HTTP requests
#define REQ_BUF_SZ   60

// MAC address from Ethernet shield sticker under board
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 1, 35); // IP address, may need to change depending on network
EthernetServer server(80);  // create a server at port 80
File webFile;               // the web page file on the SD card
char HTTP_req[REQ_BUF_SZ] = {0}; // buffered HTTP request stored as null terminated string
char req_index = 0;              // index into HTTP_req buffer
boolean LED_state[2] = {0}; // stores the states of the LEDs

void setup()
{
    // disable Ethernet chip
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    
    Serial.begin(9600);       // for debugging
    
    // initialize SD card
    Serial.println("Initializing SD card...");
    if (!SD.begin(4)) {
        Serial.println("ERROR - SD card initialization failed!");
        return;    // init failed
    }
    Serial.println("SUCCESS - SD card initialized.");
    // check for index.htm file
    if (!SD.exists("index.htm")) {
        Serial.println("ERROR - Can't find index.htm file!");
        return;  // can't find index file
    }
    Serial.println("SUCCESS - Found index.htm file.");
    // switches
    pinMode(2, INPUT);
    
    // LEDs
    pinMode(3, OUTPUT);
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);
    
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();           // start to listen for clients
}

void loop()
{   
    EthernetClient client = server.available();  // try to get client

    if (client) {  // got client?
        boolean currentLineIsBlank = true;
        while (client.connected()) {
            if (client.available()) {   // client data available to read
                char c = client.read(); // read 1 byte (character) from client
                // limit the size of the stored received HTTP request
                // buffer first part of HTTP request in HTTP_req array (string)
                // leave last element in array as 0 to null terminate string (REQ_BUF_SZ - 1)
                if (req_index < (REQ_BUF_SZ - 1)) {
                    HTTP_req[req_index] = c;          // save HTTP request character
                    req_index++;
                }
                // last line of client request is blank and ends with \n
                // respond to client only after last line received
                if (c == '\n' && currentLineIsBlank) {
                    // send a standard http response header
                    client.println("HTTP/1.1 200 OK");
                    // remainder of header follows below, depending on if
                    // web page or XML page is requested
                    // Ajax request - send XML file
                    if (StrContains(HTTP_req, "ajax_inputs")) {
                        // send rest of HTTP header
                        client.println("Content-Type: text/xml");
                        client.println("Connection: keep-alive");
                        client.println();
                        SetLEDs();
                        // send XML file containing input states
                      //  XML_response(client);
                    }
                    else {  // web page request
                        // send rest of HTTP header
                        client.println("Content-Type: text/html");
                        client.println("Connection: keep-alive");
                        client.println();
                        // send web page
                        webFile = SD.open("index.htm");        // open web page file
                        if (webFile) {
                            while(webFile.available()) {
                                client.write(webFile.read()); // send web page to client
                            }
                            webFile.close();
                        }
                    }
                    // display received HTTP request on serial port
                    Serial.print(HTTP_req);
                    // reset buffer index and all buffer elements to 0
                    req_index = 0;
                    StrClear(HTTP_req, REQ_BUF_SZ);
                    break;
                }
                // every line of text received from the client ends with \r\n
                if (c == '\n') {
                    // last character on line of received text
                    // starting new line with next character read
                    currentLineIsBlank = true;
                } 
                else if (c != '\r') {
                    // a text character was received from client
                    currentLineIsBlank = false;
                }
            } // end if (client.available())
        } // end while (client.connected())
        delay(2);      // give the web browser time to receive the data
        client.stop(); // close the connection
    } // end if (client)
    
    // read buttons and debounce

}

// function reads the push button switch states, debounces and latches the LED states
// toggles the LED states on each push - release cycle
// hard coded to debounce two switches on pins 2 and 3; and two LEDs on pins 6 and 7
// function adapted from Arduino IDE built-in example:
// File --> Examples --> 02.Digital --> Debounce



// checks if received HTTP request is switching on/off LEDs
// also saves the state of the LEDs
void SetLEDs(void)
{
    // LED 1 (pin 6)
    if (StrContains(HTTP_req, "0=1")) {
       
        digitalWrite(9, HIGH);
    }
    else if (StrContains(HTTP_req, "0=0")) {
      
        digitalWrite(9, LOW);
    }
    // LED 2 (pin 7)
    if (StrContains(HTTP_req, "1=1")) {
        
        digitalWrite(8, HIGH);
    }
    else if (StrContains(HTTP_req, "1=0")) {
        
        digitalWrite(8, LOW);
    }

    if (StrContains(HTTP_req, "2=1")) {
      
        digitalWrite(7, HIGH);
    }
    else if (StrContains(HTTP_req, "2=0")) {
     
        digitalWrite(7, LOW);
    }



    if (StrContains(HTTP_req, "3=1")) {
      
        digitalWrite(6, HIGH);
    }
    else if (StrContains(HTTP_req, "3=0")) {
     
        digitalWrite(6, LOW);
    }


    if (StrContains(HTTP_req, "4=1")) {
      
        digitalWrite(5, HIGH);
    }
    else if (StrContains(HTTP_req, "4=0")) {
     
        digitalWrite(5, LOW);
    }


    if (StrContains(HTTP_req, "5=1")) {
      
        digitalWrite(3, HIGH);
    }
    else if (StrContains(HTTP_req, "5=0")) {
     
        digitalWrite(3, LOW);
    }

}

// send the XML file with analog values, switch status
//  and LED status

/*
void XML_response(EthernetClient cl)
{
    int analog_val;            // stores value read from analog inputs
    int count;                 // used by 'for' loops
    int sw_arr[] = {2, 3};  // pins interfaced to switches
    
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");
    // checkbox LED states
    // LED1
    cl.print("<LED>");
    if (LED_state[0]) {
        cl.print("checked");
    }
    else {
        cl.print("unchecked");
    }
    cl.println("</LED>");
    // button LED states
    // LED3
    cl.print("<LED>");
    if (LED_state[1]) {
        cl.print("on");
    }
    else {
        cl.print("off");
    }
    cl.println("</LED>");
    cl.print("</inputs>");
}
*/

// sets every element of str to 0 (clears array)
void StrClear(char *str, char length)
{
    for (int i = 0; i < length; i++) {
        str[i] = 0;
    }
}

// searches for the string sfind in the string str
// returns 1 if string found
// returns 0 if string not found
char StrContains(char *str, char *sfind)
{
    char found = 0;
    char index = 0;
    char len;

    len = strlen(str);
    
    if (strlen(sfind) > len) {
        return 0;
    }
    while (index < len) {
        if (str[index] == sfind[found]) {
            found++;
            if (strlen(sfind) == found) {
                return 1;
            }
        }
        else {
            found = 0;
        }
        index++;
    }

    return 0;
}
