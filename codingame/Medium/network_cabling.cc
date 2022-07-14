/*Author: Randal Obringer
*
* Date Last Modified: 30 October 2016
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Description: Find the shortest amount of cable needed to connected all houses given the (x,y) 
*	coordinates of each house and the total number of houses
*
* Problem Statement: An internet operator plans to connect a business park to the optical 
*	fiber network. The area to be covered is large and the operator is asking you to write 
*	a program that will calculate the minimum length of optical fiber cable required to 
*	connect all buildings.
*
* Rules: For the implementation of the works, the operator has technical 
*	constraints whereby it is forced to proceed in the following manner:
*		A main cable will cross through the park from the West to the East 
*		(from the position x of the most westerly building to the position
*		x of the most easterly building).
*	The minimum length will therefore depend on the position of the main cable.
*
* Input:
*	Line 1: The number N of buildings that need to be connected to the 
*		optical fiber network
*	On the N following lines: The coordinates x and y of the buildings
*
* Output: The minimum length L of cable required to connect all of the 
*	buildings. In other words, the length of the main cable plus the length 
*	of the cables dedicated to all the buildings.
*	Note: the buildings with the same position x should not in any case 
*	share the same dedicated cable.
*
* Constraints: 
*	0 < N ≤ 100000
*	0 ≤ L ≤ 2^63
*	-2^30 ≤ x ≤ 2^30
*	-2^30 ≤ y ≤ 2^30
*
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>
#include <map>
#include <math.h>

using namespace std;

/* Function to merge the two halves arr[l..m] and arr[m+1..r] of array arr[] */
void merge(long long int array[], int left, int middle, int right){
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
 
void mergeSort(long long int array[], int left, int right){
    if (left < right){
        int middle = left+(right-left)/2; //Same as (l+r)/2, but avoids overflow for large l and h
        mergeSort(array, left, middle);
        mergeSort(array, middle+1, right);
        merge(array, left, middle, right);
    }
}

int main() {
    int N; //number of houses needing connected
    cin >> N; cin.ignore();
    
    long long int y_vals[N]; //track all y vals
    
    long long int y_total=0; //hold total of y values, prevent overflow by using long long int
    
    long long int y_average; //can only be integer values, prevent overflow as well
    
    long long int x_min = LLONG_MAX;    
    long long int x_max = LLONG_MIN;
    
    //initialize all values
    for (int i = 0; i < N; i++) {
        int X; //x coordinate of current house
        int Y; //y coordinate of current house
        
        cin >> X >> Y; cin.ignore();
        cerr << X << "," << Y << endl;
        
        //build our x range and y range
        if(X>x_max) x_max=X;
        if(X<x_min) x_min=X;
        
        y_total+=Y;
        
        y_vals[i]=Y;
    }
    
    mergeSort(y_vals,0,N-1);
    int median_index = N/2;
    
    cerr << "total of y's: " << y_total << endl;
    y_average = floor(y_total/(1.0*N));
    cerr << "average y is: " << y_average << endl;
    
    
    //distances all include main cable run from left most to right most houses
    long long int dist_with_y_average = abs(x_min - x_max);
    long long int dist_with_above_y_average = abs(x_min - x_max);
    long long int dist_with_below_y_average = abs(x_min - x_max);
    long long int dist_with_median_even = abs(x_min - x_max);
    long long int dist_with_median_odd = abs(x_min - x_max);
    
    
    //calculate distances
    for(int i=0;i<N;i++){
        //check above and below because we can only use integer values and cut precision off the average already
        dist_with_above_y_average += abs(y_vals[i] - (y_average+1)); //value above average
        dist_with_y_average += abs(y_vals[i] - y_average);
        dist_with_below_y_average += abs(y_vals[i] - (y_average-1)); //value below average
        dist_with_median_even += abs(y_vals[i] - y_vals[median_index]); //account for when we have even # of houses
        if(median_index+1<N){
            dist_with_median_odd += abs(y_vals[i] - y_vals[median_index+1]); //account for when have odd # of houses (the index with N/2 would be incorrrect)
        }
    }
    
    cerr << "Distance with average y used: " << dist_with_y_average << endl;
    cerr << "Distance with above average y used: " << dist_with_above_y_average << endl;
    cerr << "Distance with below average y used: " << dist_with_below_y_average << endl;
    cerr << "Distance with median for evens: " << dist_with_median_even << endl;
    cerr << "Distance with median for odds: " << dist_with_median_odd << endl;
    
    long long int answer=LLONG_MAX;
    
    //find the minimum value from the calculated averages
    if(dist_with_y_average<answer){
        answer=dist_with_y_average;
    }
    if(dist_with_above_y_average<answer){
        answer=dist_with_above_y_average;
    }
    if(dist_with_below_y_average<answer){
        answer=dist_with_below_y_average;
    }
    
    if(dist_with_median_even<answer){
        answer=dist_with_median_even;
    }
    //will always be the lowest if condition not included here and it was false earlier
    if(dist_with_median_odd<answer && (median_index+1<N)){ 
        answer=dist_with_median_odd;
    }
    
    cerr << endl << "number of houses: " << N << endl;
    cerr << "totals are: " <<  y_total << endl;
    cerr << "averages: " <<  y_average << endl;
    cerr << "mins: " << x_min << endl;
    cerr << "maxs: " << x_max << endl;
    cerr << "Median index is: " << median_index << endl;
    
    cout << answer << endl;
}