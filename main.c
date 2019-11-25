#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>   //para o usleep()
#include <curses.h>
#include "myf.h"
#include "prototypes.h"

#define N_MASK   1
#define NE_MASK  2
#define E_MASK   4
#define SE_MASK  8
#define S_MASK   16
#define SW_MASK  32
#define W_MASK   64
#define NW_MASK  128

int main(){
	sos jg, *pjg;
	pjg=&jg;
	int action=0,move=0,check=0, exit=0, toggle=0;
	num_player player=JOGADOR2;
	pjg->turn=player;
	InitGame(pjg);
	
	initscr();
	noecho();
	printboard(&jg, toggle);
	refresh();
	
	while(!GameEnded(&jg) && exit==0){
		while(action==0){
			move=GetPlayerMove(player);
			action=CheckAndSetMove(&jg, move, pjg->turn, action); // return 0 for no , 1 for yes
		}
		check=CheckSequence(&jg, move, pjg->turn);
		if(check==0) {
			player++;
			if(player%2==0) pjg->turn=JOGADOR2;
			else pjg->turn=JOGADOR1;
		}

		if (action==3){ //toggle
			toggle++;
		}
		if (action==4) //exit
			exit=1;
		if (action==5){ //reset
			player=JOGADOR1;
			InitGame(pjg);
			pjg->turn=player;
		}

		printboard(&jg, toggle);
		mvprintw(40,0,"%s","                                                             ");
		refresh();
		action=0;
		check=0;
	}
	
	CommunicateResults( &jg );
	sleep(5);
	endwin();
	
	/*
	pjg->L[3][3] |= NW_MASK;
	printf("%d\n",pjg->turn);
	if(pjg->C[3][3]==(pjg->C[3][3] & (NW_MASK*(pjg->turn==JOGADOR2)))) printf("player2\n");
	else printf("hello\n");
	pjg->L[3][3] |= NW_MASK;
	printf("%d\n",pjg->turn);

	if(pjg->L[3][3]==pjg->C[3][3]) printf("player1\n");
	else printf("player2");
	*/

	return 0;
}
