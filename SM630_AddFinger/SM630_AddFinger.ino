#include <SoftwareSerial.h>
<<<<<<< HEAD
#define DEBUG 0
=======
>>>>>>> ee524c68f8ba8e0b79cc7458ef18a8803ba30a76

SoftwareSerial mySerial(10, 11); // RX, TX

/************************************************************************
Communication Packet
************************************************************************/
byte addFingerPrint0[] = {0x4D, 0x58, 0x10, 0x03, 0x40, 0x00, 0x00, 0xF8}; 
<<<<<<< HEAD
=======

>>>>>>> ee524c68f8ba8e0b79cc7458ef18a8803ba30a76
byte receiveCorrect[] = {0x4D, 0x58, 0x30, 0x01, 0x01, 0xD7}; 
byte operationSuccessAdd[] = {0x4D, 0x58, 0x30, 0x02, 0x40, 0x31, 0x48}; 
byte parameterErrorAdd[] = {0x4D, 0x58, 0x30, 0x02, 0x40, 0x35, 0x4C}; 
byte processFailureAdd[] = {0x4D, 0x58, 0x30, 0x02, 0x40, 0x34, 0x4B}; 
byte timeOutAdd[] = {0x4D, 0x58, 0x30, 0x02, 0x40, 0x33, 0x4A}; 

/************************************************************************
Variables
************************************************************************/
byte respond[6], operation[7], operationSecond[7]; 
byte a,b,c,d,e,f,g,h;
int A = 0;

void setup() 
{
<<<<<<< HEAD
  mySerial.begin(57600);
  Serial.begin(9600);
=======
  mySerial.begin(57600); 
  Serial.begin(9600);
  Serial.println("Add fingerprint at ID #0");
>>>>>>> ee524c68f8ba8e0b79cc7458ef18a8803ba30a76
}

void loop() 
{
  if(A == 0)
  {
    addFinger0();
<<<<<<< HEAD
    if(correctRespond())
      operationStart();
    delay(1000); // a delay for next operation 
=======
    correctRespond();
    operationSuccesful();
>>>>>>> ee524c68f8ba8e0b79cc7458ef18a8803ba30a76
  }
} 

void addFinger0() {
<<<<<<< HEAD
 
  Serial.println("Add fingerprint at ID #0");
  mySerial.write(addFingerPrint0, sizeof(addFingerPrint0));
  
}

bool correctRespond()
{
  while(mySerial.available() <= 0) {}; //wait for incoming data
  delay(10); // give some time for all incoming bytes to be stored into serial buffer
  while(mySerial.available() > 6) // this is to make sure removal of respond from previous command
    mySerial.read();
     
  memset(respond, '\0', 6); // clear respond buffer
  mySerial.readBytes(respond, 6); //store the remaining data to respond buffer 
  
#if DEBUG  
  for(byte x=0; x<sizeof(respond); x++)
    Serial.print(respond[x], HEX);
  Serial.println();
#endif
 
  a = memcmp(receiveCorrect, respond, sizeof(receiveCorrect));
  if (a == 0)
  {
    Serial.println("Receive Correct");
    return 1;
  }
  else
  {
    Serial.println("Error!");
    return 0;
  }
}

void operationStart()
{
  while(mySerial.available() <= 0) {}; //wait for incoming data
  memset(operation, '\0', 7); // clear operation buffer
  mySerial.readBytes(operation, 7); //store data

#if DEBUG  
  for(byte x=0; x<6; x++)
    Serial.print(operation[x], HEX);
  Serial.println();
#endif

  b = memcmp(operationSuccessAdd, operation, sizeof(operationSuccessAdd));
  c = memcmp(processFailureAdd, operation, sizeof(processFailureAdd));
  d = memcmp(parameterErrorAdd, operation, sizeof(parameterErrorAdd));
  e = memcmp(timeOutAdd, operation, sizeof(timeOutAdd)); 

  if (b == 0) 
  {
    Serial.println("First Fingerprint Scanned"); 
    while(mySerial.available() <= 0) {}; //wait for incoming data
    memset(operation, '\0', 7); //clear operation buffer
    mySerial.readBytes(operation, 7); //store data to buffer

#if DEBUG  
  for(byte x=0; x<6; x++)
    Serial.print(operation[x], HEX);
  Serial.println();
#endif
     
    f = memcmp(operationSuccessAdd, operation, sizeof(operationSuccessAdd));
    g = memcmp(processFailureAdd, operation, sizeof(processFailureAdd)); 
    h = memcmp(timeOutAdd, operation, sizeof(timeOutAdd));
    
    if (f == 0)
    {
      Serial.println("Second Fingerprint Scanned");
      Serial.println("Fingerprint Added"); 
      A = 1;
    }
    else 
    {
      if (g == 0)
        Serial.println("Fingerprint Process Failure"); 
      else if (h == 0) 
        Serial.println("Time Out");
        
      Serial.println("Starting new operation!");
    }
      
  }

  else
  {
    if (c == 0) 
     Serial.println("Fingerprint Process Failure");
  
    else if (d == 0) 
     Serial.println("Parameter Error");
  
    else if (e == 0) 
     Serial.println("Time Out");
     
    Serial.println("Starting new operation!");
  }
}

=======
  mySerial.write(addFingerPrint0, sizeof(addFingerPrint0));
  delay(1000);
}

void correctRespond()
{
  for(byte x=0; x<6; x++)
  {
    while(mySerial.available() == 0) {}; 
    respond[x] = mySerial.read(); 

    a = memcmp(receiveCorrect, respond, sizeof(receiveCorrect)); 
    if (x == 5)
    {
      if (a == 0) { Serial.println("Receive Correct"); } 
      else { Serial.println("Error!"); }
    }
  }
}

void operationSuccesful()
{
  for(byte x=0; x<7; x++)
  {
    while(mySerial.available() == 0) {};
    operation[x] = mySerial.read();

    b = memcmp(operationSuccessAdd, operation, sizeof(operationSuccessAdd));
    c = memcmp(processFailureAdd, operation, sizeof(processFailureAdd));
    d = memcmp(parameterErrorAdd, operation, sizeof(parameterErrorAdd));
    e = memcmp(timeOutAdd, operation, sizeof(timeOutAdd)); 

    if (b == 0) 
    {
      Serial.println("First Fingerprint Scanned"); 
      for(byte y=0; y<7; y++)
      {
        while(mySerial.available() == 0) {}; 
        operationSecond[y] = mySerial.read();
        f = memcmp(operationSuccessAdd, operation, sizeof(operationSuccessAdd));
        g = memcmp(processFailureAdd, operation, sizeof(processFailureAdd)); 
        h = memcmp(timeOutAdd, operation, sizeof(timeOutAdd));

        if (y == 6)
        {
          if (f == 0)
          {
            Serial.println("Second Fingerprint Scanned");
            Serial.println("Fingerprint Added"); 
            A = 1;
          }
          else if (g == 0) { Serial.println("Fingerprint Process Failure"); }
          else if (h == 0) { Serial.println("Time Out");}
        }
      }
    }

    else if (c == 0) 
    {
      Serial.println("Fingerprint Process Failure");
    }
    else if (d == 0) 
    {
      Serial.println("Parameter Error");
    } 
    else if (e == 0) 
    {
      Serial.println("Time Out");
    }
  }
}


>>>>>>> ee524c68f8ba8e0b79cc7458ef18a8803ba30a76
