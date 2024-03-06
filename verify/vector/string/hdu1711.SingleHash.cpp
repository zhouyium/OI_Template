/***
https://acm.hdu.edu.cn/showproblem.php?pid=1711
http://47.110.135.197/problem.php?id=6773
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
        HashedString(int mo=998244353):_n(0),_mo(mo){}

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

void solve(){
    int n,m;
    cin>>n>>m;

    vector<int> a(n);
    for(auto &x:a){
        cin>>x;
    }
    HashedString hs1;
    hs1.init(a);

    vector<int> b(m);
    for(auto &x:b){
        cin>>x;
    }
    HashedString hs2;
    hs2.init(b);
    int v1=hs2.get_hash();

    int ans=-1;
    for(int i=1;i+m-1<=n;i++){
        int v2=hs1.get_hash(i,i+m-1);
        if(v1==v2){
            ans=i;
            break;
        }
    }
    cout<<ans<<"\n";
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    cin>>T;
    while (T--){
        solve();
    }

    return 0;
}