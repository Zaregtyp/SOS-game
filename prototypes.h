/*File generated automatically. Do not edit*/
/*Generated on bruno-GE62-2QE , sáb nov 23 09:47:27 WET 2019 */
/* main.c */
int main(void);
/* myf.c */
void printboard2(sos *jg);
void printboard(sos *jg);
void InitGame(sos *jg);
int GetPlayerMove(num_player player);
int CheckAndSetMove(sos *jg, int move, num_player player, int action);
int TestSeqDir(sos *t, int line, int col, int dir);
void UpdateDirInfo(sos *t, int line, int col, int dir, int player);
int CheckSequence(sos *jg, int move, num_player player);
