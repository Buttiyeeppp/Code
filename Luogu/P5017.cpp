#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
const int M=5e6+10;
bool mem1;
int n,m,t[N],p[M];
ll s[N],f[M];
ll X(int i) { return p[i]; }
ll Y(int i) { return f[i]+s[p[i]]; }
ll B(int i,ll k) { return Y(i)-k*X(i); }
int l=1,r,q[M];
double slope(int i,int j) { return 1.*(Y(i)-Y(j))/(X(i)-X(j)); }
void ins(int i) {
    while(l+1<=r&&1.*slope(q[r],q[r-1])>=slope(i,q[r-1])) r--;
    while(l<=r&&X(q[r])==X(i)&&Y(q[r])>Y(i)) r--;
    if(l<=r&&X(q[r])==X(i)&&Y(q[r])<=Y(i)) return;
    q[++r]=i;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    int mx=0;
    for(int i=1;i<=n;i++) cin>>t[i];
    sort(t+1,t+n+1);
    for(int i=1;i<=n;i++) mx=max(mx,t[i]), s[i]=s[i-1]+t[i];
    for(int i=0;i<=mx+m+1;i++) {
        if(i) p[i]=p[i-1];
        while(p[i]+1<=n&&t[p[i]+1]<=i) p[i]++;
    }
    for(int i=0;i<=mx+m+1;i++) if(p[i]) {
        f[i]=i*p[i]-s[p[i]];
        if(i-m>=0) ins(i-m);
        while(l<r&&slope(q[l],q[l+1])<=i) l++;
        if(l<=r) f[i]=min(f[i],B(q[l],i)+i*p[i]-s[p[i]]);
    }
    ll ans=1e18;
    for(int i=mx;i<=mx+m+1;i++) ans=min(ans,f[i]);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}