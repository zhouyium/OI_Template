#pragma once

//FHQ-Treep
//无旋转平衡树
#include <random>
const int INF=0x3f3f3f3f3f3f3f3f;

/*梅森旋转器*/
//随机数生成
random_device rd;
mt19937 sj(rd());//随机数

const int N=2e5+10;

//本例子就维护子树的大小，也就是 sz
struct FHQ{
    int ls;//左儿子
    int rs;//右儿子
    int key;//随机数
    int sz;//子树大小
    int val;//数值
} tr[N];

static int root;//根节点
static int idx;//分配新节点的计数器
static int T1,T2,T3;//三个临时变量，保存临时平衡树根节点

//新建一个节点
int add(int v){
    tr[++idx]={0,0,(int)sj(),1,v};
    return idx;
}

//维护子树信息
void push_up(int u){
    tr[u].sz=tr[tr[u].ls].sz+tr[tr[u].rs].sz+1;
}

//按值分裂
//根据数值 v，将<=v的分裂成为一个子树，子树的根节点为x；将>v的分裂为另外一个子树，子树的根节点为y。
void split(int u,int v,int &x,int &y){
    if(!u){
        //当前访问节点为空，将左右区间树的虚拟节点赋值为0
        x=y=0;
        return;
    }
    if(tr[u].val>v){
        //当前节点的val>v则该节点与其右子树一并归入右区间树，在右区间树中对左儿子建立虚拟节点并继续分裂左子树。
        y=u;
        split(tr[u].ls,v,x,tr[u].ls);
    }else{
        //当前节点的val<=v则该节点与其左子树一并归入左区间树，在左区间树中对右儿子建立虚拟节点并继续分裂右子树。
        x=u;
        split(tr[u].rs,v,tr[u].rs,y);
    }
    push_up(u);
}

//将根节点为x,y的树合并
int merge(int x,int y){
    if(!x || !y){
        //有一个为空树
        return x+y;
    }
    if(tr[x].key>tr[y].key){
        //x为根，合并x的右儿子和y，x为根节点
        tr[x].rs=merge(tr[x].rs,y);
        push_up(x);
        return x;
    }else{
        //y为根，合并y的左儿子和x，y为根节点
        tr[y].ls= merge(x,tr[y].ls);
        push_up(y);
        return y;
    }
}

//将一个点插入树
void insert(int v){
    split(root,v,T1,T2);
    root=merge(merge(T1,add(v)),T2);
}

//删除
void erase(int v){
    split(root,v,T1,T2);
    //删除T3的根节点
    split(T1,v-1,T1,T3);
    T3=merge(tr[T3].ls, tr[T3].rs);
    root=merge(merge(T1,T3),T2);
}

int find_rank(int x){
    //找到<=x-1的个数，因为数值等于 x 的可能有很多个
    split(root,x-1,T1,T2);
    //数量+1，就是x的排名
    int res=tr[T1].sz+1;
    root=merge(T1,T2);
    return res;
}

int find_kth(int K){
    int u=root;
    while(u){
        //求左子树大小
        int tmp=tr[tr[u].ls].sz+1;
        if(tmp==K){
            break;
        }else if(K<tmp){
            //向左走
            u=tr[u].ls;
        }else{
            //向右走
            K-=tmp;
            u=tr[u].rs;
        }
    }
    return tr[u].val;
}

//找前驱
int find_pre(int u,int v){
    if(u==0){
        return -INF;
    }
    if(tr[u].val<v){
        int res=find_pre(tr[u].rs,v);
        return res==-INF?tr[u].val:res;
    }else{
        return find_pre(tr[u].ls,v);
    }
}

//找后继
int find_next(int u,int v){
    if(u==0){
        return INF;
    }
    if(tr[u].val>v){
        int res=find_next(tr[u].ls,v);
        return res==INF?tr[u].val:res;
    }else{
        return find_next(tr[u].rs,v);
    }
}

#if 0
int find_pre(int v){
    //分裂树
    split(root,v-1,T1,T2);
    //找右边最大的节点
    int u=T1;
    while(tr[u].rs){
        u=tr[u].rs;
    }
    root=merge(T1,T2);
    return tr[u].val;
}

int find_next(int v){
    split(root,x,T1,T2);
    //找左边最小的节点
    int u=T2;
    while(tr[u].ls){
        u=tr[u].ls;
    }
    root=merge(T1,T2);
    return tr[u].val;
}
#endif