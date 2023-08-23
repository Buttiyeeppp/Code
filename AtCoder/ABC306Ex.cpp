#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=998244353;
bool mem1;
int n,m,u[N],v[N],cnt[N],fa[N];
ll f[N];
int find(int x) {
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=m;i++) cin>>u[i]>>v[i];
	for(int s=0;s<(1<<n);s++) {
		for(int i=1;i<=n;i++) if((1<<(i-1))&s) cnt[s]++, fa[i]=i;
		for(int i=1;i<=m;i++)
			if(((1<<(u[i]-1))&s)&&((1<<(v[i]-1))&s)) {
				int fu=find(u[i]), fv=find(v[i]);
				if(fu!=fv) cnt[s]--, fa[fu]=fv;
			}
	}
	f[0]=1;
	for(int s=1;s<(1<<n);s++)
		for(int i=s;i;i=(i-1)&s) {
			if(cnt[i]&1) f[s]=(f[s]+f[s^i])%Mod;
			else f[s]=(f[s]-f[s^i]+Mod)%Mod;
		}
	cout<<f[(1<<n)-1]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

