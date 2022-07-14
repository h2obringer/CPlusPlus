/*Author: Randal Obringer
* Date Last Modified: 8/15/2016
* 
* Difficulty: Easy
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: Casablanca’s hippodrome is organizing a new type of horse racing: duals. During a 
*	dual, only two horses will participate in the race. In order for the race to be interesting, it is 
*	necessary to try to select two horses with similar strength. Write a program which, using a given 
*	number of strengths, identifies the two closest strengths and shows their difference with an integer (≥ 0).
*
* Input:
*	Line 1: Number N of horses
*	The N following lines: the strength Pi of each horse. Pi is an integer.
*
* Output: The difference D between the two closest strengths. D is an integer greater than or equal to 0.
*
* Constraints:
*	1 < N  < 100000
*	0 < Pi ≤ 10000000
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

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
    int minDifference=10000001; //above expected value of strengths so any value will be smaller than this.
    int N; //# of horses
    cin >> N; cin.ignore();
    
    int strengths[N];
    
    for (int i = 0; i < N; i++) {
        int Pi; //strength of horse
        cin >> Pi; cin.ignore();
        strengths[i]=Pi;
    }
    
    mergeSort(strengths,0,N-1);
    
    //compute differences and keep track of the smallest difference since that is all that is being asked for
    for(int i=0;i<N-1;i++){
        int temp = abs(strengths[i]-strengths[i+1]);
        if(minDifference>temp){
            minDifference=temp;
        }
    }

    cout << minDifference << endl;
}