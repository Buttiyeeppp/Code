#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
ll n,rs[N],ls[N];
vector<int> l,r;
void Rpush(int x) {
    r.push_back(x);
    rs[r.size()]=rs[r.size()-1]+x;
}
void Rpop() { r.pop_back(); }
void Lpush(int x) {
    l.push_back(x);
    ls[l.size()]=ls[l.size()-1]+x;
}
ll L(int x) {
    return ls[l.size()]-ls[l.size()-x];
}
ll R(int x) {
    return rs[r.size()]-rs[r.size()-x];
}
int sub[N],pre[N];
string st;
void solve() {
    cin>>n>>st;
    st=" "+st;
    l.clear(), r.clear();
    for(int i=n;i>1;i--) if(st[i]=='<') Rpush(i);
    for(int i=1;i<=n;i++) pre[i]=pre[i-1]+(st[i]=='>');
    sub[n+1]=0;
    for(int i=n;i>=1;i--) sub[i]=sub[i+1]+(st[i]=='<');
    for(int i=1;i<=n;i++) {
        if((st[i]=='<'&&pre[i-1]<=sub[i+1])||(st[i]=='>'&&pre[i-1]<=sub[i+1]-1)) {
            int lv=pre[i-1], rv=lv;
            if(st[i]=='>') rv++;
            cout<<((st[i]=='<')? 1:-1)*i+(-L(lv)+R(rv))*2<<" ";
        }
        else {
            int rv=sub[i+1], lv=rv;
            if(st[i]=='<') lv++;
            cout<<n+1+((st[i]=='<')? 1:-1)*i+(-L(lv)+R(rv))*2<<" ";
        }
        if(st[i]=='>') Lpush(i);
        if(i<n&&st[i+1]=='<') Rpop();
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