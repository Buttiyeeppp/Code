#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,Q,pl[N],pr[N];
PII p[N];
vector<PII> qr[N];
#define ls (id<<1)
#define rs (id<<1|1)
struct Matrix {
    ll a[3][3];
    Matrix() { memset(a,0,sizeof(a)); }
    friend bool operator==(const Matrix &x,const Matrix &y) {
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++) if(x.a[i][j]!=y.a[i][j]) return false;
        return true;
    }
    friend Matrix operator+(const Matrix &x,const Matrix &y) {
        Matrix res;
        for(int i=0;i<3;i++) res.a[0][i]=x.a[0][i]+y.a[0][i];
        return res;
    }
    friend Matrix operator*(const Matrix &x,const Matrix &y) {
        Matrix res;
        for(int i=0;i<3;i++)
            for(int j=0;j<3;j++)
                for(int k=0;k<3;k++) res.a[i][j]+=x.a[i][k]*y.a[k][j];
        return res;
    }
}v[N<<2],lz[N<<2],unit,nxt;
namespace seg1 {
    void Build(int id,int l,int r) {
        lz[id]=unit, v[id].a[0][2]=r-l+1;
        if(l==r) return;
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
    }
    void pushdown(int id) {
        if(lz[id]==unit) return;
        Matrix val=lz[id]; lz[id]=unit;
        v[ls]=v[ls]*val, lz[ls]=lz[ls]*val;
        v[rs]=v[rs]*val, lz[rs]=lz[rs]*val;
        // int mid=(l+r)>>1;
        // v[ls].a[0][1]*=(mid-l+1);
        // v[rs].a[0][1]*=(r-mid);
    }
    void Modify(int id,int l,int r,int x,int y,Matrix val) {
        if(x<=l&&y>=r) {
            v[id]=v[id]*val, lz[id]=lz[id]*val;
            // v[id].a[0][1]*=(r-l+1);
            return;
        }
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,y,val);
        if(y>mid) Modify(rs,mid+1,r,x,y,val);
        v[id]=v[ls]+v[rs];
    }
    ll Query(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return v[id].a[0][0]+v[id].a[0][1];
        pushdown(id);
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y);
        if(x>mid) return Query(rs,mid+1,r,x,y);
        return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
    }
}
namespace seg2 {
    ll z[N<<2],lz[N<<2];
    void pushdown(int id) {
        if(!lz[id]) return;
        int val=lz[id]; lz[id]=0;
        z[ls]=val, lz[ls]=val;
        z[rs]=val, lz[rs]=val;
    }
    void Modify(int id,int l,int r,int x,int y,int val) {
        if(x<=l&&y>=r) return z[id]=lz[id]=val, void();
        pushdown(id);
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,y,val);
        if(y>mid) Modify(rs,mid+1,r,x,y,val);
        z[id]=max(z[ls],z[rs]);
    }
    int find(int id,int l,int r,int v) {
        if(l==r) return (z[id]<v)? l:-1;
        pushdown(id);
        int mid=(l+r)>>1;
        if(z[rs]>=v) return find(rs,mid+1,r,v);
        int res=find(ls,l,mid,v);
        return (~res)? res:mid+1;
    }
}
ll ans[N];
bool mem2;
int main() {
    freopen("seq.in","r",stdin);
    freopen("seq.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>Q;
    for(int i=1,x;i<=n;i++) {
        cin>>x;
        if(!pl[x]) pl[x]=i;
        pr[x]=i;
    }
    for(int i=1;i<=n;i++) 
        if(pl[i]) p[pr[i]]={pl[i],i};
    for(int i=1,l,r;i<=Q;i++) {
        cin>>l>>r;
        qr[r].emplace_back(l,i);
    }
    for(int i=0;i<3;i++) unit.a[i][i]=1;
    nxt.a[0][0]=nxt.a[0][1]=nxt.a[1][1]=nxt.a[2][2]=1;
    seg1::Build(1,1,n);
    for(int r=1;r<=n;r++) {
        if(p[r].first) {
            int g=p[r].second, l=p[r].first, pos=seg2::find(1,1,n,g);
            if((~pos)&&pos<=l) {
                Matrix c;
                c.a[0][0]=0, c.a[0][1]=0, c.a[0][2]=0;
                c.a[1][0]=0, c.a[1][1]=1, c.a[1][2]=0;
                c.a[2][0]=g, c.a[2][1]=0, c.a[2][2]=1;
                seg1::Modify(1,1,n,pos,l,c);
                seg2::Modify(1,1,n,pos,l,g);
            }
        }
        for(auto l:qr[r]) {
            ans[l.second]=seg1::Query(1,1,n,l.first,r);
        }
        seg1::Modify(1,1,n,1,n,nxt);
    }
    for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}