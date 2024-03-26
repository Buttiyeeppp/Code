#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=7e6+10;
const int V=2e9;
bool mem1;
struct SegmentTree {
    ll w[M];
    int s[M],ls[M],rs[M],lz[M],tot;
    SegmentTree() {
        tot=0;
        memset(w,0,sizeof(w));
        memset(s,0,sizeof(s));
        memset(ls,0,sizeof(ls));
        memset(rs,0,sizeof(rs));
        memset(lz,0,sizeof(lz));
    }
    void pushdown(int id) {
        if(!lz[id]) return;
        lz[id]=0;
        w[ls[id]]*=-1, lz[ls[id]]^=1;
        w[rs[id]]*=-1, lz[rs[id]]^=1;
    }
    void Modify(int &id,int l,int r,int x,int v) {
        if(!id) id=++tot;
        if(l==r) {
            v^=s[id], s[id]^=1;
            w[id]+=(v? -1:+1)*x;
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls[id],l,mid,x,v^s[rs[id]]);
        else Modify(rs[id],mid+1,r,x,v), w[ls[id]]*=-1, lz[ls[id]]^=1;
        s[id]=s[ls[id]]^s[rs[id]];
        w[id]=w[ls[id]]+w[rs[id]];
    }
}t;
int n,q,o,u[N],v[N],w[N],cnt,c[N],rt;
void upd(int x) {
    assert(c[x]<=V);
    if(c[x]) t.Modify(rt,1,V,c[x],0);
}
bool mem2;
int main() {
    freopen("game.in","r",stdin);
    freopen("game.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>q>>o;
    for(ll i=1,op,x,y,k,lst=0;i<=q;i++) {
        cin>>op;
        if(op) {
            cin>>x>>y>>k;
            if(o) x^=lst, y^=lst;
            cnt++, u[cnt]=x, v[cnt]=y, w[cnt]=k;
            upd(x); if(x!=y) upd(y);
            c[x]+=k, c[y]+=k;
            upd(x); if(x!=y) upd(y);
        }
        else {
            cin>>k;
            if(o) k^=lst;
            upd(u[k]); if(u[k]!=v[k]) upd(v[k]);
            c[u[k]]-=w[k], c[v[k]]-=w[k];
            upd(u[k]); if(u[k]!=v[k]) upd(v[k]);
        }
        lst=t.w[1]/2;
        cout<<lst<<endl;
    }


    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}