#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <list>
#include <queue>
#include <math.h>

using namespace std;

/**章４－图的建立和使用
 * time   : 2016．11．14
 * author : @`13
 * */

// 图的遍历（默认按照无向图来写
// 1.0 图的表示方法
// 邻接表

//　数据结构
//一个是顶点表，包括顶点和指向下一个邻接点的指针
//一个是边表， 数据结构跟顶点不同，存储的是顶点的序号，和指向下一个的指针

//  构造过程：
//  刚开始的时候把顶点表初始化，
//  指针指向null。然后边表插入进来，
//  是插入到前一个，也就是直接插入到firstedge指向的下一个，
//  而后面的后移

#ifndef MAX_VERTEX_NUM
    #define MAX_VERTEX_NUM 10
#endif

typedef char VertexType;    // 定点数据类型
typedef struct node   //　边表节点
{
   int adjvex;        // 定点序号[下标
   node* next;        // 下一条变
}EdgeNode;

typedef struct     //　顶点表节点
{
   VertexType vertex;    // 定点数据(表示
   EdgeNode* firstedge;  // 顶点指向的第一条边
}VertexNode;

typedef VertexNode AdjList[MAX_VERTEX_NUM]; // 顶点集，有最大上限，而且固定容量
                                            // 换成指针，参数->malloc?

typedef struct          // 图
{
    AdjList adjlist;    // 顶点集
    int Vertex_num;     // 顶点数
    int Edge_num;       // 边数
}Graph;

void CreateGraph(Graph* G)      // 构造一个图，简化了malloc判断
/** 图的构造（邻接表 */
{
    // 获取定点和边数
    int i,j,k;
    int a;
    EdgeNode *s;
    printf("读入顶点数和边数：");
    scanf("%d,%d",&G->Vertex_num,&G->Edge_num);
    // 构建定点表
    for (i=0;i<G->Vertex_num;i++)
    {
        fflush(stdin);  // 清空缓冲
        printf("建立顶点表：");
        cin>>G->adjlist[i].vertex;
        //G->adjlist[i].vertex= (VertexType) getchar();
        G->adjlist[i].firstedge=NULL;   // 第一条边指向空
    }
    // 构建边表
    printf("建立边表\n");
    for (k=0;k<G->Edge_num;k++)
    {
        printf("读入(vi-vj)的顶点对序号");
        scanf("%d,%d",&i,&j);
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=j;
        s->next=G->adjlist[i].firstedge;  //插入表头
        G->adjlist[i].firstedge=s;
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=i;
        s->next=G->adjlist[j].firstedge;
        G->adjlist[j].firstedge=s;
    }
}

// 1.1 图的表示方法
// 邻接矩阵
// 顶点集合一维数组
// 边的权值集合二维数组
// 顶点数和边数
#ifndef MAX_VERTEX_NUM
    #define MAX_VERTEX_NUM 10
#endif

