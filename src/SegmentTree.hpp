#pragma once

namespace lz{
    namespace SegmentTree{
        //普通线段树
        //以下部分需要根据题目修改
        struct Info{
            int sum;//总和
            int mx;//最大值
            int cnt_mx;//最大值的次数
            int mn;//最小值
            int cnt_mn;//最小值的次数
            Info(){
                sum=0;
                cnt_mx=cnt_mn=1;
                mx=-INF;
                mn=INF;
            }
        };
        Info merge(const Info &n1, const Info &n2) {
            Info c;
            c.sum=n1.sum+n2.sum;
            if(n1.mx>n2.mx){
                c.mx=n1.mx;
                c.cnt_mx=n1.cnt_mx;
            }else if(n1.mx<n2.mx){
                c.mx=n2.mx;
                c.cnt_mx=n2.cnt_mx;
            }else{
                c.mx=n2.mx;
                c.cnt_mx=n1.cnt_mx+n2.cnt_mx;
            }
            if(n1.mn<n2.mn){
                c.mn=n1.mn;
                c.cnt_mn=n1.cnt_mn;
            }else if(n1.mn>n2.mn){
                c.mn=n2.mn;
                c.cnt_mn=n2.cnt_mn;
            }else{
                c.mn=n2.mn;
                c.cnt_mn=n1.cnt_mn+n2.cnt_mn;
            }
            return c;
        }
        //以上部分需要根据题目修改
        int _n;
        //保存数据，我们从下标 1 开始使用
        std::vector<Info> info;
        void push_up(int p){
            assert(1<=p && p<=4*_n);
            assert(1<=2*p && 2*p<=4*_n);
            assert(1<=2*p+1 && 2*p+1<=4*_n);
            info[p]=merge(info[2*p],info[2*p+1]);
        }
        //建立线段树
        //ve从下标 0 开始
        void init(const std::vector<Info> &ve){
            //线段树要开4倍
            _n=ve.size();
            info.assign(4*_n+1, Info());
            //assert(4*_n<N);
            std::function<void(int, int, int)> build = [&](int p, int l, int r){
                if(r==l){
                    info[p]=ve[l-1];
                    return;
                }
                int m=(l+r)>>1;
                build(2*p,l,m);
                build(2*p+1,m+1,r);
                push_up(p);
            };
            build(1,1,_n);
        }
        //区域更新
        void modify(int p,int l,int r,int x,const Info &v){
            if(r==l){
                info[p]=v;
                return;
            }
            int m=(l+r)>>1;
            if(x<=m){
                modify(2*p,l,m,x,v);
            }else{
                modify(2*p+1,m+1,r,x,v);
            }
            push_up(p);
        }
        //单点更新
        void modify(int p,const Info &v){
            modify(1,1,_n,p,v);
        }
        //区域查询
        //[l,r]线段树表示区间
        //[x,y]查询的区间
        Info query(int p,int l,int r,int x,int y){
            if(l > y || r < x){
                //范围外
                return Info();
            }
            if(x<=l && r<=y){
                return info[p];
            }
            int m=(l+r)>>1;
            return merge(query(2*p,l,m,x,y),query(2*p+1,m+1,r,x,y));
        }
        //单点查询
        Info query(int l,int r){
            return query(1,1,_n,l,r);
        }
    }//namespace SegmentTree
}//namespace lz