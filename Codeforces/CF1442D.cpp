#include <bits/stdc++.h>
#include <functional>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=3e3+10;
bool mem1;
int n,k,sz[N];
vector<ll> a[N],s[N],g[N<<2];
ll f[N<<2][N];
void Modify(int id,int l,int r,int x,int y,int v) {
    if(x>y) return; 
    if(x<=l&&y>=r) return g[id].push_back(v), void();
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,y,v);
    if(y>mid) Modify(rs,mid+1,r,x,y,v);
}
ll ans;
void calc(int id,int l,int r) {
    for(auto i:g[id]) {
        for(int j=k;j>=sz[i];j--) f[id][j]=max(f[id][j],f[id][j-sz[i]]+s[i][sz[i]]);
    }
    if(l==r) {
        for(int i=0;i<=min(sz[l],k);i++) ans=max(ans,s[l][i]+f[id][k-i]);
        return;
    }
    int mid=(l+r)>>1;
    memcpy(f[ls],f[id],sizeof(f[id])), memcpy(f[rs],f[id],sizeof(f[id]));
    calc(ls,l,mid), calc(rs,mid+1,r);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++) {
        cin>>sz[i];
        a[i].resize(sz[i]+1), s[i].resize(sz[i]+1);
        for(int j=1;j<=sz[i];j++) cin>>a[i][j], s[i][j]=s[i][j-1]+a[i][j];
        Modify(1,1,n,1,i-1,i), Modify(1,1,n,i+1,n,i);
    }
    calc(1,1,n);
    cout<<ans<<endl;

    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}