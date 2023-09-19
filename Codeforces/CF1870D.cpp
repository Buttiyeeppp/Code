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
int n,c[N],k,st[N],top,s[N];
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>c[i], s[i]=0;
    cin>>k;
    top=0;
    for(int i=1;i<=n;i++) {
        while(top&&c[st[top]]>=c[i]) top--;
        st[++top]=i;
    }
    for(int i=1;i<=top;i++) {
        if(i!=1) s[st[i]]=min(k/(c[st[i]]-c[st[i-1]]),s[st[i-1]]);
        else s[st[i]]=k/(c[st[i]]-c[st[i-1]]);
        k-=(c[st[i]]-c[st[i-1]])*s[st[i]];
        s[st[i-1]]-=s[st[i]];
    }
    for(int i=n-1;i>=1;i--) s[i]+=s[i+1];
    for(int i=1;i<=n;i++) cout<<s[i]<<" ";
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