/*File name: gifts.pl
 Author: Randy Obringer
 Description: This program can be used to find gift recommendations
 for certain groups of people.
******************************************************************/

/*Basketball*************************************************yes**/
male(basketball).
use(basketball).
sporty(basketball).
age(mid_aged,basketball).
price(moderate,basketball).
/*****************************************************************/

/*Playing Cards**********************************************no***/
male(playing_cards).
female(playing_cards).
use(playing_cards).
nerdy(playing_cards).
age(mid_aged,playing_cards).
age(old,playing_cards).
price(cheap,playing_cards).
/*****************************************************************/

/*Puzzle*****************************************************no***/
male(puzzle).
female(puzzle).
use(puzzle).
nerdy(puzzle).
age(young,puzzle).
age(mid_aged,puzzle).
age(old,puzzle).
price(cheap,puzzle).
/*****************************************************************/

/*Socks******************************************************yes**/
male(socks).
female(socks).
wear(socks).
sporty(socks).
nerdy(socks).
age(young,socks).
age(mid_aged,socks).
age(old,socks).
price(cheap,socks).
/******************************************************************/

/*Ball cap***************************************************yes***/
male(ball_cap).
wear(ball_cap).
sporty(ball_cap).
age(young,ball_cap).
age(mid_aged,ball_cap).
price(moderate,ball_cap).
/******************************************************************/

/*Barbie*****************************************************no****/
female(barbie).
use(barbie).
sporty(barbie).
nerdy(barbie).
age(young,barbie).
price(cheap,barbie).
/*******************************************************************/

/*Fishing Rod*******************************************************/
male(fishing_rod).
use(fishing_rod).
sporty(fishing_rod).
age(old,fishing_rod).
price(expensive,fishing_rod).
/*******************************************************************/

/*Shoes******************************************************yes****/
male(shoes).
female(shoes).
wear(shoes).
sporty(shoes).
nerdy(shoes).
age(young,shoes).
age(mid_aged,shoes).
age(old,shoes).
price(moderate,shoes).
/*******************************************************************/

/*Scarf*************************************************************/
female(scarf).
wear(scarf).
sporty(scarf).
nerdy(scarf).
age(mid_aged,scarf).
age(old,scarf).
price(cheap,scarf).
/*******************************************************************/

/*Knitting supplies*************************************************/
female(knitting_supplies).
use(knitting_supplies).
sporty(knitting_supplies).
nerdy(knitting_supplies).
age(old,knitting_supplies).
price(moderate,knitting_supplies).
/*******************************************************************/

/*Computer games*********************************************yes****/
male(computer_games).
use(computer_games).
nerdy(computer_games).
age(mid_aged,computer_games).
price(expensive,computer_games).
/*******************************************************************/

/*Watch******************************************************yes****/
male(watch).
female(watch).
wear(watch).
sporty(watch).
nerdy(watch).
age(mid_aged,watch).
age(old,watch).
price(moderate,watch).
/*******************************************************************/

/*Necklace**********************************************************/
female(necklace).
wear(necklace).
sporty(necklace).
nerdy(necklace).
age(mid_aged,necklace).
age(old,necklace).
price(expensive,necklace).
/*******************************************************************/

/*sweater***********************************************************/
male(sweater).
wear(sweater).
nerdy(sweater).
age(mid_aged,sweater).
age(old,sweeater).
price(moderate,sweater).
/*******************************************************************/

/*Purse*************************************************************/
female(purse).
use(purse).
sporty(purse).
nerdy(purse).
age(mid_aged,purse).
age(old,purse).
price(expensive,purse).
/*******************************************************************/

/*Jersey************************************************************/
male(jersey).
wear(jersey).
sporty(jersey).
age(mid_aged,jersey).
price(expensive,jersey).
/*******************************************************************/

/*Bike**************************************************************/
male(bike).
female(bike).
use(bike).
sporty(bike).
age(mid_aged,bike).
price(expensive,bike).
/*******************************************************************/

/*Yo-yo*************************************************************/
male(yo_yo).
female(yo_yo).
use(yo_yo).
nerdy(yo_yo).
age(young,yo_yo).
age(mid_aged,yo_yo).
price(cheap,yo_yo).
/*******************************************************************/

/*Tricycle**********************************************************/
male(tricycle).
female(tricycle).
use(tricycle).
sporty(tricycle).
age(young,tricycle).
price(moderate,tricycle).
/*******************************************************************/

/*Sun hat***********************************************************/
female(sun_hat).
wear(sun_hat).
sporty(sun_hat).
age(young,sun_hat).
age(mid_aged,sun_hat).
price(cheap,sun_hat).
/*******************************************************************/

desired_age(old):-has_house(yes).
desired_age(mid_aged):-goes_to_school(yes),has_house(no).
desired_age(young):-has_house(no),goes_to_school(no).
age_ok(G):-age(X,G),desired_age(X).

kind_of(G):-sporty(G),indoors(no).
kind_of(G):-nerdy(G),indoors(yes).

gender(G):-female(G),index_longer(yes).
gender(G):-male(G),index_longer(no).

/*people with a lot of money earned every week should be able to buy the
cheaper items as well as the more expensive items*/

desired_price(cheap):-spending_money(M),M >= 0.
desired_price(moderate):-spending_money(M),M >= 400.
desired_price(expensive):-spending_money(M),M >= 800.
price_ok(G):-price(X,G),desired_price(X).

likes_clothes(yes):-has_large_closet(yes).
likes_clothes(no):-has_large_closet(no).
type(G):-use(G),likes_clothes(no).
type(G):-wear(G),likes_clothes(yes).

gift(G):-price_ok(G),age_ok(G),gender(G),type(G),kind_of(G).

suggest:-
	write('Does the recipient own a house? (yes/no) '), read(House), nl,
	assert(has_house(House)), 
	write('Does the recipient have a large closet? (yes/no)'), 
	read(Closet), nl,
	assert(has_large_closet(Closet)), 
	write('Does the recipient go to school?  (yes/no)'), 
	read(School), nl,
	assert(goes_to_school(School)), 
	write('Is recipients index finger longer '), nl,
	write('than their ring finger? (yes/no)'), read(Finger), nl,
	assert(index_longer(Finger)), 
	write('What is your income per week?'), read(Money), nl,
	assert(spending_money(Money)), 
	write('Does the recipient spend most of '), nl,
	write('his/her time indoors? (yes/no)'), read(Indoors), nl,
	assert(indoors(Indoors)),
	findall(G,gift(G),Gs),
	write('Some gifts you might consider are: '), nl,
	writelist(Gs),
	retract(has_house(House)), retract(has_large_closet(Closet)),
	retract(goes_to_school(School)), retract(index_longer(Finger)),
	retract(spending_money(Money)), retract(indoors(Indoors)).

writelist([]).
writelist([H|T]) :- writeonce(H,T), writelist(T).  
writeonce(H,T) :- member(H,T).
writeonce(H,T) :- not(member(H,T)), write(H), nl.
