#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct link
{	
	int number;
	struct link *next;
}link;

/** function prototypes **/
void read_to_linked_and_find_size(link * data,int *arr_size,int n);
void read_to_array(int *array,int arr_size);

void print_link_list_primes(link *data,int step);
void print_array_primes(int *array,int arr_size,int step);

int isPrime(int number);
/** function prototypes **/


int main(){

int *array;	/** Bu array, size ogrenildikten sonra dynamic olarak
				allocate edilecek **/
int arr_size;/** ve size i degiskenin icinde tutulacak **/
int size_of_arrays[3];/** 3 sayi icin sizeleri arrayde tutuyorum, 50000,75000,10000 **/

int i=0;
clock_t start_t, end_t;
/** 
	Process time : Asal sayilara karar verilip, dosyaya yazdirilma zamani ..
	**/

	/***** FOR LINK LIST ****/
	link *data;
	data=(link*)malloc(sizeof(link));
	
	int n;
	printf("------------------------------------\n");
	printf("----- Linked List Calculations -----\n");
	printf("------------------------------------\n");
	printf("* Process time: Calculation and printing file \n\n");
	while(i<3){

		/** Numaralari istege gore degistiriniz.**/
		if(i==0)
			n=50000;
		else if(i==1)
			n=75000;
		else
			n=100000;
		/** data.txt de  hep 1.000.000 eleman var 
			buradaki seciminize gore ilk n kadar elemanlar alinacak
			**/

		printf("->Calculating the process time for %d numbers..\n",n);
		/** Calculation of time **/
		start_t = clock();
		read_to_linked_and_find_size(data,&arr_size,n);
		print_link_list_primes(data,i);
		end_t = clock();
		/** Calculation of time **/

		/** editing the file **/
		FILE *linkk;
		linkk = fopen("output_prime_linkedlist.txt","a");
		fprintf(linkk, "-----------\n->Execution time calculated for first %d numbers: %ld ms.\n-----------\n", n,end_t-start_t);
		printf("# -> Process finished at %ld ms.!\n\n",end_t-start_t);
		/** editing the file **/
		
		fclose(linkk);
		free(data);
		size_of_arrays[i]=arr_size;
		++i;

	}
	printf("------------------------------------\n");
	printf("---- Dynamic Array Calculations ----\n");
	printf("------------------------------------\n");
	printf("* Process time: Calculation and printing file \n\n");
	i=0;
	while(i<3){

		printf("->Calculating the process time for %d numbers..\n", size_of_arrays[i]);
		/** Calculation of time **/
		start_t = clock();
		array = calloc(size_of_arrays[i],sizeof(int));
		read_to_array(array,size_of_arrays[i]);
		print_array_primes(array,size_of_arrays[i],i);
		end_t = clock();
		/** Calculation of time **/

		/** editing the file **/
		FILE *arr;
		arr = fopen("output_prime_dynamic_array.txt","a");
		fprintf(arr, "-----------\n->Execution time calculated for first %d numbers: %ld ms.\n-----------\n", size_of_arrays[i],end_t-start_t);
		printf("# -> Process finished at %ld ms.!\n\n",end_t-start_t);
		/** editing the file **/
		
		fclose(arr);
		free(array);
		++i;
	}
	/***** FOR LINK LIST****/

	return 0;
}

void read_to_linked_and_find_size(link * data,int *arr_size,int n){

int num;
int size = 0;
int i = 0;

FILE *file;
file = fopen("data.txt","r");

link * t;
t=data;

	while(fscanf(file,"%d,00\n",&num)==1 && i<n)
	{	
		data->number=num;
		data->next=(link *)malloc(sizeof(link));
		data=data->next;
		data->next=NULL;
		++size;	
		++i;
	}
	*arr_size = size;

	/** Linked list sayesinde, data.txt icinde kac tane sayi oldugunu
		biliyoruz, bu sayiyi size parametresine attim ve boylelikle
		tek malloc ile bir sonraki parttaki array icin gerekli yeri ayirdim

	**/
	
	data = t;
	fclose(file);

}

void read_to_array(int *array,int arr_size){

	FILE *file;
	file = fopen("data.txt","r");

	for (int i = 0; i < arr_size; ++i){
		fscanf(file,"%d,00\n",&array[i]);
	}
	
	fclose(file);
}

void print_array_primes(int *array,int size,int step){

	/** Step parametresi bir oldugunda, fopen "w" modunda aciliyor.
		3 sayi icin islem yapacagi icin, ilk yazdiktan sonra "a" modunda
		devam etmesi lazim.
		O yüzden bu parametreyi ekledim. **/

	/** Dosyadaki ornek cikti soyle cünkü :
		500000 icin (fopen mode "w")
		prime numbers - process time

		7500000 icin (fopen mode "a")
		prime numbers - process time

		1000000 icin (fopen mode "a")
		prime numbers - process time 

		**/

	FILE *fp;
	if(step==0)
		fp = fopen("output_prime_dynamic_array.txt","w");
	else
		fp=fopen("output_prime_dynamic_array.txt","a");
	fprintf(fp, "Prime numbers : \n");
	for (int j = 0; j < size; ++j){
		if(isPrime(array[j])){
			/*printf("%d\n", array[j]);*/ /* Ekrana print etmeyi aktive edebilirsiniz **/
			fprintf(fp, "%d,00\n", array[j]);	
		}
	}

	fclose(fp);
}

void print_link_list_primes(link *data,int step){

	/** Step parametresi aciklamasi, yukarıdaki ile ayni **/

	FILE *fp;
	if(step==0)
		fp = fopen("output_prime_linkedlist.txt","w");
	else
		fp=fopen("output_prime_linkedlist.txt","a");

	fprintf(fp, "Prime numbers :\n");
	link *t;
	t=data;
	while(t->next!=NULL)
	{	
		if(isPrime(t->number))
			/*printf("%d\n", t->number);*/ /* Ekrana print etmeyi aktive edebilirsiniz **/
			fprintf(fp, "%d,00\n", t->number);
		t=t->next;
	}
	fclose(fp);

}

int isPrime(int number){
	int res = 1;
	if(number==1)
		res=0;
	for (int i = 2; i <= number/2 && res==1; ++i)
		if(number%i==0)
			res=0;
	
	return res;
}
