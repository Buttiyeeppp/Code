#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e5+10;
const ll INF=1e17;
bool mem1;
int n,a[N],X[N],tot;
struct node {
    ll s[2][2];
    node() { memset(s,0x3f,sizeof(s)); }
    friend node operator+(const node &x,const node &y) {
        node res;
        for(int i=0;i<=1;i++)
            for(int j=0;j<=1;j++) 
                res.s[i][j]=min(max(x.s[i][0],y.s[0][j]),max(x.s[i][1],y.s[1][j]));
        return res;
    }
}nd[N<<2];
struct mem {
    int x,a,b;
};
vector<mem> pos[N];
int find(int x) {
    return lower_bound(X+1,X+tot+1,x)-X;
}
#define ls (id<<1)
#define rs (id<<1|1)
void Build(int id,int l,int r) {
    if(l==r) {
        nd[id].s[0][0]=a[l], pos[find(a[l])].push_back({l,0,0});
        if(l>1) nd[id].s[1][0]=a[l]+a[l-1], pos[find(a[l]+a[l-1])].push_back({l,1,0});
        if(l<n) nd[id].s[0][1]=a[l]+a[l+1], pos[find(a[l]+a[l+1])].push_back({l,0,1});
        return;
    }
    int mid=(l+r)>>1;
    Build(ls,l,mid), Build(rs,mid+1,r);
    nd[id]=nd[ls]+nd[rs];
}
void Modify(int id,int l,int r,int x,int a,int b) {
    if(l==r) return nd[id].s[a][b]=INF, void();
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,a,b);
    else Modify(rs,mid+1,r,x,a,b);
    nd[id]=nd[ls]+nd[rs];
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        X[++tot]=a[i];
        if(i>1) X[++tot]=a[i]+a[i-1];
    }
    cerr<<tot<<endl;
    sort(X+1,X+tot+1);
    tot=unique(X+1,X+tot+1)-X-1;
    Build(1,1,n);
    ll ans=INF;
    for(int i=1;i<=tot;i++) {
        ans=min(ans,nd[1].s[0][0]-X[i]);
        for(auto now:pos[i]) Modify(1,1,n,now.x,now.a,now.b);
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}