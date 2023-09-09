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
ll n,x[N],l[N],a[N],tot,dis[N];
bool check(ll d) {
    for(int i=1;i<=n;i++) dis[i]=abs(d-x[i]);
    sort(dis+1,dis+n+1);
    for(int i=1;i<=n;i++) if(l[i]<dis[i]) return false;
    return true;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>x[i];
    for(int i=1;i<=n;i++) cin>>l[i];
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++) {
            a[++tot]=x[i]+l[j], a[++tot]=x[i]-l[j];
        }
    sort(a+1,a+tot+1);
    tot=unique(a+1,a+tot+1)-a-1;
    ll ans=0;
    for(int i=1;i<=tot;i++) ans+=check(a[i]);
    for(int i=1;i<tot;i++) {
        if(check(a[i]+1)) ans+=a[i+1]-1-a[i];
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}