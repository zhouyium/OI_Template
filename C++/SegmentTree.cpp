#include<vector>
template<typename T=long long>
struct SEGNODE{
    int ls;//左儿子
    int rs;//右儿子
    T add;//Lazy tag;
    T sum;//和
};
template<typename T=long long>
class SEGMENTTREE{
private:
    std::vector<SEGNODE<T>> val;//保存数据

private:
    //将左右儿子合成一个新节点
    void combine(SEGNODE &t, const SEGNODE &t1, const SEGNODE &t2){
        t.sum=t1.sum+t2.sum;
        t.ls =min(t1.ls, t2.ls);
        t.rs =max(t1.rs, t2.rs);
    }

    void eval(SEGNODE &t, T add){
        t.sum = t.sum+(t.rs-t.ls+1)*add;
        if(t.ls==t.rs){
            //leaf
            t.add=0;
        }else{
            t.add+=add;//加上懒标记
        }
    }

    //下推
    void pushdown(int u){
        if(val[u].add==0){
            return;
        }
        //更新左子树
        eval(val[val[u].ls], val[u].add);
        //更新右儿子
        eval(val[val[u].rs], val[u].add);
        //清标记
        val[u].add=0;
    }
public:
    //根据数组创建树
    SEGMENTTREE(const std::vector<T> &vt){
        build(1,1,vt.size()+1,vt)
    }

    void build(int u, int l, int r,const std::vector<T> &vt){
        int ls=val[u].ls;
        int rs=val[u].rs;
        if(l==r){
            eval(val[u], vt[l-1]);
            return val[u];
        }
        int m=(l+r)>>1;
        build(ls,l,m);
        build(rs,m+1,r);
        combine(val[u], val[ls], val[rs]);
    }

    SEGNODE query(int u, int ql, int qr){
        int ls=val[u].ls;
        int rs=val[u].rs;
        if(ql<=ls && rs<=qr){
            return val[u];
        }
        pushdown(u);

        NODE res, t1, t2;
        int m=(l+r)>>1;
        if(ql<=m){
            t1= query(ls,ql,qr);
        }
        if(m<qr){
            t2= query(rs,ql,qr);
        }
        combine(res, t1, t2);
        return res;
    }

    //[ql,qr]+c
    void update(int u, int ql, int qr, int c){
        int ls=val[u].ls;
        int rs=val[u].rs;
        if(ql<=ls && rs<=qr){
            eval(val[u], c);
            return;
        }
        pushdown(u);
        int m=(l+r)>>1;
        if(ql<=m){
            update(ls,ql,qr,c);
        }
        if(m<qr){
            update(rs,ql,qr,c);
        }
        combine(val[u], val[ls], val[rs]);
    }
};

signed main(){
    vector<int> arr={1,2,3,4};
    LazySegmentTreeWithSetUpdate *mylst=new LazySegmentTreeWithSetUpdate(arr);
    mylst->update(0,3,0);
    cout<<"updating range from "<<0<<" to "<<3<<" with value : "<<0<<endl;
    mylst->update(2,3,2);
    cout<<"updating range from "<<2<<" to "<<3<<" with value : "<<2<<endl;
    mylst->update(0,2,10);
    cout<<"updating range from "<<0<<" to "<<2<<" with value : "<<10<<endl;
    int ans=mylst->query(1,2);
    cout<<"sum in range : "<<1<<" to "<<2<<" : "<<ans<<endl;
    return 0;
}