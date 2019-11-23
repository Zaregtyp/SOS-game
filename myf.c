#include <stdio.h>
#include <ctype.h>
#include <unistd.h>   //para o usleep()
#include <sys/time.h>  //header file para gettimeofday e struct timeval
#include <string.h>
#include <math.h>
#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
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


void printboard2(sos *jg){
        int num=1, count1=0,count2=0;
        for (int l=0; l<10; l++){
                if (l==0){int let =97; while(let <105) {printf("      %c ",let); let++;} printf("\n");}
                if (l>=1) {printf("  +"); for(int c=0; c<8; c++){printf(" - - - +");}}
                if (l>0 && l<9) {
                        for (int k=0; k<3; k++){
                                printf("\n"); 
                                for(int c=0; c<9; c++) {
                                        if (k==0){
                                                if (count1==0) printf("  |");
                                                count1++;
                                                if(c<8){
                                                        if( (jg->L[l-1][c] & NE_MASK) && (jg->L[l-1][c] & NW_MASK) && (jg->L[l-1][c] & N_MASK) ) printf(" \\ | / |");
                                                        else if ( (jg->L[l-1][c] & NE_MASK) && (jg->L[l-1][c] & NW_MASK) ) printf(" \\   / |");
                                                        else if ( (jg->L[l-1][c] & NW_MASK) && (jg->L[l-1][c] & N_MASK) ) printf(" \\ |   |");
                                                        else if ( (jg->L[l-1][c] & NE_MASK) && (jg->L[l-1][c] & N_MASK) ) printf("   | / |");
                                                        else if ( jg->L[l-1][c] & NE_MASK ) printf("     / |");
                                                        else if ( jg->L[l-1][c] & NW_MASK ) printf(" \\     |");
                                                        else if ( (jg->L[l-1][c] & N_MASK)) printf("   |   |");
                                                        else printf("       |");
                                                }
                                                
                                        }
                                        else if(k==1) {
                                                if(c==0) {printf("%d |",num);/* printf("ligne et colonne dans PrintBoard %d %d\n", l-1, c-1);*/}

                                                if(c>0 && c<=8){     
                                                        if((jg->L[l-1][c-1] & W_MASK) && (jg->L[l-1][c-1] & E_MASK)) printf(" - %c - |",jg->V[l-1][c-1]);
                                                        else if(jg->L[l-1][c-1] & E_MASK) printf("   %c - |",jg->V[l-1][c-1]);
                                                        else if (jg->L[l-1][c-1] & W_MASK ) printf(" - %c   |",jg->V[l-1][c-1]);         
                                                        else if (c>=1) printf("   %c   |",jg->V[l-1][c-1]);
                                                }

                                                if(c==8) printf(" %d",num++);
                                                
                                        }
                                        else if(k==2){
                                                if(count2==0) printf("  |");
                                                count2++;
                                                if(c<8){
                                                        if( (jg->L[l-1][c] & SE_MASK) && (jg->L[l-1][c] & SW_MASK) && (jg->L[l-1][c] & S_MASK) ) printf(" / | \\ |");
                                                        else if ( (jg->L[l-1][c] & SE_MASK) && (jg->L[l-1][c] & SW_MASK) ) printf(" /   \\ |");
                                                        else if ( (jg->L[l-1][c] & SE_MASK) && (jg->L[l-1][c] & S_MASK) ) printf("   | \\ |");
                                                        else if ( (jg->L[l-1][c] & SW_MASK) && (jg->L[l-1][c] & S_MASK) ) printf(" / |   |");
                                                        else if ( jg->L[l-1][c] & SE_MASK ) printf("     \\ |");
                                                        else if ( jg->L[l-1][c] & SW_MASK ) printf(" /     |");
                                                        else if ( (jg->L[l-1][c] & S_MASK)) printf("   |   |");
                                                        else printf("       |");
                                                }
                                                
                                        }
                                        
                                }count1=0; count2=0;
                        }
                        printf ("\n");
                }
        }printf("\n");
        int let =97; 
        while(let <105) {printf("      %c ",let); let++;} 
        printf("\n\n\n");

}


