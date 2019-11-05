#include "stdio.h"
#include "malloc.h"
#define SIZE 3
#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE 1
#endif
#define NONE 0
#define PLAYER_A 1
#define PLAYER_B 2
#define WARNNING 255
#define COMPETITOR 200
#define WINNER -1
char chessboard[SIZE][SIZE];
struct CHESS_MAN
{
int row;
int col;
};
/*PLAYER����ʤ���ķ���*/
int get_value(int player)
{                                                       
int i,j,ret=0;
int row,col,inc;
int bNONE=FALSE;
/*���������*/
for(i=0;i<SIZE;i++)
{
row=SIZE;
bNONE=FALSE;
for(j=0;j<SIZE;j++)
{
if(chessboard[i][j]==player) row--;      /*�����λ����player������ռ��*/
if(chessboard[i][j]==NONE) bNONE=TRUE;    /*�����λ�û�û������ռ
�ݣ��򷵻�bNONEΪTRUE*/
}
if(row==1&&bNONE==TRUE) return WARNNING;      /*����:��������һ��
��λ���ж����µ�2������,����ܻ�����þ֣�����WARNNINGֵ��*/
else if(row==SIZE) ret++;                    /*����:������û��player�����ӣ�
ret+1*/
}
/*���������*/
for(i=0;i<SIZE;i++)
{
col=SIZE;
bNONE=FALSE;
for(j=0;j<SIZE;j++)                                                       
{
if(chessboard[j][i]==player) col--;      /*�����λ����player������ռ��*/
if(chessboard[j][i]==NONE) bNONE=TRUE;    /*�����λ�û�û������ռ
�ݣ��򷵻�bNONEΪTRUE*/
}
if(col==1&&bNONE==TRUE) return WARNNING;      /*����:��������һ��
��λ���ж����µ�2������,����ܻ�����þ֣�����WARNNINGֵ*/
else if(col==SIZE) ret++;                    /*����:������û��player�����ӣ�
ret+1*/
}
/*�����Խ���*/
inc=SIZE;
bNONE=FALSE;
for(i=0,j=0;i<SIZE;i++,j++)
{
if(chessboard[i][j]==player) inc--;          /*�����λ����player������ռ��*/
if(chessboard[i][j]==NONE) bNONE=TRUE;        /*�����λ�û�û������ռ
�ݣ��򷵻�bNONEΪTRUE*/
}
if(inc==1&&bNONE==TRUE) return WARNNING;          /*����:��Խ�������
һ����λ���ж����µ�2������,���ܻ�����þ֣�����WARNNINGֵ*/
else if(inc==SIZE) ret++;                    /*����:��Խ�����û��player�����ӣ�
ret+1*/
/*����ҶԽ���*/
inc=SIZE;
bNONE=FALSE;                                                       
for(i=0,j=SIZE-1;i<SIZE;i++,j--)
{
if(chessboard[i][j]==player) inc--;          /*�����λ����player������ռ��*/
if(chessboard[i][j]==NONE) bNONE=TRUE;        /*�����λ�û�û������ռ
�ݣ��򷵻�bNONEΪTRUE*/
}
if(inc==1&&bNONE==TRUE) return WARNNING;          /*����:�ҶԽ�������
һ����λ���ж����µ�2������,���ܻ�����þ֣�����WARNNINGֵ*/
else if(inc==SIZE) ret++;                    /*����:�ҶԽ�����û��player�����ӣ�
ret+1*/
return ret;
};
/*��ʾ����ͼ�α߿�*/
void disp_chess_board(void)
{
int i,j;
/*��ʾ�������߿�*/
for(i=0;i<SIZE*4+1;i++)
printf("-");
printf("\n");
/*��ʾ3�����̸���������������Һ��±߿�*/
for(i=0;i<SIZE;i++)
{
printf("|");
for(j=0;j<SIZE;j++)                                                         
{
if(chessboard[i][j]==PLAYER_A) printf(" o |");        /*�����PLAYER_A��
������o��ʾ����*/
else if(chessboard[i][j]==PLAYER_B) printf(" x |");    /*�����PLAYER_B
��������x��ʾ����*/
else printf("  |");
}
printf("\n");
/*����ò��±߿�*/
for(j=0;j<SIZE*4+1;j++)
printf("-");
printf("\n");
}
return;
};

/*���̳�ʼ״��*/
void init_chess_board(void)
{
int i,j;
for(i=0;i<SIZE;i++)
for(j=0;j<SIZE;j++)
chessboard[i][j]=NONE;
return;
};

