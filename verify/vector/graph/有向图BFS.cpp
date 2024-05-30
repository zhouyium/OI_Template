/*
 * http://47.110.135.197/problem.php?id=7419
 */
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
/*
 * 有向图邻接表的定义
 * 使用 N 个单链表来表示每个节点的邻接表。使用头插法插入边。
 * 时间复杂度：
 *   判断是否存在 u 到 v 的边：O(d^{+}(u))
 *   遍历点 u 的所有出边：O(d^{+}(u))
 *   遍历整张图：O(n+m)
 *   空间复杂度：O(m)
 * 版本号：Ver0.1
 */
#include <vector>
using PLL=pair<long long, long long>;
using PII=pair<int, int>;
//节点相关定义
//{指向的节点, 对应的权}
std::vector<std::vector<PLL>> adj;//邻接表
std::vector<bool> vis;//访问性控制
std::vector<int> din;//入度
std::vector<int> dout;//出度

void init(int n){
    //一个 n 个节点
    //初始化行
    adj.assign(n+1, std::vector<PLL>());
    vis.assign(n+1, false);
    din.assign(n+1, 0);
    dout.assign(n+1, 0);
}

void add(int a, int b, int c=1){
    //a->b c
    //顶点 a 到顶点 b 有一条权为 c 的有向边
    adj[a].push_back({b,c});
    //更新入度出度
    din[b]++;
    dout[a]++;
}

/*
 *下面是使用代码，不需要加入到模板中。只是做为使用样例
 */
//遍历节点 u 的所有出边
void traversal(int u){
    for (const auto &node : adj[u]){
        //u->v w
        int v=node.first;
        int w=node.second;
    }
}

//以 u 为起点，深搜所有出边
void dfs(int u){
    if(vis[u]){
        return;
    }
    cout<<u<<" ";
    vis[u]=true;//访问性控制
    for (const auto &node : adj[u]){
        //u->v w
        int v=node.first;
        int w=node.second;
        //...
        //根据题目处理问题
        //...
        dfs(v);
    }
}

//以 u 为起点，广搜所有出边
void bfs(int u){
    std::queue<int> que;
    que.push(u);
    vis[u]=true;

    while(que.size()){
        int p=que.front();
        que.pop();

        cout<<p<<" ";
        for(const auto &node:adj[p]){
            int v=node.first;
            if(vis[v]){
                continue;
            }
            vis[v]=true;
            que.push(v);
        }
    }
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

void solve(){
    //初始化
    int n,m;
    cin>>n>>m;
    //初始化
    init(n);
    for(int i=1;i<=m;i++){
        int a,b;
        cin>>a>>b;
        add(a,b);
    }
    int u;
    cin>>u;
    sort(adj[u].begin(), adj[u].end());
    dfs(u);
    cout<<"\n";
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    for(int i=1;i<=T;i++){
        //cout<<"Case "<<i<<": ";
        solve();
    }
    return 0;
}