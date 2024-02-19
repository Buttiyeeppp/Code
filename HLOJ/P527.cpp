#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=998244353;
bool mem1;
int read() {
    int f=1, x=0; char ch=getchar();
    while(ch<'0'||ch>'9') {
        if(ch=='-') f*=-1;
        ch=getchar();
    }
    while(ch>='0'&&ch<='9') {
        x=x*10+ch-'0'; ch=getchar();
    }
    return f*x;
}
int n,a[N];
void solve() {
    n=read();
    for(int i=1;i<=n;i++) a[i]=read();
    for(int i=3;i<=n;i++)
        if(a[i]<a[i-1]&&a[i-1]<a[i-2]) return cout<<0<<endl, void();
    int pd=0;
    for(int i=2;i<=n;i++) if(a[i]<a[i-1]) pd=1;
    ll ans=1;
    if(!pd) {
        for(int i=1;i<=n;i++) ans=ans*2%Mod;
        cout<<ans<<endl;
        return;
    }
    int fir=0, lst=0;
    for(int i=2,x=0,y=0;i<=n;i++) {
        if(a[i]<a[i-1]) {
            if(!x) { fir=lst=x=i; continue; }
            lst=y=i;
        }
        else continue;
        ll v=1;
        for(int j=x+1;j<=y-2;j++) {
            if(a[x-1]<=a[j]&&a[j]<=a[y]) v=v*2ll%Mod;
            if(a[j]<a[x-1]&&a[j]>a[y]) return cout<<0<<endl, void();
        }
        ll res=0;
        if(a[x-1]<=a[y-1]&&a[x]<=a[y]) res=(res+v)%Mod;
        if(a[x-1]<=a[y]&&a[x]<=a[y-1]) res=(res+v)%Mod;
        ans=ans*res%Mod;
        x=y;
    }
    ans=ans*2ll%Mod;
    for(int i=1;i<=fir-1;i++) if(a[i]<=a[fir]) ans=ans*2ll%Mod;
    for(int i=lst+1;i<=n;i++) if(a[i]>=a[lst-1]) ans=ans*2ll%Mod;
    cout<<ans<<endl;
}
bool mem2;
int main() {
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T=read();
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}