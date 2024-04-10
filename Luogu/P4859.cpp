#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+9;
const int N=2e3+10;
bool mem1;
int n,k,a[N],b[N],f[N][N],g[N];
int fac[N],inv[N];
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
    for(int i=1;i<N;i++) fac[i]=1ll*fac[i-1]*i%Mod;
    inv[N-1]=Pow(fac[N-1],Mod-2);
    for(int i=N-2;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%Mod;
}
ll C(int x,int y) {
    if(x<y) return 0;
    return 1ll*fac[x]*inv[y]%Mod*inv[x-y]%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) cin>>b[i];
    if((n+k)&1) return cout<<0<<endl, 0;
    sort(a+1,a+n+1), sort(b+1,b+n+1);
    f[0][0]=1;
    for(int i=1,p=0;i<=n;i++) {
        while(p<n&&a[i]>b[p+1]) p++;
        for(int j=0;j<=i;j++) {
            f[i][j]=f[i-1][j];
            if(j&&p>=j) f[i][j]=(f[i][j]+1ll*f[i-1][j-1]*(p-j+1))%Mod;
        }
    }
    for(int i=0;i<=n;i++) f[n][i]=1ll*f[n][i]*fac[n-i]%Mod;
    int ans=0,t=(n+k)/2;
    for(int i=t;i<=n;i++) {
        int v=1ll*f[n][i]*C(i,t)%Mod;
        if((i-t)&1) v=Mod-v;
        ans=(ans+v)%Mod;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}