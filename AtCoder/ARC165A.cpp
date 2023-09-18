#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
void solve() {
    int n; cin>>n;
    int p=-1;
    for(int i=2;i*i<=n;i++) if(n%i==0) { p=i; break; }
    while(p!=-1&&n%p==0) n/=p;
    if(p==-1||n==1) cout<<"No"<<endl;
    else cout<<"Yes"<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}