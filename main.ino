int pin_hall[] = {A1, A2, A3}; // {Hall_1, Hall_2, Hall_3}
int pin_trigger[] = {2, 3, 4, 5, 6, 7}; // {H1, H2, H3, L1, L2, L3} 

const int PWM = 9;
const int ind_0 = 10;
const int ind_1 = 11;
const int ind_2 = 12;

byte data_hall[3] = {0};
int kecepatan = 0;

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(9600);
  
  for(int i=0; i<3; i++){
      pinMode(pin_hall[i], INPUT);
    }
  for(int i=0; i<6; i++){
      pinMode(pin_trigger[i], OUTPUT);
    }   
  pinMode(PWM, OUTPUT);
}

void loop() {

  baca_hall();
    
//  if(digitalRead(pin_hall[0]) == HIGH){digitalWrite(ind_0, HIGH);} else{digitalWrite(ind_0, LOW);}
//  if(digitalRead(pin_hall[1]) == HIGH){digitalWrite(ind_1, HIGH);} else{digitalWrite(ind_1, LOW);}
//  if(digitalRead(pin_hall[2]) == HIGH){digitalWrite(ind_2, HIGH);} else{digitalWrite(ind_2, LOW);}
  
  kecepatan = analogRead(A0);
  kecepatan = map(kecepatan, 0, 1023, 0, 255);
  //Serial.println(kecepatan);
  analogWrite(PWM, kecepatan);
    
  // put your main code here, to run repeatedly:
  if     (data_hall[0] == 1 && data_hall[1] == 0 && data_hall[2] == 1){trigger_mosfet(1, 0, 0, 0, 1, 0);}
  else if(data_hall[0] == 1 && data_hall[1] == 0 && data_hall[2] == 0){trigger_mosfet(1, 0, 0, 0, 0, 1);}
  else if(data_hall[0] == 1 && data_hall[1] == 1 && data_hall[2] == 0){trigger_mosfet(0, 1, 0, 0, 0, 1);}
  else if(data_hall[0] == 0 && data_hall[1] == 1 && data_hall[2] == 0){trigger_mosfet(0, 1, 0, 1, 0, 0);}
  else if(data_hall[0] == 0 && data_hall[1] == 1 && data_hall[2] == 1){trigger_mosfet(0, 0, 1, 1, 0, 0);}
  else if(data_hall[0] == 0 && data_hall[1] == 0 && data_hall[2] == 1){trigger_mosfet(0, 0, 1, 0, 1, 0);}
  
}

void trigger_mosfet(bool H1, bool H2, bool H3, bool L1, bool L2, bool L3){
  bool logic[] = {H1, H2, H3, L1, L2, L3};
  for(int i=0; i<6; i++){
      digitalWrite(pin_trigger[i], logic[i]);
    }
  }

void baca_hall(){
  for(int i=0; i<3; i++){
      data_hall[i] = digitalRead(pin_hall[i]);
    }
  }

