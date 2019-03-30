
#include <Manchester.h>  // http://mchr3k.github.com/arduino-libs-manchester/

#define TX_pin     3     // pin D3 STX882
#define OPTO_pin   2     // pin D2 detektor napětí
#define DELKA_RF   7     // delka matice dat

uint8_t buffer[DELKA_RF] = {7,'T','A','R','I','F','V'};  


void setup() 
{
 pinMode(OPTO_pin, INPUT);               
 man.setupTransmit(TX_pin, MAN_600);         
}


void loop() 
{
 if (digitalRead(OPTO_pin) == HIGH)
   {
    data[6] = 'N';
   }
 else
   {
    data[6] = 'V';
   }
   
 man.transmitArray(DELKA_RF, buffer);
   
 delay(10000);
}
