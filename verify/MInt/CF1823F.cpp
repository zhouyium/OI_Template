//https://codeforces.com/contest/1823/problem/F
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ull = unsigned long long;
using PII = pair<int,int>;

/*梅森旋转器*/
random_device rd;
mt19937 mt(rd());

const int N=2e5+10;

//快速幂
template<class T>
constexpr T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(int x) : x{norm(x % getMod())} {}

    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1ll * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        int v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};

template<>
int MInt<0>::Mod = 1;
constexpr int P = 998244353;
using Z = MInt<P>;

void solve(){
    int n,s,t;
    cin>>n>>s>>t;

    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++){
        int x,y;
        cin>>x>>y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<Z> k(n+1);
    std::function<void(int,int)> dfs=[&](int x,int p){
        for(auto y:adj[x]){
            if(y==p){
                continue;
            }
            dfs(y,x);
        }
        if(p!=t){
            k[x]=1;
            for(auto y:adj[x]){
                if(y==p||y==t){
                    continue;
                }
                k[x]-=k[y]/adj[y].size();
            }
            if(x==s){
                k[x]=1/k[x];
            }else{
                k[x]=Z(1)/adj[p].size()/k[x];
            }
        }
    };
    dfs(s,-1);

    dfs=[&](int x,int p){
        for(auto y:adj[x]){
            if(y==p){
                continue;
            }
            k[y]*=k[x];
            dfs(y,x);
        }
    };
    dfs(s,-1);

    for(int i=1;i<=n;i++){
        cout<<k[i]<<" ";
    }
    cout<<"\n";
}

signed main(){
#if 1
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
#endif

    int T=1;
    //cin>>T;
    while(T--){
        solve();
    }
    return 0;
}
