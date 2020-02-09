/* Game of Life in C */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void print(char* str){
	printf("%s\n",str);
}

int initWorld  (int sizex, int sizey, int world[sizex][sizey]);
int loadWorld  (int sizex, int sizey, int world[sizex][sizey], char* filename);
void printWorld(int sizex, int sizey, int world[sizex][sizey]);
int stepWorld  (int sizex, int sizey, int past[sizex][sizey], 
				    int future[sizex][sizey]);

int main(int argc, char**argv){
	if (argc <2){
		print("You need to supply an input filename");
		return 2;
	}
	srand(time(0));
	print("Starting life.");
	const int size=30;
	const int sizex=size;
	const int sizey=3*size;
	int past[sizex][sizey];
	int future[sizex][sizey];
	printf("Past tiles: %d\n",(int)initWorld(sizex, sizey, past));
	printWorld(sizex, sizey, past);
	printf("Future tiles: %d\n", (int)initWorld(sizex, sizey, future));
	printWorld(sizex, sizey, future);
	print("Initialization complete.");
	stepWorld(sizex, sizey,past,future);
	printWorld(sizex, sizey,future);
	stepWorld(sizex, sizey,future,past);
	printWorld(sizex, sizey, past);
	print("Step test complete.");
	loadWorld(sizex, sizey, past,argv[1]);
	printWorld(sizex, sizey, past);
	while(1){
        	stepWorld(sizex, sizey, past,future);
		system("clear");
        	printWorld(sizex, sizey, future);
		usleep(41666);
        	stepWorld(sizex, sizey,future,past);
		system("clear");
        	printWorld(sizex, sizey,past);
		usleep(41666);
	}
	print("Life is over.");
	return 0;
}

int initWorld(int sizex, int sizey, int world[sizex][sizey]){
	int total=0;
	for (int i = 0; i<sizex;i++){
		for (int j = 0; j<sizey; j++){
			world[i][j]=0;
			total++;
		}
	}
	return total;
}

int loadWorld(int sizex, int sizey, int world[sizex][sizey], char* filename){
	FILE* f = fopen(filename, "r");
	char buffer[sizey+10];
	char c;
	int  x;
	for (int i=0; i<sizex;i++){
		fgets(buffer,sizey+10,f);
		for(int j=0; j<sizey;j++){
			c=buffer[j];
			x=atoi(&c);
			world[i][j]=x;
		}
	}
	return 0;
}

char itotile(int i){
	switch (i){
	case 0:
		return '.';
	case 1:
		return 'O';
	}
	return (char)i;
}


void printWorld(int sizex, int sizey, int world[sizex][sizey]){
	for (int i = 0; i<sizex; i++){
		for (int j = 0; j<sizey; j++){
			printf("%c", itotile(world[i][j]));
		}
		printf("\n");
	}
}

int mobi(int size, int x){
	if (x<0){
		return size + x;
	}
	if (x==0){
		return 0;
	}
	return x % size;
}

int stepCell(int sizex, int sizey,
		int past[sizex][sizey],
		int future[sizex][sizey],
		int x, int y){
	int neighbors =	past[mobi(sizex,x-1)][y]+
		      	past[mobi(sizex,x+1)][y]+
			past[x][mobi(sizey,y-1)]+
			past[x][mobi(sizey,y+1)]+
			past[mobi(sizex,x-1)][mobi(sizey,y-1)]+
			past[mobi(sizex,x+1)][mobi(sizey,y+1)]+
			past[mobi(sizex,x-1)][mobi(sizey,y+1)]+
			past[mobi(sizex,x+1)][mobi(sizey,y-1)];
	int pastself=past[x][y];
	int* futureself=&future[x][y];
	if (pastself == 1 && (neighbors == 2 || neighbors == 3)){
		*futureself=1;
	}
	else if (pastself==0 && neighbors==3){
		*futureself=1;
	}
	else if(rand() > RAND_MAX-100000){
		*futureself=1;
	}
	else{
		*futureself=0;
	}
	return 0;
}

int stepWorld(int sizex, int sizey, int past[sizex][sizey], int future[sizex][sizey]){
	for (int x=0; x<sizex; x++){
		for (int y=0; y<sizey; y++){
		stepCell(sizex, sizey, past, future, x, y);
		}
	}
	return 0;
}
