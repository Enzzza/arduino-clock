#include <EEPROM.h>
#include <RTClib.h>
#include <Wtv020sd16p.h>
#include "IRremote.h"


// RTC setup
RTC_DS3231 rtc;

// Wtv020sd16p Pins
#define RESET_PIN 2  // The pin number of the reset pin.
#define CLOCK_PIN 3  // The pin number of the clock pin.
#define DATA_PIN 4  // The pin number of the data pin.
#define BUSY_PIN 5  // The pin number of the busy pin.

// IR Pin
#define RECEIVER_PIN 11 // Signal Pin of IR receiver to Arduino Digital Pin 11


// DST Pin
#define DST_PIN 9


// DST check
int DST;

/*-----( Declare objects )-----*/
IRrecv irrecv(RECEIVER_PIN);     // Create instance of 'irrecv'
decode_results results;      // Create instance of 'decode_results'

/*
  Create an instance of the Wtv020sd16p class.
  1st parameter: Reset pin number.
  2nd parameter: Clock pin number.
  3rd parameter: Data pin number.
  4th parameter: Busy pin number.
*/
Wtv020sd16p wtv020sd16p(RESET_PIN, CLOCK_PIN, DATA_PIN, BUSY_PIN);

void switchTime(DateTime &myTime, bool hourly) {
  int Hour = myTime.hour();
  int Minute = myTime.minute();

  switch (Hour) {
    case 0: wtv020sd16p.playVoice(0); delay(4500);    break;
    case 1: wtv020sd16p.playVoice(1); delay(3800);    break;
    case 2: wtv020sd16p.playVoice(2); delay(3800);    break;
    case 3: wtv020sd16p.playVoice(3); delay(3000);    break;
    case 4: wtv020sd16p.playVoice(4); delay(3000);    break;
    case 5: wtv020sd16p.playVoice(5); delay(3000);    break;
    case 6: wtv020sd16p.playVoice(6); delay(3000);    break;
    case 7: wtv020sd16p.playVoice(7); delay(3000);    break;
    case 8: wtv020sd16p.playVoice(8); delay(3000);    break;
    case 9: wtv020sd16p.playVoice(9); delay(3000);    break;
    case 10: wtv020sd16p.playVoice(10); delay(3500);  break;
    case 11: wtv020sd16p.playVoice(11); delay(2900);  break;
    case 12: wtv020sd16p.playVoice(12); delay(3000);  break;
    case 13: wtv020sd16p.playVoice(13); delay(3000);  break;
    case 14: wtv020sd16p.playVoice(14); delay(3000);  break;
    case 15: wtv020sd16p.playVoice(15); delay(3000);  break;
    case 16: wtv020sd16p.playVoice(16); delay(3500);  break;
    case 17: wtv020sd16p.playVoice(17); delay(3000);  break;
    case 18: wtv020sd16p.playVoice(18); delay(2700);  break;
    case 19: wtv020sd16p.playVoice(19); delay(3000);  break;
    case 20: wtv020sd16p.playVoice(20); delay(3000);  break;
    case 21: wtv020sd16p.playVoice(21); delay(4000);  break;
    case 22: wtv020sd16p.playVoice(22); delay(4000);  break;
    case 23: wtv020sd16p.playVoice(23); delay(3200);  break;
    default:
      Serial.println("Erorr check files");

  }

  // Play minutes audio
  if (hourly != true) {
    switch (Minute) {
      case 0: wtv020sd16p.playVoice(24); delay(1000);    break;
      case 1: wtv020sd16p.playVoice(25); delay(1000);    break;
      case 2: wtv020sd16p.playVoice(26); delay(1000);    break;
      case 3: wtv020sd16p.playVoice(27); delay(1000);    break;
      case 4: wtv020sd16p.playVoice(28); delay(1000);    break;
      case 5: wtv020sd16p.playVoice(29); delay(1000);    break;
      case 6: wtv020sd16p.playVoice(30); delay(1000);    break;
      case 7: wtv020sd16p.playVoice(31); delay(1000);    break;
      case 8: wtv020sd16p.playVoice(32); delay(1000);    break;
      case 9: wtv020sd16p.playVoice(33); delay(1000);    break;
      case 10: wtv020sd16p.playVoice(34); delay(1000);  break;
      case 11: wtv020sd16p.playVoice(35); delay(1000);  break;
      case 12: wtv020sd16p.playVoice(36); delay(1000);  break;
      case 13: wtv020sd16p.playVoice(37); delay(1000);  break;
      case 14: wtv020sd16p.playVoice(38); delay(1000);  break;
      case 15: wtv020sd16p.playVoice(39); delay(1000);  break;
      case 16: wtv020sd16p.playVoice(40); delay(1000);  break;
      case 17: wtv020sd16p.playVoice(41); delay(1000);  break;
      case 18: wtv020sd16p.playVoice(42); delay(1000);  break;
      case 19: wtv020sd16p.playVoice(43); delay(1000);  break;
      case 20: wtv020sd16p.playVoice(44); delay(1000);  break;
      case 21: wtv020sd16p.playVoice(45); delay(1000);  break;
      case 22: wtv020sd16p.playVoice(46); delay(1000);  break;
      case 23: wtv020sd16p.playVoice(47); delay(1000);  break;
      case 24: wtv020sd16p.playVoice(48); delay(1000);    break;
      case 25: wtv020sd16p.playVoice(49); delay(1000);    break;
      case 26: wtv020sd16p.playVoice(50); delay(1000);    break;
      case 27: wtv020sd16p.playVoice(51); delay(1000);    break;
      case 28: wtv020sd16p.playVoice(52); delay(1000);    break;
      case 29: wtv020sd16p.playVoice(53); delay(1000);    break;
      case 30: wtv020sd16p.playVoice(54); delay(1000);    break;
      case 31: wtv020sd16p.playVoice(55); delay(1000);    break;
      case 32: wtv020sd16p.playVoice(56); delay(1000);    break;
      case 33: wtv020sd16p.playVoice(57); delay(1000);    break;
      case 34: wtv020sd16p.playVoice(58); delay(1000);  break;
      case 35: wtv020sd16p.playVoice(59); delay(1000);  break;
      case 36: wtv020sd16p.playVoice(60); delay(1000);  break;
      case 37: wtv020sd16p.playVoice(61); delay(1000);  break;
      case 38: wtv020sd16p.playVoice(62); delay(1000);  break;
      case 39: wtv020sd16p.playVoice(63); delay(1000);  break;
      case 40: wtv020sd16p.playVoice(64); delay(1000);  break;
      case 41: wtv020sd16p.playVoice(65); delay(1000);  break;
      case 42: wtv020sd16p.playVoice(66); delay(1000);  break;
      case 43: wtv020sd16p.playVoice(67); delay(1000);  break;
      case 44: wtv020sd16p.playVoice(68); delay(1000);  break;
      case 45: wtv020sd16p.playVoice(69); delay(1000);  break;
      case 46: wtv020sd16p.playVoice(70); delay(1000);  break;
      case 47: wtv020sd16p.playVoice(71); delay(1000);  break;
      case 48: wtv020sd16p.playVoice(72); delay(1000);  break;
      case 49: wtv020sd16p.playVoice(73); delay(1000);  break;
      case 50: wtv020sd16p.playVoice(74); delay(1000);  break;
      case 51: wtv020sd16p.playVoice(75); delay(1000);  break;
      case 52: wtv020sd16p.playVoice(76); delay(1000);  break;
      case 53: wtv020sd16p.playVoice(77); delay(1000);  break;
      case 54: wtv020sd16p.playVoice(78); delay(1000);  break;
      case 55: wtv020sd16p.playVoice(79); delay(1000);  break;
      case 56: wtv020sd16p.playVoice(80); delay(1000);  break;
      case 57: wtv020sd16p.playVoice(81); delay(1000);  break;
      case 58: wtv020sd16p.playVoice(82); delay(1000);  break;
      case 59: wtv020sd16p.playVoice(83); delay(1000);  break;
      case 60: wtv020sd16p.playVoice(84); delay(1000);  break;

      default:
        Serial.println("Erorr check files");
    }

  }

  delay(5000);

}

