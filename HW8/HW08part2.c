#include <stdio.h>
#include <stdlib.h>

char * find_operations(int arr[],int ex_val,char opr[],size_t arr_len, int cursor, int current);
char * return_spaces(int arr_len);
/** These are my string functions **/
int str_comp(char str1[],char str2[]);
void str_copy(char str1[],char str2[]);
int str_len(char *str1);
/** These are my string functions **/

int main(){

	int arr[6]={25,12,6,10,32,8};
	int current = arr[0];

	char opr[5];
	str_copy(opr,"     ");
	str_copy(opr,find_operations(arr,44,opr,6,0,current));

	if(opr[0]!=' ')
		printf("Operators generated : %s\n", opr);
	else
		printf("No operators generated!\n%s\n",opr);

	return 0;
}

char * find_operations(int arr[],int ex_val,char opr[],size_t arr_len, int cursor, int current){
	
	char test[arr_len-1];

	if(cursor==arr_len-1 && current==ex_val){
	/** If current value has found, return ; **/
		return opr;
	}
	else if(cursor==arr_len-1){
	/** If cursor comes the end of the array and
		not found the ex_val, return empty string **/
		return return_spaces(arr_len);
	}

	opr[cursor]='*';
	str_copy(test,find_operations(arr,ex_val,opr,arr_len,cursor+1,current*arr[cursor+1]));
	if(str_comp(test,opr)==0)return opr;
	/** This if statements means that, program found the operators,
		so dont continue to try other operators,return current oprerators **/

	opr[cursor]='+';
	str_copy(test,find_operations(arr,ex_val,opr,arr_len,cursor+1,current+arr[cursor+1]));
	if(str_comp(test,opr)==0)return opr;
	
	opr[cursor]='-';
	str_copy(test,find_operations(arr,ex_val,opr,arr_len,cursor+1,current-arr[cursor+1]));
	if(str_comp(test,opr)==0)return opr;
	return return_spaces(arr_len);
	/** In the end, If there is no solution, function return empty string
		and stops the process.. **/
			
}

char * return_spaces(int arr_len){

	char *arr;
	//----> char arr[arr_len-1]; <-------
	arr=(char*)calloc((arr_len-1),sizeof(char));

	for (int i = 0; i < arr_len-1; ++i)
		arr[i]=' ';
			
	return arr;
}

int str_comp(char str1[],char str2[]){

	int value=0;
	int i = 0;
	while(1)
	{
		if(str1[i]!=str2[i])
			value = 1;
		++i;
		if(str1[i]=='\0' || str2[i]=='\0')
			break;
	}

	return value;
}

void str_copy(char *str1,char *str2){

	int i = 0;
	int len;

	len = str_len(str2);
	
	while(i<len)
	{
		str1[i]=str2[i];
		++i;
	}
	str1[i]='\0';	
}

int str_len(char *str){

	int i = 0;
	while(str[i]!='\0')
		++i;

	return i;
}