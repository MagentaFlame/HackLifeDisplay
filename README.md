Week 4 Display - let's make something more useful loll
This means no LOL references (or will there???)
Update: no LOL references unfortunately... HLE got eliminated so I'm feeling down.

Schematics!

I added 8 pixels, initially for a "ring" but realized that microcontroller needed to plug in somewhere lol. Cool sequences could be done with this setup that I'll show in PCB. Anyways, added a switch to change color themes - sometimes cool tones are just not it - we need some warmth in life lol
<img width="1107" height="420" alt="image" src="https://github.com/user-attachments/assets/40665100-352c-49af-82b9-94b3a5a0413e" />


PCB!
<img width="898" height="846" alt="image" src="https://github.com/user-attachments/assets/72ba6468-6720-4c80-967e-161dd756f8c4" />

I made it in this weird fashion so the pixel lights running through would look cool and it will fit. I chose Hand Solder footprints so I can actually solder the 0603 stuff. I'm quite nervous for soldering!


Code!

<img width="812" height="800" alt="image" src="https://github.com/user-attachments/assets/7c7d0ef3-b148-484b-9e5c-d024d956cfa7" />

Basically, it was a big learning curve, but through searching code libraries, tutorials, research, etc etc, I managed to do it. I call a Wifi client and HTTP client, using my free API key from OpenWeatherMap. HTTP client gets the info and puts into a Json doc, which I parse for the weather section's "main" weather condition and weather ID for more specifics. I then pass it into a function to update the colors based on the inputs (added a bunch of cool colors that hopefully will look good). I added millis so it would update every 30 min, so my api would work for the whole month with enough calls. 

CAD!(?)

<img width="649" height="588" alt="image" src="https://github.com/user-attachments/assets/a9d05a90-aee6-4679-9215-ea1a3ea0cb28" />
https://cad.onshape.com/documents/576eb80d83ee613553f22006/w/4f6dd9364f57957917df3f42/e/1331975d95a1b04019fdb0a0 
So I wanted to make a bottom mount, then resin print the top container, but I ran out of time and budget. So, I'm just gonna get the hardware part fully done. I have the bottom mount done - if my school lets me I'll print it there. If not, it'll just be a simple add-on for the future!

BOM!
<img width="903" height="764" alt="image" src="https://github.com/user-attachments/assets/fdc6916f-d22e-499a-b398-ce5c2ddddec8" />
I'm a bit over... I'm super sorry but I cannot cut this down any further...

Hopefully I can get the solder from the shop!
