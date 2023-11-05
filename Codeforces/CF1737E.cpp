#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=1e9+7;
bool mem1;
ll n,f[N],s[N];
ll Pow(ll x,ll y) {
    ll res=1;
    while(y) {
        if(y&1) res=res*x%Mod;
        x=x*x%Mod, y>>=1;
    }
    return res;
}
void solve() {
    cin>>n;
    f[n]=s[n]=1, s[n+1]=0;
    for(int i=n-1;i>=1;i--) {
        f[i]=(s[i+1]-s[min(2*i,(int)n+1)]+Mod)%Mod;
        s[i]=(f[i]+s[i+1])%Mod;
    }
    ll z=Pow(Pow(2,n-1),Mod-2);
    for(int i=1;i<=n;i++)
        cout<<Pow(2,i/2)*f[i]%Mod*z%Mod<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}