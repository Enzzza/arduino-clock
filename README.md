## _Building an Arduino clock for visually impaired_

<br/>
<br/>
 
A few years ago I visited my grandma who at the time lived by herself in Vajxo, Sweden. Her vision was slowly deteriorating and she would always ask us to tell her what time it was. I know there is a lot of talking clocks out there but mostly they are in English. Seven days before my trip to Sweden I decided to create an Arduino clock that would produce audio notifications for each hour. For this, I recorded my mother’s ( i think this was hardest part :P ) voice along with a greeting message in Bosnian that would play every morning at 8am. Needless to say, grandma was thrilled and happy that she no longer had to rely on her family and visitors to tell her what time it was. This gave her some much needed independence.

The clock produces audio notifications for every hour, or on demand using the remote control.

Down below is the tutorial - hope you find it useful.

I bought parts from a local shop. You’ll need the following:

- Arduino UNO
- DS3231 real time clock module
- Wtv020sd16p sound module
- IR Reciver module
- Speakers
- Button
- SD Card 2GB

<br>

![img01](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img01.PNG)

<br>

### _First step is to make prototype, we don't want to test it after we solder everything._

<br>

![img02](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img02.jpg)

<br>

{% youtube xsVEGVSmkcQ %}

{% youtube vn5ivbb1BCE %}

<br>

After we finished prototyping and testing everything we are ready to put it all together.

<br>

![img03](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img03.jpg)

<br>

I called my good friend to help me with soldering he is really good with it i can't risk to leave joints loose

<br>

![img04](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img04.jpg)

{% youtube EomNWaz-PTw %}

<br>

We make our box fancy

<br>

![img05](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img05.jpg)

<br>

![img06](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img06.jpg)

<br>

### _Next we will record audio for our clock_

<br>
This part was very annoying for my mom because i made her repeat all those numbers :rofl:
I used android application to record audio and edit it.

<br>
<br>

![img07](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img07.jpg)

<br>

Record all audio for hours and minutes and name them in this format '0000.wav' '0001.wav' this will be important later when we will use sound module to play this files

<br>

![img08](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img08.jpg)

<br>

### _Adding audio files to sd card_

<br>

Before everything its good to format SD card

<br>

![img09](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img09.jpg)

<br>

After we formated card we need to add audio files to the SD card. Our sound module accepts ad4 file format so we need to convert our files to that format using [AD4CONVERTER](https://www.buildcircuit.com/how-to-convert-mp3-and-wav-files-to-ad4-format-wtv020sd-tutorial/).
To make it easier for us i made powershell [script](github) that will automaticly convert all files in folder to AD4 format.

```powershell
$fileNames = Get-ChildItem -Path "your_audio_files location" -Recurse -Include *.wav
foreach($file in $fileNames ){
 Write-Host  $file.FullName
 .\your_ad4_location\AD4CONVERTER.EXE -E4 $file

}
```

Run this script inside your folder with audio files make sure to put AD4CONVERTER.exe in same folder.

<br>

![img10](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img10.JPG)

<br>

![img11](https://raw.githubusercontent.com/Enzzza/arduino-clock/main/media/img11.JPG)

<br>

Add AD4 files to SD card.

<br>

### _Time for coding :heart_eyes:_

<br>

Add all lib in rar format to our ArduinoIDE than include that libs

```C
#include <EEPROM.h>
#include <RTClib.h>
#include <Wtv020sd16p.h>
#include "IRremote.h"
```

Now we define all PINs we will use in our code

```C
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
IRrecv irrecv(RECEIVER_PIN);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

/*
  Create an instance of the Wtv020sd16p class.
  1st parameter: Reset pin number.
  2nd parameter: Clock pin number.
  3rd parameter: Data pin number.
  4th parameter: Busy pin number.
*/
Wtv020sd16p wtv020sd16p(RESET_PIN, CLOCK_PIN, DATA_PIN, BUSY_PIN);
```

DST is variable in which we will keep state of button.
Role of this button is to track if its summer time or winter time. When pressed it will advance clock by one hour and vice versa

Next we will explain what is in setup function. Setup function will run when we power on Arduino.

```C
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);


  irrecv.enableIRIn(); // Start the receiver

  // this code will get state of DST variable from EEPROM memory
  // if there is nothing ine memory we will put 1 aka summer time
  DST = EEPROM.get(0, DST);

  if (DST != 0 && DST != 1)
  {
    DST = 1;
    EEPROM.put(0, DST);
  }

  // RTC clock
  // we will loop until RTC module start
  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  // this condition will check if our RTC module lost power
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
```

In this function we setup initial values for our modules. We will try to get DST button state from EEPROM memory if there is nothing in memory we will put 1 as default (summer time).

```C
DST = EEPROM.get(0, DST);

  if (DST != 0 && DST != 1)
  {
    DST = 1;
    EEPROM.put(0, DST);
  }

```

After we finished up initial setup we Arduino will run loop function that is running in some interval

```C
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
```

In loop function we are checking if DST button has been pressed. Than we check if DST state is 0 or 1 and we adjust time accordingly. We add one hour if DST state is 1.

```C
/*loop function*/
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
```

In every loop we will get current time using

```C
DateTime  myTime = rtc.now();
```

Next we call function named _hourly_ which accepts current time

```C
/*loop function*/
// Run hourly clock notifications
hourly(myTime);
```

This function will play audio for every hour

```C
/*hourly function*/
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
  //.....
}
```

In this function we will use multiple if else statements, to play audio we use this function

```C
wtv020sd16p.playVoice(86); delay(16000);
```

Notice to play sound we use numbers and this numbers correspond to files on SD card. Number _86_ is _0086.ad4_ file on SD card. In my case ad4 file with number _86_ will play sound relaxing sound of birds. This audio will play before every audio of hours. In this function we also called function _switchTime_, this function will accept current time and boolean value. If boolean value is _true_ we will play just correct time without minutes if this value is _false_ we will play exact time in hours and minutes.
When this function is called from within _hourly_ function we will send _true_.

```C
/*switchTime function*/
void switchTime(DateTime &myTime, bool hourly) {
  int Hour = myTime.hour();
  int Minute = myTime.minute();

  switch (Hour) {
    case 0: wtv020sd16p.playVoice(0); delay(4500);    break;
    case 1: wtv020sd16p.playVoice(1); delay(3800);    break;
    case 2: wtv020sd16p.playVoice(2); delay(3800);    break;
    case 3: wtv020sd16p.playVoice(3); delay(3000);    break;
    case 4: wtv020sd16p.playVoice(4); delay(3000);    break;
    //......
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
      //....

      default:
        Serial.println("Erorr check files");
    }

  }

  delay(5000);

}
```

Back to the loop function, now we will react if we recive IR signal from remote and if we get signal from remote we will play current time with hours and minutes using same function _switchTime_ now we will send _false_ as second parametar

```C
  /*loop function*/
  // Run clock notification when remote controller button is pressed
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    if (IRvalues()) {
      switchTime(myTime, false);
      delay(1000);
    }

    irrecv.resume(); // receive the next value

  }
```

In this if block we will check if we recive signal and also to ignore other remote controlers e.g. TV remote controller we will check if signal is in the allowed _IRvalues_

```C
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
```

{% youtube GiLrG6B72Eo %}

I hope someone will make use of this and make their loved ones happy. My grandma will have easier time to know what time it is....

{% youtube Rl6sFvUqOLI %}
