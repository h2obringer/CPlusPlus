Homework Assingment #1

Randal Obringer



This project was very interesting to me and I enjoyed it very much. I have always 
wondered how computer 
graphics actually worked and this project has given me some 
insight on this subject. I started out with 
a simple idea of space. We were to 
implement a spaceship so why night set the spaceship in its natural
environment? 
So I created the cyber_space function which randomly places dots (stars) on the screen. 

This, to me, was the easiest part of the assignment. With coolness points in mind I knew 
that calling glutPostRedisplay() would automatically redraw those stars to create the effect 
of motion for my spaceship later on. 

Next I started actually developing my spaceship. I actually 
began with a simple cube to see if I could actually do it. Putting the cube into my project() 
function to project the 3D coordinates onto the 2D screen didn't seem to work out for me. So I 
decided to see what scaling my coordinates would do. I noticed that making all of the coordinates 
large at the same time wasn't having any effect on my object. However, scaling the z coordinate 
and making it smaller produced what I was looking for. I realize this may be wrong but like you 
said "quick and dirty is often better in computer graphics." I effectively managed, therefore to 
project my spaceship onto the center of the original 500x500 screen and look decently large. 
Working with the projection of objects has definately given me a greater apprectiation for 
OpenGL's built in projection functions and I know understand how it works to some extent. 
I would have actually fixed my function if I had more time because I think I know how to 
actually do it now. I think my major problem is coming from my usage of gluOrtho2D and thus 
changing where the point of view for my projection is...

After I had produced the basic objects 
on my screen I began to learn all about the callback functions to make my program look cooler and 
interact with me. I effectively learned how to use the glutGetModifiers() function in order to use 
the shift key on the keyboard. I also learned how to distinguish between the left and right mouse 
and use them for different effects in my program. I learned more about the glutPostRedisplay function 
and when it is needed for desirable effects. I learned more in depth the purpose of glClearColor: 
how everytime the glClear(GL_COLOR_BUFFER_BIT); will clear the screen and initialize the background 
the color that you specify with glClearColor. I also learned that glBegin/GlEnd is not the only way 
of drawing objects to the screen and that this way of drawing is called immediate mode. objects like 
circles (the thrusters in my program) can be drawn with the gluDisk function where a GLUquadricObj 
is passed as a parameter. I better know how and when to use the glTranslatef function now. Perhaps 
the two most important functions I learned were gluOrtho2D and glViewport functions. without the 
glViewport function my object would render itself off the screen upon reshaping of the window. 
I learned that the gluOrtho2D sets the z values to -1 and 1 so that objects really do appear 2D. 
Also it change the coordinate system so that (0,0) is at the bottom left corner of the window. 


Besides all that I learned also about alpha blending to make my spaceship look like its disappearing 
upon shift+right click. Reappearing upon shift+left click. I also managed to learn different schemes 
and tricks that will help me along my programming career. 
