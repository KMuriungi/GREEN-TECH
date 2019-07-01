    //The Green-Tech System
    //Green-Grocery Point of Sale System
    //Code Version 1.0 --- IEEE Expo in Strathmore 15/16 with P.K.Ndung'u
    //Code Version 2.0 --- Moi University Expo 15/16 with P.K.Ndung'u
    //Code Version 3.0 --- IEEE Expo in Strathmore 16/17 with E.O.Okero - 20th Jan 2017
    //Code Version 3.0 By Kithinji Muriungi & Okero Esborn
    //3.0 : Presented in Strathmore University 17th & 18th Nov 2016
    //IEEE ESEK
    //Theme : Engineering Solutions to Expand Kenya's Self Reliance
      
    
    #include <LiquidCrystal.h> //Library ya LCD
 
    LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10); // Initializing LCD
    int count =1; // Counter that enables program to cycle through the program properly
    int flag =0;  // To ensure everything starts at ZERO

     // button pins
     const int buttonPin1 = 6;     // the number of the pushbutton pin
     const int buttonPin2 = 5;     // the number of the pushbutton pin

    // declaring buttton states
    int buttonState1 = 0; 
    int buttonState2 = 0;
    
     // led pins
     const int ledPin1 =  38;      // the number of the LED pin
     const int ledPin2 =  39;      // the number of the LED pin

    //Weight Sensor Pin
    int weightPin = A0; //this takes inthe analog value of the weight : From the Improvised Potentiometer
    int weightValue = 0; //holds the weight value
    int weight = 0; //intermitent weight value

    //Cost Declaration
    int unit_cost=0; // Initial Unit Cost
    int total_cost=0; // Declaring Total Cost

     //Color Sensor Pins ****TCS3200****
    int S2= 2; //Color sensor pin S2 to Arduino pin 2
    int S3= 3; //Color sensor pin S3 to Arduino pin 3
    int outPin = 4; //Color Sensor OUT to Arduino pin 4

    //Color Value : (Primary Colors)
    int rColorStrength; //measured strength of red color
    int gColorStrength; //measured strength of green color
    int bColorStrength; //measured strength of blue color
    
    unsigned int pulseWidth; //for measuring color strength using pulseIn command
     
    void setup() {
      
      Serial.begin(115200); //turn on serial port
      
    //initializing display led
     pinMode(ledPin1, OUTPUT);
     pinMode(ledPin2, OUTPUT);
     
    // initializing the pushbutton pin as an input:
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);

      /*
      S2 and S3 are OUTPUTS and used to tell
      arduino which color to measure
      */
      pinMode(S2, OUTPUT); 
      pinMode(S3, OUTPUT);
       
      pinMode(outPin, INPUT); //This is the pin we read the color from
      
       // read the weight value from the weight sensor:
      //weightValue = analogRead(weightPin);
//      pinMode(weightPin,INPUT);
      
      
      // initialization display...
        lcd.clear();                    //clear the LCD during setup
        lcd.begin(20,4);                //define the columns (20) and rows (4)
        lcd.print("SMART GREEN-GROCERY");    //print...
      delay(10);                   //wait...
      lcd.setCursor(4,1);            //move the cursor to the 2nd line
      lcd.print("\"GREEN-TECH\"");          //print...
      delay(10);                   //wait...
      lcd.setCursor(0,2);
      lcd.print("K.MURIUNGI & E.OKERO");         //print with extra spaces to overwrite
      delay(10);                   //wait...
      lcd.setCursor(3,3);           
      lcd.print("MOI UNIVERSITY");             
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
       weight= analogRead(weightPin); // Reads the Weight as Analog
      weightValue = map( weight ,74, 1023, 0, 20);
    //Start by reading Red Component of the Color
      // S2 and S3 should be set LOW
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      
      pulseWidth =  pulseIn(outPin, LOW); //Measure raw pulsewidth coming from color sensor outpin
      
      rColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      rColorStrength = (255- rColorStrength); //reverse so that large number means strong color
      
      
      //Read Green Component of the Color
      // S2 and S3 should be set HIGH
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      
      pulseWidth =  pulseIn(outPin, LOW); //Measure raw pulsewidth coming from color sensor outpin
      
      gColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      gColorStrength = (255- gColorStrength); //reverse so that large number means strong color
      
      //gColorStrength=gColorStrength + 2;
      
      //Read Blue Component of the Color
      // S2 and S3 should be set LOW and HIGH Respectively
      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      
      pulseWidth =  pulseIn(outPin, LOW); //Measure raw pulsewidth coming from color sensor outpin
      
      bColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      bColorStrength = (255- bColorStrength); //reverse so that large number means strong color

      /*------------------------------------------------------------------------------------------
      ----------------------------------------DECISION LOOP---------------------------------------
      -------------------------------------------------------------------------------------------*/

    // Red=High
    //Green = Middle
    //Blue = Low
    if(rColorStrength>gColorStrength && gColorStrength>bColorStrength) {
      
       rColorStrength = 255;
       gColorStrength = gColorStrength/2;
       bColorStrength = 0;
    }

      // Red=High
    //Green = Low
    //Blue = Middle
      if(rColorStrength>bColorStrength && bColorStrength>gColorStrength) {
      
       rColorStrength = 255;
       bColorStrength = bColorStrength/2;
       gColorStrength = 0;
    }

    // Red=Middle
    //Green = High
    //Blue = Low
      if(gColorStrength>rColorStrength && rColorStrength>bColorStrength) {
      
       gColorStrength = 255;
       rColorStrength = rColorStrength/2;
       bColorStrength = 0;
    }

    // Red = Low
    //Green = High
    //Blue = Middle
       if(gColorStrength>bColorStrength && bColorStrength>rColorStrength) {
      
       gColorStrength = 255;
       bColorStrength = bColorStrength/2;
       rColorStrength = 0;
    }

    // Red = Middle
    //Green = Low
    //Blue = High
       if(bColorStrength>rColorStrength && rColorStrength>gColorStrength) {
      
       bColorStrength = 255;
       rColorStrength = rColorStrength/2;
       gColorStrength = 0;
    }

    // Red = Low
    //Green = Middle
    //Blue = High
        if(bColorStrength>gColorStrength && gColorStrength>rColorStrength) {
      
       bColorStrength = 255;
       gColorStrength = gColorStrength/2;
       rColorStrength = 0;
    }

    
    // to make product selection first case

         if(gColorStrength>0 && gColorStrength<127) {
          //Green is greater than 0 but less than 127
      // now we can do another if statement for selectivity
                    if(rColorStrength<1  && gColorStrength>122)
                   //if( gColorStrength>122)
                   {
                                int unit_cost =1.1;
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
                                          delay(500);
                                          digitalWrite(ledPin2, LOW);
     
                                }
                      if(bColorStrength<1){
                                int unit_cost =1.8;
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
                                          delay(500);
                                          digitalWrite(ledPin2, LOW);
     
                             }

          }
      // if conditional statement 2
      if(bColorStrength>0 && bColorStrength<127) {
                         int unit_cost =1.5;
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
                                          delay(500);
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
                                   delay(500);
                                    digitalWrite(ledPin2, LOW);
                   
    }
    delay(1000);
  
      }
         digitalWrite(buttonPin1, LOW);
         digitalWrite(ledPin1, LOW);
      
    count++;
//}    
}
