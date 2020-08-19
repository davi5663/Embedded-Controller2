# Embedded-Controller 2
<b>Short description:</b><br/>
In this project I want to work with Embedded-Controller part 2 and, where it's a bit more advanced. I have a case task that is about an office environment, where
I need to do certain task with my Controller. <br/>
<b>The Libraries I used for my project:</b> <br/>
<a href="https://github.com/ARMmbed/mbed-os.git">mbed-os 6.2.0</a> <br/>
<a href="https://os.mbed.com/teams/ST/code/BSP_DISCO_F746NG/">BSP_DISCO_F746NG</a> <br/>
<a href="https://os.mbed.com/users/cmatz3/code/Grove_LCD_RGB_Backlight/">GROVE_LCD_RGB_Backlight</a><br/>
<a href="https://os.mbed.com/teams/components/code/DHT/">DHT</a></br>
<a>String</a><br/>

<b>Components I used for my project:</b><br/>
<a>2 Light diodes</a><br/>
<a>1 Buzzer</a><br/>
<a>1 button</a><br/>
<a>1 Sensor for my Tempature & Humidity</a><br/>
<a>1 SoundSensor</a><br/>
<a>1 LightSensor</a><br/>

<b>Functionality:</b><br/>
In the office 
I need to write out which office the Controller is placed, I need to get an accurate tempature the office has. If the office is too cold I was thinking of 
a blue diode will turn on and a message will be shown on the touchscreen saying, the office is to cold. If the room is too hot a red 
diode will light up with a text saying the room is too hot.After a few seconds the red diode will switch off. In the evening if a high pitch noise happens, 
the buzzer will play and a text comes up telling you that the noise is too loud. If I want to shut down the buzzer I need to press a button twice. 
If it's sunny the LightSensor will tell you on the screen it's light and if it's dark on the screen you will see a text telling you it's dark. 
I will use C++ for the programming language.<br/>

<b>Changes/Problems/New Functions & Summary:</b><br/>
While I was working with this task I really enjoyed it. It was not easy since I did not work that much with C++ nor mbed. There where some problems but I managed 
to fix those problems. I am really happy that I was able to fix those. I had problems with sometimes the text disappeared but a white box stayed there. I figured
out the problem was that I had to much background color added in other places in the code. At the start I had problems with the tempature not showing up with the
humidity. I had to add a json file that converts my tempature value into numbers. I also want to add hopefully I can do it where if a high pitch noise happens in the 
evening then a buzzer will play!


<b>Created by David Szelmeczi</b><br/> 
