#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ArduinoJson.h>
#include <ESP_Mail_Client.h>

#define SMTP_HOST "smtp.gmail.com"  
#define SMTP_PORT 465 

// SENDER EMAIL
#define SENDER_EMAIL "tenemaildungdegui"
#define SENDER_PASSWORD "matkhauemaildungdegui"
// RECIPIENT EMAIL
#define RECIPIENT_EMAIL "hieudang2001@gmail.com"

SMTPSession smtp; //SMTP session used for sending
ESP_Mail_Session session; // Declare the session config data
SMTP_Message message; // Declare the message class
/* Variable declaration for temperature threshold for sending email */
bool trigger_Send = true;
String textMsg; //--> Variable to hold all data that will be sent to email
ESPTimeHelper ETH; //--> ESPTimeHelper declaration. This is used to get time data from the server.
 
//=========================NGƯỜI DÙNG TỰ ĐỊNH NGHĨA==========================//
const char* ssid     = "QuangVien_VNPT";  
const char* password =  "hieuluan";
const char* host     = "quang-hieu.000webhostapp.com"; 
//=========================KHAI BÁO CÁC BIẾN TOÀN CỤC===========================//

const char* serverName = "http://quang-hieu.000webhostapp.com/post-esp-data.php";
String apiKeyValue = "tPmAT5Ab3j7F9";

String sensorName = "Độ ẩm đất";
String sensorLocation = "Vườn cây tự động";
String uart_name;
String uart_value;
char c;
int idx=0;
int sta=0,sto=0;
String uartvl;
String httpRequestData="";
  
String path          = "/test/test.json";  
String line;
bool json_ok =0,en=0;
String v08="",v09="",v0A="",v0B="",v0C="",v0D="",v0E="",v0F="",v10="",v11="",v12="",v13="",v14="",v15="",v16="",v17="",v18="",v19=""
,v1A="",v1B="",v1C="",v1D="",v1E="",v1F="",v20="",v21="",v22="",v23="",v3B="",v3C="",v3D="",v3E="",v3F="";
String resultstr;
String section="message";
int count=0;
int wait=0;
//====================================SETUP BAN ĐẦU, CHẠY 1 LẦN DUY NHẤT============//
 
void setup() {  
  pinMode(D1, OUTPUT); 
  pinMode(D0, OUTPUT);
  digitalWrite(D1, HIGH);
  digitalWrite(D0, HIGH);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  //Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    //Serial.print(".");
  }
