#include <bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,a[N],Q,pre[N<<1];
ll ans[N];
struct query {
    int id,l;
};
vector<query> q[N];
ll s[N<<2],mx[N<<2],lz[N<<2],mxlz[N<<2];
void pushdown(int id) {
    mx[ls]=max(mx[ls],s[ls]+mxlz[id]);
    mxlz[ls]=max(mxlz[ls],lz[ls]+mxlz[id]);
    lz[ls]+=lz[id], s[ls]+=lz[id];

    mx[rs]=max(mx[rs],s[rs]+mxlz[id]);
    mxlz[rs]=max(mxlz[rs],lz[rs]+mxlz[id]);
    lz[rs]+=lz[id], s[rs]+=lz[id];  

    lz[id]=mxlz[id]=0;  
}
void Modify(int id,int l,int r,int x,int y,ll v) {
    if(x<=l&&y>=r) {
        s[id]+=v, lz[id]+=v;
        mx[id]=max(mx[id],s[id]);
        mxlz[id]=max(mxlz[id],lz[id]);
        return;
    }
    pushdown(id);
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,y,v);
    if(y>mid) Modify(rs,mid+1,r,x,y,v);
    mx[id]=max(mx[ls],mx[rs]);
    s[id]=max(s[ls],s[rs]);
}
ll Query(int id,int l,int r,int x,int y) {
    if(x<=l&&y>=r) return mx[id];
    int mid=(l+r)>>1; ll res=0;
    pushdown(id);
    if(x<=mid) res=max(res,Query(ls,l,mid,x,y));
    if(y>mid) res=max(res,Query(rs,mid+1,r,x,y));
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cin>>Q;
    for(int i=1,x,y;i<=Q;i++) cin>>x>>y, q[y].push_back(query{i,x});
    for(int i=1;i<=n;i++) {
        Modify(1,1,n,pre[a[i]+N]+1,i,a[i]);
        pre[a[i]+N]=i;
        for(auto now:q[i]) ans[now.id]=Query(1,1,n,now.l,i);
    }
    for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;

    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}