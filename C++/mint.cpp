template<int p>
struct mint {
	int x;
	mint() {
		x=0;
	}
	mint(int _x) {
		x=_x;
	}
	friend mint operator + (mint a,mint b) {
		return a.x+b.x>=p? a.x+b.x-p:a.x+b.x;
	}
	friend mint operator - (mint a,mint b)  {
		return a.x<b.x? a.x-b.x+p:a.x-b.x;
	}
	friend mint operator * (mint a,mint b) {
		return 1ll*a.x*b.x%p;
	}
	friend mint operator ^ (mint a,ll b) {
		mint res=1,base=a;
		while(b) {
			if(b&1)
				res*=base;
			base*=base; b>>=1;
		}
		return res;
	}
	friend mint operator ~ (mint a) {
		return a^(p-2);
	}
	friend mint operator / (mint a,mint b) {
		return a*(~b);
	}
	friend mint & operator += (mint& a,mint b) {
		return a=a+b;
	}
	friend mint & operator -= (mint& a,mint b) {
		return a=a-b;
	}
	friend mint & operator *= (mint& a,mint b) {
		return a=a*b;
	}
	friend mint & operator /= (mint& a,mint b) {
		return a=a/b;
	}
	friend mint operator ++ (mint& a) {
		return a+=1;
	}
	friend mint operator -- (mint& a) {
		return a-=1;
	}
};
const int MOD=998244353;
#define mint mint<MOD>
mint f[N];
mint res;
