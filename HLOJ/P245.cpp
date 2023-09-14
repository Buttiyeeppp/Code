#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
const int M=3e7+10;
bool mem1;
int fa[N],p[N],n,tot,nxt[M];
struct edge {
    int x,y,v;
}eg[M];
int find(int x) {
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
bool mem2;
int main() {
//    freopen("D.in","r",stdin);
//    freopen("D.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i];
    sort(p+1,p+n+1);
    n=unique(p+1,p+n+1)-p-1;
    for(int i=1;i<=n;i++) nxt[p[i]]=i;
    for(int i=M;i>=0;i--) {
        if(!nxt[i]&&i<M) nxt[i]=nxt[i+1];
    }
    for(int i=1;i<=n;i++) {
        for(int j=p[i];j<M;j+=p[i]) {
            int k=nxt[j];
            if(k&&p[k]<j+p[i]) {
                if(k==i) k++;
                if(k<=n) assert(p[i]!=0), assert(k>=1&&k<=n);
                if(k<=n) eg[++tot]={i,k,p[k]%p[i]};
            }
        }
    }
    sort(eg+1,eg+tot+1,[](const edge &q,const edge &p) { return q.v<p.v; });
    ll ans=0;
    for(int i=1;i<=n;i++) fa[i]=i;
    for(int i=1;i<=tot;i++) {
        int fx=find(eg[i].x), fy=find(eg[i].y);
        if(fx!=fy) {
            ans+=eg[i].v, fa[fx]=fy;
        }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}