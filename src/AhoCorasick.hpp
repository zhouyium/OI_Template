#pragma once

#include<string>
#include<vector>
#include<queue>
#include<cassert>
//KMP是单模式匹配。AC自动机是多模式匹配
//时间复杂度 O(m+n)。m为主串的长度，n为模式串总长度。
static const int M = 26;
static const char BASE='a';//空格' '开始为可见字符
int trie[N][M]={};//存储从节点 p 沿着 j 这条边走到的子节点
int fail[N]={};//存储以节点 p 结尾的单词插入的次数。
int ne[N]={};
int tot = 0;//当前操作位置
int maxp = 0;
/*这个部分增加额外数据*/
/*这个部分增加额外数据*/

void init(){
    for(int i=0;i<=maxp;i++){
        ne[i]=fail[i]=0;
        for(int j=0;j<M;j++){
            trie[i][j]=0;
        }
    }
    tot=0;
}

//建立 TRIE 树
void insert(const std::string &s) {
    int p=0;
    for (const auto &ch : s) {
        int t=ch-BASE;
        assert(0<=t && t<M);
        if (!trie[p][t]) {
            //字母映射没有出现
            trie[p][t]=++tot;
        }
        p=trie[p][t];
    }
    //这里我们统计的是整个单词出现次数。如果是统计前缀，将这个部分放到循环内即可。
    fail[p]++;
    maxp=max(maxp,p);
}

void build(){
    //建立AC自动机
    std::queue<int> q;
    //根节点所有儿子入队
    for(int i=0;i<M;i++){
        if(trie[0][i]){
            q.push(trie[0][i]);
        }
    }

    while(q.size()){
        int u=q.front();
        q.pop();
        //枚举节点u的所有儿子节点
        for(int i=0;i<M;i++){
            int v=trie[u][i];
            if(v){
                //儿子存在
                //爹帮儿子建回跳边
                ne[v]=trie[ne[u]][i];
                //儿子入队
                q.push(v);
            }else{
                //儿子不存在
                //爹自建转移边
                trie[u][i]=trie[ne[u][i]];
            }
        }
    }
}

//查询字符串 s 出现的次数
int query(const std::string &s) {
    int ans=0;
    int p=0;
    for (const auto &ch : s)  {
        int t=ch-BASE;
        assert(0<=t && t<M);
        p=trie[p][t];
        for(int j=p;j&&~fail[j];j=ne[j]){
            ans+=fail[j];
            fail[j]=-1;//相同字符串只累计一次
        }
    }
    return ans;
}

//下面代码来自 JiangLY
struct AhoCorasick {
    static constexpr int ALPHABET = 26;
    struct Node {
        int len;
        int link;
        std::array<int, ALPHABET> next;
        Node() : len{0}, link{0}, next{} {}
    };

    std::vector<Node> t;

    AhoCorasick() {
        init();
    }

    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }

    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }

    int add(const std::string &a) {
        int p = 1;
        for (auto c : a) {
            int x = c - 'a';
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
                t[t[p].next[x]].len = t[p].len + 1;
            }
            p = t[p].next[x];
        }
        return p;
    }

    void work() {
        std::queue<int> q;
        q.push(1);

        while (!q.empty()) {
            int x = q.front();
            q.pop();

            for (int i = 0; i < ALPHABET; i++) {
                if (t[x].next[i] == 0) {
                    t[x].next[i] = t[t[x].link].next[i];
                } else {
                    t[t[x].next[i]].link = t[t[x].link].next[i];
                    q.push(t[x].next[i]);
                }
            }
        }
    }

    int next(int p, int x) {
        return t[p].next[x];
    }

    int link(int p) {
        return t[p].link;
    }

    int len(int p) {
        return t[p].len;
    }

    int size() {
        return t.size();
    }
};