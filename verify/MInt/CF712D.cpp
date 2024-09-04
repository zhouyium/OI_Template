//https://codeforces.com/contest/712/problem/D
#include <bits/stdc++.h>
using namespace std;
#define int long long
using ull = unsigned long long;
using PII = pair<int,int>;

/*梅森旋转器*/
random_device rd;
mt19937 mt(rd());

const int N=2e5+10;

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
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();
constexpr int P = 1000000007;
using Z = MInt<P>;

void solve(){
    int a,b,k,t;
    cin>>a>>b>>k>>t;
    k*=2;

    vector<Z> dp(k*t+1);
    dp[0]=1;
    for(int i=0;i<t;i++){
        for(int j=1;j<=k*t;j++){
            dp[j]+=dp[j-1];
        }
        for(int j=k*t;j>=k+1;j--){
            dp[j]-=dp[j-k-1];
        }
    }

    Z ans=0;
    Z sum=0;
    for(int i=0,j=-1;i<=k*t;i++){
        while(j+1<=k*t && a+i>b+j+1){
            j++;
            sum+=dp[j];
        }
        ans+=dp[i]*sum;
    }
    cout<<ans<<"\n";
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
