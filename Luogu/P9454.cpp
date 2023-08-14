#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
const ll Mod=998244353;
bool mem1;
ll n,m,sp[N],vis[N],sz[N];
ll cnt[N],rt,hv[N],m1[N],m2[N];
ll d1[N],d2[N],e[N],sum[N];
vector<int> g[N];
void dfs(int x,int from) {
	sz[x]=1, cnt[x]=sp[x];
	for(auto y:g[x]) if(y!=from) {
		dfs(y,x);
		sz[x]+=sz[y], cnt[x]+=cnt[y];	
		d2[x]+=d2[y]+cnt[y];
	}
}
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
ll fac[N],inv[N],chu[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
	inv[N-1]=Pow(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
	for(int i=1;i<N;i++) chu[i]=inv[i]*fac[i-1]%Mod;
}
void dfs1(int x,int from) {
	if(from) d1[x]=d1[from]-cnt[x]+cnt[rt]-cnt[x];
	else d1[x]=d2[x];
	m1[x]=cnt[rt], m2[x]=sz[rt], vis[x]=1;
	for(auto y:g[x]) if(y!=from) {
		dfs1(y,x);
		e[x]=(e[x]-cnt[y]*(sz[rt]-sz[y])+Mod)%Mod;
	}
	e[x]=(e[x]+d1[x])%Mod;
	e[x]=(e[x]-(cnt[rt]-cnt[x])*sz[x]%Mod+Mod)%Mod;
	e[x]=(e[x]+sz[rt]*(cnt[rt]-sp[x]))%Mod;
	e[x]=e[x]*chu[2]%Mod*chu[cnt[rt]]%Mod;
}
vector<int> nd;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++) {
		cin>>x>>y;
		if(x==1||y==1) sp[x]=sp[y]=1;
		else g[x].push_back(y), g[y].push_back(x);
	}
	for(int i=2;i<=n;i++) if(!vis[i]) {
		rt=i;
		dfs(i,0), dfs1(i,0);
		if(!hv[cnt[i]]) nd.push_back(cnt[i]), hv[cnt[i]]=1;
		sum[cnt[i]]=sum[cnt[i]]+sz[i];
	}
	for(int i=1;i<=n;i++) {
		if(i!=1) {
			for(auto now:nd) {
				ll v=sum[now];
				if(m1[i]==now) v=v-m2[i];
				e[i]=(e[i]+now*chu[m1[i]+now]%Mod*v)%Mod;
			}
		}
		cout<<(e[i]+(i!=1)+1)%Mod<<" ";
	}
	cout<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
