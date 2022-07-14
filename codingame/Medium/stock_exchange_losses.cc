/*Author: Randal Obringer
*
* Date Last Modified: 28 August 2016
*
* Description: Read in stock values for a single stock in chronological order. Output the 
*	most loss the stock experienced in that time frame.
*
* Difficulty: Medium
*
* NOTE: This program is not meant to be run anywhere else but the codingame IDE at www.codingame.com
*	as the input is given through the IDE.
*
* Problem Statement: A finance company is carrying out a study on the worst 
*	stock investments and would like to acquire a program to do so. The 
*	program must be able to analyze a chronological series of stock values 
*	in order to show the largest loss that it is possible to make by buying
*	a share at a given time t0 and by selling it at a later date t1. The 
*	loss will be expressed as the difference in value between t0 and t1. If 
*	there is no loss, the loss will be worth 0.
*
* Game Input: 
*	Line 1: the number n of stock values available.
*	Line 2: the stock values arranged in order, from the date of their 
*		introduction on the stock market v1 until the last known value vn. 
*		The values are integers.
*
* Output: The maximal loss p, expressed negatively if there is a loss, otherwise 0.
*
* Constraints: 
*	0 < n < 100000
*	0 < v < 2^31
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

int main(){
    int n; //number of stock values available
    cin >> n; cin.ignore();
    
    int maxValue=INT_MIN; //not used in brute method
    int maxValIndex=0;
    int minValIndex=0;
    int minP=0; //set to 0 for if stock never decreases
    
    int stockChart[n];
    for (int i = 0; i < n; i++) { //time of stock, i=0 is earliest value of stock
        int v; //value of stock
        cin >> v; cin.ignore();
        stockChart[i]=v;
        cerr << v << " ";
    }
    cerr << endl;
    
    //linear method
    for(int i=0;i<n;i++){
        if(stockChart[i]>maxValue){
            maxValue=stockChart[i];
        }
        int p=0;
        if(maxValIndex<i){
            p=stockChart[i]-maxValue;
        }
        if(minP>p){
            minP=p;
        }
    }
    
    //brute force method - fails on large data sets
    /*for(int i=0;i<n;i++){ //earlier time
        for(int j=i+1;j<n;j++){ //later time
            int p=stockChart[j]-stockChart[i];
            if(p<minP){
                //maxValIndex=i; //not needed
                //minValIndex=j; //not needed
                minP=p;
            }
        }
    }*/

    cout << minP << endl;
}