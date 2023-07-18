#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,fa[N],id[N],tim;
vector<int> g[N];
void dfs(int x) {
	id[++tim]=x;
	for(auto y:g[x]) if(y!=fa[x])
		fa[y]=x,dfs(y);
}
int f[N];
int calc(int k) {
	if(k==1) return n;
	for(int i=1;i<=n;i++) f[i]=1;
	int res=0;
	for(int i=n;i>=1;i--) {
		int x=id[i];
		if(f[x]!=-1&&fa[x]&&f[fa[x]]!=-1) {
			if(f[x]+f[fa[x]]>=k) res++, f[fa[x]]=-1;
			else f[fa[x]]=max(f[fa[x]],f[x]+1);
		}
	}
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	dfs(1);
	int B=sqrt(n*log2(n));
	for(int i=1;i<=B;i++) cout<<calc(i)<<endl;
	for(int i=B+1;i<=n;i++) {
		int l=i-1,r=n+1,res=calc(i);
		while(l+1<r) {
			int mid=(l+r)>>1;
			if(calc(mid)==res) l=mid;
			else r=mid;
		}
		for(int j=i;j<=l;j++) cout<<res<<endl;
		i=l;
	}

	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}