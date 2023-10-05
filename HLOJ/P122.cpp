#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
const int M=2e6+10;
bool mem1;
int n,q,a[N][N],X[M],tot,l[N],h[N],nd[N];
struct query {
    int v,id;
}qr[M];
struct node { int x,y; };
vector<node> pos[M];
int ans[M];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) cin>>a[i][j], X[++tot]=a[i][j];
    for(int i=1;i<=q;i++) cin>>qr[i].v, qr[i].id=i, X[++tot]=qr[i].v;
    sort(X+1,X+tot+1);
    tot=unique(X+1,X+tot+1)-X-1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) 
            a[i][j]=lower_bound(X+1,X+tot+1,a[i][j])-X, pos[a[i][j]].push_back({i,j});
    for(int i=1;i<=q;i++) qr[i].v=lower_bound(X+1,X+tot+1,qr[i].v)-X;
    sort(qr+1,qr+q+1,[](const query &x,const query &y) { return x.v>y.v; });
    int p=1, res=0, mx=0;
    for(int i=tot;i>=1;i--) {
        for(auto now:pos[i]) {
            if(!l[now.y]) res++;
            if(l[now.y]>=2) h[now.x]++, mx=max(mx,h[now.x]);
            l[now.y]++;
            if(l[now.y]==2) {
                h[nd[now.y]]++, mx=max(mx,h[nd[now.y]]);
                h[now.x]++, mx=max(mx,h[now.x]);
            }
            nd[now.y]=now.x;
        }
        while(p<=q&&qr[p].v==i) ans[qr[p++].id]=min(n,res+mx);
    }
    for(int i=1;i<=q;i++) cout<<ans[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}