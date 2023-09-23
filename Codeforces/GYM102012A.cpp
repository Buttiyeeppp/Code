#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll Mod=1e9+7;
bool mem1;
int n,m;
ull k1,k2;
ull shift() {
    ull k3=k1, k4=k2;
    k1=k4;
    k3^=k3<<23;
    k2=k3^k4^(k3>>17)^(k4>>26);
    return k2+k4;
}
struct Edge {
    int x,y;
    ull c;
    bool operator<(const Edge &x)const {
        return c<x.c;
    }
}eg[N];
int fa[N];
int find(int x) {
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
void solve() {
    cin>>n>>m>>k1>>k2;
    for(int i=1;i<=m;i++) {
        int x=shift()%n+1, y=shift()%n+1; ull c=shift();
        eg[i]={x,y,c};
    }
    for(int i=1;i<=n;i++) fa[i]=i;
    ull ans=0; int tot=0;
    sort(eg+1,eg+m+1);
    for(int i=1;i<=m;i++) {
        int fx=find(eg[i].x), fy=find(eg[i].y);
        if(fx!=fy) fa[fx]=fy, ans=(ans+eg[i].c%Mod)%Mod, tot++;
    }
    cout<<(tot!=n-1? 0:ans)<<endl;
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