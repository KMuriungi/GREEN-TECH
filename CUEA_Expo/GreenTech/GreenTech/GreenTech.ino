    //The Green-Tech System
    //Green-Grocery Point of Sale System
    //Code Version 1.0 --- IEEE Expo in Strathmore 15/16 with P.K.Ndung'u
    //Code Version 2.0 --- Moi University Expo 15/16 with P.K.Ndung'u
    //Code Version 3.0 --- IEEE Expo in Strathmore 16/17 with E.O.Okero - 20th Jan 2017
    //Code Version 4.0 --- 15th Universities Education Exhibition & Disclosure
    //4.0 : Presented in Catholic University of Eastern Africa (CUEA) on 27th & 3rd March 2017
    //Commission for University Education
    //Theme : Positioning Universities in Innovation, Entrepreneurship & Technology Transfer in the Digital Era
      
    
    #include <LiquidCrystal.h> //Library ya LCD
 
    LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10); // Initializing LCD
    int productCount = 1; // productCounter that enables program to cycle through the program properly
    int flag = 0;  // To ensure everything starts at ZERO

     // button pins
      /*
      In the code, buttonPin1 is referring to the Button on the far end 
      followed by the Green led then buttonPin2 and the last one is Orange Led.

      Since ButtonPin1 isn't working we are replacing the buttonPin1 with
      buttonPin2
      &
      the led still remains the same 
     */
     //const int buttonPin1 = 5;     // the number of the pushbutton pin
     //const int buttonPin2 = 6;     // the number of the pushbutton pin

     const int buttonPin1 = 6;     // the number of the pushbutton pin
     const int buttonPin2 = 5;     // the number of the pushbutton pin

    // declaring buttton states
    int buttonState1 = 0; 
    int buttonState2 = 0;
    
     // led pins
     const int ledPin1_Green =  38;      // the number of the LED pin
     const int ledPin2_Yellow =  39;      // the number of the LED pin

    //Weight Sensor Pin
    int weightPin = A0; //this takes inthe analog value of the weight : From the Improvised Potentiometer
    int weightValue = 0; //holds the weight value
    int weight = 0; //intermitent weight value

    //Cost Declaration
    int unitCost = 0; // Initial Unit Cost
    int totalCost = 0; // Declaring Total Cost

     //Color Sensor Pins ****TCS3200****
    int S2 = 2; //Color sensor pin S2 to Arduino pin 2
    int S3 = 3; //Color sensor pin S3 to Arduino pin 3
    int ColorSensorOutPin = 4; //Color Sensor OUT to Arduino pin 4

    //Color Value : (Primary Colors)
    int rColorStrength; //measured strength of red color
    int gColorStrength; //measured strength of green color
    int bColorStrength; //measured strength of blue color
    
    unsigned int pulseWidth; //for measuring color strength using pulseIn command
     
    void setup() 
    {
      
      Serial.begin(115200); //turn on serial port
      
    //initializing display led
     pinMode(ledPin1_Green, OUTPUT);
     pinMode(ledPin2_Yellow, OUTPUT);
     
    // initializing the pushbutton pin as an input:
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);

      /*
      S2 and S3 are OUTPUTS and used to tell
      arduino which color to measure
      */
      pinMode(S2, OUTPUT); 
      pinMode(S3, OUTPUT);
       
      pinMode(ColorSensorOutPin, INPUT); //This is the pin we read the color from
      
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
     
