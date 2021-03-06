#include <LiquidCrystal.h>
#include <Servo.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);
Servo target1;
Servo target2;

// variable for attachment
int triggered;
int stillTriggered = 0;
int lcdCleared = 0;
int lcdCleared_num = 0;
int bullet = 13;
unsigned long firedTime;
int timeChecked = 0;
int laserOn;

// variable for target
int sensor1;
int sensor2;

unsigned long timePassed;
int result = 0;
int level = 0;
int t1Set = 0;
int t2Set = 0;
int t1Hit = 0;
int t2Hit = 0;

void setup()
{
  pinMode(6, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  
  lcd.begin(16, 2);
  target1.attach(10);
  target2.attach(11);
}

void loop()
{  
  // ----------Calculate passed time----------
  timePassed = millis();
  
  // ----------Set level----------
  if(6000 <= timePassed && timePassed < 11000) { //target1, 5sec
    level = 1;
  }
  else if(13000 <= timePassed && timePassed < 18000) { //target2, 5sec
    level = 2;
  }
  else if(20000 <= timePassed && timePassed < 25000) { //target1, 5sec
    level = 3;
  }
  else if(27000 <= timePassed && timePassed < 32000) { //target2, 5sec
    level = 4;
  }
  else if(34000 <= timePassed && timePassed < 39000) { //target1, 5sec
    level = 5;
  }
  else if(41000 <= timePassed && timePassed < 46000) { //target2, 5sec
    level = 6;
  }
  else if(48000 <= timePassed && timePassed < 55000) { //target1, target2, 7sec
    level = 7;
  }
  else if(57000 <= timePassed && timePassed < 62000) { //target1, 5sec
    level = 8;
  }
  else if(64000 <= timePassed && timePassed < 69000) { //target2, 5sec
    level = 9;
  }
  else if(71000 <= timePassed && timePassed < 76000) { //target1, target2, 7sec
    level = 10;
  }
  else {
    level = 0;
  }
  
  // ----------Display----------
  if(timePassed < 6000) {
    lcd.setCursor(0, 0);
    lcd.print("Ready...");
    lcd.setCursor(8, 0);
    if(timePassed < 5000) {
      lcd.print(5 - timePassed / 1000);
    }
    else {
      lcd.print("Start!");
    }
  }
  else {
    if(!lcdCleared) {
      lcd.clear();
      lcdCleared = 1;
    }
    if(!lcdCleared_num && bullet < 10) { //clear only once when number of remained bullet becomes one-digit number
      lcd.clear();
      lcdCleared_num = 1;
    }
    lcd.setCursor(0, 0);
    lcd.print("Bullet : ");
    lcd.setCursor(9, 0);
    lcd.print(bullet); //show remained bullet
    lcd.setCursor(0, 1);
    lcd.print("Hit : ");
    lcd.setCursor(6, 1);
    lcd.print(result); //show hit bullets
    if(timePassed > 76000) { //notice end
      lcd.setCursor(10, 1);
      lcd.print("Finish");
    }
  }

  // ----------Fire----------
  triggered = !digitalRead(6); //read button signal
  if(triggered && bullet > 0) { //if triggered
    if(!timeChecked) { //check fired time and decrease bullet. run only once per each fire
      firedTime = timePassed;
       bullet--;
       timeChecked = 1;
    }
    if(timePassed - firedTime < 100 && !stillTriggered) { //laser on
      digitalWrite(7, HIGH);
      laserOn = 1;
    }
    else { //laser offed but still triggered -> laser should not turn on
      digitalWrite(7, LOW);
      laserOn = 0;
      stillTriggered = 1;
    }
  }
  else{ //firing ended, ready for next fire
    digitalWrite(7, LOW);
    laserOn = 0;
    stillTriggered = 0;
    timeChecked = 0;
  }
  
  // ----------Target----------
  sensor1 = analogRead(A1);
  sensor2 = analogRead(A2);
  
  switch(level) {
    case 0: //Term between level
      target1.write(90);
      target2.write(90);
      t1Set = 0;
      t2Set = 0;
      t1Hit = 0;
      t2Hit = 0;
      break;
    case 1:
      if(t1Set == 0) {
          target1.write(0);
          t1Set = 1;
      }
      if(laserOn && sensor1 < 200 && t1Hit == 0) {
          target1.write(90);
          t1Hit = 1;
          result++;
      }
      break;
    case 2:
      if(t2Set == 0) {
          target2.write(0);
          t2Set = 1;
      }
      if(laserOn && sensor2 < 200 && t2Hit == 0) {
          target2.write(90);
          t2Hit = 1;
          result++;
      }
      break;
    case 3:
      if(t1Set == 0) {
          target1.write(0);
          t1Set = 1;
      }
      if(laserOn && sensor1 < 200 && t1Hit == 0) {
          target1.write(90);
          t1Hit = 1;
          result++;
      }
      break;
    case 4:
      if(t2Set == 0) {
          target2.write(0);
          t2Set = 1;
      }
      if(laserOn && sensor2 < 200 && t2Hit == 0) {
          target2.write(90);
          t2Hit = 1;
          result++;
      }
      break;
    case 5:
      if(t1Set == 0) {
          target1.write(0);
          t1Set = 1;
      }
      if(laserOn && sensor1 < 200 && t1Hit == 0) {
          target1.write(90);
          t1Hit = 1;
          result++;
      }
      break;
    case 6:
      if(t2Set == 0) {
          target2.write(0);
          t2Set = 1;
      }
      if(laserOn && sensor2 < 200 && t2Hit == 0) {
          target2.write(90);
          t2Hit = 1;
          result++;
      }
      break;
    case 7:
      if(t1Set == 0) {
          target1.write(0);
          t1Set = 1;
      }
      if(t2Set == 0) {
          target2.write(0);
          t2Set = 1;
      }
      if(laserOn && sensor1 < 200 && t1Hit == 0) {
          target1.write(90);
          t1Hit = 1;
          result++;
      }
      if(laserOn && sensor2 < 200 && t2Hit == 0) {
          target2.write(90);
          t2Hit = 1;
          result++;
      }
      break;
    case 8:
      if(t1Set == 0) {
          target1.write(0);
          t1Set = 1;
      }
      if(laserOn && sensor1 < 200 && t1Hit == 0) {
          target1.write(90);
          t1Hit = 1;
          result++;
      }
      break;
    case 9:
      if(t2Set == 0) {
          target2.write(0);
          t2Set = 1;
      }
      if(laserOn && sensor2 < 200 && t2Hit == 0) {
          target2.write(90);
          t2Hit = 1;
          result++;
      }
      break;
    case 10:
      if(t1Set == 0) {
          target1.write(0);
          t1Set = 1;
      }
      if(t2Set == 0) {
          target2.write(0);
          t2Set = 1;
      }
      if(laserOn && sensor1 < 200 && t1Hit == 0) {
          target1.write(90);
          t1Hit = 1;
          result++;
      }
      if(laserOn && sensor2 < 200 && t2Hit == 0) {
          target2.write(90);
          t2Hit = 1;
          result++;
      }
    default :
      break;  
  }
}
