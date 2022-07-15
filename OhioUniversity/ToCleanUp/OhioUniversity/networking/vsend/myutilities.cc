#include "myutilities.h"


int IsAlphaNum(char c)  
{
	if (c >= 'A' && c <= 'F') return 1;
	if (c >= 'a' && c <= 'f') return 1;
	if (c >= '0' && c <= '9') return 1;
	return 0;
}

int is_valid_address(char* checkMe){
	int x=0; //1 or 2 before each colon
	int y=0; //as high as the string length 
	std::string findLength=checkMe;
	int len=findLength.length();

	for(y=0;y<len;++y){ 
		if(checkMe[y]==':'){ //if character is a colon
			if(x>2){
				return 0; //not valid if more than 3 digits before a colon
			}
			x=0;//reset number of digits seen before colon
		}else if(IsAlphaNum(checkMe[y])){ //else you are a number or a-f or A-F
			++x;
		}else{//else not valid
			return 0;
		}
	}
	return 1;
}

//***********************************************
// Function: merge() - in the case that we are given
//   part of a filter with 2 characters, this function
//   will merge those characters into 1 character. The
//   merged character will be an ascii number representative
//   of the number symbolized by the 2 characters given in
//   the parameters. This allows for comparison with the 
//   unsigned char hw_addr parameter in our main filtering
//   function on an ascii code basis.
//
// Arguments - one - the first character to be merged
//	two - the second character to be merged
//***********************************************
unsigned char merge(unsigned char one,unsigned char two){
	unsigned char result;
	unsigned char first=one;
	unsigned char second=two;

	if((first>=UPPER_A)&&(first<=UPPER_F)){ //convert lower case to number
		first=(first-HEX_U)*HEX_BASE;
	}else if((first>=LOWER_A)&&(first<=LOWER_F)){ //convert upper case to number
		first=(first-HEX_L)*HEX_BASE;
	}else if((first>=ZERO)&&(first<=NINE)){ //convert ascii number to decimal number
		first=(first-ZERO)*HEX_BASE;
	}

	if((second>=UPPER_A)&&(second<=UPPER_F)){ //convert lower case to number
		second=second-HEX_U;
	}else if((second>=LOWER_A)&&(second<=LOWER_F)){ //convert upper case to number
		second=second-HEX_L;
	}else if((second>=ZERO)&&(second<=NINE)){ //convert ascii number to decimal number
		second=second-ZERO;
	}

	result=first+second;
	return result;
}

//***********************************************
// Function: standardize() - if in the case that we are
//   given part of a filter with only one character,
//   we need to translate it to ascii so that we may
//   compare it to the unsigned char hw_addr parameter 
//   in our main filtering function on an ascii code basis.
//
// Arguments - one - the character to translate into ascii
//***********************************************
unsigned char standardize(unsigned char one){
	if((one>=UPPER_A)&&(one<=UPPER_F)){ //if A-F
		one-=HEX_U;
	}else if((one>=LOWER_A)&&(one<=LOWER_F)){ //convert upper case to number
		one=(one-HEX_L);
	}else if((one>=ZERO)&&(one<=NINE)){ //convert ascii number to decimal number
		one=(one-ZERO);
	}
	return one;
}

void convertToStandardForm(char* convertMe,unsigned char result[6]){
	int tempOne=0; //position of character in address
	int tempTwo=0; //position of second character in address
	int howMany=0; //1 or 2 to work with?
	int pos=0; //position on string
	int rPos=0; //position of result
	std::string findLength=convertMe; //convert to string so we can find its length
	int len=findLength.length(); //length of string to convert
	for(pos=0;pos<len;++pos){
		if(convertMe[pos]==':'){
			if(howMany==1){
				result[rPos]=standardize((unsigned char)convertMe[tempOne]);
			}else if(howMany==2){
				result[rPos]=merge((unsigned char)convertMe[tempOne],(unsigned char)convertMe[tempTwo]);
			}
			++rPos;
			howMany=0;
		}else{
			if(howMany==0){
				tempOne=pos;
				++howMany;
			}else if(howMany==1){
				tempTwo=pos;
				++howMany;
			}
		}
	}
}
