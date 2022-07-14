/*Author: Randal Obringer

* Date Last Modified: 1 September 2016

* Description: Implementation of a data structure to store phone numbers without duplicating digits in memory.
*	Outputs the number of unique digits for all phone numbers.
* 
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: By joining the iDroid smartphone development team, you have been given the responsibility 
*	of developing the contact manager. Obviously, what you were not told is that there are strong technical 
*	constraints for iDroid: the system doesn’t have much memory and the processor is as fast as a Cyrix from the 90s...
*	In the specifications, there are two points in particular that catch your attention:
*		1. Intelligent Assistance for entering numbers. The numbers corresponding to the first digits entered will 
*			be displayed to the user almost instantly.
*		2. Number storage optimization. First digits which are common to the numbers should not be duplicated in the memory.
*	Your task is to write a program that displays the number of items (which are numbers) required to store a list of 
*	telephone numbers with the structure presented above.

* Input: 
*	Line 1: The number N of telephone numbers.
* 	N following lines: Each line contains a phone number, with a maximum length L. Telephone numbers consist of only 
*		the digits 0 to 9 included, without any spaces.

* Output: The number of elements (referencing a number) stored in the structure.

* Constraints: 
*	0 ≤ N ≤ 10000
*	2 ≤ L ≤ 20
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/*************************************************************************/
class Node{
    public:
        Node(int n);
        ~Node();
        int getNb();
        Node* getChild();
        Node* getSibling();
        void setChild(Node* n);
        void setSibling(Node* n);
    private:
        int nb;
        Node* child;
        Node* sibling;
};

Node::Node(int n){
    nb=n;
    child=NULL;
    sibling=NULL;
}

int Node::getNb(){
    return nb;
}

Node* Node::getChild(){
    return child;
}

Node* Node::getSibling(){
    return sibling;
}

void Node::setChild(Node* n){
    child=n;
}

void Node::setSibling(Node* n){
    sibling=n;
}

/*************************************************************************/
class PhoneTree{
    public:
        PhoneTree();
        void addPhoneNumber(string nb);
        int getUniqueCount();
    private:
        int uniqueCount;
        Node* root;
};

PhoneTree::PhoneTree(){
    root=NULL;
    uniqueCount=0;
}

int PhoneTree::getUniqueCount(){
    return uniqueCount;
}

//Function: addPhoneNumber
//Description: each phone number to add always starts at the root and iteratively 
//  searches for a match to the current character in the phone number we are adding 
//  to the tree. Always terminate each iteration at the child of the current node 
//  for the next iteration's search. That way if it is null we know to add a new node
//  right away we if not to search through that current level
void PhoneTree::addPhoneNumber(string nb){ //
    Node* current=root;
    Node* previous;
    
    for(int i=0;i<nb.length();i++){
        cerr << "i is: " << i << endl;
        cerr << "*" << nb[i] << endl;
        if(current==NULL){
            current = new Node((nb[i]-'0'));
            if(i==0){
                root=current;
            }else{
                previous->setChild(current);
            }
            previous = current;
            current = current->getChild();
            uniqueCount++;
        }else if(current->getNb() == (nb[i]-'0')){
            previous = current;
            current = current->getChild();
        }else{
            bool match=false;
            
            while(current->getSibling()!=NULL){ //walk across this level in the tree until we find a match.
                previous = current;
                current = current->getSibling();
                if(current->getNb()==(nb[i]-'0')){
                    previous = current;
                    current = current->getChild(); 
                    match = true; //allow proper setup of pointers in conditon below after editing them here
                    break;
                }
            }
            if(match == false){ //if no match then we need to add a sibling to this level in the tree
                if(current->getSibling() == NULL){
                    previous = current;
                    current = new Node((nb[i]-'0'));
                    previous->setSibling(current);
                    previous = current;
                    current = current->getChild(); 
                    uniqueCount++;
                }
            }
        }
    }
}

/*************************************************************************/
int main(){
    int N; //number of phone numbers
    cin >> N; cin.ignore();
    PhoneTree tree;
    cerr << "The count of telephone numbers is: " << N << endl;
    
    for (int i = 0; i < N; i++) {
        string telephone;
        cin >> telephone; cin.ignore();
        cerr << telephone << endl;
        tree.addPhoneNumber(telephone); //breaks at 150th phone number.
        //cerr << "Count is: " << count << endl;
    }

    // The number of elements (referencing a number) stored in the structure.
    cout << tree.getUniqueCount() << endl;
}