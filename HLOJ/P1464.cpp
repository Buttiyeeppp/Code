#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
using PLL=pair<ll,ll>;
const int N=3e5+10;
const ll INF=1e10;
bool mem1;
int n,t,x[N],a[N],que[N],L,R;
ll f[N];
int cnt;
struct list {
    int pre,nxt;
    ll v;
}li[N];
void dp(const int l,const int r) {
    L=R=1, que[L]=l-1, f[l-1]=0;
    for(int i=l;i<=r;i++) {
        while(L<=R&&x[i]-x[que[L]]>t) L++;
        if(L<=R) f[i]=max(-INF,f[que[L]]+a[i]);
        while(L<=R&&f[que[R]]<f[i]) R--;
        que[++R]=i;
    }
    ll res=-INF;
    for(int i=l;i<=r;i++)
        if(x[r+1]-x[i]<=t) res=max(res,f[i]);
    li[++cnt].v=res;
    if(cnt>1) li[cnt-1].nxt=cnt, li[cnt].pre=cnt-1;
}
ll ans[N];
int vis[N],p[N],na[N],nx[N];
bool mem2;
int main() {
    freopen("distanced.in","r",stdin);
    freopen("distanced.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>t;
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=n;i++) cin>>a[i], p[i]=i;
    sort(p+1,p+n+1,[](const int &c,const int &d) { return x[c]<x[d]; });
    for(int i=1;i<=n;i++) nx[i]=x[p[i]], na[i]=a[p[i]];
    for(int i=1;i<=n;i++) x[i]=nx[i], a[i]=na[i];
    memset(f,-0x3f,sizeof(f));
    ll res=0,tot=1,z=0;
    for(int i=1,lst=0;i<=n;i++) if(a[i]>=0) {
        if(lst&&x[i]-x[lst]>t) {
            li[++cnt].v=-z, z=0;
            if(cnt>1) li[cnt-1].nxt=cnt, li[cnt].pre=cnt-1;
            dp(lst+1,i-1), tot++;
        }
        lst=i, res+=a[i], z+=a[i];
    }
    if(z) {
        li[++cnt].v=-z, z=0;
        if(cnt>1) li[cnt-1].nxt=cnt, li[cnt].pre=cnt-1;
    }
    ans[tot]=res;
    priority_queue<PLL> q;
    for(int i=1;i<=cnt;i++) q.emplace(li[i].v,i);
    while(q.size()) {
        int x=q.top().second; q.pop();
        if(vis[x]) continue;
        if(tot==1) break;
        res+=li[x].v, ans[--tot]=res;
        int pre=li[li[x].pre].pre, nxt=li[li[x].nxt].nxt;
        vis[li[x].pre]=vis[li[x].nxt]=1;
        li[x].v=max(-INF,li[li[x].pre].v+li[li[x].nxt].v-li[x].v);
        li[x].pre=pre, li[pre].nxt=x;
        li[x].nxt=nxt, li[nxt].pre=x;
        q.emplace(li[x].v,x);
    }
    for(int i=1;i<=n;i++)
        ans[i]=max(ans[i],ans[i-1]), cout<<ans[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}