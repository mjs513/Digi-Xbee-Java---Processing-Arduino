/*
 XBee RX test for a Arduino Mega2560 using Serial2 as the XBee serial
 input for a Series 2 XBee.  I took Andrew Rapp's receive example and modified
 it heavily. 

 I wanted to experiment with and better understand how to use his XBee
 library for an actual project.  With the inclusion of support for SoftwareSerial
 so that the XBee can be put on digital pins leaving the Arduino serial port
 available for debugging and status, the library's usefullness shot way up.  These
 changes also allow for the use of the additional serial ports on a Mega2560

 This is a HEAVILY commented example of how to grab a receive packet off the
 air and do something with it using series 2 XBees.  This example also supports
 a remote XBee end device sending analog data.  Series 1 XBees are left as an
 exercise for the student.
 */

 #include <XBee.h>

 XBee xbee = XBee();
 XBeeResponse response = XBeeResponse();
 // create reusable response objects for responses we expect to handle
 ZBRxResponse rx = ZBRxResponse();
 
 XBeeAddress64 Broadcast = XBeeAddress64(0x0013A200, 0x40C04290);
  char Hello[] = "37747D3F,299BBEBD,9755DA3D,061739BB,5B2CE6BC,66CCB0BC,B11B803F,00000000,00000000,00000000,00000000,00000000,00000000,EEEDC141,00000000,B80F0942,003C1CC6,00000000,0000803F,\r";


 char cmd1[9];
 String cmd;
 int j = 0;
 int icount = 0;
 int count = 32;
 
 void setup() { 
   Serial.begin(57600);
   Serial2.begin(57600);
   xbee.setSerial(Serial2);
   xbee.setAPImode(1);
   //Serial.println("starting up yo!");
 }

 void loop() {
   xbee.readPacket();
   if (xbee.getResponse().isAvailable()) {
       getMessage();
   } else if (xbee.getResponse().isError()) {
       // some kind of error happened, I put the stars in so
       // it could easily be found
       Serial.print("************************************* error code:");
       Serial.println(xbee.getResponse().getErrorCode(),DEC);
     }
   if(cmd == "v") {
     for( icount = 0; icount < count; icount++){
       ZBTxRequest zbtx = ZBTxRequest(Broadcast, (uint8_t *)Hello, strlen(Hello));
       xbee.send(zbtx);
     }
     Serial.print(j);Serial.print(" -- ");
     Serial.println("Send data here");
     Serial.println("*****************");
     cmd="";
     j = j +1;}

 }

 //void getMessage(uint8_t *data, uint8_t length){
 void getMessage(){   

       //Serial.print("Frame Type is ");
       //Serial.println(xbee.getResponse().getApiId(), HEX);
       if (xbee.getResponse().getApiId() == ZB_RX_RESPONSE) {
           xbee.getResponse().getZBRxResponse(rx);
          if (rx.getOption() & ZB_PACKET_ACKNOWLEDGED)
              //the sender got an ACK
             Serial.println("packet acknowledged");
         
         cmd = "";
         // this is the actual data you sent
         //Serial.println("Received Data: ");
         for (int i = 0; i < rx.getDataLength(); i++) {
           //print8Bits(rx.getData()[i]);
           cmd1[i] = (char) rx.getData()[i];
           cmd += cmd1[i];
         }
         Serial.println(cmd);
         Serial.println();
       } 
 }

