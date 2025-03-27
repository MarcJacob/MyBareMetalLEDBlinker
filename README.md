**Welcome to my very first "Bare Metal" (I think ?) embedded programming project: the millionth LED blinker the world didn't need.**

I was somewhat dissatisfied with what I'd learned so far following online courses or reading "quick start" manuals that all involved either:
- Things I already know that should frankly just be taught in a dedicated C / C++ course
- Very abstract stuff I couldn't possibly have the context to take to heart like "Be careful when dynamically allocating memory on embedded platforms !" Like, sure, but you haven't even told me how to test any code at all on any platform yet.
- Very high level stuff like "Oh don't worry you can just download X or Y IDE and press the magic green button" (looking at you Arduino / STCubeIDE !)

I tend to prefer learning how things work at the most fundamental level possible and build my own foundation of understanding rather than trusting some online tutorial writer's learning plan for me or just their ability to finish their damn tutorial. So I went ahead and bought myself a B-U585I-IOT02A Discovery Kit and got started on the Datasheet, User Manual, Programming Manual and Reference Manual (*I never expected there'd be that many documents to have on hand or how much you need to cross-reference them to get ANYTHING done !*).

While I didn't set out with *zero* understanding of how things worked, I mostly followed this tutorial: https://kleinembedded.com/stm32-without-cubeide-part-1-the-bare-necessities/ while making sure I did things my own way. They're using a vastly different board in any case so I had to do a lot of research on my own which I guess is good.

So yeah, here it is. I finally managed to write something that actually blinks a specific LED (the LD6 Red LED) on the board. I almost gave up until I realized that the reason it wasn't working was because I mistakenly passed the *beginning address* of RAM memory for the initial Stack pointer whereas it of course has to be the *ending address* since the stack grows downward... Anyway.