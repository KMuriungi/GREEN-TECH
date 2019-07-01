    
    #include <LiquidCrystal.h>
 
    LiquidCrystal lcd(11, NULL, 12, 7, 8, 9, 10);
    	
    int S2= 2; //Color sensore pin S2 to Arduino pin 2
    int S3= 3; //Color sensor pin S3 to Arduino pin 3
    int outPin = 4; //Color Sensor OUT to Arduino pin 4
    
    int weightPin = A0; //this takes inthe analog value of the weight
    int weightValue = 0; //holds the weight value
    
    int rColorStrength; //measured strength of red color
    int gColorStrength; //measured strength of green color
    int bColorStrength; //measured strength of blue color
    unsigned int pulseWidth; //for measuring color strength using pulseIn command
     
  
     
    void setup() {
      // put your setup code here, to run once:
      
      Serial.begin(115200); //turn on serial port
      
      pinMode(S2, OUTPUT); //S2 and S3 are outputs and used to tell
      pinMode(S3, OUTPUT); //arduino which color to measure
      pinMode(outPin, INPUT); //This is the pin we read the color from
      
       // read the weight value from the weight sensor:
   
      
        lcd.clear();                    //clear the LCD during setup
        lcd.begin(16,2);                //define the columns (16) and rows (2
          lcd.print("GLOSARY POINT OF SALE SMART AUTOMATION PROJECT...");          //print...
                          delay(1000);                   //wait...
                          lcd.setCursor(0,0);            //move the cursor to the 2nd line
                          lcd.print("IEEE EXPOSITION --- STRATHMORE UNIVERSITY");          //print...
                          delay(1000); 
                          
                          lcd.setCursor(0,2);            //move the cursor to the 2nd line
                          lcd.print("PRESENTED BY_______");          //print...
                          delay(1000);  
                          
                          lcd.setCursor(0,3);            //move the cursor to the 2nd line
                          lcd.print("GITHINJI   AND");          //print...
                          delay(1000);  
                           lcd.clear(); 
                          lcd.setCursor(0,3);            //move the cursor to the 2nd line
                          lcd.print("PETER NDUNG'U");          //print...
                          delay(1000);  
                                                    
                          lcd.home(); 
                          lcd.clear(); 
                          lcd.home();  
              

    }
     
    void loop() {
         weightValue = analogRead(weightPin);
          outputValue = map(weightValue,75, 1023, 0, 255);
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
     

                  Serial.print(rColorStrength);
                  Serial.print(" , ");
                  Serial.print(gColorStrength);
                  Serial.print(" , ");
                  Serial.print(bColorStrength);
                  Serial.print(" , ");
                  Serial.print(weightValue);
                  Serial.println(" , "); 
                  
                  
                  lcd.print(rColorStrength);
                  lcd.print(" , ");
                    lcd.setCursor(0,1);
                  lcd.print(gColorStrength);
                  lcd.print(" , ");
                    lcd.setCursor(0,2);
                  lcd.print(bColorStrength);
                  lcd.println(" , ");
                    lcd.setCursor(0,3);
                  lcd.print(weightValue);
                  lcd.println(" , "); 
      
      // to print on lcd
                        
      delay(150);
      
    }


