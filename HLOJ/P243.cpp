#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,k,cnt_eg,cnt_nd,mn,mx,vis[N];
vector<int> g[N],seg[N];
void dfs(int x) {
    cnt_nd++, cnt_eg-=(mn!=x),  vis[x]=1;
    mx=max(mx,x), mn=min(mn,x);
    for(auto y:g[x]) {
        cnt_eg++;
        if(!vis[y]) dfs(y);
    }
}
struct query {
    int l,r,id;
}qr[N];
int ans[N],s[N];
int lowbit(int x) { return x&-x; }
void Add(int x,int v) {
    for(int i=x;i<=n;i+=lowbit(i)) s[i]+=v;
}
int Qry(int x) {
    int res=0;
    for(int i=x;i;i-=lowbit(i)) res+=s[i];
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1,a,b;i<=k;i++) {
        cin>>a>>b;
        g[a].push_back(b), g[b].push_back(a);
    }
    for(int i=1;i<=n;i++) if(!vis[i]) {
        cnt_eg=cnt_nd=0, mn=mx=i, dfs(i);
        if(cnt_eg+1==cnt_nd) seg[mn].push_back(mx);
    }
    int Q; cin>>Q;
    for(int i=1;i<=Q;i++) cin>>qr[i].l>>qr[i].r, qr[i].id=i;
    sort(qr+1,qr+Q+1,[](const query &x,const query &y) { return x.l<y.l; });
    for(int i=Q,p=n;i>=1;i--) {
        while(p>=qr[i].l) {
            for(auto now:seg[p]) Add(now,1);
            p--;
        }
        ans[qr[i].id]=Qry(qr[i].r);
    }
    for(int i=1;i<=Q;i++) cout<<(ans[i]? "No":"Yes")<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}