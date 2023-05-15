#include <bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,Q,cnt;
map<PII,int> mp;
PII q[N];
struct Edge {
    int x,y,w,t1,t2;
}g[N<<1];
vector<Edge> eg[N<<2];
void Modify(int id,int l,int r,int x,int y,int a,int b,int c) {
    if(x<=l&&y>=r) return eg[id].push_back(Edge{a,b,c,-1,-1}), void();
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,y,a,b,c);
    if(y>mid) Modify(rs,mid+1,r,x,y,a,b,c);
}
int ans[N],tot,fa[N],sz[N],xo[N];
int B[35];
PII find(int x,int res) {
    if(fa[x]==x) return make_pair(x,res);
    else return find(fa[x],res^xo[x]);
}
void insert(int x) {
    for(int i=29;i>=0;i--) if((1<<i)&x){
        if(B[i]) x^=B[i];
        else {
            B[i]=x; break;
        }
    }
}
void calc(int id,int l,int r) {
    vector<int> mem;
    int mB[35];
    memcpy(mB,B,sizeof(B));
    for(auto now:eg[id]) {
        PII nowx=find(now.x,0), nowy=find(now.y,0);
        int fx=nowx.first, fy=nowy.first;
        // cout<<"Edge "<<now.x<<" "<<now.y<<" "<<fx<<" "<<fy<<" "<<now.w<<" "<<nowx.second<<" "<<nowy.second<<endl;
        // if(now.x==1&&now.y==5) {
        //     for(int i=1;i<=n;i++) cout<<xo[i]<<" "; cout<<endl;
        //     for(int i=1;i<=n;i++) cout<<fa[i]<<" "; cout<<endl;
        // }
        if(fx==fy) insert(now.w^nowx.second^nowy.second);
        else {
            if(sz[fx]>sz[fy]) swap(fx,fy);
            sz[fy]+=sz[fx], fa[fx]=fy, xo[fx]=now.w^nowx.second^nowy.second;
            mem.push_back(fx);
        }
    }
    if(l==r) {
        if(q[l].first) {
            ans[++tot]=find(q[l].first,0).second^find(q[l].second,0).second;
            for(int i=29;i>=0;i--) if((ans[tot]^B[i])<ans[tot]) ans[tot]^=B[i];
        }
    }
    else {
        int mid=(l+r)>>1;
        calc(ls,l,mid), calc(rs,mid+1,r);
    }
    for(int i=mem.size()-1;i>=0;i--) {  
        int now=mem[i];
        sz[fa[now]]-=sz[now], fa[now]=now, xo[now]=0;
    }
    mem.clear();
    memcpy(B,mB,sizeof(B));
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) fa[i]=i, sz[i]=1;
    for(int i=1,x,y,d;i<=m;i++) {
        cin>>x>>y>>d;
        g[++cnt]=Edge{x,y,d,1,-1};
        mp[make_pair(x,y)]=cnt;
    }
    cin>>Q;
    for(int i=1,op,x,y,d;i<=Q;i++) {
        cin>>op>>x>>y;
        if(op==1) {
            cin>>d;
            g[++cnt]=Edge{x,y,d,i,-1};
            mp[make_pair(x,y)]=cnt;
        }
        if(op==2) {
            int now=mp[make_pair(x,y)];
            g[now].t2=i;
        }
        if(op==3) {
            q[i]=make_pair(x,y);
        }
    }
    for(int i=1;i<=cnt;i++) {
        if(g[i].t2==-1) g[i].t2=Q;
        // cout<<g[i].t1<<" "<<g[i].t2<<" "<<g[i].x<<" "<<g[i].y<<" "<<g[i].w<<endl;
        Modify(1,1,Q,g[i].t1,g[i].t2,g[i].x,g[i].y,g[i].w);
    }
    calc(1,1,Q);
    for(int i=1;i<=tot;i++) cout<<ans[i]<<endl;

    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}
/*
5 5
1 2 3
2 3 4
3 4 5
4 5 6
1 5 1
5
3 1 5
1 1 3 1
3 1 5
2 1 5
3 1 5

*/