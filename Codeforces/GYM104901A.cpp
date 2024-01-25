#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
string s;
int n,a[N],f[N],rt[N];
PII sta[N];
vector<int> eg[N];
void solve() {
    cin>>s;
    n=s.size(), s=" "+s;
    for(int i=1;i<=n;i++) a[i]=(s[i]=='['||s[i]==']');
    for(int i=0;i<=n;i++) eg[i].clear(), rt[i]=1;
    int tot=0,top=0;
    for(int i=1;i<=n;i++) {
        if(top&&sta[top].first==a[i]) {
            int fa=sta[top-1].second;
            if(fa) {
                eg[fa].push_back(sta[top].second);
                rt[sta[top].second]=0;
            }
            top--;
        }
        else {
            sta[++top]={a[i],++tot};
            f[tot]=a[i];
        }
    }
    vector<int> nd;
    for(int i=1;i<=tot;i++) {
        if(eg[i].size()) {
            if(eg[i].size()>1) return cout<<"No"<<endl, void();
            if(f[i]==f[eg[i][0]]) return cout<<"No"<<endl, void();
        }
        if(rt[i]) nd.push_back(i);
    }
    if(nd.size()>2) return cout<<"No"<<endl, void();
    if(nd.size()==2&&f[nd[0]]==f[nd[1]]) return cout<<"No"<<endl, void();
    cout<<"Yes"<<endl;
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
/*
1
[(([[[
*/