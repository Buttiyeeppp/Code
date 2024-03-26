#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define fi first
#define se second
using ll=long long;
using PII=pair<int,int>;
using PLI=pair<ll,int>;
using PLL=pair<ll,ll>;
const int N=1e5+10;
bool mem1;
int n,m,a[N];
struct Node {
    PLI mx,mn;
    tuple<ll,int,int> v;
};
Node merge(Node a, Node b) {
    Node res;
    res.mx=max(a.mx,b.mx);
    res.mn=min(a.mn,b.mn);
    res.v=max(a.v,b.v);
    res.v=max(res.v,{a.mx.fi-b.mn.fi,a.mx.se,b.mn.se});
    return res;
}
struct SegmentTree {
    Node node[N<<2];
    ll lz[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void pushdown(int id) {
        if(!lz[id]) return;
        ll val=lz[id]; lz[id]=0;
        node[ls].mx.fi+=val, node[ls].mn.fi+=val, lz[ls]+=val;
        node[rs].mx.fi+=val, node[rs].mn.fi+=val, lz[rs]+=val;
    }
    void pushup(int id) {node[id]=merge(node[ls],node[rs]);}
    void Build(int id,int l,int r) {
        lz[id]=0;
        if(l==r) {
            node[id].mx=node[id].mn={a[l],l};
            node[id].v={0,l,l};
            return;
        }
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
        pushup(id);
    }
    void Modify(int id,int l,int r,int x,int y,ll val) {
        if(x<=l&&y>=r) {
            node[id].mx.fi+=val, node[id].mn.fi+=val, lz[id]+=val;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,y,val);
        if(y>mid) Modify(rs,mid+1,r,x,y,val);
        pushup(id);
    }
    PLI Query(int id,int l,int r,int x,int y,int f) {
        if(x<=l&&y>=r) return (f? node[id].mx:node[id].mn);
        pushdown(id);
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y,f);
        if(x>mid) return Query(rs,mid+1,r,x,y,f);
        if(f) return max(Query(ls,l,mid,x,y,f),Query(rs,mid+1,r,x,y,f));
        else return min(Query(ls,l,mid,x,y,f),Query(rs,mid+1,r,x,y,f));
    }
    Node Query2(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return node[id];
        pushdown(id);
        int mid=(l+r)>>1;
        if(y<=mid) return Query2(ls,l,mid,x,y);
        if(x>mid) return Query2(rs,mid+1,r,x,y);
        return merge(Query2(ls,l,mid,x,y),Query2(rs,mid+1,r,x,y));
    }
}t;
struct Seg {
    int f,a,b,c,d,p1,p2;
};
priority_queue<PLI> q;
vector<Seg> sg;
void Add(int f,int a,int b,int c=0,int d=0) {
    if(a>b||c>d) return;
    if(f==1) {
        Node res=t.Query2(1,1,n,a,b);
        q.emplace(get<0>(res.v),sg.size());
        sg.push_back((Seg){1,a,b,a,b,get<1>(res.v),get<2>(res.v)});
    }
    else {
        PLI r1=t.Query(1,1,n,a,b,1), r2=t.Query(1,1,n,c,d,0);
        q.emplace(r1.fi-r2.fi,sg.size());
        sg.push_back((Seg){2,a,b,c,d,r1.se,r2.se});
    }
}
bool mem2;
int main() {
    freopen("smart.in","r",stdin);
    freopen("smart.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>a[i];
    t.Build(1,1,n);
    for(int i=1,op,l,r,x;i<=m;i++) {
        cin>>op>>l>>r>>x;
        if(op==1) t.Modify(1,1,n,l,r,x);
        else {
            ll ans=0;
            sg.clear();
            while(q.size()) q.pop();
            Add(1,l,r);
            while(x) {
                auto now=q.top(); q.pop();
                x--, ans+=now.fi;
                auto seg=sg[now.se];
                int x=seg.p1, y=seg.p2;
                if(seg.f==1) {
                    int l=seg.a, r=seg.b;
                    Add(1,l,x-1);
                    Add(1,x,x);
                    Add(1,x+1,r);
                    Add(2,l,x-1,x,r);
                    Add(2,x,x,x+1,y-1);
                    Add(2,x,x,y+1,r);
                }
                else {
                    int l1=seg.a, r1=seg.b, l2=seg.c, r2=seg.d;
                    Add(2,x,x,l2,y-1);
                    Add(2,x,x,y+1,r2);
                    Add(2,l1,x-1,l2,r2);
                    Add(2,x+1,r1,l2,r2);
                }
            }
            cout<<ans<<endl;
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}