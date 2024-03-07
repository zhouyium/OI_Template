/***
https://usaco.org/index.php?page=viewproblem2&cpid=741
http://47.110.135.197/problem.php?id=7939
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

#if 0
#include "vector/string/HashedString.hpp"
using namespace laozhou;
#else
class HashedString {
public:
    HashedString(int mo=998244353):_n(0),_mo(mo){
        pref.push_back(0);
    }

    template <typename T>
    void init(const std::vector<T>& ar){
        _n=ar.size();
        assert(_n>0);
        //处理系数
        while(_pow.size()<_n){
            _pow.push_back(normal(1ll*_pow.back()*_base));
        }

        //生成前缀哈希值
        pref.resize(_n+3,0);
        for (int i=1;i<=_n;i++) {
            pref[i]=normal(normal(1ll*pref[i-1]*_base)+ar[i-1]%_mo);
        }

        //生成后缀哈希
        suff.resize(_n+3,0);
        for(int i=_n;i>=1;i--){
            suff[i]=normal(normal(1ll*suff[i+1]*_base)+ar[i-1]%_mo);
        }
    }
    void init(const string &s){
        init(vector<char>(s.begin(),s.end()));
    }
    void add(long long x){
        _n++;
        //处理系数
        while(_pow.size()<_n){
            _pow.push_back(normal(1ll*_pow.back()*_base));
        }

        //生成前缀哈希值
        if(pref.size()==0){
            pref.resize(_n,0);
        }
        int t=normal(normal(1ll*pref[_n-1]*_base)+x%_mo);
        pref.push_back(t);
    }
    void pop_back(){
        if(_n>0){
            _n--;
            pref.pop_back();
        }
    }

    int get_hash(int l=1,int r=-1){
        if(r<0){
            r=_n;
        }
        assert(1<=l&&l<=_n&&l<=r);
        assert(1<=r&&r<=_n);
        int h=normal(pref[r]-normal(1ll*_pow[r-l+1]*pref[l-1]));
        return h;
    }

    int rev_hash(int l=-1,int r=1){
        if(l<0){
            l=_n;
        }
        assert(1<=l&&l<=_n&&l>=r);
        assert(1<=r&&r<=_n);
        int h=normal(suff[l]-normal(1ll*_pow[r-l+1]*suff[r+1]));
        return h;
    }
private:
    int normal(long long x){
        return (x%_mo+_mo)%_mo;
    }

private:
    int _n;
    int _mo;
    static int _base;//底数大家可以共用
    static std::vector<int> _pow;//pow大家可以共用
    std::vector<int> pref;//前缀哈希
    std::vector<int> suff;//后缀哈希
};
vector<int> HashedString::_pow = {1};
int HashedString::_base = 13331;
#endif

const int N=5e2+4;
HashedString hs1[N];
HashedString hs2[N];

void solve(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        hs1[i].init(s);
    }
    for(int i=1;i<=n;i++){
        string s;
        cin>>s;
        hs2[i].init(s);
    }

    int res=INT_MAX;
    int l=1, r=1;
    //if l>r then we must have just found that l=r works, which gives the ans as 1 and we can't do better
    while(l<=r && r<m){
        bool overlap=false;
        set<int> st;
        for(int i=1;i<=n;i++){
            int v1=hs1[i].get_hash(l,r);
            st.insert(v1);
        }
        for(int i=1;i<=n;i++){
            int v2=hs2[i].get_hash(l,r);
            overlap|=st.count(v2);
        }

        if(overlap){
            r++;
        }else{
            res=min(res,r-l+1);
            l++;
        }
    }
    cout<<res<<"\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    //freopen("cownomics.in","r",stdin);
    //freopen("cownomics.out","w",stdout);
    int T=1;
    //cin>>T;
    while (T--){
        solve();
    }

    return 0;
}