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
ll n,m,k,v[N],f[N][40][40][N];
ll fac[N],inv[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void init() {
    fac[0]=inv[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=inv[i+1]*(i+1)%Mod;
}
ll C(ll x,ll y) {
    if(x<y) return 0;
    return fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
void Add(ll &x,ll y) {
    return x=(x+y>=Mod? x+y-Mod:x+y), void();
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>m>>k;
    for(int i=0;i<=m;i++) cin>>v[i];
    for(int i=0;i<=n;i++) f[0][i][i][i&1]=Pow(v[0],i)*C(n,i)%Mod;
    for(int i=0;i<=m+5;i++) {
        for(int j=0;j<=n;j++) {
            for(int c=0;c<=j;c++) {
                for(int l=0;l<=i+1;l++) {
                    for(int d=0;d+j<=n;d++) 
                        Add(f[i+1][j+d][c/2+d][((c/2+d)&1)+l],f[i][j][c][l]*Pow(v[i+1],d)%Mod*C(n-j,d)%Mod);
                }
            }
        }
    }
    ll ans=0;
    for(int i=0;i<=k;i++) Add(ans,f[m+6][n][0][i]), Add(ans,f[m+6][n][1][i]);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}