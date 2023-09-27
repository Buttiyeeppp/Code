#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int k,n;
void solve() {
    cin>>k>>n;
    vector<int> v;
    while(k) v.push_back(k%10), k/=10;
    sort(v.begin(),v.end());
    int cnt=1;
    for(int i=1;i<(int)v.size();i++) if(v[i]!=v[i-1]) cnt++;
    if(!n||cnt==1) return cout<<1<<endl, void();
    if(cnt==2) {
        if(n==1) return cout<<7<<endl, void();
        else return cout<<8<<endl, void();
    }
    // cnt==3
    if(n==1) return cout<<24<<endl, void();
    return cout<<27<<endl, void();
}
bool mem2;
int main() {
    // freopen("device2.in","r",stdin);
    // freopen("device.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}