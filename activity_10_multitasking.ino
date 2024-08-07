
#define LED_PIN_1 8
#define LED_PIN_2 3
#define LED_PIN_3 7
#define POTENTI_PIN A2
#define PUSH_PIN 2


unsigned long timeStartLED1 = 0;
unsigned long timeStartLED2 = 0;
unsigned long timeStartLED3 = 0;

boolean LEDOn = true;


int blinkrate = 1000;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.setTimeout(10);
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);
  pinMode(LED_PIN_3, OUTPUT);

  pinMode(PUSH_PIN, INPUT);



}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned long currTime = millis();

  //blink led 1
  if(currTime - timeStartLED1 > userBlinkRate()){

    if(LEDOn){
      digitalWrite(LED_PIN_1, HIGH);
      LEDOn = false;
    } else {
      digitalWrite(LED_PIN_1, LOW);
      LEDOn = true;
    }
    timeStartLED1 += blinkrate;
  }

  //pontentimeter controles led 2

  if(currTime - timeStartLED2 > 50){
    //calculate brightness
    //(potenti/1023) = (brighness/255)
    double divi = analogRead(POTENTI_PIN)/1023.0;
   // Serial.println("division");
    //Serial.println(divi);
    int brigntess = divi * 255;
    //Serial.println("brigntess");
    //Serial.println(brigntess);
    analogWrite(LED_PIN_2, brigntess);
    timeStartLED2 += 50;
  }

  //button controls led 3
  if(currTime - timeStartLED3 > 50){
    //led is not pushed
    if(digitalRead(PUSH_PIN) ==LOW ){
      Serial.println("NO PUSH");
      digitalWrite(LED_PIN_3, LOW);
    }
    if(digitalRead(PUSH_PIN) ==HIGH ){
      Serial.println("PUSH");

      digitalWrite(LED_PIN_3, HIGH);
    }
  
    timeStartLED3 += 50;
  }


}

int userBlinkRate(){
  if(Serial.available() > 0 ){
    blinkrate = Serial.parseInt();
    if(blinkrate > 1000 || blinkrate < 100){
      blinkrate = 1000;
    }
  }

  return blinkrate;
}
