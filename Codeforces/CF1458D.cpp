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
int d[N];
void solve() {
    string s; cin>>s;
    int n=s.size();
    // for(int i=0;i<=2*n;i++) d[i]=0;
    for(int i=0,cur=0;i<n;i++) {
        if(s[i]=='1') d[n+(cur++)]++;
        else d[n+(--cur)]++;
    }
    for(int i=0,cur=0;i<n;i++) {
        if(!d[n+cur]||d[n+cur-1]>1) cout<<0, d[n+(--cur)]--;
        else cout<<1, d[n+(cur++)]--;
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