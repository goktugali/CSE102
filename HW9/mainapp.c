#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER 1024
typedef struct 
{	
	int **map;
	int width;
	int height;
	int flower_x;
	int flower_y;
	
}forest;

typedef struct $
{	
	int coord_x;
	int coord_y;
	int water_bottle_size;
	
}botanist;

void init_game(forest *forest, botanist *botanist);
int search(forest *forest,botanist *botanist);
void print_map(forest forest);

int main(){

srand(time(NULL));

forest forest;
botanist botanist;

	init_game(&forest,&botanist);

	int test = search(&forest,&botanist);
	print_map(forest);
	if(test)
		printf("I have found on it (%d,%d)\n",forest.flower_x,forest.flower_y);
	else
		printf("Help, I'm on (%d,%d)\n",botanist.coord_x,botanist.coord_y);

	return 0;
}
void init_game(forest *forest, botanist *botanist){
	char ** map;
	char sepr;

	FILE *file;
	file=fopen("init.csv","r");
	if(file==NULL)
		printf("Cannot open the file ! Exiting...\n");

	fscanf(file,"%d",&botanist->water_bottle_size);
	fscanf(file,"%d%c%d",&forest->width,&sepr,&forest->height);
				
	map = calloc(2*forest->height-1,sizeof(char*));
	for (int i = 0; i < 2*forest->width-1; ++i)
		map[i] = calloc(2*forest->width-1,sizeof(char*));

	forest->map = calloc(forest->height,sizeof(int*));
	for (int j = 0; j < forest->width; ++j)
		forest->map[j] = calloc(forest->width,sizeof(int*));
	
	fgets(map[0],BUFFER,file);
	int line = 0;
	for (int p = 0; p < forest->height; ++p)
	{	
		fgets(map[p],BUFFER,file);
		line = 0;
		for (int k = 0; k < 2*forest->width-1; ++k)
		{
			if(map[p][k]!=','){
			
				if(map[p][k]=='#')
					forest->map[p][line]=1;
				else if(map[p][k]=='F'){
					forest->map[p][line]=3;
					forest->flower_x=p;
					forest->flower_y=line;
				}
				else if(map[p][k]=='B'){
					forest->map[p][line]=2;
					botanist->coord_x=p;
					botanist->coord_y=line;
				}
				else if(map[p][k]==' ')
					forest->map[p][line]=0;	
			++line;
				
			}
		}
		
	}
	
	fclose(file);
	free(map);

}

int search(forest *forest, botanist *botanist){

if(botanist->coord_x == forest->flower_x && botanist->coord_y == forest->flower_y)
	return 1;
if(botanist->water_bottle_size==0)
	return 0;

int move = rand() % 4 +1;
/* 
moves : 1 up , 2 down , 3 left , 4 right */	
	if(move==1){
		if(botanist->coord_y<1)return search(forest,botanist);

		if(forest->map[botanist->coord_x][botanist->coord_y-1]==3){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_y = botanist->coord_y-1;
			botanist->water_bottle_size--;
		}
		else if(forest->map[botanist->coord_x][botanist->coord_y-1]==0){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_y = botanist->coord_y-1;
			botanist->water_bottle_size--;
			forest->map[botanist->coord_x][botanist->coord_y]=2;
		}
		return search(forest,botanist);
	}
	
	if(move==2){
		if(botanist->coord_y+1 >= forest->height)return search(forest,botanist);

		if(forest->map[botanist->coord_x][botanist->coord_y+1]==3){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_y = botanist->coord_y+1;
			botanist->water_bottle_size--;
		}
		else if(forest->map[botanist->coord_x][botanist->coord_y+1]==0){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_y = botanist->coord_y+1;
			botanist->water_bottle_size--;
			forest->map[botanist->coord_x][botanist->coord_y]=2;
		}
		return search(forest,botanist);
	}
	
	if(move==3){
		if(botanist->coord_x<1)return search(forest,botanist);

		if(forest->map[botanist->coord_x-1][botanist->coord_y]==3){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_x = botanist->coord_x-1;
			botanist->water_bottle_size--;
		}
		else if(forest->map[botanist->coord_x-1][botanist->coord_y]==0){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_x = botanist->coord_x-1;
			botanist->water_bottle_size--;
			forest->map[botanist->coord_x][botanist->coord_y]=2;
		}
		return search(forest,botanist);
	}
	if(move==4){
		if(botanist->coord_x+1>=forest->width)return search(forest,botanist);

		if(forest->map[botanist->coord_x+1][botanist->coord_y]==3){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_x = botanist->coord_x+1;
			botanist->water_bottle_size--;
		}
		else if(forest->map[botanist->coord_x+1][botanist->coord_y]==0){
			forest->map[botanist->coord_x][botanist->coord_y]=0;
			botanist->coord_x = botanist->coord_x+1;
			botanist->water_bottle_size--;
			forest->map[botanist->coord_x][botanist->coord_y]=2;
		}
		return search(forest,botanist);
	}		
}

void print_map(forest forest){

	for (int i = 0; i < forest.height; ++i)
	{
		for (int j = 0; j < forest.width; ++j)
		{
			if(forest.map[i][j]==0)
				printf("  ");
			if(forest.map[i][j]==2)
				printf("B ");
			if(forest.map[i][j]==3)
				printf("F ");
			if(forest.map[i][j]==1)
				printf("# ");

		}
		printf("\n");
	}
}