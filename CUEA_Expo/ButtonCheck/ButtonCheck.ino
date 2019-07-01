   
     const int buttonPin1 = 6;     // the number of the pushbutton pin
     const int buttonPin2 = 5;     // the number of the pushbutton pin

    // declaring buttton states
    int buttonState1 = 0; 
    int buttonState2 = 0;
    
     // led pins
     const int ledPin1 =  38;      // the number of the LED pin
     const int ledPin2 =  39;      // the number of the LED pin

   
    void setup() {
      
      Serial.begin(115200); //turn on serial port
      
    //initializing display led
     pinMode(ledPin1, OUTPUT);
     pinMode(ledPin2, OUTPUT);
     
    // initializing the pushbutton pin as an input:
    pinMode(buttonPin1, INPUT);
    pinMode(buttonPin2, INPUT);

    }
     
void loop() {
     // looping it to wait for commands
            
    buttonState1 = digitalRead(buttonPin1);

    buttonState2 = digitalRead(buttonPin2);
    
   if (buttonState1 == HIGH) {
    // turn LED on:
     digitalWrite(ledPin1, HIGH);
     delay(500);
         digitalWrite(ledPin1, LOW);
   }

    if (buttonState2 == HIGH){
         digitalWrite(ledPin2, HIGH);
         delay(500);
         digitalWrite(ledPin2, LOW);
         
      }
      delay(500);
}
