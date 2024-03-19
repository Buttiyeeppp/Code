#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,q,fa[N],dep[N];
int dfn[N],rdfn[N],tim,mxdfn[N],top[N],son[N],sz[N];
int tag[N],qbs[N],col[N];
vector<int> eg[N];
void dfs(int x) {
    sz[x]=1;
    for(auto y:eg[x]) {
        dep[y]=dep[x]+1;
        dfs(y);
        sz[x]+=sz[y];
        if(!son[x]||sz[y]>sz[son[x]]) son[x]=y;
    }
}
void dfs1(int x) {
    dfn[x]=++tim, rdfn[tim]=x;
    if(son[x]) top[son[x]]=top[x], dfs1(son[x]);
    for(auto y:eg[x]) if(y!=son[x]) {
        qbs[x]++;
        top[y]=y, dfs1(y);
    }
    mxdfn[x]=tim;
}
struct SegmentTree {
    struct node {
        int od,ev,qod,qev; // 重链上奇/偶深度数量，轻链上...
        int b,qb,lz; // 黑重边数，黑轻边数
        // 重链点向上的边和向下的轻链
        friend node operator+(const node &x,const node &y) {
            return {x.od+y.od,x.ev+y.ev,x.qod+y.qod,x.qev+y.qev,x.b+y.b,x.qb+y.qb,-1};
        }
    }d[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void pushdown(int id) {
        if(d[id].lz==-1) return;
        int f=d[id].lz; d[id].lz=-1;
        d[ls].lz=d[rs].lz=f;
        d[ls].b=(f? d[ls].od:d[ls].ev);
        d[ls].qb=(f? d[ls].qev:d[ls].qod);
        d[rs].b=(f? d[rs].od:d[rs].ev);
        d[rs].qb=(f? d[rs].qev:d[rs].qod);
    }
    void Build(int id,int l,int r) {
        if(l==r) {
            d[id]={0,0,0,0,0,0,-1};
            int x=rdfn[l];
            if(x!=top[x]) ((dep[x]&1)? d[id].od:d[id].ev)++;
            for(auto y:eg[x]) if(y!=son[x]) {
                ((dep[x]&1)? d[id].qev:d[id].qod)++;
            }
            return;
        }
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
        d[id]=d[ls]+d[rs];
    }
    void Modify(int id,int l,int r,int x,int y,int f) {
        if(x<=l&&y>=r) {
            d[id].lz=f;
            d[id].b=(f? d[id].od:d[id].ev);
            d[id].qb=(f? d[id].qev:d[id].qod);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,y,f);
        if(y>mid) Modify(rs,mid+1,r,x,y,f);
        d[id]=d[ls]+d[rs];
    }
    void Modify1(int id,int l,int r,int x,int f) { // 特殊处理轻链
        if(l==r) {
            d[id].qb+=(((dep[rdfn[l]]&1)==f)? -1:+1);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify1(ls,l,mid,x,f);
        else Modify1(rs,mid+1,r,x,f);
        d[id]=d[ls]+d[rs];
    }
    void Modify2(int id,int l,int r,int x,int v) { // 链修改时的 son[x]
        if(l==r) {
            d[id].b=v;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify2(ls,l,mid,x,v);
        else Modify2(rs,mid+1,r,x,v);
        d[id]=d[ls]+d[rs];
    }
    void Modify(int p) {
        int x=p,f=dep[x]&1;
        while(x) {
            Modify(1,1,n,dfn[top[x]],dfn[x],f);
            x=fa[top[x]];
        }
        x=p;
        int fat=fa[top[x]];
        while(fat) {
            tag[fat]=top[x], col[fat]=((dep[fat]&1)==f);
            Modify1(1,1,n,dfn[fat],f);
            Modify2(1,1,n,dfn[son[fat]],((dep[son[fat]]&1)!=f));
            x=fat, fat=fa[top[x]];
       }
        if(son[p]) Modify2(1,1,n,dfn[son[p]],((dep[son[p]]&1)!=f));
    }
    int Query(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return d[id].b;
        pushdown(id);
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y);
        if(x>mid) return Query(rs,mid+1,r,x,y);
        return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
    }
    int qQuery(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return d[id].qb;
        pushdown(id);
        int mid=(l+r)>>1;
        if(y<=mid) return qQuery(ls,l,mid,x,y);
        if(x>mid) return qQuery(rs,mid+1,r,x,y);
        return qQuery(ls,l,mid,x,y)+qQuery(rs,mid+1,r,x,y);
    }
    int Query1(int x) { // 链查
        int res=0, fat=fa[top[x]];
        while(x) {
            res+=Query(1,1,n,dfn[top[x]],dfn[x]);
            if(fat) {
                int qc=qQuery(1,1,n,dfn[fat],dfn[fat]);
                if(!qc||qc==qbs[fat]) res+=(qc!=0);
                else {
                    res+=col[fat]^(tag[fat]==top[x]);
                }
            }
            x=fat, fat=fa[top[x]];
        }
        return res;
    }
    int Query2(int x) { // 子树查
        int res=((dfn[x]!=mxdfn[x])? Query(1,1,n,dfn[x]+1,mxdfn[x]):0)+qQuery(1,1,n,dfn[x],mxdfn[x]);
        return res;
    }
}t;
// 重链挂儿子上，轻链挂父亲上
bool mem2;
int main() {
    freopen("chain.in","r",stdin);
    freopen("chain.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=2;i<=n;i++) cin>>fa[i], eg[fa[i]].push_back(i);
    dfs(1), top[1]=1, dfs1(1);
    t.Build(1,1,n);
    cin>>q;
    for(int i=1,op,x;i<=q;i++) {
        cin>>op>>x;
        if(op==1) t.Modify(x);
        if(op==2) cout<<t.Query1(x)<<endl;
        if(op==3) cout<<t.Query2(x)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}