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
	int action=0,move=0, count=0,check=0;
	num_player player=JOGADOR1;
	InitGame(pjg);
	initscr();
	noecho();
	
	while(count<64){
		printboard(&jg);
		while(action!=1){
			move=GetPlayerMove(player);
			action=CheckAndSetMove(&jg, move, player, action); // return 0 for no , 1 for yes
		}
		check=CheckSequence(&jg, move, player);
		if(check==0) player++;
		printboard(&jg);
		action=0;
		count++;
		check=0;
	}
	

	endwin();

	return 0;
}