void loop() 
{
     // looping it to wait for commands
            
    buttonState1 = digitalRead(buttonPin1);

    buttonState2 = digitalRead(buttonPin2);
    
   if (buttonState1 == HIGH) {
    // turn LED on:
     digitalWrite(ledPin1_Green, HIGH);
     digitalWrite(buttonPin1, HIGH);
    
     lcd.clear(); 
    // read the weight value from the weight sensor:
       weight= analogRead(weightPin); // Reads the Weight as Analog
      weightValue = map( weight ,74, 1023, 0, 20);
    //Start by reading Red Component of the Color
      // S2 and S3 should be set LOW
      digitalWrite(S2, LOW);
      digitalWrite(S3, LOW);
      
      pulseWidth =  pulseIn(ColorSensorOutPin, LOW); //Measure raw pulsewidth coming from color sensor ColorSensorOutPin
      
      rColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      rColorStrength = (255- rColorStrength); //reverse so that large number means strong color
      
      
      //Read Green Component of the Color
      // S2 and S3 should be set HIGH
      digitalWrite(S2, HIGH);
      digitalWrite(S3, HIGH);
      
      pulseWidth =  pulseIn(ColorSensorOutPin, LOW); //Measure raw pulsewidth coming from color sensor ColorSensorOutPin
      
      gColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      gColorStrength = (255- gColorStrength); //reverse so that large number means strong color
      
      //gColorStrength=gColorStrength + 2;
      
      //Read Blue Component of the Color
      // S2 and S3 should be set LOW and HIGH Respectively
      digitalWrite(S2, LOW);
      digitalWrite(S3, HIGH);
      
      pulseWidth =  pulseIn(ColorSensorOutPin, LOW); //Measure raw pulsewidth coming from color sensor ColorSensorOutPin
      
      bColorStrength = pulseWidth/400. -1; //normalize number to number between 0 and 255
      
      bColorStrength = (255- bColorStrength); //reverse so that large number means strong color

      /*------------------------------------------------------------------------------------------
       * -----------------------------------------------------------------------------------------
       * -----------------------------------------------------------------------------------------
       * ----------------------------------------DECISION LOOP------------------------------------
       * -----------------------------------------------------------------------------------------
       * -----------------------------------------------------------------------------------------
       * -----------------------------------------------------------------------------------------*/

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

        // if(gColorStrength>0 && gColorStrength<127) {
          //Green is greater than 0 but less than 127
      // now we can do another if statement for selectivity
                    if(rColorStrength<1  && gColorStrength>122)
                   //if( gColorStrength>122)
                   {
                                int unitCost =1.1;
                                int kalesFactor = 15;
                                int realWeightVal = weightValue * kalesFactor;
                                totalCost = (unitCost * realWeightVal) / kalesFactor;
                                
                                
                                Serial.print("PRODUCT REF : ");
                                Serial.print(productCount);
                                Serial.println("PRODUCT  =  KALES ");
                                Serial.println("WEIGHT  =  ");
                                Serial.print(realWeightVal);
                                Serial.print("  Gms");
                                Serial.print("PRICE  =  ");
                                Serial.print(totalCost);
                                Serial.print("  Kshs");
                                
                                          lcd.clear(); 
                                          lcd.setCursor(0,0);
                                          lcd.print("PRODUCT REF : ");
                                          lcd.print(productCount);
                                          lcd.setCursor(0,1);
                                          lcd.print("PRODUCT  =  KALES ");
                                          lcd.setCursor(0,2);
                                          lcd.print("WEIGHT  =  ");
                                          lcd.print(realWeightVal);
                                          lcd.print("  Gms");
                                          lcd.setCursor(0,3); 
                                          lcd.print("PRICE  =  ");
                                          lcd.print(totalCost);
                                          lcd.print("  Kshs");
                                          flag=1;
                                                  digitalWrite(ledPin2_Yellow, HIGH);
                                                  delay(500);
                                                  digitalWrite(ledPin2_Yellow, LOW);
        
                                                  delay(20000);
                                                   digitalWrite(buttonPin1, LOW);
                                                   digitalWrite(ledPin1_Green, LOW);
                                                   lcd.clear();
                                                   lcd.setCursor(3,1);
                                                   lcd.print("PLACE THE NEXT");
                                                   lcd.setCursor(0,2);
                                                   lcd.print("   ITEM / PRODUCT   ");
                                                   lcd.setCursor(3,3);
                                                   lcd.print("ON THE COUNTER");

                                                   delay(5000);

                                                           digitalWrite(ledPin2_Yellow, HIGH);
                                                           lcd.clear();
                                                           lcd.setCursor(3,0);
                                                           lcd.print("THANK YOU FOR");
                                                           lcd.setCursor(1,1);
                                                           lcd.print("SHOPPING WITH US.");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("**COME BACK AGAIN**");
                                                           
                                                           delay(5000);
                                                           
                                                           lcd.clear();
                                                           lcd.setCursor(0,0);
                                                           lcd.print("         **         ");
                                                           lcd.setCursor(0,1);
                                                           lcd.print("******* NEXT *******");
                                                           lcd.setCursor(0,2);
                                                           lcd.print("***** CUSTOMER *****");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("         **         ");

                                }
                      if(gColorStrength>0 && gColorStrength<127 ) { //&& bColorStrength<1
          //Green is greater than 0 but less than 127
      // now we can do another if statement for selectivity
                                int unitCost =1.8;

                                int bananaFactor = 15;
                                int realWeightVal = weightValue * bananaFactor;
                                totalCost = (unitCost * realWeightVal) / bananaFactor;
                                
                                
                                Serial.print("PRODUCT REF : ");
                                Serial.print(productCount);
                                Serial.println("PRODUCT = BANANA ");
                                Serial.println("WEIGHT  =  ");
                                Serial.print(realWeightVal);
                                Serial.print("  Gms");
                                Serial.print("PRICE  =  ");
                                Serial.print(totalCost);
                                Serial.print("  Kshs");
                                
                                          lcd.clear(); 
                                          lcd.setCursor(0,0);
                                          lcd.print("PRODUCT REF : ");
                                          lcd.print(productCount);
                                          lcd.setCursor(0,1);
                                          lcd.print("PRODUCT = BANANAS ");
                                          lcd.setCursor(0,2);
                                          lcd.print("WEIGHT  =  ");
                                          lcd.print(realWeightVal);
                                          lcd.print("  Gms");
                                          lcd.setCursor(0,3); 
                                          lcd.print("PRICE  =  ");
                                          lcd.print(totalCost);
                                          lcd.print("  Kshs");
                                          flag=1;
                                                  digitalWrite(ledPin2_Yellow, HIGH);
                                                  delay(500);
                                                  digitalWrite(ledPin2_Yellow, LOW);
        
                                                  delay(20000);
                                                   digitalWrite(buttonPin1, LOW);
                                                   digitalWrite(ledPin1_Green, LOW);
                                                   lcd.clear();
                                                   lcd.setCursor(3,1);
                                                   lcd.print("PLACE THE NEXT");
                                                   lcd.setCursor(0,2);
                                                   lcd.print("   ITEM / PRODUCT   ");
                                                   lcd.setCursor(3,3);
                                                   lcd.print("ON THE COUNTER");

                                                   delay(5000);

                                                           digitalWrite(ledPin2_Yellow, HIGH);
                                                           lcd.clear();
                                                           lcd.setCursor(3,0);
                                                           lcd.print("THANK YOU FOR");
                                                           lcd.setCursor(1,1);
                                                           lcd.print("SHOPPING WITH US.");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("**COME BACK AGAIN**");
                                                           
                                                           delay(5000);
                                                           
                                                           lcd.clear();
                                                           lcd.setCursor(0,0);
                                                           lcd.print("         **         ");
                                                           lcd.setCursor(0,1);
                                                           lcd.print("******* NEXT *******");
                                                           lcd.setCursor(0,2);
                                                           lcd.print("***** CUSTOMER *****");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("         **         ");
                                              
                             }
      // if conditional statement 2
      if(bColorStrength>0 && bColorStrength<127 ) { //&& gColorStrength<1
        
                         int unitCost =1.5;
                         
                        int tomatoFactor = 15;
                                int realWeightVal = weightValue * tomatoFactor;
                                totalCost = (unitCost * realWeightVal) / tomatoFactor;
                                
                                
                                Serial.print("PRODUCT REF : ");
                                Serial.print(productCount);
                                Serial.println("PRODUCT = TOMATOES ");
                                Serial.println("WEIGHT  =  ");
                                Serial.print(realWeightVal);
                                Serial.print("  Gms");
                                Serial.print("PRICE  =  ");
                                Serial.print(totalCost);
                                Serial.print("  Kshs");
                                
                                          lcd.clear(); 
                                          lcd.setCursor(0,0);
                                          lcd.print("PRODUCT REF : ");
                                          lcd.print(productCount);
                                          lcd.setCursor(0,1);
                                          lcd.print(" PRODUCT = TOMATOES");
                                          lcd.setCursor(0,2);
                                          lcd.print("WEIGHT  =  ");
                                          lcd.print(realWeightVal);
                                          lcd.print("  Gms");
                                          lcd.setCursor(0,3); 
                                          lcd.print("PRICE  =  ");
                                          lcd.print(totalCost);
                                          lcd.print("  Kshs");
                                          flag=1;
                                                  digitalWrite(ledPin2_Yellow, HIGH);
                                                  delay(500);
                                                  digitalWrite(ledPin2_Yellow, LOW);
        
                                                  delay(20000);
                                                   digitalWrite(buttonPin1, LOW);
                                                   digitalWrite(ledPin1_Green, LOW);
                                                   lcd.clear();
                                                   lcd.setCursor(3,1);
                                                   lcd.print("PLACE THE NEXT");
                                                   lcd.setCursor(0,2);
                                                   lcd.print("      PRODUCT      ");
                                                   lcd.setCursor(3,3);
                                                   lcd.print("ON THE COUNTER");

                                                   delay(9000);

                                                           digitalWrite(ledPin2_Yellow, HIGH);
                                                           lcd.clear();
                                                           lcd.setCursor(3,0);
                                                           lcd.print("THANK YOU FOR");
                                                           lcd.setCursor(1,1);
                                                           lcd.print("SHOPPING WITH US.");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("**COME BACK AGAIN**");
                                                           
                                                           delay(9000);
                                                           
                                                           lcd.clear();
                                                           lcd.setCursor(0,0);
                                                           lcd.print("         **         ");
                                                           lcd.setCursor(0,1);
                                                           lcd.print("******* NEXT *******");
                                                           lcd.setCursor(0,2);
                                                           lcd.print("***** CUSTOMER *****");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("         **         ");
                                              
                      
    } // Ends Tomato Loop
    
    // if conditional statement 3
      if(rColorStrength>0 && rColorStrength<127 ) { //&& gColorStrength<1
        
                         int unitCost =2;
                         
                        int onionFactor = 15;
                                int realWeightVal = weightValue * onionFactor;
                                totalCost = (unitCost * realWeightVal) / onionFactor;
                                
                                
                                Serial.print("PRODUCT REF : ");
                                Serial.print(productCount);
                                Serial.println("PRODUCT = ONIONS ");
                                Serial.println("WEIGHT  =  ");
                                Serial.print(realWeightVal);
                                Serial.print("  Gms");
                                Serial.print("PRICE  =  ");
                                Serial.print(totalCost);
                                Serial.print("  Kshs");
                                
                                          lcd.clear(); 
                                          lcd.setCursor(0,0);
                                          lcd.print("PRODUCT REF : ");
                                          lcd.print(productCount);
                                          lcd.setCursor(0,1);
                                          lcd.print("PRODUCT = ONIONS ");
                                          lcd.setCursor(0,2);
                                          lcd.print("WEIGHT  =  ");
                                          lcd.print(realWeightVal);
                                          lcd.print("  Gms");
                                          lcd.setCursor(0,3); 
                                          lcd.print("PRICE  =  ");
                                          lcd.print(totalCost);
                                          lcd.print("  Kshs");
                                          flag=1;
                                                  digitalWrite(ledPin2_Yellow, HIGH);
                                                  delay(500);
                                                  digitalWrite(ledPin2_Yellow, LOW);
        
                                                  delay(20000);
                                                   digitalWrite(buttonPin1, LOW);
                                                   digitalWrite(ledPin1_Green, LOW);
                                                   lcd.clear();
                                                   lcd.setCursor(3,1);
                                                   lcd.print("PLACE THE NEXT");
                                                   lcd.setCursor(0,2);
                                                   lcd.print("   ITEM / PRODUCT   ");
                                                   lcd.setCursor(3,3);
                                                   lcd.print("ON THE COUNTER");

                                                   delay(5000);

                                                           digitalWrite(ledPin2_Yellow, HIGH);
                                                           lcd.clear();
                                                           lcd.setCursor(3,0);
                                                           lcd.print("THANK YOU FOR");
                                                           lcd.setCursor(1,1);
                                                           lcd.print("SHOPPING WITH US.");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("**COME BACK AGAIN**");
                                                           
                                                           delay(5000);
                                                           
                                                           lcd.clear();
                                                           lcd.setCursor(0,0);
                                                           lcd.print("         **         ");
                                                           lcd.setCursor(0,1);
                                                           lcd.print("******* NEXT *******");
                                                           lcd.setCursor(0,2);
                                                           lcd.print("***** CUSTOMER *****");
                                                           lcd.setCursor(0,3);
                                                           lcd.print("         **         ");
                                              
                   
    } // Ends Onion Loop
    
    delay(1000); // Delays the Loop to check for the next product on the counter
  
        } // Ends the Loop => if (buttonPin1 == HIGH)
      
    productCount++; /*Increments the Productcounter by ensuring that all the products 
                      picked by one customer are all scanned properly through the system
                      */

} //Ends the Main Loop
