
#include<bits/stdc++.h>
using namespace std;
using LL=long long;
using PLL=pair<LL,LL>;
const LL INF=0x3f3f3f3f3f3f3f3f;
const double EPS=1e-10;
const LL MO=1e9+7;

const int N=5e5+10;

//并查集节点定义
template<typename T=long long>
struct DSUNODE{
    int fa;//表示编号为i的节点父亲是谁。-1表示根节点
    T w;//节点到父亲的权值
    //下面的内容根据题目添加
	T minx;
	T maxx;
};
//并查集模板
template<typename T=long long>
struct DSU{
	//
private:
	std::vector<DSUNODE<T>> val;
	
public:
	DSU(int n=5e5){
        //初始化数据
		for(int i=0;i<=n;i++){
			val.push_back({-1,0,i,i});
		}
	}

    //找x的父亲
	int find(int x){
		if(val[x].fa<0){
			return x;
		}
		val[x].fa=find(val[x].fa);
		val[x].w+=val[x].w;//val[x].w原来是与t的相对距离，现在是相对root的距离
		return val[x].fa;
	}
	
	bool join(int x,int y,T c=0){
		int fx=find(x);
		int fy=find(y);
		if(fx==fy){
			return false;
		}
		val[fx].fa+=val[fy].fa;//合并集合大小
		val[fy].fa=fx;
		val[fy].w=val[x].w-val[y].w+c;
		val[fx].minx=min(val[fx].minx,val[fy].minx);
		val[fx].maxx=max(val[fx].maxx,val[fy].maxx);
		return true;
	}
	
	int size(int x){
		int fx=find(x);
		return -val[fx].fa;
	}
	
	bool same(int x,int y){
		int fx=find(x);
		int fy=find(y);
		return fx==fy;
	}
	
	DSUNODE<T> node(int x){
		int fx=find(x);
		return val[fx];
	}
};

void solve() {
	int n,m;
	cin>>n>>m;
	DSU<> dsu(n);
	for(int i=1;i<=m;i++){
		string op;
		cin>>op;
		int x,y;
		if(op=="union"){
			cin>>x>>y;
			dsu.join(x,y);
		}else if(op=="get"){
			cin>>x;
			DSUNODE<long long> ret=dsu.node(x);
			cout<<ret.minx<<" "<<ret.maxx<<" "<<-ret.fa<<"\n";
		}
	}
}

int main() {
#if 1
	//�ύ��OJ
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	
	LL T=1;
	//cin>>T;
	while(T--) {
		//cout<<i<<"\n";
		solve();
	}
#else
	int n=10;
	for(int i=0;i<n;i++){
		char in[16];
		sprintf(in, "%02d.in", i);
		char out[16];
		sprintf(out, "%02d.out", i);
		
		freopen(in, "r", stdin);
		freopen(out, "w", stdout);
		
		LL T=1;
		//cin>>T;
		while(T--) {
			//cout<<i<<"\n";
			solve();
		}
		
		fclose(stdin);
		fclose(stdout);
	}
#endif
	
	return 0;
}