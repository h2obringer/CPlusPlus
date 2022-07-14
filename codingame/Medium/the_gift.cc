/*Author: Randal Obringer
*
* Date Last Modified: 2 November 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: If total of all budgets is less than cost then it is impossible
*	to buy that gift. Sort all budget values from least to greatest. The participant's
*	with budgets below the average cost will pay their entire budget. Keep track
*	of the new average cost and how many participants there are left to contribute.
*	Participants with budgets less than the new average cost will also pay their
*	entire budget. Again keep track of the new average cost and # of participants
*	that haven't contributed to the gift. Once we get to the individual's whose budgets
*	are more than the new average cost will only pay the average cost. The last
*	participant will usually have to pay for the yet unaccounted for remainder due
*	to division remainder being left off the average cost.
*
* Problem Statement: The Oods want to offer a present to one of them. The thing 
*	is, they all have different budgets to invest in this present. Of course, 
*	their unique wish is to find the fairest method that will determine the 
*	maximum budget that each Ood can afford. The Oods have been discussing this 
*	issue for days, and up until now, they have not managed to find a totally 
*	satisfactory solution. The Doctor decides to give a helping hand by creating
*	a program. His idea is to check if the Oods have enough money to buy the 
*	present, and if so, to calculate how much each Ood should pay, according to 
*	their respective budget limit.
*
* Rules: The Doctor has in hand the list of maximum budgets for each Ood. The 
*	Doctor's aim is to share the cost very precisely. To respect the Oods 
*	democratic values and to select the best solution, the Doctor decides that:
*		no Ood can pay more than his maximum budget
*		the optimal solution is the one for which the highest contribution is 
*			minimal
*		if there are several optimal solutions, then the best solution is the 
*			one for which the highest second contribution is minimal, and so on 
*			and so forth...
*	Moreover, to facilitate the calculations, the Doctor wants each financial 
*	participation to be an integer of the local currency (nobody should give any
*	cents).
*
*	Examples: For example, the Oods wish to buy a gift that cost 100. The first 
*		Ood has a budget of 3, the second has a budget of 45 and the third has 
*		a budget of 100. In that case:
*			Budget	Solution
*			3		3
*			45		45
*			100		52
*
*		Second example: they still wish to buy a gift that costs 100 but the 
*		second Ood has a budget of 100 this time. In that case:
*			Budget	Solution
*			3		3
*			100		48
*			100		49
*
* Input: 
*	Line 1: the number N of participants
*	Line 2: the price C of the gift
*	N following lines: the list of budgets B of participants.
*
* Output: 
*	If it is possible to buy the present : N lines, each containing the 
*	contribution of a participant. The list is sorted in ascending order.
*   Otherwise the word IMPOSSIBLE.
*
* Constraints:
*	0 < N ≤ 2000
*	0 ≤ C ≤ 1000000000
*	0 ≤ B ≤ 1000000000
*/

/* Function to merge the two halves arr[l..m] and arr[m+1..r] of array arr[] */
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool DEBUG = true;

/* Function to merge the two halves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(int array[], int left, int middle, int right){
    int i, j, k;
    int sizeL = middle - left + 1; //size of left array
    int sizeR =  right - middle; //size of right array
 
    // create temp arrays 
    int leftArray[sizeL], rightArray[sizeR];
 
    //initiate arrays
    for(i = 0; i < sizeL; i++){
        leftArray[i] = array[left + i];
    }
    for(j = 0; j < sizeR; j++){
        rightArray[j] = array[middle + 1 + j];
    }
 
    //merge arrays back together
    i = 0;
    j = 0;
    k = left;
    while (i < sizeL && j < sizeR){
        if (leftArray[i] <= rightArray[j]){
            array[k] = leftArray[i];
            i++;
        }
        else{
            array[k] = rightArray[j];
            j++;
        }
        k++;
    }
 
    //there can be leftover elements due to leftArray not being same size as the rightArray. Ensure all were copied back in.
    while (i < sizeL){
        array[k] = leftArray[i];
        i++;
        k++;
    }
    while (j < sizeR){
        array[k] = rightArray[j];
        j++;
        k++;
    }
}
 
void mergeSort(int array[], int left, int right){
    if (left < right){
        int middle = left+(right-left)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        mergeSort(array, left, middle);
        mergeSort(array, middle+1, right);
        merge(array, left, middle, right);
    }
}

int main(){
    int N; //number of participants
    cin >> N; cin.ignore();
    if(DEBUG) cerr << "There are " << N << " participants" << endl;
    int noncontributors=N; //holds the total of participants that have yet to contribute, used for math
    int C; //cost of the gift
    cin >> C; cin.ignore();
    if(DEBUG) cerr << "The cost of the gift is: " << C << endl;
    int unpaid_cost=C; //holds the amount of the gift not yet paid
    int budgets[N]; //holds each individuals budget
    long long int budget_total=0; //holds the combined budgets
    long long int average; //holds the average cost expected of participants
    int answers[N];
    long long int unpaid_average; //hold the running average cost of uncontributed particpants
    
    for (int i = 0; i < N; i++) {
        int B; //list of budgets of participants
        cin >> B; cin.ignore();
        budgets[i]=B;
        budget_total+=B;
    }
    average = C/N;
    unpaid_average = average;
    if(DEBUG) cerr << "The average budget is: " << average << endl;
    
    //sort budgets here from least to greatest so the greedy algorithm below may work properly
    mergeSort(budgets, 0, N-1);
    
    if(DEBUG){
        cerr << "Budgets in order are: " << endl;
        for (int i = 0; i < N; i++) {
            cerr << budgets[i] << endl;
        }
    }
    
    
    if(budget_total<C){
        cout << "IMPOSSIBLE" << endl;
    }else{
        //*****************BEGIN GREEDY ALGORITHM********************
        //for every participant
        for(int i=0;i<N;i++){
            //if the participant's budget is less than the average cost
            if(budgets[i]<average){
                answers[i]=budgets[i]; //the participant will contribute their entire budget
                unpaid_cost-=budgets[i]; //book keeping
                noncontributors--; //this participant has paid
                unpaid_average=unpaid_cost/noncontributors; //other participant's will have to pick up the slack
            //if the participant's budget is less than the unpaid average cost
            }else if(budgets[i]<unpaid_average){
                answers[i]=budgets[i]; //then this participant will also have to contribute their entire budget
                unpaid_cost-=budgets[i]; //book keeping
                noncontributors--; //this participant has paid
                unpaid_average=unpaid_cost/noncontributors; //other participant's will have to pick up the slack
            //if we are here then participant's have more than the unpaid average cost
            }else if(budgets[i]>=unpaid_average){
                answers[i]=unpaid_average; //participants will pay the now-average cost of the gift
                unpaid_cost-=unpaid_average; //book keeping
                noncontributors--; //this participant has paid
                if(noncontributors!=0){ //account for the last participant
                    unpaid_average=unpaid_cost/noncontributors; //should have no effect here, continue book keeping
                }
            }
        }
        //account for unpaid cost due to leftover remainder in average
        //the last participant will have to make up this cost.
        if((unpaid_cost>0)&&(answers[N-1]<budgets[N-1])){ //ensure the extra cost is within their budget
            answers[N-1]++;
            unpaid_cost--;
        }
        //*****************END GREEDY ALGORITHM********************
        
        //conduct last sanity check
        if(unpaid_cost!=0){
            //this statement should never be executed with proper book keeping above
            cout << "IMPOSSIBLE" << endl;
        }
        
        //display the solution
        for(int i=0;i<N;i++){
            cout << answers[i] << endl;
        }
    }   
}