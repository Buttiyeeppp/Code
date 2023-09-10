#include <bits/stdc++.h>
#include <ctime>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
ll n,x,y,p[N],t[N],ans[N];
void cal(ll tim) {
    ll res=tim;
    for(int i=1;i<n;i++) {
        if(res%p[i]!=0) res+=p[i]-(res%p[i]);
        res+=t[i];
    }
    ans[tim]=res+y;
}
int gcd(int x,int y) {
    if(!x) return y;
    return gcd(y%x,x);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>x>>y;
    int g=1;
    for(int i=1;i<n;i++) cin>>p[i]>>t[i], g=g*p[i]/gcd(g,p[i]);
    for(int tim=1;tim<=g;tim++) cal(tim);
    int Q; cin>>Q;
    for(int i=1,q;i<=Q;i++) {
        cin>>q; q+=x;
        ll now=q%g;
        if(!now) now=g;
        cout<<ans[now]+q-now<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}