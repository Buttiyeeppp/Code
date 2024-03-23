#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define int long long
using ll=long long;
using PII=pair<int,int>;
const int N=6e6+10;
const ll Mod=998244353;
bool mem1;
int n,c,a[N],z[N],vis[N],po[N];
vector<int> nd[N];
void solve() {
    cin>>n>>c;
    for(int i=1;i<=(n<<1);i+=2) a[i]=-1;
    for(int i=2;i<=(n<<1);i+=2) cin>>a[i];
    int p=0;
    for(int i=1;i<=n;i++) nd[i].clear(), vis[i]=0, po[i]=i;
    for(int i=1;i<=(n<<1);i++) {
        z[i]=0;
        if(p&&p+z[p]-1>=i) z[i]=min(p+z[p]-i,z[2*p-i]);
        while(i-z[i]>=1&&i+z[i]<=(n<<1)&&a[i-z[i]]==a[i+z[i]]) {
            if((i+z[i])%2==0) po[(i+z[i])>>1]=po[(i-z[i])>>1];
            z[i]++;
        }
        if(i+z[i]<=(n<<1)&&i-z[i]>=1) nd[(i+z[i])>>1].push_back((i-z[i])>>1);
        if(i+z[i]>p+z[p]) p=i;
    }
    ll ans=1;
    for(int i=1;i<=n;i++) if(i==po[i]) {
        int cnt=c;
        for(auto j:nd[i]) if(vis[po[j]]!=i) {
            vis[po[j]]=i, cnt--;
        }
        ans=ans*cnt%Mod;
    }
    cout<<ans<<endl;
}
bool mem2;
signed main() {
    freopen("palindrome.in","r",stdin);
    freopen("palindrome.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}