void printboard(sos *jg){


  //my_win = create_newwin(25, 50, 0, 0);
  
 
 int row,col;		/* to store the number of rows and */
 int num=1;
 int let=97;
 /*the number of colums of the screen */
 
 //while (getch()!= '\n'){
 				/* start the curses mode */
 start_color();
 
 init_pair(1, COLOR_RED, COLOR_BLACK);
 init_pair(2, COLOR_YELLOW, COLOR_BLACK);
 curs_set(2);
 
 
 for(row=1;row<35;row++){
	 mvprintw(1,1,"+",0);
	 if((row-1)%4==0) mvprintw(row,1,"+",0);
	 for(col=2; col<66;col+=8){
			 mvprintw(0,col,"   %c  ",let-8);
			 if(row<34){
			 	if((row-1)%4==0) mvprintw(row,col," - - - +",0);
			 	if((row-1)%4==1) {
					mvprintw(row,col-1,"|",0);
					mvprintw(row,65,"|",0);
			 	}
			 	if((row-1)%4==2) {
					mvprintw(row,col-1,"|",0);
					mvprintw(row,65,"|",0);
					mvprintw(row,0,"%d",num/8);
					mvprintw(row,66,"%d",num/8);
					num++;
			 	}
			 	if((row-1)%4==3) {
					mvprintw(row,col-1,"|",0);
			 		mvprintw(row,65,"|",0);
			 	}
	 		}
			mvprintw(34,col,"   %c  ",let-8);
			let++;
		}		
	 }


	for(row=1;row<35;row++){
	 for(col=2; col<73;col+=8){
			 if(row<34){
			 	if((row-1)%4==1) {
					if(jg->L[row/4][col/8] & NW_MASK){
                                                if(jg->L[row/4][col/8]==jg->C[row/4][col/8]){
                                                        attron(COLOR_PAIR(1));
                                                        mvprintw(row/4,col/8,"\\",0);
                                                        attroff(COLOR_PAIR(1));
                                                }
                                                else {attron(COLOR_PAIR(2)); mvprintw(row/4,col/8,"\\",0);attroff(COLOR_PAIR(2));}
                                        }
                                        if( jg->L[row/4][col/8] & N_MASK){
                                                if(jg->L[row/4][col/8]==jg->C[row/4][col/8]){
                                                        attron(COLOR_PAIR(1));
                                                        mvprintw(row/4,col/8,"|",0);
                                                        attroff(COLOR_PAIR(1));
                                                }
                                                else {attron(COLOR_PAIR(2)); mvprintw(row/4,col/8,"\\",0);attroff(COLOR_PAIR(2));}
                                        }
                                        if( jg->L[row/4][col/8] & NE_MASK) {
                                                if(jg->L[row/4][col/8]==jg->C[row/4][col/8]){
                                                        attron(COLOR_PAIR(1));
                                                        mvprintw(row/4,col/8,"/",0);
                                                        attroff(COLOR_PAIR(1));
                                                }
                                                else {attron(COLOR_PAIR(2)); mvprintw(row/4,col/8,"\\",0);attroff(COLOR_PAIR(2));}
                                        }
			 	}

			 	if((row-1)%4==2) {
					mvprintw(row,col-5,"%c",jg->V[row/4][col/8]);
                                        move(200,100);
                                        //printf("%c\n",jg->V[row/4][col/8]);
				}
			 	if((row-1)%4==3) {
			 	}
	 		}
		}
		
	}




	//printf("\n");


 //}
 //move(100,100);
 //getch();
 refresh();
}


void InitGame(sos *jg){
       
        for(int l=0; l<8; l++){
                for (int c=0; c<8; c++){
                        jg->V[l][c]=VAZIO;
                        jg->L[l][c]=0;
                        jg->C[l][c]=0;
                        jg->P[l][c]=0;
                }
        }
        
}

int GetPlayerMove( num_player player){
        char str[3]={0};
        char let[100]={0};
        int move=0;
        if(player%2==0) printw("It's player 2 turn!\n");
        else printw("It's player 1 turn!\n");
        printw("\nPlease put the letter indicating the column and the number indicating the line and press enter: ");
        scanf("%s",str);
        printw("\nPease enter the letter (S or O) that you would like to have: ");
        scanf("%s",let);
        //printf("\n");
        strcat(let,str);
        //printf("%s\n",let);
        if (let[0]== 'S' || let[0]=='s') move=200;
        if (let[0]== 'O' || let[0]=='o') move=100;
        move+=(let[1]-96)*10;
        move+=(let[2]-48);
        return move;
}

int CheckAndSetMove(sos *jg, int move, num_player player, int action){ // return 0 for no , 1 for yes
        int let=0, l=0,c=0;
        let=move/100;
        c=(move%100)/10;
        l=(move%100)%10;
        if (let>=1 && let<=2){
                if(l>=1 && l<=8){
                        if(c>=1 && c<=8){
                                if(jg->V[l-1][c-1]==VAZIO){
                                action=1;
                                if(player%2==0) jg->P[l-1][c-1]=2;
                                else jg->P[l-1][c-1]=1;
                                if(let==1)jg->V[l-1][c-1]=LETRA_O;
                                else jg->V[l-1][c-1]=LETRA_S;
                                }
                        }
                }
        }
        else action=0;
        return action;
}

