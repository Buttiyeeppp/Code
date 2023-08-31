#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,k,h[N],ind[N],tot,id[N],tim,p[N];
ll f[N],l[N],r[N],mx[N];
vector<int> g[N];
void topsort() {
	queue<int> q;
	tot=tim=0;
	for(int i=1;i<=n;i++) if(!ind[i]) q.push(i), p[++tot]=i;	
	while(q.size()) {
		int x=q.front(); q.pop();
		id[++tim]=x;
		if(h[x]<(f[x]%k)) f[x]+=h[x]-(f[x]%k)+k;
		else f[x]+=h[x]-(f[x]%k);
		mx[x]=f[x];
		for(auto y:g[x]) {
			f[y]=max(f[y],f[x]), ind[y]--;
			if(!ind[y]) q.push(y);
		}
	}
	for(int i=n;i>=1;i--) {
		int x=id[i];
		for(auto y:g[x]) {
			if(f[y]/k==f[x]/k+(h[x]>h[y])) mx[x]=max(mx[x],mx[y]);
		}
	}
}
void solve() {
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) cin>>h[i], g[i].clear(), ind[i]=f[i]=0;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		g[x].push_back(y), ind[y]++;
	}
	topsort();
	sort(p+1,p+tot+1,[](const int &x,const int &y) { return h[x]<h[y]; });
	for(int i=1;i<=tot;i++) r[i]=max(r[i-1],mx[p[i]]+k);
	l[tot+1]=0;
	for(int i=tot;i>=1;i--) l[i]=max(l[i+1],mx[p[i]]);
	ll ans=1e17;
	for(int i=1;i<=tot;i++) ans=min(ans,max(r[i-1],l[i])-h[p[i]]);
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
