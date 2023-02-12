#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define ls (id<<1)
#define rs (id<<1|1)
const int N=5e5+10;
const ll INF=1e15;
int n,q;
ll a[4][N],s[4][N],w[N],c[N<<2];
struct op {
    int l,r; ll k;
    bool operator<(const op &q)const {
        return r<q.r;
    }
};
vector<vector<op>> g;
void insert(int id,int l,int r,int x,int y,ll val) {
    if(x>r||y<l) return;
    if(x<=l&&y>=r) {
        c[id]=min(c[id],val);
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid&&mid<y) g[id].emplace_back((op){x,y,val});
    insert(ls,l,mid,x,y,val), insert(rs,mid+1,r,x,y,val);
}
ll mxS[N],mxW[N],mx[N];
void solve(int id,int l,int r) {
    int mid=(l+r)>>1;
    if (l!=r) solve(ls,l,mid);
    ll mxs=-INF,mxw=w[l-1]-c[id];
    for(int i=l;i<=r;i++) {
        mxs=max(mxs,s[1][i]-s[2][i-1]-c[id]);
        mxw=max(mxw,w[i]-c[id]);
        w[i]=max({w[i],mxs,mxw});
    }
    mxS[mid]=s[1][mid]-s[2][mid-1], mxW[mid]=w[mid];
    for(int i=mid-1;i>=l-1;i--) {
        if(i>=l) mxS[i]=max(mxS[i+1],s[1][i]-s[2][i-1]);
        mxW[i]=max(mxW[i+1],w[i]);
    }
    for(int i=mid+1;i<=r+1;i++) mx[i]=-INF;
    for(auto now:g[id]) {
        mx[min(r,now.r)]=max({mx[min(r,now.r)],mxS[max(l,now.l)]-now.k,mxW[max(l,now.l)-1]-now.k});
    }
    for(int i=r;i>mid;i--) mx[i]=max(mx[i],mx[i+1]), w[i]=max(w[i],mx[i]);
    if (l!=r) solve(rs,mid+1,r);
}
int main() {
    scanf("%d%d",&n,&q);
    g.resize(4*n+2);
    for(int i=1;i<=3;i++)
        for(int j=1;j<=n;j++) scanf("%lld",&a[i][j]), s[i][j]=s[i][j-1]+a[i][j];
    for(int i=1;i<=n*4+1;i++) c[i]=INF;
    for(int i=1,l,r,k;i<=q;i++) {
        scanf("%d%d%d",&l,&r,&k);
        insert(1,1,n,l,r,k);
    }
    for(int i=0;i<=n+1;i++) w[i]=-INF;
    solve(1,1,n);
    ll ans=-INF;
    // for(int i=1;i<=n;i++) cerr<<"check "<<i<<" "<<w[i]<<endl;
    for(int i=1;i<=n;i++) ans=max(ans,w[i]+s[2][i]+s[3][n]-s[3][i-1]);
    printf("%lld\n",ans);
    return 0;
}