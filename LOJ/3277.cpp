#include <bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,l[N],r[N];
vector<int> h[N];
vector<PII> star[N];
ll s[N];
int lowbit(int x) { return x&-x; }
void add(int x,ll v) {
    for(int i=x;i<=n;i+=lowbit(i)) s[i]+=v;
}
ll query(int x) {
    ll res=0;
    for(int i=x;i;i-=lowbit(i)) res+=s[i];
    return res;
}
int find(int x,int *fa) {
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x],fa);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1,x;i<=n;i++) {
        cin>>x;
        h[x].push_back(i);
    }
    for(int i=0;i<=n+1;i++) l[i]=r[i]=i;
    cin>>m;
    for(int i=1,x,y,c;i<=m;i++) {
        cin>>x>>y>>c;
        star[y].emplace_back(x,c);
    }
    ll ans=0;
    for(int i=1;i<=n;i++) {
        for(auto now:star[i]) {
            ll v=query(now.first);
            if(now.second<=v) ans+=now.second;
            else ans+=v, add(find(now.first,l)+1,now.second-v), add(find(now.first,r),v-now.second);
        }
        for(auto now:h[i]) l[now]=find(now-1,l), r[now]=find(now+1,r);
    }
    cout<<ans<<endl;

    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}