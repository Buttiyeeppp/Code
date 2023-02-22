#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=998244353;
const int N=2e5+10;
int n,m,a[N],np[N];
vector<int> P;
void Get_Prime() {
    // int ok=0;
    for(int i=2;i<N;i++) {
        if(!np[i]) P.emplace_back(i);
        // if(!np[i]&&i>=100000&&!ok) cout<<"1e5: "<<P.size(), ok=1;
        for(auto now:P) {
            if(1ll*now*i>=N) break;
            np[now*i]=1;
            if(i%now==0) break;
        }
    }
    return;
}
vector<int> d;
void solve() {
    scanf("%d%d",&n,&m);
    ll ans=1;
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        if(i==1||!ans) continue;
        if(a[i-1]%a[i]) { ans=0; continue; }
        int v=a[i-1]/a[i];
        d.clear();
        for(auto now:P) {
            if(v%now==0) {
                while(v%now==0) v/=now;
                d.emplace_back(now);
                if(now*now>a[i-1]/a[i]) break;
            }
            if(v==1) break;
        }
        if(v!=1) d.emplace_back(v);
        ll z=0;
        for(int s=0;s<(1<<d.size());s++) {
            int c=1, f=1;
            for(int j=0;j<(int)d.size();j++) if((1<<j)&s) c*=d[j], f*=-1;
            z=(z+f*(m/a[i]/c)%Mod+Mod)%Mod;
        }
        ans=ans*z%Mod;
    }
    printf("%lld\n",ans);
    return;
}
int main() {
    Get_Prime();
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}