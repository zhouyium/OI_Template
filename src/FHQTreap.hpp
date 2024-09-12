#pragma once

#include <random>

namespace lz{
    namespace HFQTreap{
        static std::mt19937 rnd(std::random_device{}());

        struct NODE{
            int ls;//左儿子
            int rs;//左儿子
            int key;//随机数
            //下面是题目实际内容
            int sz;//子树大小
            int val;//数值
            int fa;//父亲
            //懒标志
        } tree[N];
        int tot;
        int root;//根节点

        void push_up(int u){
            tree[u].sz=tree[tree[u].ls].sz+tree[tree[u].rs].sz+1;
            if(tree[u].ls>0){
                tree[tree[u].ls].fa=u;
            }
            if(tree[u].rs>0){
                tree[tree[u].rs].fa=u;
            }
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
            tree[tot].fa=0;
            return tot;
        }
        //按值分裂
        //根据数值 v，将<=v的分裂成为一个子树，子树的根节点为x；将>v的分裂为另外一个子树，子树的根节点为y。
        //x.val <= v < y.val
        void split_by_value(int u,int value,int &x,int &y){
            if(!u){
                //当前访问节点为空，将左右区间树的虚拟节点赋值为0
                x=y=0;
                return;
            }
            if(tree[u].val<=value){
                //当前节点的value<=v则该节点与其左子树一并归入左区间树，在左区间树中对右儿子建立虚拟节点并继续分裂右子树。
                x=u;
                split_by_value(tree[u].rs,value,tree[u].rs,y);
            }else{
                //当前节点的value>v则该节点与其右子树一并归入右区间树，在右区间树中对左儿子建立虚拟节点并继续分裂左子树。
                y=u;
                split_by_value(tree[u].ls,value,x,tree[u].ls);
            }
            push_up(u);
        }
        /*
         * 要分裂区间 [l,r] 中的 [ql,qr]。
         * 可以将 [l,r] 先拆成 [l,qr] 和 [qr+1,r]，再将区间 [l,qr] 拆成 [l,ql-1] 和 [ql,qr]
         * split_by_value(root,qr,x,z);//原区间(l,r)分成两个区间(l,qr)和(qr+1,r)，x为左区间树的根节点，y为右区间树的根节点。
         * split_by_value(x,ql-1,x,y);//将(l,qr)分成(l,ql-1)和(ql,qr)，此时y就是(ql,qr)区间树的根节点，从y进行遍历就是这整个区间的所有节点。
         */

        //按位置分裂
        void split_by_pos(int u,int K,int &x,int &y){
            if(!u){
                x=y=0;
                return;
            }
            push_down(u);
            if(tree[tree[u].ls].sz<K){
                x=u;
                K-=tree[tree[u].ls].sz+1;
                split_by_pos(tree[u].rs,K,tree[u].rs,y);
            }else{
                y=u;
                split_by_pos(tree[u].ls,K,x,tree[u].ls);
            }
            push_up(u);
        }

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
        void append(int value){
            int x=0,y=0;
            //按照 value 分裂，找到插入点 x<=v<y
            split_by_value(root,value,x,y);
            //建立新节点
            int z=create(value);
            // 依次合并 x, z 和 y (权值 value 也满足如此顺序)
            root=merge(merge(x,z),y);
        }

        //删除所有
        //分裂出 (l,v-1),(v,v),(v+1,r)三个区间，合并左右两个即可
        void erase_all(int value){
            int x=0,y=0,z=0;
            split_by_value(root,value,x,y);
            split_by_value(x,value-1,x,z);
            root=merge(x,y);
        }
        //删除一个点
        void erase(int value){
            int x=0,y=0,z=0;
            // 先找到 v 的分割点 => x <= v < z
            split_by_value(root,value,x,z);
            // 再按 v-1 分裂 x 树 => x <= v-1 < y <= v
            split_by_value(x,value-1,x,y);
            // y 就是值等于 v 的节点, 删除它
            // 如果找不到 v, y 就是空树, 其左右孩子都是 0, 不影响
            y=merge(tree[y].ls, tree[y].rs);
            // 再把 x, y, z 合并起来
            root=merge(merge(x,y),z);
        }

        // 查找排名, 满足 < v 的个数+1
        int find_rank(int value){
            //找到<=x-1的个数，因为数值等于 x 的可能有很多个
            int x=0,y=0;
            split_by_value(root,value-1,x,y);
            //数量+1，就是x的排名
            int res=tree[x].sz+1;
            root=merge(x,y);
            return res;
        }

        //从子树 u 找第 K 小
        //返回节点位置
        int find_kth(int u,int K){
            int lsz=tree[tree[u].ls].sz;
            if(K==lsz+1){
                return u;//tree[u].val;
            }else if(K<=lsz){
                //进入左子树查询
                return find_kth(tree[u].ls,K);
            }else{
                //进入右子树查询
                return find_kth(tree[u].rs,K-lsz-1);
            }
        }

        //找前驱节点
        //返回节点位置
        int find_pre(int value){
            int x,y;
            //因为已经将树由权值value-1分成了T1子树和T2子树,
            //严格<value
            //split_by_value(root,value-1,x,y);
            //P2234修改这里
            //<=value
            split_by_value(root,value,x,y);
            //接下来只需查找T1子树中最大的那个即可;
            int ret=find_kth(x,tree[x].sz);
            root=merge(x,y);
            return ret;
        }

        //找后继节点，严格 >value
        //返回节点位置
        int find_next(int value){
            int x,y;
            split_by_value(root,value,x,y);
            int ret=find_kth(y,1);
            root=merge(x,y);
            return ret;
        }
    }//namespace FHQTreap
}//namespace lz