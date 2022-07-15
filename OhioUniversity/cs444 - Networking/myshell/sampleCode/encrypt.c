#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <string.h>

static int first_level_even=-1;
static int first_level_odd=-1;
static int second_level_even=-1;
static int second_level_odd=-1;
static int third_level_even=-1;
static int third_level_odd=-1;
static int fourth_level_even=-1;
static int fourth_level_odd=-1;

void encrypt_data(char* data){
  int i;
  first_level_even=-1;
  first_level_odd=-1;
  second_level_even=-1;
  second_level_odd=-1;
  third_level_even=-1;
  third_level_odd=-1;
  fourth_level_even=-1;
  fourth_level_odd=-1;
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%2==0){
        data[i]+=5;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]-=5;
          first_level_even=i;
        }
      }else{
        data[i]-=1;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]+=1;
          first_level_odd=i;
        }
      }
    }
  }
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%3==0){
        data[i]-=2;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]+=2;
          second_level_even=i;
        }
      }else{
        data[i]-=1;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]+=1;
          second_level_odd=i;
        }
      }
    }
  }
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%4==0){
        data[i]+=3;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]-=3;
          third_level_even=i;
        }
      }else{
        data[i]+=4;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]+=4;
          third_level_odd=i;
        }
      }
    }
  }
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%2==0){
        data[i]-=1;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]+=1;
          fourth_level_even=i;
        }
      }else{
        data[i]-=2;
        if((data[i]=='\n')||(data[i]=='\r')){
          data[i]+=2;
          fourth_level_odd=i;
        }
      }
    }
  }
}

void decrypt_data(char* data){
  int i;
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%2==0){
        if(fourth_level_even!=i){
          data[i]+=1;
        }
      }else{
        if(fourth_level_odd!=i){
          data[i]+=2;
        }
      }
    }
  }
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%4==0){
        if(third_level_even!=i){
          data[i]-=3;
        }
      }else{
        if(third_level_odd!=i){
          data[i]-=4;
        }
      }
    }
  }
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%3==0){
        if(second_level_even!=i){
          data[i]+=2;
        }
      }else{
        if(second_level_odd!=i){
          data[i]+=1;
        }
      }
    }
  }
  for(i=0;data[i]!=NULL;++i){
    if((data[i]!='\r')&&(data[i]!='\n')){
      if(i%2==0){
        if(first_level_even!=i){
          data[i]-=5;
        }
      }else{
        if(first_level_odd!=i){
          data[i]+=1;
        }
      }
    }
  }
}
