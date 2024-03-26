#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n,k;
string s[2];
multiset<int> st;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k>>s[0]>>s[1];
    s[0]=" "+s[0], s[1]=" "+s[1];
    ll ans=0, op=-1;
    for(int i=1;i<=n;i++) if(s[0][i]!=s[1][i]){
        int f=(s[1][i]=='1');
        if(st.empty()||op==f) {
            ans-=i/k, st.insert(i%k), op=f;
        }
        else {
            ans+=i/k;
            auto it=st.lower_bound(i%k);
            if(it!=st.end()) st.erase(it);
            else {
                st.erase(st.begin());
                ans++;
            }
        }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}