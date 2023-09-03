#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
const int M=1e6+10;
const ll Mod=998244353;
bool mem1;
int n,q,m,pri[N],a[M],tot[N],yz[N],mx[N];
int g[20000],f[20000][400],cnt[N];
ll two[M];
vector<int> P;
void init() {
	for(int i=2;i<N;i++) {
		if(!pri[i]) P.push_back(i);
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			pri[now*i]=1;
			if(i%now==0) break;
		}
	}
	for(int i=1;i<N;i++)
		for(int j=0;j<(int)P.size();j++) if(i%P[j]==0) {
			if(j<14) yz[i]|=(1<<j);
			mx[i]=j;
		}
	two[0]=1;
	for(int i=1;i<M;i++) two[i]=2*two[i-1]%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	init();
	cin>>n;
	for(int i=1,x;i<=n;i++) cin>>x, cnt[x]++;
	for(int s=0;s<(1<<14);s++) {
		for(int j=1;j<=2000;j++) {
			if(yz[j]&s) continue;
			g[s]+=cnt[j], f[s][mx[j]]+=cnt[j];
		}
	}
	cin>>q;
	while(q--) {
		cin>>m;
		for(int i=1;i<=m;i++) cin>>a[i], tot[a[i]]++;
		ll v=0, ans=0;
		for(int i=0;i<14;i++) if(tot[P[i]]) v|=(1<<i);
		for(int s=0;s<(1<<14);s++) {
			if((s|v)!=v) continue;
			ll res=1, gs=g[s];
			for(int i=14;i<(int)P.size();i++)
				if(tot[P[i]]) res=res*(two[f[s][i]]-1+Mod)%Mod, gs-=f[s][i];
			res=res*two[gs]%Mod;
			ans=(ans+((__builtin_popcount(s)%2==1)? -1:1)*res+Mod)%Mod;
		}
		cout<<ans<<endl;
		for(int i=1;i<=m;i++) tot[a[i]]=0;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
