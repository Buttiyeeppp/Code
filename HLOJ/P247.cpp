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
ll n,a[N],s[N];
bool mem2;
int main() {
//     freopen("figure2.in","r",stdin);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1);
    for(int i=1;i<=n;i++) s[i]=s[i-1]+a[i];
    ll ans=0;
    for(int i=1;i<=n;i++) if(s[i]<a[i]*i) {
        int l=i-1, r=n+1;
        while(l+1<r) {
            int mid=(l+r)>>1;
            if(s[mid]<a[i]*mid) l=mid;
            else r=mid;
        }
        ans=max(ans,(ll)l-i+1);
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
