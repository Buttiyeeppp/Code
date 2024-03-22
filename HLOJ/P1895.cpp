#include <algorithm>
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
int n,k,a[N],t[N],fa[N],nt[N],vis[N],sz[N],ans[N];
int find(int x) {
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
    x=find(x), y=find(y);
    if(x!=y) fa[x]=y, sz[y]+=sz[x];
}
bool mem2;
int main() {
    freopen("carpet.in","r",stdin);
    freopen("carpet.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    while((1<<k)+k-1<=n) k++;
    k--;
    int m=1<<k, d=1<<(k-1);
    for(int i=0;i<=m;i++) fa[i]=i, sz[i]=1;
    for(int i=0;i<m;i++) a[i]=(i+d)%m, t[i]=(i<a[i]), merge(i,(2*i+t[i])%m);
    for(int i=0;i<m;i++) if(find(i)!=find(a[i])) swap(t[i],t[a[i]]), merge(i,a[i]);
    if((1<<k)+k-1==n) {
        int v=0;
        for(int i=k+1;i<=n;i++) ans[i]=t[v], v=(2*v+t[v])%m;
        for(int i=1;i<=n;i++) cout<<ans[i];
        cout<<endl;
        return 0;
    }
    int p=t[0], val=t[0], nm=1<<(k+1);
    for(int i=0;i<=nm;i++) fa[i]=i, sz[i]=1;
    for(int i=1;i<=m;i++) {
        nt[p]=t[val], merge(p,(2*p+nt[p])%nm), vis[p]=1;
        p=(2*p+t[val])%nm;
        val=(2*val+t[val])%m;
    }
    m=nm, d=1<<k;
    for(int i=0;i<d;i++) a[i]=i+d;
    for(int i=0;i<m;i++) if(!vis[i]) {
        nt[i]=nt[(i<d)? i+d:i-d]^1;
        merge(i,(2*i+nt[i])%m);
    }
    int rt=t[0];
    for(int i=0;i<d;i++) {
        if(sz[find(rt)]>=n-k) break;
        if(find(i)!=find(a[i])) {
            rt=(find(rt)==find(i))? (i*2+nt[i])%m:(a[i]*2+nt[a[i]])%m;
            merge(i,a[i]), swap(nt[i],nt[a[i]]);
        }
    }
    for(int i=1;i<=k+1;i++) ans[i]=(((1<<(k+1-i))&rt)!=0);
    for(int i=k+2;i<=n;i++) ans[i]=nt[rt], rt=(rt*2+nt[rt])%m;
    for(int i=1;i<=n;i++) cout<<ans[i];
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}