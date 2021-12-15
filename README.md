Season's Greetings from TexElec.com!

We hope you like the Christmas SID Player, and thanks for supporting us!  

This player is based on the STM32 Sid Player. Special Thanks to Bashika 
for making the Source available.

GitHub Link: https://github.com/Bakisha/STM32-SID-PLAYER

I would also like to think all of the great authors out there for the Christmas
tunes!  We picked out 20 we liked below, but you may add most any SID you like to 
the root directory of the SD card, and it should play.  Files with digital samples
are not supported, and some files may not playback correctly, or at full speed.  
The emulation is certainly not exact, but it does make a good attempt.  

Song List (All of these were sourced from the HVSC 75 SID Collection)
Christmas_Time_is_Here - 2020 Eric Dobek<br>
Christmas18 - by 2017 Censor Design <br>
The Christmas Song - 1989 Pirates of Denver<br>
Christmas_Terror - 1991 Rob Peters<br>
The Electronic Christmas Card - 1985 Tim Cannell<br>
Official Father Christmas Game - 1989 Alternative Software<br>
White Christmas - 2007 Crypt (A-Man) Steven Diemer<br>
A Christmas Song - Nantco Bakker - 1992<br>
A Christmas Medley - Nantco Bakker - 1992<br>
Christmas_1989_tune_2 = Yavuz Sukur 1989<br>
GP Christmas - 2017 Michael Brzeski - Genesis Project<br>
Christmas_boogie -  Johan Samuelson - 2019<br>
12 Days of Christmas - Warren Pilkington 1992<br>
Mice's Christmas - Cris 2020 The Santas<br>
Feliz Navidad - Jose Feliciano - 2017<br>
Christmas_One - Unknown Author - 1987<br>
Rudolph The Red Nosed Reindeer - Klegg & Miztluren - 2007<br>
Merry Christmas 2017 - Nilsson & Miztluren - 2017<br>
XMas Demo - Stian Gudbrandsen - 2020<br>
Frosty The Snowman - Unknown Author - 198x?<br>
--------------------------------------------------------------------------------------

Button Function:
There are four capacitive touch sensors which serve as buttons on the
Christmas SID.  Three of them are on the main red board below the previous,
next & play/pause buttons.  The fourth button is on the center of the flame.

The follow functions are present in the code from the STM32 SID Player.  I 
left them all in-tact, but items marked (*) below will have no function.

Taps  Previous                       Play/Pause           Next
--------------------------------------------------------------------------------------
1     play previous tune             play / pause toggle  play next tune
2     play previous file             restart tune         play next file
3     *play previous folder          restart tune's time  *play next folder
4     *play first folder of playlist *SID INFO            *play last folder of playlist
5     *HELP                          *HELP                *HELP
hold  Channel 1 OFF                  Channel 2 OFF        Channel 3 OFF

We added the code for the fourth button on the flame to change the lighting modes.

Taps  Light Control
---------------------------
1     Change Mantle Pattern/Off
2     Change Fire Pattern/Off
3     All off/on

Updated Code:
We added some functionality to update the LEDs so I created a repository 
with the changes if you want to make modifications on your own.

Notes:
1. There is an adjustment for the capacitive sensors on the back.  If issues
   are encountered registering pushes, try adjusting the sensitivity.
2. The flame may be removed from the board, and it will continue to operate
   correctly. It will also draw less power.
3. The lower you keep the volume, the longer the batteries will last. 
4. If you add the optional DC power jack, do not supply more than 3.3V or 
   damage may occur.  Polarity is center positive. Cut BR1 if installed.
5. A few times during development, the board completely locked up.  I have
   been trying to isolate why, but I have been unable to reproduce the 
   problem with any consistency. It may be because the LED update routines
   are stealing too much CPU, but it's a hard lock so I do believe it is
   related to the original code in some way.
6. This board uses an STM32F401CCU6 CPU @ 84MHz. Approx 60.9k of RAM is
   free. The code loads each SID into memory before playing it, so this is 
   the largest file which can be played, assuming it is supported. 

Thanks, and have a great New Year!
https://texelec.com
