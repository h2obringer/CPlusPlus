/*Author: Randal Obringer
*
* Date Last Modified: 30 October 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Read in the Mayan Numeral Set of the digits 0-19. It's resulting position in the 
*	MayanNumber class's vector is the numeral's base 10 value. This is then used to translate
*	two Mayan Numbers that are subsequently also read in, into base 10. Overloaded math operators
*	allow us to directly execute the computation and store the result in a new MayanNumber object.
*	We then translate the base 10 value in the resulting object back into a MayanNumber before
*	returning the answer as a MayanNumber. An enumeration distinguishes the MayanNumbers between
*	a number we need to do math against, and the library of values which help us translate. 
*
* Problem Statement: Upon discovering a new Maya site, hundreds of mathematics, 
*	physics and astronomy books have been uncovered. The end of the world might 
*	arrive sooner than we thought, but we need you to be sure that it doesn't!
*	Thus, in order to computerize the mayan scientific calculations, you're 
*	asked to develop a program capable of performing basic arithmetical 
*	operations between two mayan numbers.
*
* Rules: The mayan numerical system contains 20 numerals going from 0 to 19. 
*	Here's an ASCII example of their representation: 
*		0 = .oo.	6 = o...	12 = oo..	18 = ooo.
*			o..o		----		 ----		 ---- 
*			.oo.		....		 ----		 ----
*			....		....		 ....		 ----
*
*		1 = o...	7 = oo..	13 = ooo.	19 = oooo
*			....		----		 ----		 ----
*			....		....		 ----		 ----
*			....		....		 ....		 ----
*
*		2 = oo..	8 = ooo.	14 = oooo
*			....		----		 ----
*			....		....		 ----
*			....		....		 ....
*
*		3 =	ooo.	9 = oooo	15 = ....
*			....		----		 ----
*			....		....		 ----
*			....		....		 ----
*
*		4 = oooo	10 = ....	16 = o...
*			....		 ----		 ----
*			....		 ----		 ----
*			....		 ....		 ----
*
*		5 = ....	11 = o...	17 = oo..
*			----		 ----		 ----
*			....		 ----		 ----
*			....		 ....		 ----
*
*	A mayan number is divided into vertical sections. Each section contains 
*	a numeral (from 0 to 19) representing a power of 20. The lowest section 
*	corresponds to 200, the one above to 201 and so on. Thereby, the example 
*	below is : (12 x 20 x 20) + (0 x 20) + 5 = 4805
*		
*	(Mayan 12) = 12x20^2
*	(Mayan 0) = 0x20^1
*	(Mayan 5) = 5X20^0
*
*	To spice the problem up, the mayans used several dialects, and the 
*	graphical representation of the numerals could vary from one dialect to 
*	another. The representation of the mayan numerals will be given as the 
*	input of your program in the form of ASCII characters. You will have to 
*	display the result of the operation between the two given mayan numbers. 
*	The possible operations are *, /, +, -
*
* Input:
*	Line 1: the width L and height H of a mayan numeral.
*	H next lines: the ASCII representation of the 20 mayan numerals. Each 
*		line is (20 x L) characters long.
*	Next line: the amount of lines S1 of the first number.
*	S1 next lines: the first number, each line having L characters.
*	Next line: the amount of lines S2 of the second number.
*	S2 next lines: the second number, each line having L characters.
*	Last line: the operation to carry out: *, /, +, or -
*
* Output: The result of the operation in mayan numeration, H lines per 
*	section, each line having L characters.
*
* Constraints:
*	0 < L, H < 100
*	0 < S1, S2 < 1000
*	The remainder of a division is always 0.
*	The mayan numbers given as input will not exceed 263.
*/
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;

//single = receive a single Mayan number (consisting of the multiple tiers)
//numeral_set = receive the set of numerals 0-19 to determine the Mayan dialect being used.
//used in the MayanNumbers class constructor to build the data structure properly for each case.
enum MayanType { nulled, single, numeral_set };

enum Environment { standard, debug }; //used for printing debug messages or standard output

const bool DEBUG = true; //true = print debug messages, false = print just what is needed

class MayanNumber{
    public:
        MayanNumber(MayanType t, int w, int h);
        int getValue();
        int getWidth();
        int getHeight();
        void setWidth(int w);
        void setHeight(int h);
		void setValue(long long int v);
        MayanType getType();
        void printNumber(int n, Environment e);
        void printAll(Environment e);
        void computeValue(const MayanNumber &m);
        MayanNumber operator+(const MayanNumber &m);
        MayanNumber operator-(const MayanNumber &m);
        MayanNumber operator*(const MayanNumber &m);
        MayanNumber operator/(const MayanNumber &m);
        void mayanizeValue(const MayanNumber &m);
    private:
        int width;
        int height;
        long long int value; //the value of the mayan number in base 10 - must compute
        MayanType type;
        vector< vector<string> > num;
};