int enter_chess_man(int row, int col, int player)
{
if(row>=SIZE||col>=SIZE) return FALSE;          /*����λ�ó����������꣬����
����*/
if(chessboard[row][col]!=NONE) return FALSE;    /*���뵱��λ����������ռ
�ݣ���������*/
chessboard[row][col]=player;                    /*�������*/
return TRUE;
};
/*�ж�ʤ��״��*/
int chk_winner(int player)
{
int i,j;
int col,row,inc;
/*ռ��һ��*/
for(i=0;i<SIZE;i++)
{
row=TRUE;
for(j=0;j<SIZE;j++)
{
if(chessboard[i][j]!=player) row=FALSE;
}
if(row==TRUE) return TRUE;
}
/*ռ��һ��*/                                                         
for(i=0;i<SIZE;i++)
{
col=FALSE;
for(j=0;j<SIZE;j++)
{
if(chessboard[j][i]!=player) col=FALSE;
}
if(col==TRUE) return TRUE;

}
/*ռ����Խ���*/
inc=TRUE;
j=0;
for(i=0;i<SIZE;i++)
{
if(chessboard[i][i+j]!=player) inc=FALSE;
}
if(inc==TRUE) return TRUE;
/*ռ���ҶԽ���*/
inc=TRUE;
j=SIZE-1;
for(i=0;i<SIZE;i++)
{
if(chessboard[i][j-i]!=player) inc=FALSE;
}
if(inc==TRUE) return TRUE;
/*��û��һ��ʤ��*/                                                         
return FALSE;
};
/*��ѵ�һ����*/
int get_best_chess(struct CHESS_MAN *best_chess, int player, int other)
{
int chess_value[9];
struct CHESS_MAN chess[9];
int i,j,cur=0;
for(i=0;i<SIZE;i++)
{
for(j=0;j<SIZE;j++)
{
chess[cur].row=i;
chess[cur++].col=j;
}
}
for(i=0;i<9;i++)
{
if(enter_chess_man(chess[i].row,chess[i].col,player)==TRUE)
{


chess_value[i]=get_value(other);                      /**/
if(chk_winner(player)==TRUE) chess_value[i]=WINNER;  /*���δʤ����
��chess_value[i]ΪWINNER*/
chessboard[chess[i].row][chess[i].col]=NONE;          /*�������λ�ô���
����Ϊ0*/
}                                                     
else chess_value[i]=COMPETITOR;                          /*
�������λ����ȷ��*/
}
/*ѡ��ֵΪ��͵�chess_value*/
cur=0;
for(i=0;i<9;i++)
{
if(chess_value[cur]>chess_value[i]) cur=i;
}
/**/
best_chess->row=chess[cur].row;
best_chess->col=chess[cur].col;
return chess_value[cur];
};
/*����Ƿ���δ���ӵ����*/
int chk_full(void)
{
int i,j;
for(i=0;i<SIZE;i++)
for(j=0;j<SIZE;j++)
{
if(chessboard[i][j]==NONE) return FALSE;
}
return TRUE;
};
int main(void)                                                     
{
int i;
struct CHESS_MAN best_chess;
int player=PLAYER_A;          /*�������*/
int competitor=PLAYER_B;    /*���Ժ���*/
int bEND=FALSE; /*��ʼbEND��ֵ*/
int row,col; /*��������������ӵ�λ��*/
init_chess_board();  /*��ʼ��������*/
disp_chess_board();  /*�������̱߿�*/
while(bEND==FALSE)  /*��bENDΪFALSE�����ж���ֽ���*/
{
if(player==PLAYER_A)
{
/*�ֵ��������ʱ����ʾ�������������ʾ*/
do
{
printf("] �����������ӵ�λ�� : \n");
printf("] ������Ϊ: ");
scanf("%d",&row);
printf("] ������Ϊ: ");
scanf("%d",&col);
if(enter_chess_man(row-1,col-1,player)==TRUE)    /*���������ȷ����
��������ʾ����������ѭ��*/


{
printf("] �����ӵ�λ���� [%d][%d]\n",row,col);
break;                                                         
}
else printf("] ����������������������������\n");  /*�����������
������ʾ*/
}while(TRUE);
}
else
{
/*����ѡ�����λ�����岢��ʾ���ӵ�����������ʾ*/
     get_best_chess(&best_chess,player,competitor);
     enter_chess_man(best_chess.row,best_chess.col,player);
     printf("] �������ӵ�λ����[%d][%d]\n",best_chess.row+1,best_chess.col+1);
}
/*��ʾ��ǰ��������״��*/
disp_chess_board();
/*�ж�ʤ������ʾ����ֵ�ʤ������ʾ*/
bEND=TRUE;
if(chk_winner(player)) printf("] ʤ������Player %d.\n",player);
else if(chk_winner(competitor)) printf("] ʤ������Player %d.\n",competitor);
else if(chk_full()) printf("] ƽ��.\n");

else bEND=FALSE;
competitor=player;
if(player==PLAYER_A) player=PLAYER_B;
else player=PLAYER_A; };
printf("\n\n����ֽ���.\n\n");    /*�þ��ѽ���*/
return 0;                                                       
};