//  Serial.println("");
//  Serial.print("Connected to WiFi network with IP Address: ");
 //Serial.println(WiFi.localIP());  
 ETH.TZ = 7; // Get time data from server --> GMT+7 
  ETH.DST_MN = 0;  // Daylight Saving Time
  ETH.setClock(ETH.TZ, ETH.DST_MN);
  
  /* Enable the debug via Serial port
   * none debug or 0
   * basic debug or 1 */
  smtp.debug(1);
  smtp.callback(smtpCallback);  // Callback function to get sending results
  /* Set the session config */
  session.server.host_name = SMTP_HOST;
  session.server.port = SMTP_PORT;
  session.login.email = SENDER_EMAIL;
  session.login.password = SENDER_PASSWORD;
  /* Set the message headers */
  message.sender.name = "Smart Watering System";
  message.sender.email = SENDER_EMAIL;
  message.subject = "Warning about water supply system";
  message.addRecipient("Quang Hieu", RECIPIENT_EMAIL);
  /* The Plain text message character set */
  message.text.charSet = "us-ascii";
  /* The content transfer encoding */
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;
  /* The message priority */
  message.priority = esp_mail_smtp_priority::esp_mail_smtp_priority_high;
  /* The Delivery Status Notifications */
  message.response.notify = esp_mail_smtp_notify_success | esp_mail_smtp_notify_failure | esp_mail_smtp_notify_delay;
}
//====================================================================//
void loop() {  
 //Serial.print("Connect to IoT-server");
 //Serial.println(host);
 
   if(WiFi.status()== WL_CONNECTED){
    if(digitalRead(D0)==HIGH){
      digitalWrite(D0,LOW);
    }else{
      digitalWrite(D0,HIGH);
    }
    count++;
    WiFiClient client;
    HTTPClient http;
    
    // Your Domain name with URL path or IP address with path
    http.begin(client, serverName);
    
    // Specify content-type header
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  
  if(Serial.available()>0){
    c=Serial.read();
    if(c=='!'){
      sta=1;
      idx=0;
      uartvl="";
    }
     if(sta==1){
      
      uartvl+=c;
      if(c=='#'){
        sto=1;
      }
    }
  }
  if(sto==1){
    
    sta=0;
    sto=0;
    uart_name="";
    uart_value="";
    uart_name+=uartvl[1];
    uart_name+=uartvl[2];
    uart_value+=uartvl[3];
    uart_value+=uartvl[4];
    if(uartvl[1]=='p'){
       textMsg =  "Your password is ";
       textMsg=textMsg+uartvl[3]+uartvl[4]+uartvl[5]+uartvl[6];
       message.subject = "Password";
      setTextMsg();
      sendTextMsg();
    }
    uartvl="";

    if(uart_name[0]=='h'){
      if(uart_name[1]=='u'){
            httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensorName
                          + "&location=" + sensorLocation + "&value1=" + uart_value
                           + "";
                     
      }
    }else{
      httpRequestData = uart_name + "=" + uart_value + "";
      switch(uart_name[0]){
        case '0':
          switch(uart_name[1]){
            case '8':v08=uart_value;break;
            case '9':v09=uart_value;break;
            case 'A':v0A=uart_value;break;
            case 'B':v0B=uart_value;break;
            case 'C':v0C=uart_value;break;
            case 'D':v0D=uart_value;break;
            case 'E':v0E=uart_value;break;
            case 'F':v0F=uart_value;break;       
          }
          break;
       case '1':
       switch(uart_name[1]){
            case '0':v10=uart_value;break;
            case '1':v11=uart_value;break;
            case '2':v12=uart_value;break;
            case '3':v13=uart_value;break;
            case '4':v14=uart_value;break;
            case '5':v15=uart_value;break;
            case '6':v16=uart_value;break;
            case '7':v17=uart_value;break;
            case '8':v18=uart_value;break;
            case '9':v19=uart_value;break;
            case 'A':v1A=uart_value;break;
            case 'B':v1B=uart_value;break;
            case 'C':v1C=uart_value;break;
            case 'D':v1D=uart_value;break;
            case 'E':v1E=uart_value;break;
            case 'F':v1F=uart_value;break;
       }
       break;
       case '2':
        switch(uart_name[1]){
            case '0':v20=uart_value;break;
            case '1':v21=uart_value;break;
            case '2':v22=uart_value;break;
            case '3':v23=uart_value;break;
       }
       break;
      }
    }
      

    

    // Prepare your HTTP POST request data
    if(httpRequestData!=""){
    int httpResponseCode = http.POST(httpRequestData);
    httpRequestData="";
    }
    if(uart_name[0]=='w'){
      textMsg =  "Maybe your water supply system is no longer working,soil moisture does not increase even though the system has supplied electricity to the water supply system.";
      message.subject = "Warning about water supply system";
      setTextMsg();
      sendTextMsg();
    }
    
  }
  
    http.end();
if(wait<500){
  wait++;
}else{
    if(count>10){
  count=0;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    //Serial.println("Connect to server fail!");  
    return;
  }
                         
      
  //Serial.println("Send request");
  client.print(String("GET ") + path + " HTTP/1.1\r\n" +
  "Host: " + host + "\r\n" + 
  "Connection: keep-alive\r\n\r\n");
  delay(500); // wait for server to respond
//============================================= read response=================================
    while(client.available()){

 //=====================================   
    if(json_ok==false)
    {
      line = client.readStringUntil('\r');
     //Serial.println(line); 
      en=false;
    }
    else
    {  
      line = client.readStringUntil('}'); 
      int find_json = line.indexOf('{');
      
      if(find_json>=0) 
      {resultstr=line+"}"; en=true;}
      json_ok=false;  
    }
//=======================================    
        if (line=="\n") 
        { 
          section="json";
          json_ok=true;
        }
        else 
        {
          section="header";
        }
 
//=========================================        
 
      if(en==true) // Nếu response là json
      {     
         String result = resultstr.substring(1);
         line="";
              
// ===============Parse JSON===============
      int size = 800;
      
      char json[size];
      result.toCharArray(json, size);
      
      DynamicJsonDocument doc(size);
      DeserializationError error = deserializeJson(doc,json);
      //serializeJson(doc, Serial);
      if (error)
      {
        //Serial.print("deserializeJson() failed with code ");
        //Serial.println(error.c_str());
        break;
      }
      else  { 
//===========================================================  
 if(v08!=doc["08"]){v08=doc["08"].as<String>();Serial.print('!'); Serial.print("08");Serial.print((char)v08.toInt()/10); Serial.print((char)v08.toInt()%10); Serial.print('#');delay(200);}
 if(v09!=doc["09"]){v09=doc["09"].as<String>();Serial.print('!'); Serial.print("09");Serial.print((char)v09.toInt()/10); Serial.print((char)v09.toInt()%10); Serial.print('#');delay(200);}
 if(v0A!=doc["0A"]){v0A=doc["0A"].as<String>();Serial.print('!'); Serial.print("0A");Serial.print((char)v0A.toInt()/10); Serial.print((char)v0A.toInt()%10); Serial.print('#');delay(200);}
 if(v0B!=doc["0B"]){v0B=doc["0B"].as<String>();Serial.print('!'); Serial.print("0B");Serial.print((char)v0B.toInt()/10); Serial.print((char)v0B.toInt()%10); Serial.print('#');delay(200);}
 if(v0C!=doc["0C"]){v0C=doc["0C"].as<String>();Serial.print('!'); Serial.print("0C");Serial.print((char)v0C.toInt()/10); Serial.print((char)v0C.toInt()%10); Serial.print('#');delay(200);}
 if(v0D!=doc["0D"]){v0D=doc["0D"].as<String>();Serial.print('!'); Serial.print("0D");Serial.print((char)v0D.toInt()/10); Serial.print((char)v0D.toInt()%10); Serial.print('#');delay(200);}
 if(v0E!=doc["0E"]){v0E=doc["0E"].as<String>();Serial.print('!'); Serial.print("0E");Serial.print((char)v0E.toInt()/10); Serial.print((char)v0E.toInt()%10); Serial.print('#');delay(200);}
 if(v0F!=doc["0F"]){v0F=doc["0F"].as<String>();Serial.print('!'); Serial.print("0F");Serial.print((char)v0F.toInt()/10); Serial.print((char)v0F.toInt()%10); Serial.print('#');delay(200);}
 if(v10!=doc["10"]){v10=doc["10"].as<String>();Serial.print('!'); Serial.print("10");Serial.print((char)v10.toInt()/10); Serial.print((char)v10.toInt()%10); Serial.print('#');delay(200);}
 if(v11!=doc["11"]){v11=doc["11"].as<String>();Serial.print('!'); Serial.print("11");Serial.print((char)v11.toInt()/10); Serial.print((char)v11.toInt()%10); Serial.print('#');delay(200);}
 if(v12!=doc["12"]){v12=doc["12"].as<String>();Serial.print('!'); Serial.print("12");Serial.print((char)v12.toInt()/10); Serial.print((char)v12.toInt()%10); Serial.print('#');delay(200);}
 if(v13!=doc["13"]){v13=doc["13"].as<String>();Serial.print('!'); Serial.print("13");Serial.print((char)v13.toInt()/10); Serial.print((char)v13.toInt()%10); Serial.print('#');delay(200);}
 if(v14!=doc["14"]){v14=doc["14"].as<String>();Serial.print('!'); Serial.print("14");Serial.print((char)v14.toInt()/10); Serial.print((char)v14.toInt()%10); Serial.print('#');delay(200);}
 if(v15!=doc["15"]){v15=doc["15"].as<String>();Serial.print('!'); Serial.print("15");Serial.print((char)v15.toInt()/10); Serial.print((char)v15.toInt()%10); Serial.print('#');delay(200);}
 if(v16!=doc["16"]){v16=doc["16"].as<String>();Serial.print('!'); Serial.print("16");Serial.print((char)v16.toInt()/10); Serial.print((char)v16.toInt()%10); Serial.print('#');delay(200);}
 if(v17!=doc["17"]){v17=doc["17"].as<String>();Serial.print('!'); Serial.print("17");Serial.print((char)v17.toInt()/10); Serial.print((char)v17.toInt()%10); Serial.print('#');delay(200);}
 if(v18!=doc["18"]){v18=doc["18"].as<String>();Serial.print('!'); Serial.print("18");Serial.print((char)v18.toInt()/10); Serial.print((char)v18.toInt()%10); Serial.print('#');delay(200);}
 if(v19!=doc["19"]){v19=doc["19"].as<String>();Serial.print('!'); Serial.print("19");Serial.print((char)v19.toInt()/10); Serial.print((char)v19.toInt()%10); Serial.print('#');delay(200);}
 if(v1A!=doc["1A"]){v1A=doc["1A"].as<String>();Serial.print('!'); Serial.print("1A");Serial.print((char)v1A.toInt()/10); Serial.print((char)v1A.toInt()%10); Serial.print('#');delay(200);}
 if(v1B!=doc["1B"]){v1B=doc["1B"].as<String>();Serial.print('!'); Serial.print("1B");Serial.print((char)v1B.toInt()/10); Serial.print((char)v1B.toInt()%10); Serial.print('#');delay(200);}
 if(v1C!=doc["1C"]){v1C=doc["1C"].as<String>();Serial.print('!'); Serial.print("1C");Serial.print((char)v1C.toInt()/10); Serial.print((char)v1C.toInt()%10); Serial.print('#');delay(200);}
 if(v1D!=doc["1D"]){v1D=doc["1D"].as<String>();Serial.print('!'); Serial.print("1D");Serial.print((char)v1D.toInt()/10); Serial.print((char)v1D.toInt()%10); Serial.print('#');delay(200);}
 if(v1E!=doc["1E"]){v1E=doc["1E"].as<String>();Serial.print('!'); Serial.print("1E");Serial.print((char)v1E.toInt()/10); Serial.print((char)v1E.toInt()%10); Serial.print('#');delay(200);}
 if(v1F!=doc["1F"]){v1F=doc["1F"].as<String>();Serial.print('!'); Serial.print("1F");Serial.print((char)v1F.toInt()/10); Serial.print((char)v1F.toInt()%10); Serial.print('#');delay(200);}
 if(v20!=doc["20"]){v20=doc["20"].as<String>();Serial.print('!'); Serial.print("20");Serial.print((char)v20.toInt()/10); Serial.print((char)v20.toInt()%10); Serial.print('#');delay(200);}
 if(v21!=doc["21"]){v21=doc["21"].as<String>();Serial.print('!'); Serial.print("21");Serial.print((char)v21.toInt()/10); Serial.print((char)v21.toInt()%10); Serial.print('#');delay(200);}
 if(v22!=doc["22"]){v22=doc["22"].as<String>();Serial.print('!'); Serial.print("22");Serial.print((char)v22.toInt()/10); Serial.print((char)v22.toInt()%10); Serial.print('#');delay(200);}
 if(v23!=doc["23"]){v23=doc["23"].as<String>();Serial.print('!'); Serial.print("23");Serial.print((char)v23.toInt()/10); Serial.print((char)v23.toInt()%10); Serial.print('#');delay(200);}
 
 

                          
   }   //end if(error)     
  }//end if(en==true)
 
} // end while client_available 
    } 
}
}     //end wifi available          
}// loop

void setTextMsg() {
  
  message.text.content = textMsg.c_str();
}
// =========================================

// ============= void sendTextMsg() =========
void sendTextMsg() {
 
  message.addHeader("Message-ID: <sws.send@gmail.com>");
  
  
  if (!smtp.connect(&session)) return;

 
  MailClient.sendMail(&smtp, &message);
 
}
// ========================================

// ============= void smtpCallback(SMTP_Status status) ===========
/* Callback function to get the Email sending status */
void smtpCallback(SMTP_Status status) {
  
  if (status.success()) {
    
    struct tm dt;

    for (size_t i = 0; i < smtp.sendingResult.size(); i++) {
      /* Get the result item */
      SMTP_Result result = smtp.sendingResult.getItem(i);
      time_t ts = (time_t)result.timestamp;
      localtime_r(&ts, &dt);

      
    }
    
  }
}
