#include<stdio.h>
#include<malloc.h>
#define max 100 
typedef struct      //���¶����ٽӾ�������
{
int number;
int info;   
}VertexType;     
typedef struct  //ͼ�Ķ���
{
int edges[max][max];
int n,e;
VertexType vexs[max];
}MGraph;
//�����ڽӱ�����
typedef struct  ANode
{
int adjvex;
struct ANode *nextarc;    //ָ����һ������ָ��
int info;    //��Ż�����Ϣ��Ȩֵ��
}ArcNode;
typedef struct Vnode
{
int data;     
ArcNode *firstarc;  //ָ���һ����
}VNode;
typedef VNode AdjList[max];  //AdjList���ڽӱ����ͣ��Ѵ���ɼ���С�����ӵ�һ��
typedef struct
{
AdjList adjlist;
int n,e;                  //ͼ�ж������ͱ���
}ALGraph;
int visited[max];      //ȫ�����������жϺ���ڵ��Ƿ񱻷��ʹ�
void DispMat(MGraph g)        //����ڽӾ���
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
void MatToList(MGraph g,ALGraph *&G)        //���ڽӾ���gת��Ϊ�ڽӱ�G
{
int i,j;
int n=g.n;
ArcNode *p;
G=(ALGraph *)malloc(sizeof(ALGraph));
for(i=0;i<n;i++)  //������ڽӱ�������ͷ����ָ���򸱳�ֵ
G->adjlist[i].firstarc=NULL;
for(i=0;i<n;i++)        //����ڽӾ����ÿ��Ԫ��
for(j=0;j<n;j++)
if(g.edges[i][j]!=0)
{
p=(ArcNode *)malloc(sizeof(ArcNode));
p->adjvex=j;
p->info=g.edges[i][j];
p->nextarc=G->adjlist[i].firstarc;  //��*p���ӵ����
G->adjlist[i].firstarc=p;
}
G->e=g.e;
G->n=g.n;
}
void DispAdj(ALGraph *G)        //����ڽӱ�
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
printf(" %d ",p->adjvex);    //��������յ�
p=p->nextarc;
}
printf("\n");
}
}
void  change(int visited[],ALGraph *G)      //��ȫ�ֱ���visited����ֵ
{
int i;
for(i=0;i<G->n;i++)
visited[i]=0;
}
void ListToMat(ALGraph *G,MGraph g)    //���ڽӱ�ת��Ϊ�ڽӾ������ʽ
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
void DFS(ALGraph *G,int v)      //�ݹ�������ȱ���
{
ArcNode *p;
//change(visited,G);
visited[v]=1;          //��һ������Ϊ�ѱ����ʲ��������������Ϊ�����б���
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
int queue[max],front=0,rear=0;  //����ѭ�����в���ʼ��
int visited[max];
int w,i;
for(i=0;i<G->n;i++)
visited[i]=0;
printf(" %d ",v);      //������ĵ�v����Ϊ��һ����ȱ����Ľڵ㣬һֱ����������ȥ
visited[v]=1;     
rear=(rear+1)%max; 
queue[rear]=v;      //��v���
while(front!=rear)  //���в�Ϊ�յ�ʱ��
{
front=(front+1)%max; 
w=queue[front];
p=G->adjlist[w].firstarc; 
while(p!=NULL)
{
if(visited[p->adjvex]==0)  //��ǰ�ڵ�δ������
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
printf("�������ڽӾ���\n");
for(i=0;i<4;i++)
for(j=0;j<4;j++)
scanf("%d",&A[i][j]);
g.n=4;
g.e=10;
for(i=0;i<g.n;i++)
for(j=0;j<g.n;j++)
g.edges[i][j]=A[i][j];  //���ڽӾ���ֵ
printf("����ͼ���ڽӾ������ʽ��");
printf("\n");
DispMat(g);          //����ڽӾ���ĺ���
G=(ALGraph *)malloc(sizeof(ALGraph));
MatToList(g,G);
printf("����ͼ���ڽӱ����ʽ��");
printf("\n");
DispAdj(G);
printf("�Ӷ���0��ʼ��������ȱ�����\n");
DFS(G,0);
printf("\n");
printf("�Ӷ���0��ʼ�Ĺ�����ȱ�����\n");
BFS(G,0);
printf("\n");
}