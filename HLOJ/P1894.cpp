#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,q,ans;
int mx[2][N],mn[2][N];
void Max(int &x,int y) { if(y>x) x=y; }
void Min(int &x,int y) { if(y<x) x=y; }
struct Union {
    int fa[N];
    void init(int n) {
        for(int i=1;i<=n;i++) fa[i]=i;
    }
    int find(int x) {
        if(x==fa[x]) return x;
        return fa[x]=find(fa[x]);
    }
    void merge(int x,int y) {
        int fx=find(x), fy=find(y);
        if(fx!=fy) fa[fx]=fy;
    }
    void dmerge(int x,int y) {
        x=find(x);
        while(x<y) {
            fa[x]=x+1, x=find(fa[x]);
            ans--;
        }
    }
}t,d,tree;
int vis[N],st[N],top,tot,p[N],id[N];
int sz[N],dep[N];
vector<int> nd[N];
void upd(int x,int y,int f) {
    if(!x||!y||x==0x3f3f3f3f||y==0x3f3f3f3f) return;
    if(x>y) swap(x,y);
    if(!f) d.dmerge(x,y);
    else d.dmerge(y,tot+1), d.dmerge(1,x);
}
void tmerge(int x,int y) {
    int fx=tree.find(x), fy=tree.find(y);
    if(fx==fy) return; 
    if(sz[fy]<sz[fx]) swap(fx,fy), swap(x,y);
    sz[fy]+=sz[fx], tree.fa[fx]=fy;
    int c=dep[x]^dep[y];
    for(auto i:nd[fx]) {
        nd[fy].push_back(i);
        dep[i]^=c^1;
        if(id[i])
            Max(mx[dep[i]^(id[i]&1)][fy],id[i]), Min(mn[dep[i]^(id[i]&1)][fy],id[i]);
    }
    y=fy;
    for(auto i:{0,1}) for(auto j:{0,1}) {
        upd(mn[i][y],mx[j][y],i^j);
        upd(mn[i][y],mn[j][y],i^j);
        upd(mx[i][y],mx[j][y],i^j);
    }
}
int ver;
vector<int> eg[N];
void dfs(int x) {
    if(tot) return;
    st[++top]=x, vis[x]=1;
    for(auto y:eg[x]) if(!vis[y]) {
        int ny=(y>n)? y-n:y+n;
        if(vis[ny]) {
            while(st[top+1]!=ny) {
                int d=(st[top]>n)? st[top]-n:st[top];
                p[++tot]=d, id[d]=tot, top--;
            }
            return;
        }
        dfs(y);
        if(tot) return;
    }
    st[top--]=0;
}
void work(int x) { // 出现奇环
    /*
        ans=奇环长度
        判断剩下的边形成的图是否合法
        合法：维护各种树
    */
    ver=2;
    dfs(x), ans=tot;
    assert(tot!=0);
    t.init(n<<1);
    tree.init(n), d.init(n+1);
    memset(mx,0,sizeof(mx)), memset(mn,0x3f,sizeof(mn));
    for(int i=1;i<=n;i++) {
        nd[i].push_back(i);
        if(id[i]) mn[id[i]&1][i]=mx[id[i]&1][i]=id[i], sz[i]=1;
    }
    for(int i=1;i<=n;i++) {
        for(auto j:eg[i]) {
            j-=n;
            if(!id[i]||!id[j]||(abs(id[i]-id[j])!=1&&abs(id[i]-id[j])!=tot-1)) {
                t.merge(i,j+n), t.merge(i+n,j);
                tmerge(i,j);
            }
        }
    }
    for(int i=1;i<=n;i++) 
        if(t.find(i)==t.find(i+n)) ver=3;
}
bool mem2;
int main() {
    freopen("algorithm.in","r",stdin);
    freopen("algorithm.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>q;
    t.init(n<<1);
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        t.merge(x,y+n), t.merge(x+n,y);
        eg[x].push_back(y+n), eg[y+n].push_back(x);
        eg[x+n].push_back(y), eg[y].push_back(x+n);
    }
    ver=1;
    for(int i=1;i<=n;i++)
        if(t.find(i)==t.find(i+n)) work(i);
    for(int i=1,op,x,y;i<=q;i++) {
        cin>>op;
        if(op==1) {
            cin>>x>>y;
            m++;
            if(ver==1) {
                t.merge(x,y+n), t.merge(x+n,y);
                eg[x].push_back(y+n), eg[y+n].push_back(x);
                eg[x+n].push_back(y), eg[y].push_back(x+n);
                if(t.find(x)==t.find(x+n)) work(x);
                else if(t.find(y)==t.find(y+n)) work(y);
            }
            else if(ver!=3) {
                t.merge(x,y+n), t.merge(x+n,y);
                if(t.find(x)==t.find(x+n)||t.find(y)==t.find(y+n)) { ver=3; continue; }
                tmerge(x,y);
            }
        }
        if(op==2) {
            cout<<((ver==1)? "YES":"yes")<<endl;
        }
        if(op==3) {
            if(ver==1) cout<<m<<endl;
            if(ver==2) cout<<ans<<endl;
            if(ver==3) cout<<0<<endl;
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}