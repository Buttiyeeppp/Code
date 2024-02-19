#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
ll n,K,s,sum[N];
int a[N],pre[N];
pair<ll,ll> f[N];
bool check(int k) {
    for(int i=1;i<=n;i++) {
        f[i]=f[i-1];
        if(pre[i]>=0) f[i]=min(f[i],{f[pre[i]].first+i-pre[i]-1-k,f[pre[i]].second+1});
    }
    return (f[n].first+f[n].second*k<=n-K);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>K>>s;
    for(int i=1;i<=n;i++) cin>>a[i], sum[i]=sum[i-1]+a[i];
    for(int i=1,p=0;i<=n;i++) {
        while(sum[i]-sum[p]>=s) p++;
        pre[i]=p-1;
    }
    int l=0, r=n;
    while(l+1<r) {
        int mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    check(l);
    int x=min(f[n].second,K), y=f[n].first+f[n].second*l;
    while(y+l<=n-K&&x<K) x++, y+=l;
    cout<<x<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}