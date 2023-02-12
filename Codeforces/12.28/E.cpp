#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e6+10;
ll n,m,a[N];
void solve() {
    cin>>n>>m;
    for(int i=n;i>=1;i--) {
        a[i]=(n/i)*(n/i-1)/2;
        for(int j=i*2;j<=n;j+=i) a[i]-=a[j];
    }
    ll ans=m;
    for(int i=n-1;i>=1;i--) {
        ll res=min(a[i+1]/i,m/i);
        m-=res*i, ans+=res;
    }
    if(m) ans=-1;
    cout<<ans<<endl;
}
int main() {
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
