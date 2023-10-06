#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=8e5+10;
const ll Mod=998244353;
const ll inf=1e9+10;
bool mem1;
ll n,v[N],m,pre[N];
struct Option {
    ll op,x;
}a[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i].op;
        if(a[i].op!=3) cin>>a[i].x;
        pre[i]=pre[i-1];
        if(a[i].op==2) pre[i]=min(inf,pre[i]+a[i].x);
        if(a[i].op==3) pre[i]=min(inf,pre[i]<<1);
    }
    ll val=0,ans=0,c=1;
    for(int i=n;i>=1;i--) {
        if(a[i].op==1) {
            a[i].x-=val;
            if(a[i].x<=0) continue;
            ll res=1;
            for(int j=0;j<m;j++) {
                if(a[i].x>v[j]) res=(res+(1ll<<(m-j-1)))%Mod, a[i].x-=v[j];
            }
            ans=(ans+res*c)%Mod;
        }
        if(a[i].op==2) val=min(inf,val+a[i].x);
        if(a[i].op==3) if(pre[i-1]<inf) {
            if(pre[i-1]) v[m++]=pre[i-1];
            else c=(c<<1)%Mod;
        }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}