/*Author: Randal Obringer
*
* Date Last Modified: 3 September 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Program the "War" Card game. Greater card wins per round, if cards are equal
*	then a war commences. Each player lays down 3 cards then continues with more wars until their cards do
*	not equal. Winner will take all cards from the war and place player1's cards in the deck first followed
*	by player2's cards. Implement our own queue class to add queues together faster for long test cases.
*	First impelementation using standard queue class is commented out at bottom which fails long test cases
*	due to time constraints.
*
* Problem Statement: Your goal is to write a program which finds out which player is the winner for a given 
*	card distribution of the "war" game.
*
* Rules: War is a card game played between two players. Each player gets a variable number of cards of the 
*	beginning of the game: that's the player's deck. Cards are placed face down on top of each deck.
*	Step 1 : the fight
*		At each game round, in unison, each player reveals the top card of their deck – this is a "battle" – 
*		and the player with the higher card takes both the cards played and moves them to the bottom of their 
*		stack. The cards are ordered by value as follows, from weakest to strongest:
*			2, 3, 4, 5, 6, 7, 8, 9, 10, J, Q, K, A.
*	Step 2 : war
*		If the two cards played are of equal value, then there is a "war". First, both players place the three 
*		next cards of their pile face down. Then they go back to step 1 to decide who is going to win the war 
*		(several "wars" can be chained). As soon as a player wins a "war", the winner adds all the cards from 
*		the "war" to their deck.
*	Special cases:
*		If a player runs out of cards during a "war" (when giving up the three cards or when doing the battle), 
*		then the game ends and both players are placed equally first. The test cases provided in this puzzle 
*		are built in such a way that a game always ends (you do not have to deal with infinite games)
*
* Each card is represented by its value followed by its suit: D, H, C, S. For example: 4H, 8C, AS.
* When a player wins a battle, they put back the cards at the bottom of their deck in a precise order. First 
* the cards from the first player, then the one from the second player (for a "war", all the cards from the 
* first player then all the cards from the second player).
*
* For example, if the card distribution is the following:
*	Player 1 : 10D 9S 8D KH 7D 5H 6S
*	Player 2 : 10H 7H 5C QC 2C 4H 6D
*	Then after one game turn, it will be:
*	Player 1 : 5H 6S 10D 9S 8D KH 7D 10H 7H 5C QC 2C
*	Player 2 : 4H 6D
*
* Victory Conditions: A player wins when the other player no longer has cards in their deck.
*
* Game Input: 
*	Line 1: the number N of cards for player one.
*	N next lines: the cards of player one.
*	Next line: the number M of cards for player two.
*	M next lines: the cards of player two.
*
* Output:
*	If players are equally first: PAT
*	Otherwise, the player number (1 or 2) followed by the number of game rounds separated by a space character. 
*		A war or a succession of wars count as one game round.
* 
*Constraints:
*	0 < N, M < 1000
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <sstream>

//function definition to convert int to string
#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

using namespace std;
//********************************************************************
class Card{
    public:
        Card();
        Card(string card);
        int getValue();
        void setValue(string s);
        char getSuit();
        void setSuit(char c);
        string getCard();
    private:
        int value;
        char suit;
};

Card::Card(){
    value=0;
    suit='X';
}

Card::Card(string card){
    suit = card[card.length()-1];
    //value = card.substr(0,card.length()-1);
    setValue(card);
}

int Card::getValue(){
    return value;
}

void Card::setValue(string s){
    //value=s;
    switch(s[0]){
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            value = s[0]-'0';
            break;
        case '1':
            value = 10;
            break;
        case 'J':
            value = 11;
            break;
        case 'Q':
            value = 12;
            break;
        case 'K':
            value = 13;
            break;
        case 'A':
            value = 14;
            break;
        default:
            value = 0;
    }
}

char Card::getSuit(){
    return suit;
}

void Card::setSuit(char c){
    suit=c;
}

string Card::getCard(){
    return SSTR(value)+suit;
}

//********************************************************************
class CardNode{
    public:
        CardNode(Card c);
        ~CardNode();
        CardNode* getNext();
        Card getCard();
        void setNext(CardNode* c);
    private:
        Card card;
        CardNode* next;
};

CardNode::CardNode(Card c){
    card=c;
    next=NULL;
}

CardNode::~CardNode(){
    if(next!=NULL){
        free(next);
    }
}

CardNode* CardNode::getNext(){
    return next;
}

Card CardNode::getCard(){
    return card;
}

void CardNode::setNext(CardNode* c){
    next=c;
}

//********************************************************************
class CardQueue{
    public:
        CardQueue();
        ~CardQueue();
        void explicitFree();
        Card front();
        void push(Card c);
        void push(CardQueue q);
        bool empty();
        void pop();
        CardNode* getFront();
        CardNode* getBack();
    private:
        CardNode* first;
        CardNode* last;
};

CardQueue::CardQueue(){
    first=last=NULL;
}

CardQueue::~CardQueue(){
    /*while(first!=NULL){ //not needed because we assign the whole data structure to the next CardQueue with push. Deleting here would affect the other data set.
        CardNode* current = first;
        first = first->getNext();
        //cerr << current->getCard().getCard() << " will be deleted" << endl;
        free(current);        
    }*/
    first=last=NULL;
}

