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
ll n,c,d,a[N],b[N],v[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>c>>d;
    ll res=0;
    for(ll i=1,a,b;i<=n;i++) cin>>a>>b, v[i]=i*(c-d)+b-a, res+=a;
    sort(v+1,v+n+1,[](const ll &x,const ll &y) { return x>y; });
    ll ans=res;
    for(int i=1;i<=n;i++) {
        res+=v[i]-c+n*d;
        ans=max(ans,res);
        res+=i*(-c-d);
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}