MayanNumber::MayanNumber(MayanType t, int w, int h){
    type=t;
    width = w;
    height = h;
    value=-1; //initialize it to something. If negative later on then we will throw an exception.
    
    switch(t){
        case nulled:
            //can't reserve number of digits yet because we haven't translated the value yet. Used for created a temporary object;
            type=single; //change now that we have dodged soliciting user input from cases below.
            break;
        case numeral_set:
            num.reserve(20); //There are 20 numerals we need to keep track of
            for(int i=0;i<20;i++){ //initialize the vector space
                vector<string> temp;
                temp.reserve(height); //reserve the number of rows needed for this numeral
                num.push_back(temp);
            }
            
            if(DEBUG) cerr << "The numeral representations are: " << endl;
            
            //receive the numeral representations
            for (int i = 0; i < height; i++) { //for each row of the numerals (this row contains all rows of all numerals)
                string numeral;
                cin >> numeral; cin.ignore();
                
                if(DEBUG) cerr << numeral << endl;
                
                for(int j=0;j<20;j++){ //for each numeral
                    string temp = "";
                    for(int k=0;k<width;k++){ //grab the piece of the row of the numeral that belongs to the number j
                        temp+=numeral[(j*width)+k];
                    }
                    num[j].push_back(temp);
                }
            }
            break;
        case single:
            int rows; //number of rows in the current number
            cin >> rows; cin.ignore();
            int digits = rows/height; //amount of digits in the number
            num.reserve(digits); //reserve the amount of digits present in the number
            
            //initialize the vector space
            for(int i=0;i<digits;i++){ 
                vector<string> temp;
                temp.reserve(height); //reserve the number of rows needed for this digit
                num.push_back(temp);
            }
            
            for(int i=0;i<digits;i++){ //for each digit
                for (int j = 0; j < height; j++) { //for the height of each digit
                    string line;
                    cin >> line; cin.ignore();
                    num[i].push_back(line);
                }
            }
            break;
    }
}

void MayanNumber::printNumber(int n, Environment e){
    if(e==debug){
        for(vector<string>::iterator it = num[n].begin(); it != num[n].end(); ++it){
            cerr << *it << endl;
        }
    }else{
        for(vector<string>::iterator it = num[n].begin(); it != num[n].end(); ++it){
            cout << *it << endl;
        }
    }
}

void MayanNumber::printAll(Environment e){
    for(int i=0;i<num.size();i++){
        printNumber(i, e);
    }
}

int MayanNumber::getValue(){
    return value;
}

void MayanNumber::setValue(long long int v){
	if(v<0){ //MayanNumbers do not go negative.
		value=-v;
	}else{
		value=v;
	}
}

MayanType MayanNumber::getType(){
    return type;
}

int MayanNumber::getWidth(){
    return width;
}

int MayanNumber::getHeight(){
    return height;
}

void MayanNumber::setWidth(int w){
    width=w;
}

void MayanNumber::setHeight(int h){
    height=h;
}

//do not call on numeral_set object. Only call on enum type "single"
void MayanNumber::computeValue(const MayanNumber &m){
    //can only compute a value if we have a numeral_set to compare digits with
    if(m.type!=numeral_set){
        return;
    }
    
    //previously -1 so change it so our math works out later
    value=0;
    for(int i=0;i<num.size();i++){ //for every digit in the number
        for(int j=0;j<m.num.size();j++){ //for every numeral in the numeral set
            bool similar=true;
            for(int k=0;k<height;k++){ //for every row in the digit/numeral
                for(int l=0;l<m.num[j][k].length();l++){ //for every column in the numeral
                    //if digit in our number, row, letter != current digit (0-19) in numeral set, row, letter
                    if(num[i][k][l]!=m.num[j][k][l]){
                        similar=false;
                        break; //break L
                    }
                }
                if(similar==false){ //break K, on to the next numeral in the numeral set
                    break;
                }
            }
            //if we get here then the current digit was the same as the one in the numeral set, so we now know our digit value (j)
            //compute this digit of the overall value, doing this i times will yield the final result
            if(similar==true){
                //first element is highest power, last element is power 0. 
                //if size() is 3, then 3-1-0=2 for highest power. The 3rd # would be 3-1-2=0 for lowest power.
                int power = num.size()-1-i; 
                long long int base=1; //20^0=1;
                for(int a=0;a<power;a++){
                    base*=20; //20^power
                }
                    
                value+=(j*base); //j is the translated value of the digit that matched
                break; //break J, move on to the next digit in the number we are trying to compute a base 10 value for
            }
        }
    }
}

