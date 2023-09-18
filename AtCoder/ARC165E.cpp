#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
const ll Mod=998244353;
bool mem1;
int n,k;
ll g[N][N],sz[N],f[N][N][N];// node,size,edge
vector<int> eg[N];
void Add(ll &x,ll y) {
    return x=(x+y>=Mod)? x+y-Mod:x+y, void();
}
void dfs(int x,int from) {
    f[x][1][0]=sz[x]=1;
    for(auto y:eg[x]) if(y!=from) {
        dfs(y,x);
        for(int i=1;i<=sz[x]+sz[y];i++)
            for(int j=0;j<=sz[x]+sz[y];j++) g[i][j]=((!j)? 0:f[x][i][j-1]);
        for(int i=1;i<=sz[x];i++)
            for(int j=0;j<=sz[x];j++) if(f[x][i][j])
                for(int k=1;k<=sz[y];k++)
                    for(int l=0;l<=sz[y];l++) if(f[y][k][l])
                        Add(g[i+k][j+l],f[x][i][j]*f[y][k][l]%Mod);
        sz[x]+=sz[y];
        for(int i=1;i<=sz[x];i++)
            for(int j=0;j<=sz[x];j++) f[x][i][j]=g[i][j];
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
ll fac[N],inv[N];
void init() {
	fac[0]=inv[0]=1;
	for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
	inv[N-1]=Pow(fac[N-1],Mod-2);
	for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y), eg[y].push_back(x);
    }
    dfs(1,0);
    memset(g,0,sizeof(g));
    for(int x=1;x<=n;x++) {
        for(int i=1;i<=n;i++)
            for(int j=0;j<=n;j++) {
                if(x>1) {
                    if(j) Add(g[i][j],f[x][i][j-1]);
                }
                else Add(g[i][j],f[x][i][j]);
            }
    }
    init();
    ll ans=0;
    for(int i=k+1;i<=n;i++)
        for(int j=0;i+j<=n;j++) Add(ans,g[i][j]*fac[i]%Mod*fac[j]%Mod*inv[i+j]%Mod);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}