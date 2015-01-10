# Digi-Xbee-Java---Processing-Arduino

1-10-15

Updated sample send-receive processing sketch as well as the associated arduino sketch to test the interface between Processing and Digi's Java libary.

The Arduino sketch is based on examples from the Desert Home web site - Using the XBee Library Part 3 (http://www.desert-home.com/2013/02/using-xbee-library-part-3.html) for sending packet string data.
The XBee library is a my modifications of the XBee-Arduino library by Andrew Rapp (http://code.google.com/p/xbee-arduino/).  The modified allows you set the API mode of the radios to 1 or 2.  It is called from the setup() of the Arduino sketch as:

Xbee.setAPImode(1);  //for API mode 1 or
Xbee.setAPImode(2);  //for API mode 2.

Default is API mode 2 per the original library.

The examples in the XBee-Arduino library are defaulted to API mode 2 as it was only designed for API mode 2.

