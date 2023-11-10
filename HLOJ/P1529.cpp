#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,m,st[N],ed[N],f[N];
struct node {
    int a,b,c,d;
}nd[N];
namespace Segt {
    int v[N<<2];
    #define ls (id<<1)
    #define rs (id<<1|1)
    void Build(int id,int l,int r) {
        v[id]=0x3f3f3f3f;
        if(l==r) return;
        int mid=(l+r)>>1;
        Build(ls,l,mid), Build(rs,mid+1,r);
    }
    void Modify(int id,int l,int r,int x,int val) {
        if(l==r) return v[id]=val, void();
        int mid=(l+r)>>1;
        if(x<=mid) Modify(ls,l,mid,x,val);
        else Modify(rs,mid+1,r,x,val);
        v[id]=min(v[ls],v[rs]);
    }
    int Query(int id,int l,int r,int x,int y) {
        if(x<=l&&y>=r) return v[id];
        int mid=(l+r)>>1;
        if(y<=mid) return Query(ls,l,mid,x,y);
        if(x>mid) return  Query(rs,mid+1,r,x,y);
        return min(Query(ls,l,mid,x,y),Query(rs,mid+1,r,x,y));
    }
}
using namespace Segt;
int sta[N],top;
bool mem2;
int main() {
    freopen("tp.in","r",stdin);
    freopen("tp.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    vector<int> di;
    for(int i=1;i<=m;i++) cin>>nd[i].a>>nd[i].b>>nd[i].c>>nd[i].d, di.push_back(i);
    sort(nd+1,nd+m+1,[](const node &x,const node &y) 
        { return (x.a==y.a)? x.c<y.c:x.a<y.a; });
    sort(di.begin(),di.end(),[](const int &x,const int &y) 
        { return nd[x].c>nd[y].c; });
    for(int i=m;i>=1;i--) st[nd[i].a]=i;
    for(int i=1;i<=m;i++) ed[nd[i].a]=i;
    memset(f,0x3f,sizeof(f));
    Build(1,1,m);
    for(int i:di) {
        if(nd[i].b==n) f[i]=nd[i].d;
        if(st[nd[i].b]) {
            int l=st[nd[i].b]-1, r=ed[nd[i].b]+1;
            while(l+1<r) {
                int mid=(l+r)>>1;
                if(nd[mid].c>=nd[i].d) r=mid;
                else l=mid;
            }
            if(r<=ed[nd[i].b])
                f[i]=min(f[i],Query(1,1,m,r,ed[nd[i].b]));
        }
        Modify(1,1,m,i,f[i]);
    }
    vector<int> vc;
    for(int i=1;i<=m;i++) if(nd[i].a==1) vc.push_back(i);
    sort(vc.begin(),vc.end(),[](const int &x,const int &y) 
        { return (nd[x].c!=nd[y].c)? nd[x].c<nd[y].c:f[x]>f[y]; });
    for(int i:vc) if(f[i]!=0x3f3f3f3f) {
        while(top&&f[i]<=f[sta[top]]) top--;
        sta[++top]=i;
    }
    int q,t; cin>>q;
    while(q--) {
        cin>>t;
        int l=0,r=top+1;
        while(l+1<r) {
            int mid=(l+r)>>1;
            if(f[sta[mid]]<=t) l=mid;
            else r=mid;
        }
    	cout<<((!l)? -1:nd[sta[l]].c)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
