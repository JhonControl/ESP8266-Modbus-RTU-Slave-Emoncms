#include <modbus.h>
#include <modbusDevice.h>
#include <modbusRegBank.h>
#include <modbusSlave.h>
#include <ESP8266WiFi.h>


const char* ssid     = "Nitro X";
const char* password = "25364016";

const char* host = "192.168.1.57";
const char* streamId   = "....................";
const char* apikey = "6a36f95a048ff8ba64f5c0eb18204381";




//https://code.google.com/p/arduino-modbus-slave/downloads/detail?name=MODBUS.zip&can=2&q=/




//Setup the brewtrollers register bank
//All of the data accumulated will be stored here
modbusDevice regBank;
//Create the modbus slave protocol handler
modbusSlave slave;

///salida pwm pin 9
//#define  LED 9 

  
int conta=0;
 
void setup()
{   



    WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    //Serial.print(".");
  }



  

  



//Assign the modbus device ID.  
  regBank.setId(1);
  regBank.add(160);
  regBank.add(161);

   
// Añade Salida analógica registra 40.001-40.020 al banco de registros
  regBank.add(40001);  
  regBank.add(40002);  
  regBank.add(40003);  
  regBank.add(40004);  
  regBank.add(40005);  
  regBank.add(40006);  
  regBank.add(40007);  
  regBank.add(40008);  
  regBank.add(40009);  
  regBank.add(40010);  
  regBank.add(40100);  
  regBank.add(40101);  

  slave._device = &regBank;  
  slave.setBaud(19200);   //19200 None   
}

void loop()
{  


  
    
 while(1)
  {
    
        // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }

 
       conta++;   
     delay(1000);
     

     float valor = regBank.get(40100);

    char outstr1[15];
    dtostrf(valor,4, 2, outstr1);   //float to char  4 numero de caracteres  3 cifras sin espacio
    String cadena = outstr1;   // char to string
    String url = "/emoncms/input/post.json?json={ESP8266_Modbus_Slave:"+ cadena +"}&apikey="+apikey;

     client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" + 
               "Connection: close\r\n\r\n");


        
      
      
      
  
      
     slave.run();  
  }
}

