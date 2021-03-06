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
boolean RELE_state[6] = {0}; // stores the states of the RELEs

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

    // RELEs
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
                        
                        XML_response(client);
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
}
// checks if received HTTP request is switching on/off RELEs
void SetLEDs(void)
{
    // RELE 1 (pin 9)
    if (StrContains(HTTP_req, "0=1")) {
        RELE_state[0] = 1;  // save RELE state
        digitalWrite(9, HIGH);
    }
    else if (StrContains(HTTP_req, "0=0")) {
        RELE_state[0] = 0;  // save RELE state
        digitalWrite(9, LOW);
    }
    // RELE 2 (pin 8)
    if (StrContains(HTTP_req, "1=1")) {
        RELE_state[1] = 1;  
        digitalWrite(8, HIGH);
    }
    else if (StrContains(HTTP_req, "1=0")) {
        RELE_state[1] = 0;  
        digitalWrite(8, LOW);
    }
    // RELE 3 (pin 7)
    if (StrContains(HTTP_req, "2=1")) {
        RELE_state[2] = 1;  
        digitalWrite(7, HIGH);
    }
    else if (StrContains(HTTP_req, "2=0")) {
        RELE_state[2] = 0;
        digitalWrite(7, LOW);
    }
    // RELE 4 (pin 6)
    if (StrContains(HTTP_req, "3=1")) {
        RELE_state[3] = 1;
        digitalWrite(6, HIGH);
    }
    else if (StrContains(HTTP_req, "3=0")) {
        RELE_state[3] = 0;
        digitalWrite(6, LOW);
    }
    // RELE 5 (pin 5)
    if (StrContains(HTTP_req, "4=1")) {
        RELE_state[4] = 1;
        digitalWrite(5, HIGH);
    }
    else if (StrContains(HTTP_req, "4=0")) {
        RELE_state[4] = 0;
        digitalWrite(5, LOW);
    }
    // RELE 6 (pin 4)
    if (StrContains(HTTP_req, "5=1")) {
        RELE_state[5] = 1;
        digitalWrite(3, HIGH);
    }
    else if (StrContains(HTTP_req, "5=0")) {
        RELE_state[5] = 0;
        digitalWrite(3, LOW);
    }

}

void XML_response(EthernetClient cl)
{   
    cl.print("<?xml version = \"1.0\" ?>");
    cl.print("<inputs>");

    for (int P = 0; P < 6; P++) {
        cl.print("<R>");
        if (RELE_state[P]) {
            cl.print("1");
        }
        else {
            cl.print("0");
        }
        cl.println("</R>");
    }
    
    
    cl.print("</inputs>");
}

// sets every element of str to 0
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
