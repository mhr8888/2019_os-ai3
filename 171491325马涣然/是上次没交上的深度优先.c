#include<stdio.h>
#include<malloc.h>
#define max 100 
typedef struct      //以下定义临接矩阵类型
{
int number;
int info;   
}VertexType;     
typedef struct  //图的定义
{
int edges[max][max];
int n,e;
VertexType vexs[max];
}MGraph;
//定义邻接表类型
typedef struct  ANode
{
int adjvex;
struct ANode *nextarc;    //指向下一条弧的指针
int info;    //存放弧的信息（权值）
}ArcNode;
typedef struct Vnode
{
int data;     
ArcNode *firstarc;  //指向第一条弧
}VNode;
typedef VNode AdjList[max];  //AdjList是邻接表类型，把大表变成几个小的连接到一起
typedef struct
{
AdjList adjlist;
int n,e;                  //图中顶点数和边数
}ALGraph;
int visited[max];      //全局数组用于判断后面节点是否被访问过
void DispMat(MGraph g)        //输出邻接矩阵
{
int i,j;
for(i=0;i<g.n;i++)
{
for(j=0;j<g.n;j++)
if(g.edges[i][j]==0)
printf("0  ");
else
printf("%d  ",g.edges[i][j]);
printf("\n");
}
}
void MatToList(MGraph g,ALGraph *&G)        //将邻接矩阵g转换为邻接表G
{
int i,j;
int n=g.n;
ArcNode *p;
G=(ALGraph *)malloc(sizeof(ALGraph));
for(i=0;i<n;i++)  //给大的邻接表中所有头结点的指针域副初值
G->adjlist[i].firstarc=NULL;
for(i=0;i<n;i++)        //检查邻接矩阵的每个元素
for(j=0;j<n;j++)
if(g.edges[i][j]!=0)
{
p=(ArcNode *)malloc(sizeof(ArcNode));
p->adjvex=j;
p->info=g.edges[i][j];
p->nextarc=G->adjlist[i].firstarc;  //将*p连接到表后
G->adjlist[i].firstarc=p;
}
G->e=g.e;
G->n=g.n;
}
void DispAdj(ALGraph *G)        //输出邻接表
{
int i;
ArcNode *p;     
for(i=0;i<G->n;i++)
{
p=G->adjlist[i].firstarc;
if(p!=NULL)
printf(" %d:  ",i); 
while(p!=NULL)       
{
printf(" %d ",p->adjvex);    //输出弧的终点
p=p->nextarc;
}
printf("\n");
}
}
void  change(int visited[],ALGraph *G)      //给全局变量visited赋初值
{
int i;
for(i=0;i<G->n;i++)
visited[i]=0;
}
void ListToMat(ALGraph *G,MGraph g)    //将邻接表转换为邻接矩阵的形式
{
int i,j;
int n=G->n;
ArcNode *p;
for(i=0;i<n;i++)
for(j=0;j<n;j++)
g.edges[i][j]=0;
for(i=0;i<n;i++)
{
p=G->adjlist[i].firstarc;
while(p!=NULL)
{
g.edges[i][p->adjvex]=p->info;
p=p->nextarc;
}
}
g.n=n;
g.e=G->e;
}
void DFS(ALGraph *G,int v)      //递归深度优先遍历
{
ArcNode *p;
//change(visited,G);
visited[v]=1;          //第一个点设为已被访问并输出，接着以他为主进行遍历
printf(" %d",v); 
p=G->adjlist[v].firstarc;
while(p!=NULL)
{
if(visited[p->adjvex]==0)
DFS(G,p->adjvex);
p=p->nextarc;
}
}
void BFS(ALGraph *G,int v) 
{
ArcNode *p;
int queue[max],front=0,rear=0;  //定义循环队列并初始化
int visited[max];
int w,i;
for(i=0;i<G->n;i++)
visited[i]=0;
printf(" %d ",v);      //把输入的第v个作为第一个广度遍历的节点，一直这样进行下去
visited[v]=1;     
rear=(rear+1)%max; 
queue[rear]=v;      //把v入队
while(front!=rear)  //队列不为空的时候
{
front=(front+1)%max; 
w=queue[front];
p=G->adjlist[w].firstarc; 
while(p!=NULL)
{
if(visited[p->adjvex]==0)  //当前节点未被访问
{
printf("%d ",p->adjvex);
visited[p->adjvex]=1;
rear=(rear+1)%max;   
queue[rear]=p->adjvex;
}
p=p->nextarc;
}
}
printf("\n");
}
int main( )
{
int i,j;
MGraph g;
ALGraph *G;   
int A[max][4];
printf("请输入邻接矩阵：\n");
for(i=0;i<4;i++)
for(j=0;j<4;j++)
scanf("%d",&A[i][j]);
g.n=4;
g.e=10;
for(i=0;i<g.n;i++)
for(j=0;j<g.n;j++)
g.edges[i][j]=A[i][j];  //给邻接矩阵赋值
printf("这是图的邻接矩阵的形式：");
printf("\n");
DispMat(g);          //输出邻接矩阵的函数
G=(ALGraph *)malloc(sizeof(ALGraph));
MatToList(g,G);
printf("这是图的邻接表的形式：");
printf("\n");
DispAdj(G);
printf("从顶点0开始的深度优先遍历：\n");
DFS(G,0);
printf("\n");
printf("从顶点0开始的广度优先遍历：\n");
BFS(G,0);
printf("\n");
}