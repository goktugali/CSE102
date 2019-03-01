#include <stdio.h>
#include <string.h>
#define BOARD_SIZE 10

typedef enum{
	P,S,M,B,T,normal
}piece;

typedef struct{
	char text[10];
	int data;
	int pos_x;
	int pos_y;
	int jump_x;
	int jump_y;
	piece p_type;
}block;

void init_board(block board[][BOARD_SIZE]);
int test_end_of_game(int pos_x,int pos_y);


int main(void){

block board[BOARD_SIZE][BOARD_SIZE];
init_board(board);

	return 0;
}
int test_end_of_game(int pos_x,int pos_y){

	if(pos_x==0 && pos_y==9)return 1;
	else return 0;
}
void init_board(block board[][BOARD_SIZE]){

int data = 1;
int data2;

	for (int i = BOARD_SIZE-1; i >= 0; --i)
		for (int j = BOARD_SIZE-1; j >= 0; --j)
			board[i][j].p_type=normal;
		
	for (int i = BOARD_SIZE-1; i >= 0; --i)
	{	
		if(i%2!=0){
			for (int j = BOARD_SIZE-1; j>=0; --j)
			{
				board[i][j].data=data;
				data++;
			}
			
		}
		else{
			data2 = data;
			for (int k = 0; k < BOARD_SIZE; ++k)
			{
				
				board[i][k].data=data2;
				++data2;
			}
			data = data2;
			
		}
	}

	for (int i = 0; i < BOARD_SIZE; ++i)
	{
		for (int j = 0; j < BOARD_SIZE; ++j)
		{
			board[i][j].pos_y=j;
			board[i][j].pos_x=i;		
		}
	}



	/** initializating M **/
	board[1][1].p_type=M;
	board[1][1].jump_x=0;
	board[1][1].jump_y=3;
	strcpy(board[1][1].text,"M{94}");

	board[2][5].p_type=M;
	board[2][5].jump_x=1;
	board[2][5].jump_y=7;
	strcpy(board[2][5].text,"M{83}");

	board[3][1].p_type=M;
	board[3][1].jump_x=2;
	board[3][1].jump_y=6;
	strcpy(board[3][1].text,"M{77}");

	board[4][6].p_type=M;
	board[4][6].jump_x=2;
	board[4][6].jump_y=6;
	strcpy(board[4][6].text,"M{77}");

	board[6][1].p_type=M;
	board[6][1].jump_x=4;
	board[6][1].jump_y=1;
	strcpy(board[6][1].text,"M{52}");

	board[8][6].p_type=M;
	board[8][6].jump_x=7;
	board[8][6].jump_y=2;
	strcpy(board[8][6].text,"M{28}");

	board[9][3].p_type=M;
	board[9][3].jump_x=8;
	board[9][3].jump_y=0;
	strcpy(board[9][3].text,"M{11}");
	/** initializating M **/

	/** initializating S **/
	board[0][7].p_type=S;
	board[0][7].jump_x=2;
	board[0][7].jump_y=2;
	strcpy(board[0][7].text,"S{72}");

	board[0][8].p_type=S;
	board[0][8].jump_x=4;
	board[0][8].jump_y=5;
	strcpy(board[0][8].text,"S{56}");

	board[2][2].p_type=S;
	board[2][2].jump_x=3;
	board[2][2].jump_y=2;
	strcpy(board[2][2].text,"S{68}");

	board[3][7].p_type=S;
	board[3][7].jump_x=4;
	board[3][7].jump_y=1;
	strcpy(board[3][7].text,"S{52}");

	board[4][9].p_type=S;
	board[4][9].jump_x=5;
	board[4][9].jump_y=6;
	strcpy(board[4][9].text,"S{44}");

	board[5][5].p_type=S;
	board[5][5].jump_x=7;
	board[5][5].jump_y=8;
	strcpy(board[5][5].text,"S{22}");

	board[7][5].p_type=S;
	board[7][5].jump_x=8;
	board[7][5].jump_y=1;
	strcpy(board[7][5].text,"S{12}");

	board[9][4].p_type=S;
	board[9][4].jump_x=9;
	board[9][4].jump_y=9;
	strcpy(board[9][4].text,"S{1 }");
	/** initializating S **/

	/** initializating T **/
	board[0][2].p_type=T;
	board[0][2].jump_x=1;
	board[0][2].jump_y=2;
	strcpy(board[0][2].text,"T");

	board[2][8].p_type=T;
	board[2][8].jump_x=2;
	board[2][8].jump_y=3;
	strcpy(board[2][8].text,"T");

	board[4][3].p_type=T;
	board[4][3].jump_x=5;
	board[4][3].jump_y=1;
	strcpy(board[4][3].text,"T");
	
	board[6][9].p_type=T;
	board[6][9].jump_x=5;
	board[6][9].jump_y=4;
	strcpy(board[6][9].text,"T");
	/** initializating T **/

	/** initializating P **/
	board[1][5].p_type=P;
	strcpy(board[1][5].text,"P");

	board[5][2].p_type=P;
	strcpy(board[5][2].text,"P");

	board[8][2].p_type=P;
	strcpy(board[8][2].text,"P");

	board[6][9].p_type=P;
	strcpy(board[6][9].text,"P");
	/** initializating P **/

	/** initializating B **/
	board[1][8].p_type=B;
	board[1][8].jump_x=1;
	board[1][8].jump_y=3;
	strcpy(board[1][8].text,"B");

	board[3][4].p_type=B;
	board[3][4].jump_x=2;
	board[3][4].jump_y=0;
	strcpy(board[3][4].text,"B");

	board[6][5].p_type=B;
	board[6][5].jump_x=5;
	board[6][5].jump_y=9;
	strcpy(board[6][5].text,"B");

	board[7][1].p_type=B;
	board[7][1].jump_x=6;
	board[7][1].jump_y=3;
	strcpy(board[7][1].text,"B");
	/** initializating B **/	
}

