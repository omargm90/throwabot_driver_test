#define DIR_PIN         3 // Direction
#define STEP_PIN        4 // Step
#define SLEEP_PIN       5 // Step
#define RST_PIN         6 // Reset 
#define M2_PIN          7 // M2 pin
#define M1_PIN          8 // M1 pin
#define M0_PIN          9 // M0 pin
#define EN_PIN          10 // Enable

#define FREQ_MAX_L 400//800
#define FREQ_MAX_H 3500//7000

#define LOW_SPEED_THLD 0.02
#define DELTATIME 10

#define JoyStick_X    A8 // X-axis-signal - pin no. 14
#define JoyStick_Y    A9 // Y-axis-signal - pin no. 15

float freq = 0;
float freq_max = FREQ_MAX_H;
float x = 0;
float y = 0;
bool dir_sign = LOW;

char speed_set = 'f';
char speed_read = speed_set;

void setup() {
  
  //initialize 

  Serial.begin(9600);

  pinMode(RST_PIN, OUTPUT);
  digitalWrite(RST_PIN, HIGH);
  
  pinMode(DIR_PIN, OUTPUT);
  pinMode(STEP_PIN, OUTPUT);
  pinMode(SLEEP_PIN, OUTPUT);
  pinMode(M2_PIN, OUTPUT);
  pinMode(M1_PIN, OUTPUT);
  pinMode(M0_PIN, OUTPUT);
  pinMode(EN_PIN, OUTPUT);

  pinMode (JoyStick_X, INPUT);
  pinMode (JoyStick_Y, INPUT);

  digitalWrite(DIR_PIN, dir_sign);    
  digitalWrite(SLEEP_PIN, LOW);
  
  digitalWrite(M0_PIN, LOW);
  digitalWrite(M1_PIN, LOW);
  digitalWrite(M2_PIN, HIGH);
  digitalWrite(EN_PIN, LOW);      // Enable driver in hardware
  
}

float time = millis();

void loop() {


  if (millis() - time > DELTATIME) {  
// change of speed
    if (Serial.available()){

      speed_read = Serial.read();
      Serial.println(speed_read);

      if ((speed_set!= speed_read) && (speed_read!=10)) {

        speed_set = speed_read;
        Serial.print("Speed changed to: ");

        if(speed_read == 's'){

          freq_max = FREQ_MAX_L;
          digitalWrite(M0_PIN, LOW);
          digitalWrite(M1_PIN, HIGH);
          digitalWrite(M2_PIN, HIGH);
          Serial.println("SLOW");
        }
        else if(speed_read = 'f'){

          freq_max = FREQ_MAX_H;
          digitalWrite(M0_PIN, LOW);
          digitalWrite(M1_PIN, LOW);
          digitalWrite(M2_PIN, HIGH);
          Serial.println("FAST");
        }       
      }
    }
// update speed 

      y = (analogRead(JoyStick_X) - 511.5 ) / 511.5; //change midpoint according to initial measurement

      if ( y < 0)
        dir_sign = HIGH; 
      else
        dir_sign = LOW;
  
      y *=y;
  
      if(y>LOW_SPEED_THLD){
        digitalWrite(SLEEP_PIN, HIGH);
        freq = y * freq_max;
        Serial.println(freq);
      }
      else{
        digitalWrite(SLEEP_PIN, LOW);
        freq = 0;
      }

      
  
      digitalWrite(DIR_PIN, dir_sign);
      analogWriteFrequency(STEP_PIN, freq);
      analogWrite(STEP_PIN, 128);

      time = millis();    

    }
    
}
