#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=1e9+7;
const int N=2e2+10;
int n,dep[N],fa[N][20];
vector<int> g[N];
void dfs(int x,int from) {
    fa[x][0]=from, dep[x]=dep[from]+1;
    for(auto y:g[x]) {
        if(y==from) continue;
        dfs(y,x);
    }
}
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    for(int h=dep[x]-dep[y],i=0;h;h>>=1,i++)
        if(h&1) x=fa[x][i];
    if(x==y) return x;
    for(int i=10;i>=0;i--)
        if(fa[x][i]!=fa[y][i]) x=fa[x][i], y=fa[y][i];
    return fa[x][0];
}
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return sum;
}
ll fac[N],inv[N],f[N][N];
void init() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Mul(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(int x,int y) {
    if(x==0||x==y) return 1;
    return fac[y]*inv[x]%Mod*inv[y-x]%Mod;
}
int main() {
    init();
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++) f[0][i]=1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) f[i][j]=(f[i-1][j]+f[i][j-1])*inv[2]%Mod;
    ll ans=0;
    for(int rt=1;rt<=n;rt++) {
        dfs(rt,0);
        for(int i=1;i<=10;i++)
            for(int j=1;j<=n;j++) fa[j][i]=fa[fa[j][i-1]][i-1];
        for(int i=1;i<=n;i++)
            for(int j=1;j<i;j++) {
                int l=lca(i,j), szi=dep[i]-dep[l], szj=dep[j]-dep[l];
                if(l==i) {ans=(ans+1)%Mod; continue;}
                if(l==j) continue;
                // ans=(ans+C(szi,szi+szj-1)*Mul(C(szi,szi+szj),Mod-2)%Mod)%Mod;
                ans=(ans+f[szi][szj])%Mod;
            }
    }
    ans=ans*Mul(n,Mod-2)%Mod;
    printf("%lld",ans);
    return 0;
}