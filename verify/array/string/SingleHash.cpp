/***
https://www.acwing.com/problem/content/843/
http://47.110.135.197/problem.php?id=5869
***/
#include <bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;

#include "array/string/HashedString.hpp"

const int N=1e5+10;
laozhou::HashedString<N> hs1;

void solve(){
    int n,m;
    cin>>n>>m;
    string s;
    cin>>s;

    hs1.init(s);
    for(int i=1;i<=m;i++){
        int l1,r1,l2,r2;
        cin>>l1>>r1>>l2>>r2;
        int v1=hs1.get_hash(l1,r1);
        int v2=hs1.get_hash(l2,r2);
        if(v1==v2){
            cout<<"Yes\n";
        }else{
            cout<<"No\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int T=1;
    //cin>>T;
    while (T--){
        solve();
    }

    return 0;
}
