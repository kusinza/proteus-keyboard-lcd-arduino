
#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
#include <Keypad.h>

const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns
//define the cymbols on the buttons of the keypads
char id[][11]={
  {"2393402015"},{"2393502015"},{"2393602015"},{"2393702015"}
  };
  char finger[][5]={
  {"2012"},{"2013"},{"2014"},{"2015"}
  };
char  finger_temp[]={"201-"};
 char temp[]="239-4/2015";
 int position=0;
 bool finger_print=false;
 bool check=false;
char hexaKeys[ROWS][COLS] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[ROWS] = {7,6,37,38}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {8, 9, 10}; //connect to the column pinouts of the keypad

//initialize an instance of class NewKeypad
static uint32_t timer;

Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 
void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(20, 4);
  Serial.begin(9600);
  // pinMode(10, INPUT);
  // pinMode(9, OUTPUT);
  Serial.println( "Inputing ID number");
  lcd.print("Input ID number");
   lcd.setCursor(0, 2);
   lcd.print("Use #:Enter *:Delete");
   lcd.setCursor(0, 3);
   lcd.print("Use 0:/");
 // Serial.println("turning on the led");
//  digitalWrite(9, HIGH);
}

void loop() {
 
  //lcd.setCursor(0, 2);
  //lcd.print(millis() / 1000);
  
  char customKey = customKeypad.getKey();
  
  if (customKey){
    
   
    if(customKey=='*'){
       lcd.setCursor(position,1 );
        lcd.print(' ');
        if(position>0)
          position--;
    }
    else if(customKey=='#'){
     
      if(finger_print){
         lcd.setCursor(0, 3);
       lcd.print("cheking finger");
        Serial.println("finger input");
       Serial.println(finger_temp);
        lcd.setCursor(0, 0);
     lcd.print("               ");
     lcd.setCursor(0, 0);
      for(int i=0;i<4;i++){
         Serial.println(finger[i]);
         check=true;
         for(int j=0;j<4;j++){
          if(finger_temp[j]!=finger[i][j])
           {
            check=false;
            break;
           }
          }
        if(check){
           lcd.print("PASS");
           finger_print=false;
           Serial.println("finger check pass");
            delay(2000);
            Serial.println("delay 2 seconds");
              lcd.setCursor(0, 0);
              lcd.print("               ");
               lcd.setCursor(0, 0);
              lcd.print("Input ID number");
              lcd.setCursor(0, 3);
              lcd.print("               ");
              lcd.setCursor(0, 3);
              lcd.print("Use 0:/");
              
              
           break;
        }
      }
      if(finger_print)
      {
        lcd.print("NO MACH");
        Serial.println("finger check failed");
      }
       lcd.setCursor(0,1 );
       lcd.print("               ");
       lcd.setCursor(0,1 );
       
       position=0;  
      }
      else{
         lcd.setCursor(0, 3);
       lcd.print("                ");
      lcd.setCursor(0, 3);
       lcd.print("cheking ID");
       
       Serial.println("ID input");
       Serial.println(temp);
      lcd.setCursor(0, 0);
     lcd.print("               ");
     lcd.setCursor(0, 0);
      for(int i=0;i<4;i++){
         Serial.println(id[i]);
         check=true;
         for(int j=0;j<10;j++){
          if(temp[j]!=id[i][j])
           {
            
            check=false;
            break;
           }
          }
        if(check){
          Serial.println("ID check pass");
           lcd.print("Input finger");
           finger_print=true;
           break;
        }
      }
      if(!finger_print)
      {
        lcd.print("Invalid ID");
        Serial.println("ID check failed");
      }
       lcd.setCursor(0,1 );
       lcd.print("               ");
       lcd.setCursor(0,1 );
       
       position=0;  
      }
      
       
      
    }
    else {
      if(position<10 && !finger_print){
      
        temp[position]=customKey;
         lcd.setCursor(position, 1);   
        lcd.print(customKey);
          position++;
       
        
        
      }
       else if(position<4 && finger_print){
       finger_temp[position]=customKey;
       lcd.setCursor(position, 1);    
        lcd.print(customKey);
          position++;
        
        
        
      }
       
    }
  }
  
}
