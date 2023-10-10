#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
bool mem1;
ll n,k,Mod,a[N],s[N],p[100];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k>>Mod;
    for(int i=1;i<=k;i++) cin>>a[i], a[i]%=Mod;
    for(int i=1;i<=k;i++) a[i+k]=a[i];

    ll sum[2]={0,0},sum2[2]={0,0};
    k<<=1, s[1]=sum[1]=a[1];
    for(int i=2;i<=k;i++) s[i]=s[i-1]*a[i]%Mod, sum[i&1]=(sum[i&1]+s[i])%Mod;
 
    ll c=n/k, d=n%k;
    for(int i=1;i<=d;i++) sum2[i&1]=(sum2[i&1]+s[i])%Mod;

    p[0]=1;
    for(ll i=1;i<=62;i++) p[i]=p[i-1]*(Pow(s[k],1ll<<(i-1))+1)%Mod;
    ll len=0, now=0;
    for(ll i=62;i>=0;i--) if((1ll<<i)&c) {
        now=(now+p[i]*Pow(s[k],len))%Mod;
        len+=1ll<<i;
    }
    ll ans;
    if(n&1) ans=(sum[1]*now%Mod+sum2[1]*Pow(s[k],c)%Mod)%Mod;
    else ans=(sum[0]*now%Mod+sum2[0]*Pow(s[k],c)%Mod+1)%Mod;
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}