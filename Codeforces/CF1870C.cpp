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
int n,k,a[N];
vector<int> pos[N];
set<int> s;
void solve() {
    cin>>n>>k;
    s.clear();
    for(int i=1;i<=k;i++) pos[i].clear();
    for(int i=1;i<=n;i++) cin>>a[i], s.insert(i), pos[a[i]].push_back(i);
    for(int v=1;v<=k;v++)  {
        if(pos[v].size()) {
            cout<<2ll*((*(--s.end()))-(*s.begin())+1)<<" ";
            for(auto now:pos[v]) s.erase(now);
        }
        else cout<<0<<" ";
    }
    cout<<endl;
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