void hourly(DateTime &myTime) {
  // 7 o'clock
  if (myTime.hour() == 7 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    delay(500);
    switchTime(myTime, true);
    delay(1000);
  }
  // 8 o'clock
  else if (myTime.hour() == 8 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000); // the birds begin to sing
    switchTime(myTime, true); delay(1000); // tells what time it is
    wtv020sd16p.playVoice(84); delay(6500); // message from grandma's daughter
    wtv020sd16p.playVoice(85); delay(5500); // message from granddaughter

    delay(1000);
  }
  // 9 o'clock
  else if (myTime.hour() == 9 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 10 o'clock
  else if (myTime.hour() == 10 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 11 o'clock
  else if (myTime.hour() == 11 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 12 o'clock
  else if (myTime.hour() == 12 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 13 p.m.
  else if (myTime.hour() == 13 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 14 p.m.
  else if (myTime.hour() == 14 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 15 p.m.
  else if (myTime.hour() == 15 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 16 p.m.
  else if (myTime.hour() == 16 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 17 p.m.
  else if (myTime.hour() == 17 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 18 p.m.
  else if (myTime.hour() == 18 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 19 p.m.
  else if (myTime.hour() == 19 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 20 p.m.
  else if (myTime.hour() == 20 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 21 p.m.
  else if (myTime.hour() == 21 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 22 p.m.
  else if (myTime.hour() == 22 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }
  // 23 p.m.
  else if (myTime.hour() == 23 && myTime.minute() == 00 && myTime.second() == 00) {
    wtv020sd16p.playVoice(86); delay(16000);
    switchTime(myTime, true);
    delay(1000);
  }



}
bool IRvalues() {
  // Accept signals only from custom remote
  switch (results.value) {
    case 0xFFA25D: return true; break;
    case 0xFFE21D: return true; break;
    case 0xFF629D: return true; break;
    case 0xFF22DD: return true; break;
    case 0xFF02FD: return true; break;
    case 0xFFC23D: return true; break;
    case 0xFFE01F: return true; break;
    case 0xFFA857: return true; break;
    case 0xFF906F: return true; break;
    case 0xFF9867: return true; break;
    case 0xFFB04F: return true; break;
    case 0xFF6897: return true; break;
    case 0xFF30CF: return true; break;
    case 0xFF18E7: return true; break;
    case 0xFF7A85: return true; break;
    case 0xFF10EF: return true; break;
    case 0xFF38C7: return true; break;
    case 0xFF5AA5: return true; break;
    case 0xFF42BD: return true; break;
    case 0xFF4AB5: return true; break;
    case 0xFF52AD: return true; break;
    case 0xFFFFFFFF: return true; break;

    default:
      return false;

  } // End Case


}

void setup() {
  // Put your setup code here, to run once:
  Serial.begin(9600);


  irrecv.enableIRIn(); // Start the receiver

  // This code will get state of DST variable from EEPROM memory
  // If there is nothing ine memory we will put 1 aka summer time
  DST = EEPROM.get(0, DST);

  if (DST != 0 && DST != 1)
  {
    DST = 1;
    EEPROM.put(0, DST);
  }

  // RTC clock
  // We will loop until RTC module start
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // This condition will check if our RTC module has lost power
  if (rtc.lostPower()) {
    Serial.println("RTC lost power, lets set the time!");

    // Following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  // Comment out below lines once you set the date & time.
  // Following line sets the RTC with an explicit date & time
  // for example to set January 27 2017 at 12:56 you would call:
  // rtc.adjust(DateTime(2017, 1, 27, 12, 56, 0));

  // Initializes the sound module.
  wtv020sd16p.reset();

  // Setting up our DST button
  pinMode(DST_PIN, INPUT_PULLUP);
}

void loop() {
  // Check if DST button is pressed
  
  if (digitalRead(DST_PIN) == LOW) {
    DateTime now = rtc.now();
    if (DST == 0) {
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour() + 1, now.minute(), now.second()));
      DST = 1;
      EEPROM.put(0, DST);
    } else if (DST == 1) {
      rtc.adjust(DateTime(now.year(), now.month(), now.day(), now.hour() - 1, now.minute(), now.second()));
      DST = 0;
      EEPROM.put(0, DST);
    }
  }

  // Initialize time object
  DateTime  myTime = rtc.now();
  
  // Run hourly clock notifications
  hourly(myTime);

  // Run clock notification when remote controller button is pressed
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    if (IRvalues()) {
      switchTime(myTime, false);
      delay(1000);
    }

    irrecv.resume(); // receive the next value

  }

}
