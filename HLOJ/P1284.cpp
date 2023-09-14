#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const ll Mod=998244353;
const int N=(1<<19);
const int M=410;
bool mem1;
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
ll n,p[20],f[N][20],chu[M],fac[M];
int c[20];
void init() {
    fac[0]=1;
    for(int i=1;i<M;i++) fac[i]=fac[i-1]*i%Mod;
    ll inv=Pow(fac[M-1],Mod-2);
    for(int i=M-1;i>=1;i--) chu[i]=inv*fac[i-1]%Mod, inv=inv*i%Mod;
    for(int i=0;i<=n;i++) c[i]=1<<i;
}
void Add(ll &x,ll y) {
    return x=(x+y>=Mod? x+y-Mod:x+y), void();
}
ll calc(int s,int p) {
    if(~f[s][p]) return f[s][p];
    ll res=0, cnt=0, c1=0;
    for(int i=1;i<=n;i++) if(!(c[i-1]&s))
        for(int j=i+1;j<=n;j++) if((c[j-1]&s)&&j!=p)
            Add(res,calc(s^c[i-1]^c[j-1],p)), cnt++;
    for(int i=1;i<p;i++) if(!(c[i-1]&s))
        Add(res,calc(s^c[i-1]^c[p-1],i)), cnt++, c1++;
    for(int i=p+1;i<=n;i++) if(c[i-1]&s)
        Add(res,calc(s,i)), cnt++, c1++;
    // cerr<<s<<" "<<p<<" "<<(res*chu[cnt]+1)%Mod<<endl;
    return f[s][p]=((res+c1)*chu[cnt])%Mod;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    init();
    ll ans=0;
    for(int i=1;i<=n;i++) {
        // cerr<<"Val "<<i<<endl;
        memset(f,-1,sizeof(f));
        f[c[i]-1][i]=0;
        int U=0,pos=0;
        for(int j=n;j>=1;j--) U=(U<<1)|(p[j]<=i), pos=((p[j]==i)? j:pos);
        Add(ans,calc(U,pos));
    }
    cout<<ans*chu[2]%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}