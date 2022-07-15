Randy Obringer

In this assignment I chose to implement my planets and asteroids as spheres.
I used a class to create the sun, then I used the sun as a parent class to most other objects. 
I chose to do this becaues all of the terrestrial objects had most of the same functions, the 
only difference is the value of the variables each class owned. So i overwrote all of the 
constructors to include different sized radii and start distances from the orgin as well as 
different orbit speeds. This way every object can move around independent from one another. 

I implemented my ships with triangle fans. I rendered them differnt colors to same time in creating a 
completely different ship. This was extremely helpful as I had limited time to work on this project 
and with all the requirements for this assignment time was a major issue. 

I spent a lot of time trying to implement the movement of the ship. I started out trying to move the ship through the world and trying to tranform the projection matrix as well so the camera would follow the ship. After many struggles I finally found out that this was not the way to go; that move all the objects in the world instead of the ship would get better results. 

Because I put so much time into the movement of the ship and could only get one axis to move correctly at a time I decided to break it up and make one ship move with angle increments in the x angles and the other ship move in the y angles. This saved me time as well. I couldn't get the functions from math.h to work for me so I did my own function with the typed in values of sin from angle ranging from 0-90. 

I wanted my aliens to look cool and I found a great coding example that provided the construction of torus shapes. I rendered my spaceships as such.I did not have time to implement an object with varrying heights or do collision detection with every object.3-dimensional programming was a big jump and at the end I finally got the swing of things.

I pride myself at how I got the ships to move how well they do through space. I tried matrix transformations and feel I got close but I couldnt get the camera to follow the ship the same way so I quit that approach after much frustration.

I finally managed to split my program up into multiple files. I had to used classes which is not what I wanted to actually do but it worked out in the end. That took me a little learning curve as well to get back into that since I'm not used to working with such big programs... 

Asteroids are spheres that don't orbit the sun in the same way the planets do. They rendered in a whitish texture.

New: 

I have improved the Error checking of my program with loading textures. It will tell you which file it had trouble loading now. 

I have fixed the flickering in my program.

My aliens now move.

There is collision detection between the ship and the sun, and with the ship and the outer regions of "space".

In first person view the user can look around while maintaining the ships coarse of movement.

Viewing the world from an alien's perspective has now been implemented. The user can click on the alien he/she wishes to view the world from. The user can undo this view by pressing 'f' for first person view.

I have fixed the "new game feature". By pressing 'n' the user can restart the game correctly. 

I have cleaned up some code to make it more readable.

I have fixed issues with pausing the game. (FUEL management while paused)

I have removed the ability to switch the user's view by clicking on the ship to elimate some frustration during game play.

I have implemented a reshape function to allow proper resizing of the window.

Note: Please move all my .bmp files into a file called "textures"

