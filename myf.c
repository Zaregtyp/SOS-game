#include <stdio.h>
#include <ctype.h>
#include <unistd.h>   //para o usleep()
#include <sys/time.h>  //header file para gettimeofday e struct timeval
#include <string.h>
#include <math.h>
#include <ncurses.h>			/* ncurses.h includes stdio.h */  
#include <string.h> 
#include <time.h>
#include <stdlib.h>
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
 int row,col, l, c;
 int num=1;
 int count1=3, let=97;
 
 //while (getch()!= '\n'){
 start_color();
 
 init_pair(1, COLOR_RED, COLOR_BLACK);
 init_pair(2, COLOR_YELLOW, COLOR_BLACK);
 curs_set(2);
 /*mvprintw(0,col,"   %c  ",let-8);
 mvprintw(34,col,"   %c  ",let-8);
 let++;*/
 
 for(row=1, l=0;row<34;row++, l++){
	 for(col=1, c=0; col<34;col+=4, c++){
			 	if((row-1)%4==0 ) {
                                        mvprintw(row,1,"%s","+");
                                        if(col <30) mvprintw(row,col+1,"%s","---+");
                                }
			 	if((row-1)%4==1) {
					mvprintw(row,col,"%s","|");
				        mvprintw(row,33,"%s","|");
			 	}
			 	if((row-1)%4==2) {
					mvprintw(row,col,"%s","|");
					mvprintw(row,33,"%s","|");
					if (col<30) {
                                                mvprintw(row,0,"%d",num/8);
					        mvprintw(row,34,"%d",num/8);
                                        }
                                        if(col<33) mvprintw(row, col+2,"%c",jg->V[row/4][col/4]);
					num++;
			 	}
			 	if((row-1)%4==3) {
					mvprintw(row,col,"%s","|");
			 		mvprintw(row,33,"%s","|");
			        }
                         
		}	
	}
        while(let!=105){
                mvprintw(0,count1,"%c",let);
                mvprintw(34,count1,"%c",let);
                count1+=4;
                let++;
        }

        mvprintw(37,0,"%s","\n");

 refresh();
}


void InitGame(sos *jg){
       jg->countJ1=0;
       jg->countJ2=0;
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
        if(player%2==0) mvprintw(10,50,"%s\n","It's player 2 turn!"); 
        //printf("\nIt is player 2 turn");
        else mvprintw(10,50,"%s","It's player 1 turn!");      
        //printf("\nIt is player 1 turn");
        mvprintw(12,50,"%s","Please put the letter indicating the column and the number indicating the line and press enter: ");
        //printf("\nPlease put the letter indicating the column and the number indicating the line and press enter: ");
        scanf("%s",str);
        mvprintw(14,50,"%s","Please enter the letter (S or O) that you would like to have: ");
        //printf("\nPlease enter the letter (S or O) that you would like to have: ");
        scanf("%s",let);
        mvprintw(10,70,"%s%s",let,str);
        strcat(let,str);
        if (let[0]== 'S' || let[0]=='s') move=200;
        if (let[0]== 'O' || let[0]=='o') move=100;
        move+=(let[1]-96)*10;
        move+=(let[2]-48);
        mvprintw(15,50,"%d",move);
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
                                        return action;
                                }
                                else printf("Press c to continue, t for toggle, x for exit and r to reset\n"); //modify here with numbers and return them
                        }
                }
        }
        else return 0;
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

        if(player%2 ==1) t->countJ1++;
        else t->countJ2++;

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


int GenerateMove(sos *jg){
        int move, num, let, SorO;
        srand(time(NULL));
        let=(rand() % 8)+1;
        num=(rand() % 8)+1;
        SorO=(rand() % 2)+1;
        move=SorO*100+let*10+num;
        return move;
}

int GameEnded(sos *t){
        int counter=0;
        for (int l=0; l<8; l++){
                for (int c=0; c<8 ; c++){
                        if (t->V[l][c]==VAZIO) counter++;
                }
        }
        if (counter == 0) return 1;
        else return 0;
}

void CommunicateResults( sos *t ){
        printf("Points for player 1 : %d\n", t->countJ1);
        printf("Points for player 2 : %d\n", t->countJ2);
}
