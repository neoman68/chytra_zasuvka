#include <Manchester.h> // http://mchr3k.github.com/arduino-libs-manchester/

#define DELKA_RF    7

#define RELE_pin    2   // relé RAS-0515 
#define BUZZER_pin  5   // piezosirénka KXG1205C
#define RX_pin      7   // přijímač SRX882
#define RED_LED     9   // červená LED
#define GREEN_LED  10   // zelená LED
#define BUTTON_pin 12   // tlačítko



uint8_t buffer[DELKA_RF];

bool cekaci_rezim = false;
bool nocni_proud = false;


void setup() 
{
  man.setupReceive(RX_pin, MAN_600);
  man.beginReceiveArray(DELKA_RF, buffer);

  pinMode(RX_pin, INPUT);         
  pinMode(BUZZER_pin, OUTPUT);    
  pinMode(GREEN_LED, OUTPUT);     
  pinMode(RED_LED, OUTPUT);       
  pinMode(BUTTON_pin, INPUT);     
  pinMode(RELE_pin, OUTPUT);     
 
  digitalWrite(BUZZER_pin, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(RELE_pin, LOW);
}



void loop() 

{
  if (man.receiveComplete()) 
   { 
     
     if (buffer[6] == 'N')             // je noční proud = nízký tarif
       {
         nocni_proud = true;
         if (cekaci_rezim) 
           {
            cekaci_rezim = false;        
           }
       }
     
     if (buffer[6] == 'V')            // není noční proud = vysoký tarif
       {
         nocni_proud = false;        
       }
    
             
     vyhodnotit();
   
     man.beginReceiveArray(DELKA_RF, buffer);
   }

  kontrola_tlacitka();

}


// ****************************************************************************************
// ****************************************************************************************

void vyhodnotit()
{
  
  if (cekaci_rezim && !nocni_proud)      // rozsvítí RED LED a sepne relé (odpojí spotřebiče)
     {
       digitalWrite(GREEN_LED, LOW);
       digitalWrite(RED_LED, HIGH);
       digitalWrite(RELE_pin, HIGH);
     }

  if (!cekaci_rezim && nocni_proud)     // rozsvítí GREEN LED a vypne relé (připojí spotřebiče)
     {
       digitalWrite(GREEN_LED, HIGH);
       digitalWrite(RED_LED, LOW);
       digitalWrite(RELE_pin, LOW);
     }

  if (!cekaci_rezim && !nocni_proud)    // blikne GREEN LED a vypne relé (připojí spotřebiče)
     {
       digitalWrite(GREEN_LED, LOW);
       digitalWrite(RED_LED, LOW);
       digitalWrite(RELE_pin, LOW);
       digitalWrite(GREEN_LED, HIGH);
       delay(200);
       digitalWrite(GREEN_LED, LOW);
     }
}

// ****************************************************************************************
// ****************************************************************************************

void kontrola_tlacitka()

{
 
 if (digitalRead(BUTTON_pin) == HIGH)
     {
       if (cekaci_rezim)                     // zruší nastavený čekací režím
         {
           beep(1,1000);
           cekaci_rezim = false;
           vyhodnotit(); 
           return;
         }
       
       if (!cekaci_rezim && !nocni_proud)    // nastaví čekací režím na noční proud
         {
           beep(3,300);
           cekaci_rezim = true;
           vyhodnotit();  
           return;
         }

       if (!cekaci_rezim && nocni_proud)     // noční proud jede, není na co čekat
         {
           beep(5, 100);
         }
             
     }
   
  }


// ****************************************************************************************

void beep(int pocet, int delka)             // generování zvukového signálu pípákem

  {
    while (pocet != 0)
      {
       digitalWrite(BEEP_pin, HIGH);    
       delay(delka);
       digitalWrite(BEEP_pin, LOW);
       delay(delka);    
       pocet = pocet - 1;   
      }
  }
  
// ****************************************************************************************
