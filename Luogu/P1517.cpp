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
int n,m,g,h,L,R;
struct node {
    int t,a,b,c,d;
}nd[N];
const int M=N*420;
const ll INF=1e17;
ll v[M],dp[N];
int ls[M],rs[M],cnt,tot,X[N<<1],rt[N<<1],Y[N],toty;
void Modify(int &id,int l,int r,int x,ll val) {
    if(!id) id=++cnt, v[id]=-INF, ls[id]=rs[id]=0;
    if(l==r) return v[id]=val, void();
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls[id],l,mid,x,val);
    else Modify(rs[id],mid+1,r,x,val);
    v[id]=max(v[ls[id]],v[rs[id]]);
}
ll Query(int id,int l,int r,int x,int y) {
    if(x<=l&&y>=r) return v[id];
    int mid=(l+r)>>1;
    if(y<=mid) return Query(ls[id],l,mid,x,y);
    if(x>mid) return Query(rs[id],mid+1,r,x,y);
    return max(Query(ls[id],l,mid,x,y),Query(rs[id],mid+1,r,x,y));
}
int lowbit(int x) { return x&-x; }
int p[2][N];
void modify(int x,int f) {
    int a=lower_bound(Y+1,Y+toty+1,nd[x].a)-Y;
    for(int i=nd[x].c;i<=tot;i+=lowbit(i))
        Modify(rt[i],1,toty,p[f][a],(f? dp[x]:-INF));
    p[f][a]++;
}
ll query(int x) {
    int al=nd[x].a-h, ar=nd[x].a+h;
    al=lower_bound(Y+1,Y+toty+1,al)-Y, ar=upper_bound(Y+1,Y+toty+1,ar)-Y-1;
    ll res=-INF;
    if(al>ar) return res;
    for(int i=nd[x].b;i;i-=lowbit(i)) 
        res=max(res,Query(rt[i],1,toty,al,ar));
    return res;
}
void solve() {
    cin>>n>>m>>g>>h>>L>>R;
    for(int i=1;i<=n;i++)
        cin>>nd[i].t>>nd[i].a>>nd[i].b>>nd[i].c>>nd[i].d,
        X[++tot]=nd[i].b, X[++tot]=nd[i].c, Y[++toty]=nd[i].a;
    sort(X+1,X+tot+1); tot=unique(X+1,X+tot+1)-X-1;
    sort(Y+1,Y+toty+1);
    for(int i=1;i<=toty;i++) p[0][i]=p[1][i]=i;
    for(int i=1;i<=n;i++) 
        nd[i].b=lower_bound(X+1,X+tot+1,nd[i].b)-X,
        nd[i].c=lower_bound(X+1,X+tot+1,nd[i].c)-X;
    int l=1,r=0;
    for(int i=1;i<=n;i++) {
        dp[i]=-INF;
        int tl=nd[i].t-R, tr=nd[i].t-L;
        if(g<=X[nd[i].b]&&tl<=0) dp[i]=nd[i].d;
        while(r+1<i&&nd[r+1].t<=tr) modify(++r,1);
        while(l<=r&&!(tl<=nd[l].t)) modify(l++,0);
        dp[i]=max(dp[i],query(i)+nd[i].d);
    }
    ll ans=-INF;
    for(int i=1;i<=n;i++) if(m-nd[i].t<R) ans=max(ans,dp[i]);
    if(ans>=-1e14) cout<<ans<<endl;
    else cout<<"Retire"<<endl;

    for(int i=1;i<=tot;i++) rt[i]=0;
    tot=toty=cnt=0;
}
bool mem2;
int main() {
    freopen("contest.in","r",stdin);
    freopen("contest.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    v[0]=-INF;
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}