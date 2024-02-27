#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll Mod=998244353;
const int N=1e5+10;
bool mem1;
int n,k,a[N],B,lz[317],c[N],p[N],pre[N];
int f[N],g[317][N<<1],sm[317];
void Add(int &x,int y) { x=(x+y>=Mod)? x+y-Mod:x+y; }
void Modify(int l,int r,int v) {
    if(l>r) return;
    int bl=(l-1)/B, br=(r-1)/B;
    // cout<<l<<" "<<r<<" "<<v<<endl;
    // for(int i=1;i<=4;i++) cout<<c[i]<<" "; cout<<endl;
    // for(int i=0;i<=10;i++) cout<<g[0][i+N]<<" "; cout<<endl;
    if(bl==br) {
        for(int i=l;i<=r;i++) {
            if(v==-1) Add(g[bl][c[i]+N],Mod-f[i-1]);
            c[i]+=v;
            if(v==+1) Add(g[bl][c[i]+N],f[i-1]);
        }
        return;
    }
    for(int i=l;i<=(bl+1)*B;i++) {
        if(v==-1) Add(g[bl][c[i]+N],Mod-f[i-1]);
        c[i]+=v;
        if(v==+1) Add(g[bl][c[i]+N],f[i-1]);
    }
    for(int i=br*B+1;i<=r;i++) {
        if(v==-1) Add(g[br][c[i]+N],Mod-f[i-1]);
        c[i]+=v;
        if(v==+1) Add(g[br][c[i]+N],f[i-1]);
    }
    for(int i=bl+1;i<br;i++) lz[i]+=v;
}
ll Qry(int r) {
    int bl=0, br=(r-1)/B;
    int res=0;
    if(bl==br) {
        for(int i=1;i<=r;i++)
            if(c[i]+lz[bl]<=k) Add(res,f[i-1]);
        return res;
    }
    for(int i=bl;i<br;i++) if(k+1-lz[i]>=0)
        Add(res,(1ll*sm[i]-g[i][k+1-lz[i]+N]+Mod)%Mod);
    for(int i=br*B+1;i<=r;i++) if(c[i]+lz[br]<=k) Add(res,f[i-1]);
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i], pre[i]=p[a[i]], p[a[i]]=i;
    B=sqrt(n)+1;
    f[0]=1;
    for(int i=1;i<=n;i++) {
        //  [pre[i]+1,i]          [pre[pre[i]]+1,pre[i]]
        int blo=(i-1)/B; c[i]=-lz[blo];
        Add(g[blo][c[i]+N],f[i-1]), Add(sm[blo],f[i-1]);
        Modify(pre[i]+1,i,+1), Modify(pre[pre[i]]+1,pre[i],-1);
        f[i]=Qry(i);
    }
    // for(int i=1;i<=n;i++) cout<<f[i]<<" "; cout<<endl;
    cout<<f[n]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}