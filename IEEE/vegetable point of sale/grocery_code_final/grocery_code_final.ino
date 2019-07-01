   
    #include <LiquidCrystal.h>
 
    LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
    int count =1;
    int flag =0;
  

    int S2= 2; //Color sensore pin S2 to Arduino pin 2
    int S3= 3; //Color sensor pin S3 to Arduino pin 3
    int outPin = 4; //Color Sensor OUT to Arduino pin 4
    
    int weightPin = A0; //this takes inthe analog value of the weight
    int weightValue = 0; //holds the weight value
    int weight = 0; //intermitent weight value
    int unit_cost=0;
    int total_cost=0; //declaring total
    
    
    int rColorStrength; //measured strength of red color
    int gColorStrength; //measured strength of green color
    int bColorStrength; //measured strength of blue color
    unsigned int pulseWidth; //for measuring color strength using pulseIn command
     
     // button and led pins
     const int buttonPin1 = 6;     // the number of the pushbutton pin
     const int ledPin1 =  38;      // the number of the LED pin
     const int buttonPin2 = 5;     // the number of the pushbutton pin
     const int ledPin2 =  39;      // the number of the LED pin
    // declaring buttton states
    int buttonState1 = 0; 
    int buttonState2 = 0; 
     
    void setup() {
    //initializing buttons and display led
     pinMode(ledPin1, OUTPUT);
     pinMode(ledPin2, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
      
      
      
      
      Serial.begin(115200); //turn on serial port
      
      pinMode(S2, OUTPUT); //S2 and S3 are outputs and used to tell
      pinMode(S3, OUTPUT); //arduino which color to measure
      pinMode(outPin, INPUT); //This is the pin we read the color from
      
       // read the weight value from the weight sensor:
      //weightValue = analogRead(weightPin);
      
      
      // initialization display...
        lcd.clear();                    //clear the LCD during setup
        lcd.begin(20,4);                //define the columns (16) and rows (2
             lcd.print("SMART GREEN-GROCERY");          //print...
  //delay(1000);                   //wait...
  lcd.setCursor(0,1);            //move the cursor to the 2nd line
  lcd.print("IEEE EXPO 2015");          //print...
  //delay(1000);                   //wait...
  lcd.setCursor(0,2);
  lcd.print("P.NDUNGU &K.MURIUNGI");         //print with extra spaces to overwrite
  //delay(1000);                   //wait...
  lcd.setCursor(0,3);           
  lcd.print("STRATHMOREUNIVERSITY");             //Make It becomes Makes Us

  delay(1000);
  lcd.home();  
                                                                    
              

    }
     
void loop() {
     // looping it to wait for commands
      
                         
    buttonState1 = digitalRead(buttonPin1);
    
   if (buttonState1 == HIGH) {
    // turn LED on:
     digitalWrite(ledPin1, HIGH);
     digitalWrite(buttonPin1, HIGH);
    
     lcd.clear(); 
    // read the weight value from the weight sensor:
       weight= analogRead(weightPin);
      weightValue = map( weight ,120, 1023, 0, 100);
    //Lets start by reading Red Component of the Color
      // S2 and S3 should be set LOW
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      
      pulseWidth =  pulseIn(outPin, LOW); //Measure raw pulsewidth coming from color sensor outpin
      
      rColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      rColorStrength = (255- rColorStrength); //reverse so that large number means strong color
      
      
      //Lets read Green Component of the Color
      // S2 and S3 should be set HIGH
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      
      pulseWidth =  pulseIn(outPin, LOW); //Measure raw pulsewidth coming from color sensor outpin
      
      gColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      gColorStrength = (255- gColorStrength); //reverse so that large number means strong color
      
      //gColorStrength=gColorStrength + 2;
      
      //Lets read Blue Component of the Color
      // S2 and S3 should be set LOW and HIGH Respectively
      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      
      pulseWidth =  pulseIn(outPin, LOW); //Measure raw pulsewidth coming from color sensor outpin
      
      bColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      bColorStrength = (255- bColorStrength); //reverse so that large number means strong color
    
    if(rColorStrength>gColorStrength && gColorStrength>bColorStrength) {
      
       rColorStrength = 255;
       gColorStrength = gColorStrength/2;
       bColorStrength = 0;
    }
      if(rColorStrength>bColorStrength && bColorStrength>gColorStrength) {
      
       rColorStrength = 255;
       bColorStrength = bColorStrength/2;
       gColorStrength = 0;
    }
      if(gColorStrength>rColorStrength && rColorStrength>bColorStrength) {
      
       gColorStrength = 255;
       rColorStrength = rColorStrength/2;
       bColorStrength = 0;
    }
       if(gColorStrength>bColorStrength && bColorStrength>rColorStrength) {
      
       gColorStrength = 255;
       bColorStrength = bColorStrength/2;
       rColorStrength = 0;
    }
       if(bColorStrength>rColorStrength && rColorStrength>gColorStrength) {
      
       bColorStrength = 255;
       rColorStrength = rColorStrength/2;
       gColorStrength = 0;
    }
        if(bColorStrength>gColorStrength && gColorStrength>rColorStrength) {
      
       bColorStrength = 255;
       gColorStrength = gColorStrength/2;
       rColorStrength = 0;
    }
    
    // to make product selection first case

         if(gColorStrength>0 && gColorStrength<127) {
      // now we can do annother if statement for selectivity
                    if(rColorStrength<1  && gColorStrength>122)
                   //if( gColorStrength>122)
                   {
                                int unit_cost =2;
                                Serial.print(count);
                                Serial.print(" , ");
                                Serial.print("KALES");
                                Serial.print(" , ");
                                Serial.print(weightValue);
                                Serial.print(" , "); 
                                Serial.print(unit_cost);
                                Serial.print(" , ");
                               total_cost =unit_cost*weightValue;
                                Serial.print(total_cost);
                                Serial.print(" , ");
                                
                                           lcd.clear(); 
                                          lcd.setCursor(0,0);
                                          lcd.print(" PRODUCT   ");
                                          lcd.print(count);
                                          lcd.print(" , ");
                                          lcd.setCursor(0,1);
                                          lcd.print(" KALES, ");
                                          lcd.setCursor(0,2);
                                          lcd.print("weight");
                                          lcd.print(weightValue);
                                          lcd.println(" , ");
                                          lcd.setCursor(0,3); 
                                          lcd.print("PRICE = , ");
                                          lcd.print(total_cost);
                                          lcd.println(" , ");
                                          flag=1;
                                          digitalWrite(ledPin2, HIGH);
                                          delay(150);
                                          digitalWrite(ledPin2, LOW);
     
                                }
                      if(bColorStrength<1){
                                int unit_cost =3;
                                Serial.print(count);
                                Serial.print(" , ");
                                Serial.print("BANANAS");
                                Serial.print(" , ");
                                Serial.print(weightValue);
                                Serial.print(" , "); 
                                Serial.print(unit_cost);
                                Serial.print(" , ");
                               total_cost =unit_cost*weightValue;
                                Serial.print(total_cost);
                                Serial.println(" , ");
                                
                                           lcd.clear(); 
                                          lcd.setCursor(0,0);
                                          lcd.print(" PRODUCT   ");
                                          lcd.print(count);
                                          lcd.print(" , ");
                                          lcd.setCursor(0,1);
                                          lcd.print(" BANANAS, ");
                                          lcd.setCursor(0,2);
                                          lcd.print("weight");
                                          lcd.print(weightValue);
                                          lcd.println(" , ");
                                          lcd.setCursor(0,3); 
                                          lcd.print("PRICE = , ");
                                          lcd.print(total_cost);
                                          lcd.println(" , ");
                                           flag=1;
                                           digitalWrite(ledPin2, HIGH);
                                          delay(150);
                                          digitalWrite(ledPin2, LOW);
     
                             }

          }
      // if conditional statement 2
      if(bColorStrength>0 && bColorStrength<127) {
                         int unit_cost =3;
                        Serial.print(count);
                        Serial.print(" , ");
                        Serial.print("TOMATOES");
                        Serial.print(" , ");
                        Serial.print(weightValue);
                        Serial.print(" , "); 
                        Serial.print(unit_cost);
                        Serial.print(" , ");
                       total_cost =unit_cost*weightValue;
                        Serial.print(total_cost);
                        Serial.println(" , ");
                        
                                   lcd.clear(); 
                                  lcd.setCursor(0,0);
                                  lcd.print(" PRODUCT   ");
                                  lcd.print(count);
                                  lcd.print(" , ");
                                  lcd.setCursor(0,1);
                                  lcd.print(" TOMATOES, ");
                                  lcd.setCursor(0,2);
                                  lcd.print("weight");
                                  lcd.print(weightValue);
                                  lcd.println(" , ");
                                  lcd.setCursor(0,3); 
                                  lcd.print("PRICE = , ");
                                  lcd.print(total_cost);
                                  lcd.println(" , "); 
                                   flag=1;   
                                  digitalWrite(ledPin2, HIGH);
                                          delay(150);
                                          digitalWrite(ledPin2, LOW);
      
                      
    }
    // if conditional statement 3
      if(rColorStrength>0 && rColorStrength<127) {
                         int unit_cost =2;
                        Serial.print(count);
                        Serial.print(" , ");
                        Serial.print("ONIONS");
                        Serial.print(" , ");
                        Serial.print(weightValue);
                        Serial.print(" , "); 
                        Serial.print(unit_cost);
                        Serial.print(" , ");
                       total_cost =unit_cost*weightValue;
                        Serial.print(total_cost);
                        Serial.println(" , ");
                        
                                   lcd.clear(); 
                                  lcd.setCursor(0,0);
                                  lcd.print(" PRODUCT   ");
                                  lcd.print(count);
                                  lcd.print(" , ");
                                  lcd.setCursor(0,1);
                                  lcd.print(" ONIONS, ");
                                  lcd.setCursor(0,2);
                                  lcd.print("weight");
                                  lcd.print(weightValue);
                                  lcd.println(" , ");
                                  lcd.setCursor(0,3); 
                                  lcd.print("PRICE = , ");
                                  lcd.print(total_cost);
                                  lcd.println(" , "); 
                                   flag=1;   
                                   digitalWrite(ledPin2, HIGH);
                                   delay(150);
                                    digitalWrite(ledPin2, LOW);
                   
    }
    delay(2000);
  
      }
         digitalWrite(buttonPin1, LOW);
         digitalWrite(ledPin1, LOW);
      
    count++;
//}    
}
