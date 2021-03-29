## _Using Arduino to help my grandma_

<br/>
<br/>
 
A few years ago I visited my grandma who at the time lived by herself in Vajxo, Sweden. Her vision was slowly deteriorating and she would always ask us to tell her what time it was. I know there is a lot of talking clocks out there but mostly they are in English. Seven days before my trip to Sweden I decided to create an Arduino clock that would produce audio notifications for each hour. For this, I recorded my mother’s ( i think this was hardest part :P ) voice along with a greeting message in Bosnian that would play every morning at 8am. Needless to say, grandma was thrilled and happy that she no longer had to rely on her family and visitors to tell her what time it was. This gave her some much needed independence.

This clock will say time every hour or if u use remote controller you will get time at that point

Down bellow i will make tutorial maybe it will be useful to someone.

I bought parts from local shop.
We will need following parts:

- DS3231 real time clock module
- Wtv020sd16p sound module
- IR Reciver module
- Speakers
- Button
- SD Card 2GB

<br>

![img1](šema)

<br>

### _First step is to make prototype, we don't want to test it after we solder everything._

<br>

![img2](prototype)

<br>

{% youtube vid1 %}

<br>

After we finished prototyping and testing everything we are ready to put it all together.

<br>

![img3](assembly)

<br>

I called my good friend to help me with soldering he is really good with it i can't risk to leave joints loose

<br>

![img4](friend)

<br>

We make our box fancy

<br>

![img5](fancy)

<br>

![img6](inside)

<br>

### _Next we will record audio for our clock_

<br>
This part was very annoying for my mom because i made her repeat all those numbers :rofl:
I used android application to record audio and edit it.

<br>
<br>

![img7](lexis)

<br>

Record all audio for hours and minutes

<br>

![img8](files)

<br>

### _Adding audio files to sd card_

<br>

Before everything its good to format SD card

<br>

![img9](format)

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

![img10](script)

<br>

![img11](converted)

<br>

Add AD4 files to SD card.

<br>

### _Time for coding :heart_eyes:_

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
This button will enable us when pressed to change time calculation to summer/winter time.
