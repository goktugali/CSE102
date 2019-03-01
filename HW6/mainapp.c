#include <stdio.h>
#define BUFFSIZE 1024

void menu();
void encrypt_open_msg();
void decrypt_secret_msg();
int find_size_of_line(char line[]);
void reverse_line(char line[], int line_lenght);

int main(void){

menu();	
	return 0;
}
void menu(){

	int choice;
	/** MENU PART **/
	do
	{	
		printf("1) Encrypt \n2) Decrypt\n0) Exit \n");
		printf("Enter your choice (0 to exit): ");
		scanf("%d",&choice);
		if(choice>2 || choice<0){
			printf("Wrong input!\n");
		}
		switch(choice){
			case 1:
			encrypt_open_msg();
			break;

			case 2:
			decrypt_secret_msg();
			break;

			case 0:
			printf("Program terminated.\n");
			break;

			default:
			break;
		}	
	} while (choice!=0);
}

void encrypt_open_msg(){

int key;
char line[BUFFSIZE];
int i;
int add_nummber;

	printf("Key : ");
	scanf("%d",&key);
	while(key>26 || key<0)
	{
		printf("Wrong input! Enter key : ");
		scanf("%d",&key);
	}
	add_nummber = 26 - key;// alfabe sinirini asarsa ekleyecegi miktar

   	FILE *file;
	file = fopen("open_msg.txt","r");

	FILE *wr;
	wr = fopen("secret_msg.txt","w");
    while(fgets(line, BUFFSIZE, file))
    {
		printf("\nInput processed : %s\n",line);
		reverse_line(line,find_size_of_line(line));
		i=0;
		while(line[i]!='\0')
		{	
			/** Eger alfabe sinirini asiyorsa bunu yap **/
			if((int)line[i]-key<97 && (int)line[i]>=97)
				line[i] = line[i] + add_nummber;
			else{
				if(line[i]==' ')
				line[i]='_';
				else if(line[i]=='.')
				line[i]='*';
				else{
				line[i] = line[i] - key;	
				}
			}		 	 
		 	++i;
		}
	
	printf("Encrypted message : %s",line);
	printf("\n");
	fprintf(wr, "%s\n", &line[1]);
	/** Hocam &line[1] yapmadıgımda \n i de yaziyordu dosyaya, o yüzden bunu kullandım**/
	/** Ekrana yazdırırken sıkıntı yok ancak dosyada sıkıntı yapıyor **/
	
    }
    printf("\n");
   
    fclose(file);
    fclose(wr);      
}

void decrypt_secret_msg(){

int key;
char line[BUFFSIZE];
int i,j,p;
int add_nummber;

	printf("Key :");
	scanf("%d",&key);
	while(key>26 || key<0)
	{
		printf("Wrong input! Enter key : ");
		scanf("%d",&key);
	}
	add_nummber = 26 - key;

    FILE *file;
    file = fopen("secret_msg.txt","r");

    FILE *wr;
	wr = fopen("open_msg.txt","w");
    while(fgets(line, BUFFSIZE, file))
    {
	    printf("\nInput processed : %s",line);
	    reverse_line(line,find_size_of_line(line));
	 
	    i = 0;
		while(line[i]!='\0')
		{	
			/** Eger alfabe sinirini asiyorsa bunu yap **/
			if((int)line[i]+key>122 && (int)line[i]>=97){	
				line[i] = line[i] - add_nummber;
			}
			/** All combinations for decryption **/
			else{
				if(line[i]=='_')
				line[i]=' ';
				else if(line[i]=='*')
				line[i]='.';
				else{
				line[i] = line[i] + key;
				}
			} 	
	    	++i;
	    }
	/** Printing **/
    printf("Decrypted message : %s",line);
    printf("\n");
    fprintf(wr, "%s\n", &line[1]);
    /** Hocam &line[1] yapmadıgımda \n i de yaziyordu dosyaya, o yüzden bunu kullandım**/
	
    }
    fclose(file);
    fclose(wr);   
}

int find_size_of_line(char line[]){

	int i = 0;
	while(line[i]!='\0')++i;
	
	return i;
}

void reverse_line(char line[], int line_lenght){

int last_item = line_lenght-1;
int i = 0;
char tmp;

	/** Reversing the last and first items **/
	while(i<line_lenght/2)
	{
		tmp=line[i];
		line[i]=line[last_item];
		line[last_item]=tmp;

		++i;
		--last_item;
	}		
}