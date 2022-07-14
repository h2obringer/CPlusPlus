/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: The goal for your program is to safely land the "Mars Lander" shuttle, the landing
*	ship which contains the Opportunity rover. Mars Lander is guided by a program, and right now the 
*	failure rate for landing on the NASA simulator is unacceptable. Note that it may look like a difficult 
*	problem, but in reality the problem is easy to solve. This puzzle is the first level among three, 
*	therefore, we need to present you some controls you won't need in order to complete this first level.
*
* Rules: 
*	Built as a game, the simulator puts Mars Lander on a limited zone of Mars sky.
*	The zone is 7000m wide and 3000m high.
*	For this level, Mars Lander is above the landing zone, in vertical position, with no initial speed.
*
* There is a unique area of flat ground on the surface of Mars, which is at least 1000 meters wide.
*	Every second, depending on the current flight parameters (location, speed, fuel ...), the program must 
*	provide the new desired tilt angle and thrust power of Mars Lander: 
*		Angle goes from -90° to 90° . Thrust power goes from 0 to 4 .
* For this level, you only need to control the thrust power: the tilt angle should be 0.
*	The game simulates a free fall without atmosphere. Gravity on Mars is 3.711 m/s² . For a thrust power 
*	of X, a push force equivalent to X m/s² is generated and X liters of fuel are consumed. As such, a 
*	thrust power of 4 in an almost vertical position is needed to compensate for the gravity on Mars.
*
* For a landing to be successful, the ship must:
*   land on flat ground
*   land in a vertical position (tilt angle = 0°)
*   vertical speed must be limited ( ≤ 40m/s in absolute value)
*   horizontal speed must be limited ( ≤ 20m/s in absolute value)
*	Remember that this puzzle was simplified:
*	    the landing zone is just below the shuttle. You can therefore ignore rotation and always output 0 
*			as the target angle.
*	    you don't need to store the coordinates of the surface of Mars to succeed.
*	    you only need your vertical landing speed to be between 0 and 40m/s – your horizontal speed being nil.
*	    As the shuttle falls, the vertical speed is negative. As the shuttle flies upward, the vertical 
*			speed is positive.
*		For this first level, Mars Lander will go through a single test.
*
* Tests and validators are only slightly different. A program that passes a given test will pass the corresponding 
*	validator without any problem.
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
    int surfaceN; // the number of points used to draw the surface of Mars.
    cin >> surfaceN; cin.ignore();
    for (int i = 0; i < surfaceN; i++) {
        int landX; // X coordinate of a surface point. (0 to 6999)
        int landY; // Y coordinate of a surface point. By linking all the points together in a sequential fashion, you form the surface of Mars.
        cin >> landX >> landY; cin.ignore();
    }

    // game loop
    while (1) {
        int X; //x coord of lander
        int Y; //y coord of lander
        int hSpeed; // the horizontal speed (in m/s), can be negative.
        int vSpeed; // the vertical speed (in m/s), can be negative.
        int fuel; // the quantity of remaining fuel in liters.
        int rotate; // the rotation angle in degrees (-90 to 90).
        int power; // the thrust power (0 to 4).
        cin >> X >> Y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();

        if(abs(vSpeed)>39){
            cout << "0 4" << endl;
        }else{
            cout << "0 0" << endl;
        }
    }
}