MayanNumber MayanNumber::operator+(const MayanNumber &m){
	if(value<0) throw logic_error("The left value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
	if(m.value<0) throw logic_error("The right value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
    MayanNumber result(nulled, width, height);
    if(DEBUG) cerr << "The operation to be performed: " << value << "+" << m.value << endl;
    result.value = value + m.value;
    if(DEBUG) cerr << "The result is: " << result.value << endl;
    return result;
}

MayanNumber MayanNumber::operator-(const MayanNumber &m){
	if(value<0) throw logic_error("The left value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
	if(m.value<0) throw logic_error("The right value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
    MayanNumber result(nulled, width, height);
    if(DEBUG) cerr << "The operation to be performed: " << value << "-" << m.value << endl;
    result.value = value - m.value;
    if(DEBUG) cerr << "The result is: " << result.value << endl;
    return result;    
}

MayanNumber MayanNumber::operator*(const MayanNumber &m){
	if(value<0) throw logic_error("The left value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
	if(m.value<0) throw logic_error("The right value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");MayanNumber result(nulled, width, height);
    if(DEBUG) cerr << "The operation to be performed: " << value << "*" << m.value << endl;
    result.value = value * m.value;
    if(DEBUG) cerr << "The result is: " << result.value << endl;
    return result;
}

MayanNumber MayanNumber::operator/(const MayanNumber &m){
	if(value<0) throw logic_error("The left value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
	if(m.value<0) throw logic_error("The right value has not yet been computed or it's result from previous math was negative. Try calling .computeValue(MayanNumber set object here) on the object first.");
    MayanNumber result(nulled, width, height);
    if(DEBUG) cerr << "The operation to be performed: " << value << "/" << m.value << endl;
    result.value = value / m.value;
    if(DEBUG) cerr << "The result is: " << result.value << endl;
    return result;
}

//After performing math operations we need to produce the mayan equivalent of the value and store it in num
//This is required to be called on the resulting MayanNumber from a simple math computation (*,/,+,-)
void MayanNumber::mayanizeValue(const MayanNumber &m){
	if(value<0) throw logic_error("The value for this object has not been computed yet or resulted in a negative value. Try calling .setValue(value here) on the object or set the object to the result of math on two MayanNumbers.");
    long long int base=1; //*20^0
    int power=0; //start at the smallest value
    long long int copiedValue=value; //make a copy to compute against
    
    //find the base and power
    while(base<value){
        base*=20;
        power++;
    } 
    //base and power will be over our value here so backtrack one step
	//unless the number we attempt to mayanize is 0 which makes the below
	//logic useless.
    base/=20;
    power--;
    if(power<0){ //fix if we were mayanizing value 0
        power=0;
    }
    
    //********initialize the vector space and strings, for each digit*************
    
    //there are power+1 digits in this Mayan Number so reserve them here
    num.reserve(power+1);
    for(int i=0;i<power+1;i++){ 
        vector<string> temp;
        temp.reserve(height); //reserve the number of rows needed for this digit
        num.push_back(temp);
    }
    for(int i=0;i<power+1;i++){ //for each digit
        for (int j = 0; j < height; j++) { //for the height of each digit
            string line="";
            num[i].push_back(line);
        }
    }
    //*********************end initialization**************************************
    
    if(DEBUG) cerr << "Attempting to Mayanize... " << endl;
    //if initial power is 0 then no Mayan value would be produced in the loop below
    //so cover it here
    for(int i=0;i<power+1;i++){ //first digit we find goes first in the vector
        int digit;
        //fix if we were mayanizing value 0
        if(base==0){
            digit = 0;
        }else{
            //since base is just below our value by a multiple of 20 this will give us the digit we are looking for
            digit = copiedValue/base; 
        }
        //get our new value to work against in further iterations
        copiedValue-=(digit*base);
        //get our new base 20^current power
        base/=20;
    
        num[i]=m.num[digit]; //set the vector of the numeral set's digit to our Mayan Number's vector
    }
}

//*******************************************************************************************************************************
int main(){
    int width;
    int height;
    cin >> width >> height; cin.ignore();
    if(DEBUG) cerr << "width is " << width  << " and height is " << height << endl;
    MayanNumber mn(numeral_set, width, height);
    
    if(DEBUG){
        cerr << "The numeral set is: " << endl;
        mn.printAll(debug);
    }
    
    MayanNumber first(single, width, height);
    if(DEBUG){
        cerr << "The first number is: " << endl;
        first.printAll(debug);
    }
    //the numeral has been loaded through the constructor, now compute and store it's base 10 value
    first.computeValue(mn);
    if(DEBUG) cerr << "The value of this number is: " << first.getValue() << endl;
    
    MayanNumber second(single, width, height);
    if(DEBUG){
        cerr << "The second number is: " << endl;
        second.printAll(debug);
    }
    //the numeral has been loaded through the constructor, now compute and store it's base 10 value
    second.computeValue(mn);
    if(DEBUG) cerr << "The value of this number is: " << second.getValue() << endl;
    
    string operation;
    cin >> operation; cin.ignore();
    
	MayanNumber result(nulled,width,height);
	try{
		//execute the computation
		switch(operation[0]){
			case '+':
				result = first+second;
				break;
			case '-':
				result = first-second;
				break;
			case '*':
				result = first*second;
				break;
			case '/':
				result = first/second;
				break;
			default:
				throw invalid_argument(operation + " is not a supported operation. Try one of these (+,-,*,/)");
				break;
		}
		result.mayanizeValue(mn);
	//always print exception regardless of DEBUG value
	}catch(const logic_error &e){
		cerr << e.what() << endl;
	}catch(const invalid_argument &e){
		cerr << e.what() << endl;
	}
    
    if(DEBUG) cerr << "The resulting mayan number is: " << endl;
    result.printAll(standard);
}