//Because of our push(CardQueue q) implementation we must explicitly free our queue at end of usage
//  of any Deck
void CardQueue::explicitFree(){
    while(first!=NULL){ 
        CardNode* current = first;
        first = first->getNext();
        cerr << current->getCard().getCard() << " will be deleted" << endl;
        free(current);        
    }
    first=last=NULL;   
}

CardNode* CardQueue::getFront(){
    return first;
}

CardNode* CardQueue::getBack(){
    return last;
}

Card CardQueue::front(){
    return first->getCard();
}

void CardQueue::push(Card c){
    if(first==NULL){
        first=new CardNode(c);
        last=first;
    }else{
        last->setNext(new CardNode(c));
        last=last->getNext();
    }
}

//Solves the speed problem we were having with the standard queue
void CardQueue::push(CardQueue q){
    if(first==NULL){
        first=q.getFront();
        last=q.getBack();
    }else{
        last->setNext(q.getFront()); 
        last=q.getBack();
    }
}

bool CardQueue::empty(){
    if(first==NULL){
        return true;
    }else{
        return false;
    }
}

void CardQueue::pop(){
    CardNode* current = first;
    first = first->getNext();
    free(current);
}

//********************************************************************
class Deck{
    public:
        Deck();
        ~Deck();
        void addCard(string card);
        void addCard(Card c);
        void addPile(CardQueue pile);
        Card nextCard();
        bool empty();
        
    private:
        CardQueue deck;
};

Deck::Deck(){
}

Deck::~Deck(){
    deck.explicitFree();
}

void Deck::addCard(string card){
    Card c(card);
    deck.push(c);
}

void Deck::addCard(Card c){
    deck.push(c);
}

void Deck::addPile(CardQueue pile){
    deck.push(pile);
}

Card Deck::nextCard(){
    Card c;
    if(!deck.empty()){
        c = deck.front();
    }
    deck.pop();
    return c;
}

bool Deck::empty(){
    return deck.empty();
}
//********************************************************************

int main(){
    Deck p1;
    int n; // the number of cards for player 1
    cin >> n; cin.ignore();
    for (int i = 0; i < n; i++) {
        string cardp1; // the n cards of player 1
        cin >> cardp1; cin.ignore();
        cerr << cardp1 << endl;
        p1.addCard(cardp1);
    }
    
    Deck p2;
    int m; // the number of cards for player 2
    cin >> m; cin.ignore();
    for (int i = 0; i < m; i++) {
        string cardp2; // the m cards of player 2
        cin >> cardp2; cin.ignore();
        cerr << cardp2 << endl;
        p2.addCard(cardp2);
    }
    
    int roundCount=0;
    bool tie = false;
    string answer=""; //player# and roundCount
    
    while((!p1.empty())&&(!p2.empty())){
        roundCount++;
        Card warCardP1 = p1.nextCard();
        Card warCardP2 = p2.nextCard();
        
        if(warCardP1.getValue()>warCardP2.getValue()){
            p1.addCard(warCardP1);
            p1.addCard(warCardP2);
            cerr << "P1 won the battle" << endl;
        }else if(warCardP1.getValue()<warCardP2.getValue()){
            p2.addCard(warCardP1);
            p2.addCard(warCardP2);
            cerr << "P2 won the battle" << endl;
        }else{ //The cards are equal. WAR!
            cerr << "WAR!" << endl;
            CardQueue pile1;
            CardQueue pile2;
            tie=false;
            while(warCardP1.getValue()==warCardP2.getValue()){ //continue successive wars while cards are of equal value
                pile1.push(warCardP1);
                pile2.push(warCardP2);
                for(int i=0; i<3; i++){
                    if(!p1.empty()){
                        pile1.push(p1.nextCard());
                    }else{
                        tie=true;
                        break;
                    }
                    if(!p2.empty()){
                        pile2.push(p2.nextCard());
                    }else{
                        tie=true;
                        break;
                    }
                }
                
                if(!p1.empty()){
                    warCardP1 = p1.nextCard();
                }else{
                    tie=true;
                    break;
                }
                
                if(!p2.empty()){
                    warCardP2 = p2.nextCard();
                }else{
                    tie=true;
                    break;
                }
                
                if(warCardP1.getValue()>warCardP2.getValue()){
                    p1.addPile(pile1);
                    p1.addCard(warCardP1);
                    p1.addPile(pile2);
                    p1.addCard(warCardP2);
                    cerr << "P1 won the war" << endl;
                }else if(warCardP1.getValue()<warCardP2.getValue()){
                    p2.addPile(pile1);
                    p2.addCard(warCardP1);
                    p2.addPile(pile2);
                    p2.addCard(warCardP2);
                    cerr << "P2 won the war" << endl;
                }else{
                    cerr << "A successive war will commence" << endl;
                }
            } //end while loop
        } //end else
    } //end while loop
    
    if(tie){
        answer = "PAT";
    }else if(p1.empty()){
        answer = "2 " + SSTR(roundCount);
    }else if(p2.empty()){
        answer = "1 " + SSTR(roundCount);
    }
    
    cout << answer << endl;
}