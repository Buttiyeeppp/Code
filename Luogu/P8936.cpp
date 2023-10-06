#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
const ll Mod=(1ll<<32);
bool mem1;
int n,m;
struct Seg { int l,r,id; };
vector<Seg> op[N];
vector<int> pos[N];
#define ls (id<<1)
#define rs (id<<1|1)
int s[N<<2],lz[N<<2];
void Build(int id,int l,int r) {
    s[id]=lz[id]=0;
    if(l==r) return;
    int mid=(l+r)>>1;
    Build(ls,l,mid), Build(rs,mid+1,r);
}
void pushdown(int id) {
    if(!lz[id]) return;
    int v=lz[id]; lz[id]=0;
    s[ls]=max(s[ls],v), s[rs]=max(s[rs],v);
    lz[ls]=max(lz[ls],v), lz[rs]=max(lz[rs],v);
}
void Modify(int id,int l,int r,int x,int y,int v) {
    if(x<=l&&y>=r) return s[id]=max(s[id],v),  lz[id]=max(lz[id],v), void();
    int mid=(l+r)>>1;
    pushdown(id);
    if(x<=mid) Modify(ls,l,mid,x,y,v);
    if(y>mid) Modify(rs,mid+1,r,x,y,v);
    s[id]=min(s[ls],s[rs]);
}
void Query(int id,int l,int r) {
    if(l==r) return pos[s[id]].push_back(l), void();
    pushdown(id);
    int mid=(l+r)>>1;
    Query(ls,l,mid), Query(rs,mid+1,r);
}
int X[N];
ll f[N],ans[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    Build(1,1,n);
    for(int i=1,l,r,x;i<=m;i++) {
        cin>>l>>r>>x;
        op[x].push_back({l,r,i});
        Modify(1,1,n,l,r,x);
    }
    Query(1,1,n);
    for(int i=1;i<=m;i++) ans[i]=i;
    for(int v=1;v<=m;v++) {
        int tot=0;
        for(auto nd:pos[v]) X[++tot]=nd;
        if(!tot) continue;
        Build(1,1,tot);
        ans[op[v][0].id-1]=0;
        for(int i=0;i<(int)op[v].size();i++) {
            Seg opt=op[v][i];
            opt.l=lower_bound(X+1,X+tot+1,opt.l)-X;
            opt.r=upper_bound(X+1,X+tot+1,opt.r)-X-1;
            if(opt.l>=1&&opt.l<=tot&&opt.r>=1&&opt.r<=tot)
                Modify(1,1,tot,opt.l,opt.r,opt.id);
            int p=(i+1<(int)op[v].size())? op[v][i+1].id-1:m;
            ans[p]=min(ans[p],(ll)s[1]);
        }
    }
    for(int i=m-1;i>=1;i--) ans[i]=min(ans[i],ans[i+1]);
    // for(int i=1;i<=m;i++) cerr<<ans[i]<<" ";
    // cerr<<endl;
    ll res1=0,res2=0,res3=0;
    for(int i=1;i<=m;i++) res1=(res1+ans[i])%Mod;
    for(int i=1;i<=m;i++) f[ans[i]]++;
    for(int i=m;i>=1;i--)
        f[i]=(f[i+1]+f[i])%Mod, res2^=f[i]*i%Mod, res3=(res3+f[i]*i)%Mod;
    cout<<res1<<" "<<res2<<" "<<res3<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}