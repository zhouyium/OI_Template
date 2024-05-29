/*
 * 有向图邻接表的定义
 * 使用 N 个单链表来表示每个节点的邻接表。使用头插入边。
 */
//节点相关定义
const int N=5e5+10;//Vetrex number
int h[N];//头节点，单链表

//边相关定义
const int M=2*N;//Edge number
int idx;
int e[M];//edge
int w[M];//weight
int ne[M];//next

void init(int n, int m){
    //一个 n 个节点，m 条有向边的图
    idx=0;
    for(int i=0;i<=n;i++){
        h[i]=-1;//表示节点 i 的没有出边
    }
}

void add(int a, int b, int c){
    //a->b c
    //顶点 a 到顶点 b 有一条权为 c 的有向边
    e[idx] = b;
    w[idx] = c;
    ne[idx]= h[a];
    h[a]=idx++;//使用头插法
}

/*
 * 使用方法
 * 1. 读取节点数和变数
 * int n,m;
 * cin>>n>>m;
 * 2. 初始化图
 * init(n,m);
 * 3. 读取边
 * for(int i=1;i<=m;i++){
 *   int a,b,c;
 *   cin>>a>>b>>c;
 *   //有向图加一条边。无向图加两条边
 *   add(a,b,c);
 *   //如果是无向图
 *   //add(b,a,c);
 * }
 * 4. 遍历编号为 u 的节点所有出边
 * for (int i=h[u]; i!=-1; i=ne[i]){
 *   //这样，我们存在一条 u->v 权为 w[i] 的有向边
 *   int v=e[i];
 *   ...
 * }
 *
 */