typedef char VertexType ;  //顶点类型
typedef int EdgeType;      //边上的权值类型
typedef struct
{
    VertexType Vexter[MAX_VERTEX_NUM];
    EdgeType Edge[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
    int Vexter_num;
    int Edge_num;
}Graph_A;

void CreateGraph_A(Graph_A* G)
/** 图的建立(邻接表 */
{
    int i,j,k,w=0,p;
    printf("输入顶点数和边数");
    scanf("%d,%d",&G->Vexter_num,&G->Edge_num);
    // 顶点表建立
    for ( p=0;p<G->Vexter_num;p++)
    {
          fflush(stdin);       //清除缓冲区
          printf("输入顶点信息");
          cin>>G->Vexter[p];
    }
    printf("邻接矩阵初始化完成\n");
    for ( i=1;i<=G->Vexter_num;i++)
        for ( j=1;j<=G->Vexter_num;j++)
           G->Edge[i][j]=0;
    // 边矩阵建立（全矩阵
    for ( k=0;k<G->Edge_num;k++)
    {
        printf("读入两个顶点(i,j[序号)之间边的值w:");
        scanf("%d,%d,%d",&i,&j,&w);
        G->Edge[i][j]=w;
        G->Edge[j][i]=w;
    }
}

// 1.２ 图的遍历
//  邻接表－深度优先遍历(DFS),广度优先遍历(BFS)
//  邻接矩阵－深度优先遍历(DFS)

// 最初思路：
void dfs_x(Graph *G, int v, int *isV, int vn, int t)
/** 图的深度优先遍历（遍历过程[有瑕疵
 * @param G　图游标
 * @param v　递归开始位置
 * @param isV　遍历矩阵
 * @param vn 顶点数
 * @param t 次数*/
{
    v%=vn;      // 边界处理
    // 访问
    if(!isV[v])
    {
        isV[v] = 1; // 访问节点
        printf("第%d访问的顶点：%c\n",t+1 ,G->adjlist[v].vertex);
        ++t;
    }

    if(t<vn)    // 判断是否遍历完成
    {
        node* cur;  // 边表游标
        cur = G->adjlist[v].firstedge;
        if(cur!=NULL)   // 有邻接顶点
        {
            while (cur)
            {// 找到第一个未访问的节点
                if (!isV[cur->adjvex])
                {
                    v = cur->adjvex;
                    dfs_x(G, v, isV, vn, t);
                }
                else
                    cur = cur->next;
            }
            goto e; //　如果都访问了就换下一个没访问的节点[简单处理
        }
        else
        { e:
            v++;
            dfs_x(G, v, isV, vn, t);
        }
    }
    else    // 遍历完成
        return;
}

void GraphDFS_x(Graph* G)
/** 图的深度优先遍历[~循环 */
{
    Graph* cur = G;                 // 临时游标
    int v;                          // 开始访问的位置
    int Vertex_num = G->Vertex_num; // 读取边节点
    int visited[Vertex_num] = {0};  // 是否访问过
    cout<<"请输入从第几个节点开始访问：";
    cin>>v;
    dfs_x(cur, v - 1, visited, Vertex_num, 0);
}

void dfs(Graph *G, int v, int *isV)
/** 图的深度优先遍历[递归
 * @param G　图
 * @param v　访问位置
 * @param isV 访问数组 */
{
    isV[v] = 1;
    printf("深度优先遍历:结点%c\n", G->adjlist[v].vertex);
    EdgeNode *p = G->adjlist[v].firstedge;
    while(p != nullptr)
    {
        if(!isV[p->adjvex])
            dfs(G, p->adjvex, isV);
        p = p->next;
    }
}

// 优化后
void GraphDFS(Graph *G)
/** 图的深度优先遍历 */
{
    int i;
    int visited[G->Vertex_num] = {0};
    for(i = 0; i < G->Vertex_num; i++)
        if(!visited[i])
            dfs(G, i, visited);
}

void bfs(Graph* G, int v, int* isV, int vn, int t)
/** 图的广度优先遍历（遍历过程
 * @param G　图游标
 * @param v　递归开始位置
 * @param isV　遍历矩阵
 * @param vn 顶点数
 * @param t 次数*/
{
    v%=vn;
    node* cur;
    if(!isV[v])     //未访问过
    {// 访问这个节点
        isV[v] = 1;//遍历
        cout<<"访问了节点:"<<G->adjlist[v].vertex<<endl;
        t++;
    }
    cur = G->adjlist[v].firstedge;
    while(cur)
    {// 访问这个节点的所有相邻节点
        cur = G->adjlist[v].firstedge;
        if(!isV[cur->adjvex])
        {
            isV[cur->adjvex] = 1;t++;
            cout<<"访问了节点:"<<G->adjlist[cur->adjvex].vertex<<endl;
        }
        cur = cur->next;
    }
    if (t<vn)   // 还有顶点尚未访问
        bfs(G,++v,isV,vn,t);
    else        // 访问了全部节点
        return;
}

void GraphBFS(Graph* G)
/** 图的广度优先遍历 */
{
    int v;
    Graph* cur = G;                     //　临时游标
    int Vertex_num = G->Vertex_num; // 读取边节点
    int visited[Vertex_num] = {0};  // 是否访问过
    cout<<"请输入从第几个节点开始访问：";
    cin>>v;
    bfs(G,v-1,visited,Vertex_num,0);
}

void dfs_a(Graph_A *G, int v, int* isV)
/** 图的深度优先遍历[邻接矩阵
 * @param G　图
 * @param v　访问位置
 * @param isV 访问数组 */
{
    if(!isV[v])
    {// 访问
        isV[v] = 1;
        cout<<"深度优先遍历:顶点"<<G->Vexter[v]<<endl;
    }
    // 递归深度遍历
    int j;
    for(j=0;j<G->Vexter_num;j++)
        if(G->Edge[v][j]!=0&&isV[j]==0)
            dfs_a(G,j,isV);
}

void GraphDFS_A(Graph_A* G)
/** 图的深度优先遍历[邻接矩阵 */
{   //初始化visited数组
    int visited[G->Vexter_num] = {0};
    //深度优先搜索
    int i;
    for(i=0;i<G->Vexter_num;i++)
        if(!visited[i]) // 寻找尚未被访问的节点
            dfs_a(G,i,visited);
}

// 2.1 图的最小生成树
//  最小生成树的生成算法
//      1) kruskal算法：依次选择最小的且不会产生环的边加入到集合中[贪心算法
//      2) prim算法   ：选择集合节点中与非集合节点最小的一条边加入到集合

//  邻接矩阵－kruskal算法（稀疏）:
/** 邻接矩阵－kruskal算法 伪代码*/
// while(集合中的顶点数<总顶点数-1)
//      if(这条边的权值是非集合中最短的&&这条边的两个点最多只有一条访问过)
//          将这个点加入集合

//  邻接矩阵－prim算法（稠密）:
#ifndef pri_flag    // 记录是否时联通图的变量
    #define pri_flag 100000
#endif
int pri(Graph_A *G, int v, int vn_now, int vn, int *isV, int *vv, int tc)
/**  邻接矩阵－prim算法构造最小生成树[递归
 * @param G 图
 * @param v 访问节点下标
 * @param vn_now 目前访问过的个数
 * @param vn 节点个数
 * @param isV 访问数组
 * @param vv 访问
 * @return tc 路径总权值
 * */
{
    //　访问节点
    isV[v] = 1;
    vv[vn_now] = v;
    cout<<"prim算法访问节点："<<G->Vexter[v]<<endl;
    vn_now++;
    // 判断是否完成
    if (vn_now==vn)
        return  tc;
    // 寻找下个节点
    //      临时记录变量
    int e_min = pri_flag; // 最小边权值记录变量
    int v_next = -1;    // 下一次访问位置
    //      寻找下一个节点
    for(int i=0;i<vn_now;i++)
    // 遍历目前所有访问过的节点 - vv[i]
        for(int j=0;j<vn;j++)
        // 遍历这些节点与未访问过节点的距离 - cost：G->Edge[vv[i]][j]
            if(!isV[j])  // 这些节点与未访问过的节点的距离
                 if(G->Edge[vv[i]][j]<e_min&&G->Edge[vv[i]][j]) // 边权值默认为0
                {   // 找到比以之前存储过权值更小的边 则访问下一个边
                    e_min = G->Edge[vv[i]][j];
                    v_next = j;
                }
    // 处理下一个节点-递归
    //cout<<"e_min:"<<e_min<<endl;
    if(e_min!=pri_flag)    // 找到了下一个相邻的要访问的节点
        tc += e_min;
    else
    {// 遍历中没有发现与现有节点集合相连的节点-自动按序号去访问下一个节点
        // cout<<"找不到下一个相邻节点"<<endl;   // 这个地方可能会重复多次输出,蠢！
        tc += pri_flag;                         // 改为加等一个较大的数，作为标记 %操作即可
        for(int l=0;l<vn;l++)
            if(!isV[l])
            {// 寻找第一个没访问过的点
                v_next = l;
                break; }
    }
    //cout<<"tc:"<<tc<<endl;
    pri(G,v_next,vn_now,vn,isV,vv,tc);  // 递归过程
}

//  邻接矩阵－prim算法:(默认从第一个顶点开始
void GraphPrim(Graph_A *G)
/**  邻接矩阵－prim算法构造最小生成树 */
{
    cout<<"prim算法开始："<<endl;
    int visited[G->Vexter_num] = {0}; // 初始化访问数组
    int Vexter_visited[G->Vexter_num] = {0};  // 访问顺序数组
    int total_edge_cost = pri(G, 0, 0, G->Vexter_num, visited, Vexter_visited, 0);
    if(total_edge_cost==0)
        cout<<"图G有且仅有一个根节点"<<endl;
    else if(total_edge_cost>pri_flag)
        cout<<"图G是非联通图"<<endl;
    else
        cout<<"图G是联通图,最小生成树权值为："<<total_edge_cost<<endl;
}
// 2.2 图的最小生成树（实际问题
// 思路：利用图的邻接矩阵表示和上面实现的pri最小生成树算法即可轻松解决这个问题
// * 没啥意思 就不再重写上面的结构体和这个题的实现代码了

// 思路及伪代码
//  初始化时
//      定点数=N,边数=N(N-1)/2
//      用一个含有（城市名称：String city,城市横坐标 double pos_x,城市横坐标 double pos_x）
//      的结构体来表示节点
//      输入全部节点后,循环生成每个城市之间的距离 EdgeType = double
//      Edge = pow(pow(abs(city1_x-citi2_x),2)+pow(abs(city1_y-citi2_y),2)),1/2)
//  之后利用pri算法取得最小生成数权值,即为最小费用

void cityInit()
/** 初始化城市图 */
{/*...*/}

void cityWaySolution()
/** 解决城市问题 */
{/*pri(Graph_A city);*/}

// 3.1 图的拓扑排序
// 有向图的构造
void CreateALGraph(Graph* G)      // 构造一个图，简化了malloc判断
/** 有向图的构造（邻接表 */
{
    // 获取定点和边数
    int i,j,k;
    int a;
    EdgeNode *s;
    printf("读入顶点数和边数：");
    scanf("%d,%d",&G->Vertex_num,&G->Edge_num);
    // 构建定点表
    for (i=0;i<G->Vertex_num;i++)
    {
        fflush(stdin);  // 清空缓冲
        printf("建立顶点表：");
        cin>>G->adjlist[i].vertex;
        //G->adjlist[i].vertex= (VertexType) getchar();
        G->adjlist[i].firstedge=NULL;   // 第一条边指向空
    }
    // 构建边表
    printf("建立边表\n");
    for (k=0;k<G->Edge_num;k++)
    {
        printf("读入(vi-vj)的顶点对序号");
        scanf("%d,%d",&i,&j);
        // 只构造一条边
        s=(EdgeNode*)malloc(sizeof(EdgeNode));
        s->adjvex=j;    // 边指向j
        s->next=G->adjlist[i].firstedge;  //插入到顶点i的边表（头插
        G->adjlist[i].firstedge=s;
//        s=(EdgeNode*)malloc(sizeof(EdgeNode));
//        s->adjvex=i;
//        s->next=G->adjlist[j].firstedge;
//        G->adjlist[j].firstedge=s;
    }
}

// 有向图的拓扑排序
// 思路：选择一个没有前驱的节点,删除这个节点和以这个节点为起点发出的边,重复这个过程
//      维护一个顶点出度集来进行操作[不改变本身图的内容，也不用复制

// Kahn算法的图拓扑排序
void topSort_kahn(Graph* G)
/** 拓扑排序Kahn算法 */
{
    EdgeNode *cur = nullptr;         // 临时用邻接表游标
    queue<char> result;              // 拓扑排序结果队列
    queue<int> temp;                 // 拓扑排序临时队列
    int VertexIndegree[G->Vertex_num] = {0};    // 顶点入度集
    // 初始化顶点入度集
    for(int i=0;i<G->Vertex_num;i++)
    {
        cur = G->adjlist[i].firstedge;
        while(cur)
        {
            VertexIndegree[cur->adjvex]++;
            cur = cur->next;
        }
    }
    // 循环查找
    for(int j=0;j<G->Vertex_num;j++)
        if(!VertexIndegree[j])  // 找到第一个入度为0的点
        {
            temp.push(j);
            break;
        }

    if(temp.empty())
    {// 特殊情况处理
        cout<<"找不到入度为0的点"<<endl;
        return;
    }
    while(!temp.empty())
    {// 完成拓扑序列
        int v = temp.front();   // 处理节点
        VertexIndegree[v] = -1;     // 处理过的点标记为-1
        temp.pop(); // 这个地方其实temp退化成一个数就可以了
                    // 当然也可以每次把入度为0的点全部入队,
                    // 然后再处理，两个思路的拓扑序列是不同的
        result.push(G->adjlist[v].vertex);  // 加入到拓扑序列中
        cur = G->adjlist[v].firstedge;
        while(cur)
        {// 去掉这个以这个节点为起点的边
            VertexIndegree[cur->adjvex]--;
            cur = cur->next;
        }
        for(int k=0;k<G->Vertex_num;k++)
            if(VertexIndegree[k]==0)
            {   // 一次处理一个就行了,否则会重复输出
                temp.push(k);
                break;
            }   // 还有其他思路
//        cout<<"\ntest：VertexIndegree ";
//        for(int k=0;k<G->Vertex_num;k++)
//            cout<<VertexIndegree[k]<<" ";
    }
    // 有环情况处理
    for(int l=0;l<G->Vertex_num;l++)
        if(VertexIndegree[l]!=-1)
        {   // 这样少用了一个计数变量
            cout<<"图中有环"<<endl;
            return;
        }
    while(!result.empty())
    {// 输出排序序列
        cout<<result.front()<<"->";
        result.pop();
    }

}

void topSort_BFS(Graph* G)
/** 拓扑排序Kahn算法 */
{/** 按照广度优先的思路遍历图也可以完成拓扑排序,实现基本同BFS,代码略... */}

// 3.2 图的拓扑排序 输出全部可能
//      思路：关键是回朔~参考csdn
//      网上参考～http://www.docin.com/p-680578799.html
//      [这个以后看的时候可以再想想
//      最简单的思路:先按照bfs的想法生成一个序列，从最后开始弹出节点，看能否换个顺序，如果与之前的顺序集合中的每一个顺序都不同
//                  则加入集合，反复执行这个操作（一定次数[需要计算] 直到回溯到第一个为止
//      2 暴力生成所有序列,依次检查能否按照这个次序拓扑,能就输出，不能则跳过 算法:O(n!)      

//      思路2:记录每个节点的层数，不光记录最大的层数，也记录最小的层数
//            通过这个记录层数的容器来完成全部输出
//            规则-当要输出节点时，所有最大层数小与此节点的最小层数的节点一定要已经输出
//            以下是实现
// 2016年11月17日22:50:59 这个算法还是有点问题,漏了部分情况，[有的最小深度是2的也可以先于一部分最小深度是1的节点输出
void topSort_ArrayBFS(Graph* G)
/** 拓扑排序[输出所有可能 */
{// 默认是个联通图且无环 !
    EdgeNode *cur = nullptr;         // 临时用邻接表游标
    queue<int> temp;                 // 拓扑排序临时队列
    int depth_max = -1;
    int VerterDepth[G->Edge_num][2] ={0};          // 定点深度数组 0-最小深度 1-最大深度
    int VertexIndegree[G->Vertex_num] = {0};       // 顶点入度集
    // 初始化顶点入度集
    for (int i=0;i<G->Vertex_num;i++)
    {
        cur = G->adjlist[i].firstedge;
        while (cur)
        {
            VertexIndegree[cur->adjvex]++;
            cur = cur->next;
        }
    }
    // 循环查找
    for (int j=0;j<G->Vertex_num;j++)
        if (!VertexIndegree[j])  // 找到第一个入度为0的点
        {
            VerterDepth[j][0] = 0;  // 起点设置最小深度为0
            VerterDepth[j][1] = 0;  // 起点设置最大深度为0
            temp.push(j);
        }
    while(!temp.empty())
    {
        int v = temp.front();   // 顶点序号
        VertexIndegree[v] = -1; // 处理过这个定点
        int min_depth = VerterDepth[v][0]; // 当前顶点最小深度
        int max_depth = VerterDepth[v][1]; // 当前顶点最大深度
        // cout<<"TEST：正在处理"<<G->adjlist[v].vertex<<endl;
        temp.pop();
        cur = G->adjlist[v].firstedge;
        while(cur)
        {// 更新这个定点所连接的定点的深度值
            VertexIndegree[cur->adjvex]--;  // 更新入度表
            // 更新深度值,（初始化||需要更改值）
            if(VerterDepth[cur->adjvex][0]==0||VerterDepth[cur->adjvex][0]>(min_depth+1))
                VerterDepth[cur->adjvex][0] = min_depth+1;
            if(VerterDepth[cur->adjvex][1]==0||VerterDepth[cur->adjvex][1]<(max_depth+1))
            {
                VerterDepth[cur->adjvex][1] = max_depth+1;
                if(VerterDepth[cur->adjvex][1]>depth_max)
                    depth_max = VerterDepth[cur->adjvex][1];    // 更新最大层数记录变量
            }
            cur = cur->next;
        }
        for(int k=0;k<G->Vertex_num;k++)
            if(VertexIndegree[k]==0)
            {// 入度为0的定点入队
                temp.push(k);
                break;
            }
    }
//    // just show
//    for(int k=0;k<G->Vertex_num;k++)
//    {
//        cout<<"顶点 "<<G->adjlist[k].vertex<<
//            " 的最小深度为: "<<VerterDepth[k][0]<<
//            " 的最大深度为: "<<VerterDepth[k][1]<<endl;
//    }
    // 思路1：   0，按照最大层数排序输出，
    //          1，同层需要遍历所有排序可能
    //          2，输出之后，如果最大层大于最小层，则将最大层的数值-1
    //          3，重复上述过程，直到所有最大层数等于最小层
    // 代码略... 感觉这个好麻烦

    // 思路2：根据最大最小层数输出序列[输出成一个字符串
    int count = 0;  // 记录输出了多少的序列 - 层数
    // cout<<"TEST:最大深度 "<<depth_max;
    cout<<"note：‘|’之间的定点可以随意互换位置,带‘[]’标志的节点有且仅能输出一次，选择不同的位置将出现不同的拓扑序列"<<endl;
    while(count <= depth_max)
    {
        for(int l=0;l<G->Vertex_num;l++)
        {   // 输出序列
            if(VerterDepth[l][0]==count&&VerterDepth[l][1]==count)
                cout<<G->adjlist[l].vertex<<" ";
            else if(VerterDepth[l][0]==count||VerterDepth[l][1]==count)
                cout<<"["<<G->adjlist[l].vertex<<"] ";
        }
        cout<<"| ";
        count ++;
    }
    cout<<endl<<"此图的所有拓扑序列输出完毕"<<endl;
}

// 3.3 图的拓扑排序[十字链表 ～ 参考http://blog.csdn.net/junbopengpeng/article/details/13020315
// 图的十字链表描述
#define MaxVex 20
typedef int EdgeType ;     // 定义弧信息的类型
typedef char VertexType ;  // 定义顶点的类型

typedef struct EdgeNode_l  // 弧结点的定义
{
    int tailvex ;   // 弧尾结点的下标
    int headvex ;   // 弧头结点的下标
    struct EdgeNode_l* headlink ;  // 指向弧头相同的下一条弧的链域
    struct EdgeNode_l * taillink ;  // 指向弧尾相同的下一条弧的链域
    EdgeType info ; // 弧中所含的信息
} EdgeNode_l ;

typedef struct VertexNode_l  // 顶点结点的定义
{
    int index ;  // 下标值
    VertexType data  ;  // 顶点内容
    EdgeNode_l* firstout ; // 顶点的第一条出弧
    EdgeNode_l* firstin ;  // 顶点的第一条入弧
} VertexNode_l ;

typedef struct OLGraph   // 十字链表存储结构的有向图定义
{
    VertexNode_l vertices[MaxVex] ;
    int vexnum ;    // 边数
    int arcnum ;    // 弧数
} OLGraph ;

// 图的十字链表描述的构造
void CreateGraph_L(OLGraph* G)
/** 图的十字链表描述的构造 */
{
    cout << "输入弧的数目与顶点的数目:";
    cin >> G->arcnum;
    cin >> G->vexnum;
    // 输入顶点的信息
    printf("请输入顶点信息:");
    for (int i = 0; i < G->vexnum; i++) {
        scanf("%c", &G->vertices[i].data);
        G->vertices[i].index = i;
        G->vertices[i].firstin = NULL;
        G->vertices[i].firstout = NULL;
    }
    // 输入弧的信息
    printf("请输入边的信息:");
    for (int j = 0; j < G->arcnum; j++) {
        EdgeNode_l *edge = (EdgeNode_l *) malloc(sizeof(EdgeNode_l));
        edge->taillink = NULL;
        edge->headlink = NULL;
        scanf("%d %d", &edge->tailvex, &edge->headvex);
        // 将该弧插入到当前顶点的出弧中
        EdgeNode_l *p = G->vertices[edge->tailvex].firstout;
        if (p == NULL)  // 第一次插入边结点
            G->vertices[edge->tailvex].firstout = edge;
        else {
            while (p != NULL) {
                if (p->taillink == NULL)
                    break;
                p = p->taillink;
            }
            p->taillink = edge;
        }
        // 将该弧插入到当前顶点的入弧中
        EdgeNode_l *q = G->vertices[edge->headvex].firstin;
        if (q == NULL)
            G->vertices[edge->headvex].firstin = edge;
        else {
            while (q->headlink != NULL) {
                if (q->headlink == NULL)
                    break;
                q = q->headlink;
            }
            q->headlink = edge;
        }
    }
}

// 3.3 图[十字链表描述]拓扑排序
// @override
void topSort_kahn(OLGraph* G)
/** 图[十字链表描述]拓扑排序 */
{/*思路与邻接表相同,依然是kahn算法,利用边链表初始化存储和更新顶点入度集即可,与上面的重载基本相同*/}

int main(void)
{
    // 初始化图的时候需要先为变量申请内存空间
    // demo
//    Graph* G= (Graph*)malloc(sizeof(Graph));
//    CreateALGraph(G);
//    topSort_ArrayBFS(G);

    cout<<"author：`13,以上代码使用 gcc 全部编译测试通过,IDE：Clion -2016.11.17"<<endl;
}
