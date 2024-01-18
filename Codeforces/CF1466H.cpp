#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const int M=42;
const ll Mod=1e9+7;
bool mem1;
int n,p[N],vis[N],len;
ll f[M][M],fac[N],inv[N];
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
    return x=(x+y>=Mod)? x+y-Mod:x+y, void();
}
void dfs(int x) {
    vis[x]=1, len++;
    if(!vis[p[x]]) dfs(p[x]);
}
map<vector<int>,ll> mp;
int siz(vector<int> &cnt) {
    int res=0;
    for(auto i:cnt) res+=i;
    return res;
}
int s(vector<int> &cnt) {
    int res=0;
    for(int i=0;i<(int)cnt.size();i++) res+=i*cnt[i];
    return res;
}
ll calc(vector<int> cnt) {
    if(mp[cnt]) return mp[cnt];
    vector<int> pcnt(n+1);
    ll res=0, sm=s(cnt), sz=siz(cnt);
    while(cnt!=pcnt) {
        ll psm=s(pcnt);
        ll c=1;
        for(int i=0;i<(int)cnt.size();i++) c=c*C(cnt[i],pcnt[i]);
        Add(res,(((sz-siz(pcnt))&1)? 1:Mod-1)*calc(pcnt)%Mod*f[psm][sm-psm]%Mod*c%Mod);
        pcnt[0]++;
        for(int i=0;i<(int)pcnt.size();i++) {
            if(pcnt[i]>cnt[i]) pcnt[i]=0, pcnt[i+1]++;
            else break;
        }
    }
    return mp[cnt]=res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    init();
    for(int i=0;i<=n;i++) {
        for(int j=0;j<=i;j++) Add(f[i][1],C(i,j)*fac[j]%Mod*fac[n-j-1]%Mod);
        for(int j=2;j<=n;j++) f[i][j]=f[i][j-1]*f[i][1]%Mod;
    }
    vector<int> cnt(n+1);
    for(int i=1;i<=n;i++) if(!vis[i]) {
        len=0, dfs(i), cnt[len]++;
    }
    mp[vector<int> (n+1,0)]=1;
    cout<<calc(cnt)<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}