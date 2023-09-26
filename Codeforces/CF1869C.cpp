#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
vector<int> nd[N];
void solve() {
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=m;i++) nd[i].clear();
    if(m==1) {
        cout<<0<<endl;
        for(int i=1;i<=n;i++) cout<<0<<endl;
        return;
    }
    int res=min(n+1,m);
    for(int i=2;i<=res;i++) {
        for(int j=i-2;j>=0;j--) nd[i].push_back(j);
    }
    for(int i=1,v=res-1;i<=res;i++,v--) {
        if(i-1!=v) {
            for(int j=1;j<=n-i+1;j++) nd[i].push_back(v);
        }
        else {
            for(int j=1;j<=n-i+1;j++) nd[i-1].pop_back();
            for(int j=1;j<=n-i+1;j++) nd[i-1].push_back(v);
            for(int j=1;j<=n-i+1;j++) nd[i].push_back(v+1);
        }
    }
    for(int j=res+1;j<=m;j++)
        for(int i=1;i<=n;i++) nd[j].push_back(j-1);
    cout<<res<<endl;
    for(int i=0;i<n;i++) {
        for(int j=1;j<=m;j++) cout<<nd[j][i]<<" ";
        cout<<endl;
    }
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