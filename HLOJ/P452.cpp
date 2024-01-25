#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
const ll Mod=998244353;
bool mem1;
int n,m,a[N];
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
ll c(int x) { return inv[x]*fac[x-1]%Mod; }
int cnt[N],sum[2];
ll calc(int del) {
    vector<int> v;
    ll s=0;
    for(int i=del;i<=n;i+=2) {
        if(a[i]==1) v.push_back(-s);
        else s++;
    }
    for(int i=0;i<(int)v.size();i++) v[i]+=s, sum[del]+=v[i];
    ll res=fac[sum[del]];
    memset(cnt,0,sizeof(cnt));
    for(int i=(int)v.size()-1;i>=0;i--) {
        for(int j=1;j<=v[i];j++) res=res*c(v[i]-j+1+(cnt[j]++))%Mod;
    }
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    cin>>m;
    for(int i=1,x,pre=0;i<=m;i++,pre=x) {
        cin>>x;
        for(int j=1;j<=x-pre;j++) a[++n]=1;
        a[++n]=0;
    }
    int c[2]={0,0};
    for(int i=1;i<=n;i++) c[i&1]+=(a[i]==0);
    if(c[1]!=c[0]&&c[1]!=c[0]+1) return cout<<0<<endl, 0;
    cout<<calc(0)*calc(1)%Mod*C(sum[0]+sum[1],sum[0])%Mod<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}