int TestSeqDir(sos *t, int line, int col, int dir){
        int seq=0;
        line=line-1;
        col=col-1;

        switch (dir)
        {
        case N_MASK :
                //printf("I am here in N\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((line-2)>=0){
                                if(t->V[line-1][col]==LETRA_O){
                                        if(t->V[line-2][col]==LETRA_S) {
                                                seq=1;
                                                //printf("yey N!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                if(t->V[line][col]==LETRA_O){
                        if(line-1>=0 && line+1<=7){
                                if (t->V[line-1][col]==LETRA_S && t->V[line+1][col]==LETRA_S) {
                                        seq=1;
                                        //printf("yey N!\n\n");
                                        break;
                                }
                        }
                }
                break;
        case NE_MASK :
                //printf("I am here in NE\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((line-2)>=0 && (col+2)<=7){
                                if(t->V[line-1][col+1]==LETRA_O){
                                        if(t->V[line-2][col+2]==LETRA_S) {
                                                seq=1;
                                                //printf("yey NE!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                if(t->V[line][col]==LETRA_O){
                        if(line-1>=0 && line+1<=7){
                                if(col-1>=0 && col+1<=7)   
                                        if (t->V[line-1][col+1]==LETRA_S && t->V[line+1][col-1]==LETRA_S) {
                                                seq=1; 
                                                //printf("yey NE!\n\n");
                                                break;
                                }
                        }
                }
                
                break;
        case E_MASK :
                //printf("I am here in E\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((col+2)<=7) { 
                                if(t->V[line][col+1]==LETRA_O){
                                        if(t->V[line][col+2]==LETRA_S) {
                                                seq=1; 
                                                //printf("yey E!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                if(t->V[line][col]==LETRA_O){
                        if(col-1>=0 && col+1<=7){
                                if (t->V[line][col+1]==LETRA_S && t->V[line][col-1]==LETRA_S) {
                                        seq=1;
                                        //printf("yey E!\n\n");
                                        break;
                                }
                        }
                }
                
                break;
        case SE_MASK :
                //printf("I am here in SE\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((line+2)<=7 && (col+2)<=7){
                                if(t->V[line+1][col+1]==LETRA_O){
                                        if(t->V[line+2][col+2]==LETRA_S) {
                                                seq=1;
                                                //printf("yey SE!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                if(t->V[line][col]==LETRA_O){
                        if(line-1>=0 && line+1<=7){
                                if(col-1>=0 && col+1<=7)   
                                        if (t->V[line-1][col-1]==LETRA_S && t->V[line+1][col+1]==LETRA_S) {
                                                seq=1;
                                                //printf("yey SE!\n\n");
                                                break;
                                }
                        }
                }

                
                break;
        case S_MASK :
                //printf("I am here in S\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((line+2)<=7){
                                if(t->V[line+1][col]==LETRA_O){
                                        if(t->V[line+2][col]==LETRA_S) {
                                                seq=1;
                                                //printf("yey S!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                
                break;
        case SW_MASK :
                //printf("I am here in SO\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((line+2)<=7 && (col-2)>=0){
                                if(t->V[line+1][col-1]==LETRA_O){
                                        if(t->V[line+2][col-2]==LETRA_S) {
                                                seq=1;
                                                //printf("yey SO!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                break;
        case W_MASK :
                //printf("I am here in W\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((col-2)>=0){
                                if(t->V[line][col-1]==LETRA_O){
                                        if(t->V[line][col-2]==LETRA_S) {
                                                seq=1;
                                                //printf("yey W!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                
                break;
        case NW_MASK :
                //printf("I am here in NO\n\n\n");
                if(t->V[line][col]==LETRA_S){
                        if((line-2)>=0 && (col-2)>=0){
                                if(t->V[line-1][col-1]==LETRA_O){
                                        if(t->V[line-2][col-2]==LETRA_S) {
                                                seq=1;
                                                //printf("yey NO!\n\n");
                                                break;
                                        }
                                }
                        }
                }
                
                break;
        default:
                break;
        }

        return seq;
}

void UpdateDirInfo( sos *t, int line, int col, int dir, int player){
        
        line=line-1;
        col=col-1;

        switch (dir)
        {
        case N_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= N_MASK;
                        t->L[line-1][col] |= N_MASK;
                        t->L[line-1][col] |= S_MASK;
                        t->L[line-2][col] |= S_MASK;
                        break;
                }
                

                if(t->V[line][col]==LETRA_O){
                        t->L[line-1][col] |= S_MASK;
                        t->L[line][col] |= N_MASK;
                        t->L[line][col] |= S_MASK;
                        t->L[line+1][col] |= N_MASK; 
                        break;
                }

                break;
        case NE_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= NE_MASK;
                        t->L[line-1][col+1] |= NE_MASK;
                        t->L[line-1][col+1] |= SW_MASK;
                        t->L[line-2][col+2] |= SW_MASK;
                        break;
                }
                
                if(t->V[line][col]==LETRA_O){
                        t->L[line][col] |= NE_MASK;
                        t->L[line][col] |= SW_MASK;
                        t->L[line+1][col-1] |= NE_MASK;
                        t->L[line-1][col+1] |= SW_MASK;
                        break;
                }
                
                break;
        case E_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= E_MASK;
                        t->L[line][col+1] |= E_MASK;
                        t->L[line][col+1] |= W_MASK;
                        t->L[line][col+2] |= W_MASK;
                        break;
                }
                
                if(t->V[line][col]==LETRA_O){
                        t->L[line][col] |= W_MASK;
                        t->L[line][col] |= E_MASK;
                        t->L[line][col+1] |= W_MASK;
                        t->L[line][col-1] |= E_MASK;
                        break;
                }
                
                break;
        case SE_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= SE_MASK;
                        t->L[line+1][col+1] |= NW_MASK;
                        t->L[line+1][col+1] |= SE_MASK;
                        t->L[line+2][col+2] |= NW_MASK;
                        break;
                }
                
                if(t->V[line][col]==LETRA_O){
                        t->L[line][col] |= SE_MASK;
                        t->L[line][col] |= NW_MASK;
                        t->L[line-1][col-1] |= SE_MASK;
                        t->L[line+1][col+1] |= NW_MASK;
                        break;
                }
                
                break;
        case S_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= S_MASK;
                        t->L[line+1][col] |= S_MASK;
                        t->L[line+1][col] |= N_MASK;
                        t->L[line+2][col] |= N_MASK;
                        break;
                }
                
                break;
        case SW_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= SW_MASK;
                        t->L[line+1][col-1] |= SW_MASK;
                        t->L[line+1][col-1] |= NE_MASK;
                        t->L[line+2][col-2] |= NE_MASK;
                        break;
                }
                
                break;
        case W_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= W_MASK;
                        t->L[line][col-1] |= E_MASK;
                        t->L[line][col-1] |= W_MASK;
                        t->L[line][col-2] |= E_MASK;
                        break;
                }
                break;
        case NW_MASK :
                if(t->V[line][col]==LETRA_S){
                        t->L[line][col] |= NW_MASK;
                        t->L[line-1][col-1] |= SE_MASK;
                        t->L[line-1][col-1] |= NW_MASK;
                        t->L[line-2][col-2] |= SE_MASK;
                        break;
                }
                break;
        default:
                break;
        }
}

int CheckSequence(sos *jg, int move, num_player player){
        int dir=0, power=2, i=0, l=0,c=0,responseturn=0, replay=0;
        l=((move%100)%10);
        c=((move%100)/10);
        //printf("ligne et colonne dans Check Sequence %d %d\n", l, c);

                while(dir<128){
                        dir=pow(power,i);
                        //printf("value of direction and letter before function :%d %c\n\n",dir, jg->V[l-1][c-1]);
                        responseturn= TestSeqDir(jg,l,c, dir);
                        if (responseturn==1){
                                replay=1;
                                UpdateDirInfo( jg, l, c, dir, player);
                        }
                        i++;
                        //printf("value of replay: %d\n",replay);
                }
        
        return replay;
}


/*

typedef enum { VAZIO=' ', LETRA_O='O', LETRA_S='S'} cell;
typedef enum { JOGADOR1=1, JOGADOR2=2} num_player;
typedef unsigned link;
typedef unsigned color;
typedef struct {
        cell  V[8][8];  // Array bidimensional [8][8] com o valor de cada célula (VAZIO, LETRA_S ou LETRA_O)
        link  L[8][8];  // Array bidimensional [8][8] com as ligações de cada célula (1+2+4+8+16+32+64+128) - se existe ou não
        color C[8][8];  // Array bidimensional [8][8] com as cores das ligações de cada célula (1+2+4+8+16+32+64+128) - qual a cor (jogador)
        num_player P[8][8]; // Array bidimensional [8][8] com a indicação de qual o jogador que jogou a letra
        num_player turn;   // inteiro que designa quem é a vez do próximo a jogar (JOGADOR1 ou JOGADOR2)
        int countJ1;    // número de sequências SOS completadas pelo Jogagor 1 até ao momento (0 ou mais)
        int countJ2;    // número de sequências SOS completadas pelo Jogagor 2 até ao momento (0 ou mais)
        } sos;

*/
