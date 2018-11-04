#include "intal.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

char* 	reverse(char* str);
void* 	intal_create(const char* str);
int 	intal_compare(void* intal1, void* intal2);
char* 	intal2str(void* intal);
void*	intal_add(void*	intal1, void* intal2);
void* 	intal_increment(	void* intal);
char* 	diff(void* intal1, void* intal2);
void* 	intal_diff(void* intal1, void* intal2);
void* 	intal_decrement(void* intal);
void* 	long_multiplication(void* intal1, void* intal2);
void* 	intal_multiply(void* intal1, void* intal2);
void* 	intal_divide(void* intal1, void* intal2);
void* 	intal_pow(void* intal1, void* intal2);
void 	intal_destroy(void* intal);

char* reverse(char* str){
	int len=strlen(str);
	int index=0;
	char* answer=(char*)malloc(sizeof(char)*len+1);
	for(int i=len-1;i>=0;i--){
		answer[index++]=str[i];
	}
	answer[index]='\0';
	return answer;
}

void* intal_create(const char* str){

	int len=strlen(str);	
	if(len==0) 
		return NULL;

	if(str[0]=='-') 
		return NULL;

	for(int i=0;i<len;i++){  
		char ch=str[i];
		if(ch<'0' || ch>'9' )
			return NULL;
	}

	char* number=(char*)malloc(sizeof(char)*len+1);
	strcpy(number,str);	
	strcpy(number,reverse(number));
	
	while(number[--len]=='0' && len>0)
		number[len]='\0';
	
	strcpy(number,reverse(number));

	return number;
}

int intal_compare(void* intal1, void* intal2){

	if(intal1==NULL || intal2==NULL) 
		return 0;   //-2

	char* str1=(char*)intal1;
	char* str2=(char*)intal2;
	int len1=strlen(str1);
	int len2=strlen(str2);

	if(len1>len2) return 1;               
	else if(len2>len1) return -1;
	else return strcmp(str1,str2);	   	
}

char* intal2str(void* intal){
	if(intal==NULL) return NULL; // Nan
	
	char* str=(char*)malloc(strlen((char*)intal)); 
	strcpy(str,(char*)intal);
	return str;
}

void* intal_add(void* intal1, void* intal2){

	if(intal1==NULL || intal2==NULL) 
		return NULL;
	
	char* str1=(char*)intal1;
	char* str2=(char*)intal2;

	int len1=strlen(str1);
	int len2=strlen(str2);

	char* answer=(char*)malloc(sizeof(char)*(len1+len2+1));
	char* str1r=(char*)malloc(sizeof(char)*len1);
	char* str2r=(char*)malloc(sizeof(char)*len2);

	strcpy(str1r,reverse(str1));
	strcpy(str2r,reverse(str2)); 

	int result=0,carry=0,i=0;
	while(i<len1 && i<len2){							
		result=(str1r[i]-'0')+ (str2r[i]-'0')+ carry;
		if(result>9){
			carry=1;
			result=result%10;
		}
		else 
			carry=0;
		answer[i++]=result +'0';
	}
	while(i<len1){							
		result= (str1r[i]-'0')+carry;
		if(result>9){
			carry=1;
			result=result%10;
		}
		else 
			carry=0;

		answer[i++]=result +'0';
	}
	while(i<len2){						
		result= (str2r[i]-'0')+carry;
		if(result>9){
			carry=1;
			result=result%10;
		}
		else 
			carry=0;
		answer[i++]=result +'0';
	}
	if(carry==1)					
		answer[i++]='1';
	answer[i]='\0';

	strcpy(answer,reverse(answer));

	free(str1r);
	free(str2r);

	return answer;
}

void* intal_increment(void* intal){
	if(intal==NULL) 
		return NULL;    
	return intal_add(intal, intal_create("1")); 
}

char* diff(void* intal1, void* intal2){

	char* str1=(char*)intal1;
	char* str2=(char*)intal2;

	int len1=strlen(str1);
	int len2=strlen(str2);

	char* answer=(char*)malloc(sizeof(char)*len1);
	
	char* str1r=(char*)malloc(sizeof(char)*len1);
	char* str2r=(char*)malloc(sizeof(char)*len2);
	strcpy(str1r,reverse(str1));    
	strcpy(str2r,reverse(str2));

	int res=0,borrow=0,i=0;
	
	while(i<len1 && i<len2){
		res = (str1r[i]-'0') - (str2r[i]-'0') - borrow;
		if(res<0){
			borrow=1;
			res=res+10;
		}
		else borrow=0;
		answer[i++]=res +'0';

	}
	while(i<len1){
		res= (str1r[i]-'0') - borrow;
		if(res <0){
			borrow=1;
			res=res+10;
		}
		else borrow=0;

		answer[i++]=res +'0';
	}
	answer[i]='\0';
	
	while(answer[--i]=='0')
		answer[i]='\0';
	
	strcpy(answer,reverse(answer));
	free(str1r);
	free(str2r);
	return answer;	
}

void* intal_diff(void* intal1, void* intal2){
	
	if(intal1==NULL || intal2==NULL) return NULL;

	int n=intal_compare(intal1,intal2);  
	if(n==0)
		return intal_create("0");
	if(n>0)
		return diff(intal1,intal2);
	else
		return diff(intal2,intal1);
}

