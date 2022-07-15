//**************************************************************************************
//File: length7.cc
//
//Author: Randal Obringer
//
//Date Last Modified: ~2011
//
//Desciption: Implementation of hashing class on strings A-ZZZZZZZ
//**************************************************************************************

#include "length7.h"

length7::length7(){
	HASH0=HASH996=HASH500=HASH400=HASH211=0;
}

//compute a hash value for a given string and hashcode# (M)
long long length7::hash(string &x,int M){
	long long sum=0;
	for(int i=0;i<x.length();i++){
		long long power=pow(26,i);
		sum+=(((x[i]-65)%M)*(power%M)%M);
	}
	return sum;
}

//computes hash codes for every combination of A-ZZZZZZZ using hashcode# 997
//totals hash values of 0, 996, 400, 500, and 211
void length7::compute(){
	string output;
	for(char c1='A';c1<='Z';c1++){ //1st loop
		output="";
		output+=c1;
		TOTAL++;
		if(hash(output,997)==0){
			HASH0++;
		}
		if(hash(output,997)==996){
			HASH996++;
		}
		if(hash(output,997)==400){
			HASH400++;
		}
		if(hash(output,997)==500){
			HASH500++;
		}
		if(hash(output,997)==211){
			HASH211++;
		}
		for(char c2='A';c2<='Z';c2++){ //2nd loop
			string o2;
			o2=output+c2;
			TOTAL++;
			if(hash(o2,997)==0){
				HASH0++;
			}
			if(hash(o2,997)==996){
				HASH996++;
			}
			if(hash(o2,997)==400){
				HASH400++;
			}
			if(hash(o2,997)==500){
				HASH500++;
			}
			if(hash(o2,997)==211){
				HASH211++;
			}
			for(char c3='A';c3<='Z';c3++){ //3rd loop
				string o3;
				o3=o2+c3;
				TOTAL++;
				if(hash(o3,997)==0){
					HASH0++;
				}
				if(hash(o3,997)==996){
					HASH996++;
				}
				if(hash(o3,997)==400){
					HASH400++;
				}
				if(hash(o3,997)==500){
					HASH500++;
				}
				if(hash(o3,997)==211){
					HASH211++;
				}
				for(char c4='A';c4<='Z';c4++){ //4th loop
					string o4;
					o4=o3+c4;
					TOTAL++;
					if(hash(o4,997)==0){
						HASH0++;
					}
					if(hash(o4,997)==996){
						HASH996++;
					}
					if(hash(o4,997)==400){
						HASH400++;
					}
					if(hash(o4,997)==500){
						HASH500++;
					}
					if(hash(o4,997)==211){
						HASH211++;
					}
					for(char c5='A';c5<='Z';c5++){ //5th loop
						string o5;
						o5=o4+c5;
						TOTAL++;
						if(hash(o5,997)==0){
							HASH0++;
						}
						if(hash(o5,997)==996){
							HASH996++;
						}
						if(hash(o5,997)==400){
							HASH400++;
						}
						if(hash(o5,997)==500){
							HASH500++;
						}
						if(hash(o5,997)==211){
							HASH211++;
						}
						for(char c6='A';c6<='Z';c6++){ //6th loop
							string o6;
							o6=o5+c6;
							TOTAL++;
							if(hash(o6,997)==0){
								HASH0++;
							}
							if(hash(o6,997)==996){
								HASH996++;
							}
							if(hash(o6,997)==400){
								HASH400++;
							}
							if(hash(o6,997)==500){
								HASH500++;
							}
							if(hash(o6,997)==211){
								HASH211++;
							}
							for(char c7='A';c7<='Z';c7++){ //7th loop
								string o7;
								o7=o6+c7;
								TOTAL++;
								//o7=o3+c7;
								if(hash(o7,997)==0){
									HASH0++;
								}
								if(hash(o7,997)==996){
									HASH996++;
								}
								if(hash(o7,997)==400){
									HASH400++;
								}
								if(hash(o7,997)==500){
									HASH500++;
								}
								if(hash(o7,997)==211){
									HASH211++;
								}
							}
						}
					}
				}
			}
		}
	}
}


//Accessors
long long length7::getTotal(){
	return TOTAL;
}

long long length7::get0(){
	return HASH0;
}

long long length7::get996(){
	return HASH996;
}

long long length7::get500(){
	return HASH500;
}

long long length7::get400(){
	return HASH400;
}

long long length7::get211(){
	return HASH211;
}


