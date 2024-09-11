#pragma once

//FHQ-Treep
//无旋转平衡树
#include <random>
static std::mt19937 rnd(std::random_device{}());
template<int N=200010>
struct FHQTreap{
    struct NODE{
        int ls;//左儿子
        int rs;//左儿子
        int key;//随机数
        //下面是题目实际内容
        int sz;//子树大小
        int val;//数值
    } tree[N];
    int tot;
    int root;//根节点

    FHQTreap(){
        tot=0;
    }

    void push_up(int u){
        tree[u].sz=tree[tree[u].ls].sz+tree[tree[u].rs].sz+1;
    }
    void push_down(int u){
    }
    //创建一个新节点
    int create(int x){
        ++tot;
        tree[tot].ls=tree[tot].rs=0;
        tree[tot].key=rnd();
        tree[tot].sz=1;
        tree[tot].val=x;
        return tot;
    }
//按值分裂
//根据数值 v，将<=v的分裂成为一个子树，子树的根节点为x；将>v的分裂为另外一个子树，子树的根节点为y。
//x.val <= v < y.val
    void split(int u,int val,int &x,int &y){
        if(!u){
            //当前访问节点为空，将左右区间树的虚拟节点赋值为0
            x=y=0;
            return;
        }
        if(tree[u].val<=val){
            //当前节点的val<=v则该节点与其左子树一并归入左区间树，在左区间树中对右儿子建立虚拟节点并继续分裂右子树。
            x=u;
            split(tree[u].rs,val,tree[u].rs,y);
        }else{
            //当前节点的val>v则该节点与其右子树一并归入右区间树，在右区间树中对左儿子建立虚拟节点并继续分裂左子树。
            y=u;
            split(tree[u].ls,val,x,tree[u].ls);
        }
        push_up(u);
    }
/*
 * 要分裂区间 [l,r] 中的 [ql,qr]。
 * 可以将 [l,r] 先拆成 [l,qr] 和 [qr+1,r]，再将区间 [l,qr] 拆成 [l,ql-1] 和 [ql,qr]
 * split(root,qr,x,z);//原区间(l,r)分成两个区间(l,qr)和(qr+1,r)，x为左区间树的根节点，y为右区间树的根节点。
 * split(x,ql-1,x,y);//将(l,qr)分成(l,ql-1)和(ql,qr)，此时y就是(ql,qr)区间树的根节点，从y进行遍历就是这整个区间的所有节点。
 */

//将根节点为x,y的树合并
    int merge(int x,int y){
        if(!x || !y){
            //有一个为空树
            return x+y;
        }
        //> 表示大根堆
        //< 表示小根堆
        if(tree[x].key<tree[y].key){
            push_down(x);
            //x为根，合并x的右儿子和y，x为根节点
            tree[x].rs=merge(tree[x].rs,y);
            push_up(x);
            return x;
        }else{
            push_down(y);
            //y为根，合并y的左儿子和x，y为根节点
            tree[y].ls= merge(x,tree[y].ls);
            push_up(y);
            return y;
        }
    }

    //将一个点插入树
    void insert(int val){
        int x=0,y=0;
        //按照 val 分裂，找到插入点 x<=v<y
        split(root,val,x,y);
        //建立新节点
        int z=create(val);
        // 依次合并 x, z 和 y (权值 val 也满足如此顺序)
        root=merge(merge(x,z),y);
    }

//删除所有
//分裂出 (l,v-1),(v,v),(v+1,r)三个区间，合并左右两个即可
    void erase_all(int val){
        int x=0,y=0,z=0;
        split(root,val,x,y);
        split(x,val-1,x,z);
        root=merge(x,y);
    }
//删除一个点
    void erase(int val){
        int x=0,y=0,z=0;
        // 先找到 v 的分割点 => x <= v < z
        split(root,val,x,z);
        // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
        split(x,val-1,x,y);
        // y 就是值等于 v 的节点, 删除它
        // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
        y=merge(tree[y].ls, tree[y].rs);
        // 再把 x, y, z 合并起来
        root=merge(merge(x,y),z);
    }

    // 查找排名, 满足 < v 的个数+1
    int find_rank(int val){
        //找到<=x-1的个数，因为数值等于 x 的可能有很多个
        int x=0,y=0;
        split(root,val-1,x,y);
        //数量+1，就是x的排名
        int res=tree[x].sz+1;
        root=merge(x,y);
        return res;
    }

    //从子树 u 找第 K 小
    int find_kth(int u,int K){
        int lsz=tree[tree[u].ls].sz;
        if(K==lsz+1){
            return tree[u].val;
        }else if(K<=lsz){
            //进入左子树查询
            return find_kth(tree[u].ls,K);
        }else{
            //进入右子树查询
            return find_kth(tree[u].rs,K-lsz-1);
        }
    }

    //找前驱节点<=val
    int find_pre(int val){
        int x,y;
        //因为已经将树由权值val分成了T1子树和T2子树,
        //严格<val
        //split(root,val-1,x,y);
        split(root,val,x,y);
        //接下来只需查找T1子树中最大的那个即可;
        int ret=find_kth(x,tree[x].sz);
        root=merge(x,y);
        return ret;
    }

    //找后继节点，严格>val
    int find_next(int val){
        int x,y;
        split(root,val,x,y);
        int ret=find_kth(y,1);
        root=merge(x,y);
        return ret;
    }

    void print(int u){
        if(tree[u].rs){
            print(tree[u].rs);
        }
        cout<<tree[u].val<<" ";
        if(tree[u].ls){
            print(tree[u].ls);
        }
    }
};
