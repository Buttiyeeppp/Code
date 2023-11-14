#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=1e6+10;
bool mem1;
ll n,m,k,a[N],s,cnt[M];
bool mem2;
int main() {
    freopen("biscuit.in","r",stdin);
    freopen("biscuit.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>k;
    for(int i=1;i<=n;i++) cin>>a[i], s+=a[i];
    sort(a+1,a+n+1);
    ll p,sum,ans=0;
    for(p=1,sum=0;p<=n&&sum<s-m;sum+=a[p],p++); 
    p--, sum=0;
    for(int i=1;i<=p;i++) {
        ll l=max(a[i]-(s-m-sum)+1,1ll), r=a[i];
        ans+=(l+r)*(r-l+1)/2, sum+=a[i];
        cnt[r]++, cnt[l-1]--;
    }
    for(int i=M-5;i>=1&&k;i--) {
        cnt[i]+=cnt[i+1];
        ll v=min(k,cnt[i]);
        ans-=v*i, k-=v;
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}