void* intal_decrement(void* intal){

	if(intal==NULL) 
		return NULL;
	void *zero=intal_create("0");
	if(intal_compare(intal,zero)==0) 
		return zero;  
	return intal_diff(intal, intal_create("1"));
}

void* long_multiplication(void* intal1, void* intal2){
	
	char* str1=intal2str(intal1);
	char* str2=intal2str(intal2);
	
	int len1=strlen(str1);
	int len2=strlen(str2);
	int i;

	char* str1r=(char*)malloc(sizeof(char)*len1+1);
	char* str2r=(char*)malloc(sizeof(char)*len2+1);
	char* answer=(char*)malloc(sizeof(char)*(len1+len2)+1);
	int* digits=(int*)malloc(sizeof(int)*(len1+len2)+1);
	for (i = 0; i<(len1+len2); i++)
        digits[i] = 0;   

	strcpy(str1r,reverse(str1));
	strcpy(str2r,reverse(str2));
	
	for(i=0;i<len2; i++){
		for(int j=0;j<len1;j++)
			digits[i+j]+= (str1r[j]-'0')*(str2r[i]-'0');
		
	}
	int carry=0;
	for(i=0;i<len1+len2;i++){
		digits[i]+=carry;
		answer[i]=(digits[i]%10) + '0';
		carry=digits[i]/10;
	}
	free(digits);
	free(str1r);
	free(str2r);
	answer[i]='\0';

	while(answer[--i]=='0')
		answer[i]='\0';
	
	strcpy(answer,reverse(answer));
	
	return answer;
}

void* intal_multiply(void* intal1, void* intal2){
	if(intal1==NULL || intal2==NULL) return NULL;
	void *zero=intal_create("0");
	if(intal_compare(intal1,zero)==0 || intal_compare(intal2,zero)==0) return zero;

	if(intal_compare(intal1,intal2)>=0) 
		return long_multiplication(intal1,intal2);
	else 
		return long_multiplication(intal2,intal1);
}

void* intal_divide(void* intal1, void* intal2){

	if(intal1==NULL || intal2==NULL) return NULL;

	if(intal_compare(intal2,intal_create("0"))==0)	return NULL; //division by zero
	if(intal_compare(intal1,intal_create("0"))==0)	return intal_create("0"); 

	if(intal_compare(intal1,intal2)<0)	return intal_create("0");
	if(intal_compare(intal2,intal_create("1"))==0)	return intal1;

	char digit[2];
	digit[1]='\0';

	char* str1=(char*)intal1;
	char* str2=(char*)intal2;
	int len1=strlen(str1);
	int len2=strlen(str2);
	char*temp=(char*)malloc(len2+2);
	char*answer=(char*)malloc(len1-len2+2);

	int i,j,k;
	for(i=0;i<len2;i++)
		temp[i]=str1[i];
	temp[i]='\0';
	i=0;

	void* multiplier;
	j=len2;
	while(j<=len1){
			void* temp2=intal_create(temp);
			void* op2=intal_create(str2);
			if(intal_compare(temp2,op2)<0){
			    temp[strlen(temp)+1]='\0';
			    if(j==len1){
			        answer[i++]='0';
			        break;
			    }
			    temp[strlen(temp)]=str1[j];
			    temp2=intal_create(temp);
			    j++;
			    answer[i++]='0';
			}
		k=0;
		while(intal_compare(temp2,op2)>-1){
		    k++;
		    if(k<10){
		        digit[0]=k+'0';
		        multiplier=intal_create(digit);
			}
		    else
		        multiplier=intal_create("10");
		    op2=intal_multiply(intal2,multiplier);
		}
		if(j==len1){
		    if(k>0)
		        answer[i++]=k-1+'0';
		    else
		        answer[i++]='0';
		    break;
		}
		if(k==0)
		    answer[i++]='0';
		else
		    answer[i++]=k-1+'0';
		
		op2=intal_diff(op2,intal2);
		void* diff=intal_diff(temp2,op2);
		
		temp=intal2str(diff);
		for(k=0;k<strlen(temp);k++)
		    temp[k]=temp[k];

		temp[k++]=str1[j++];
		temp[k]='\0';

	}
	answer[i]='\0';
	free(temp);
	free(multiplier);
	return intal_create(answer);
}

void* intal_pow(void* intal1, void* intal2){

    if(intal1==NULL ||intal2==NULL)	return NULL;

    void *intal;
    char *str1=intal2str(intal1);
    char *str2=intal2str(intal2);
    
    if(str1[0]=='0')
        return intal_create("0");

    if(str2[0]=='0')
        return intal_create("1");

    void *two=intal_create("2");
    intal=intal_pow(intal1,(intal_divide(intal2,two)));

    if((str2[strlen(str2)-1]-'0')%2==0)//even
        return intal_multiply(intal,intal);

    else
        return intal_multiply(intal1,(intal_multiply(intal,intal)));
}

void intal_destroy(void* intal){

	if(intal==NULL) 
		return;
	free(intal);
}