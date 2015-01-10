/**

 */

//package com.rapplogic.xbee.examples.zigbee;
import processing.serial.*; 

import com.digi.xbee.api.RemoteXBeeDevice;
import com.digi.xbee.api.XBeeDevice;
import com.digi.xbee.api.XBeeNetwork;
import com.digi.xbee.api.exceptions.XBeeException;
import com.digi.xbee.api.utils.HexUtils;
import com.digi.xbee.api.listeners.IDataReceiveListener;
import com.digi.xbee.api.models.XBeeMessage;
 

String version = "1.02";

// *** REPLACE WITH THE SERIAL PORT (COM PORT) FOR YOUR LOCAL XBEE ***
String mySerialPort = "COM5";

String DATA_TO_SEND = "v";
String REMOTE_NODE_IDENTIFIER = "END_ROUTER_1";
int BAUD_RATE = 57600;
int packetCnt = 0;
int count = 32;

XBeeDevice myDevice = new XBeeDevice(mySerialPort, BAUD_RATE);
byte[] dataToSend = DATA_TO_SEND.getBytes();
XBeeNetwork xbeeNetwork;
RemoteXBeeDevice remoteDevice;

void setup() {

  size(800, 230); // screen size
  smooth(); // anti-aliasing for graphic display

    System.out.println(" +--------------------------------------+");
    System.out.println(" |  XBee Java Library Send Data Sample  |");
    System.out.println(" +--------------------------------------+\n");
    
    try {
      myDevice.open();
      
      // Obtain the remote XBee device from the XBee network.
      xbeeNetwork = myDevice.getNetwork();
      remoteDevice = xbeeNetwork.discoverDevice(REMOTE_NODE_IDENTIFIER);
      if (remoteDevice == null) {
        System.out.println("Couldn't find the remote XBee device with '" + REMOTE_NODE_IDENTIFIER + "' Node Identifier.");
        System.exit(1);
      }
      myDevice.addDataListener(new MyDataReceiveListener());
      
      System.out.println("\n>> Waiting for data...");
      
    } catch (XBeeException e) {
      System.out.println("Error ");
      e.printStackTrace();
      System.exit(1);
    } 
}    
    
// draw loop executes continuously
void draw() {
    if(packetCnt == count) {
	try {      
	   myDevice.sendData(remoteDevice, dataToSend);
           packetCnt = 0;
           println("DATA REQUEST SENT");
	} catch (XBeeException e) {
	    System.out.println("Error");
	    e.printStackTrace();
	    System.exit(1);
	} 
    } else {
	packetCnt = packetCnt + 1;
    }
}


