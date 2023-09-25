#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n,s,e;
void solve() {
    cin>>n;
    cin>>s>>e;
    int mx=-1;
    for(int i=2,x,y;i<=n;i++) {
        cin>>x>>y;
        if(x>=s) mx=max(mx,y);
    }
    if(mx>=e) cout<<-1<<endl;
    else cout<<s<<endl;
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