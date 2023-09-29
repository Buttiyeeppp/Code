#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n;
string s;
void solve() {
    cin>>n>>s;
    ll ans=0,val=0;
    vector<int> v;
    stack<int> q;
    for(int i=0;i<n;i++) {
        if(s[i]=='(') q.push(i), val++;
        else {
            if(q.size()) {
                ans-=1ll*(q.top()+1)*(n-i);
                q.pop();
            }
            val--;
        }
        v.push_back(val);
    }
    ll res=0,sum=0;
    v.push_back(0);
    sort(v.begin(),v.end());
    for(int i=0;i<(int)v.size();i++) res+=v[i]*i-sum, sum+=v[i];
    for(int i=1;i<=n;i++) res+=1ll*i*(n-i+1);
    ans+=res/2;
    cout<<ans<<endl;
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