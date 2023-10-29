#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=998244353;
bool mem1;
int pre[N][30],f[N],ed[30],be[30];
void solve() {
    string st; cin>>st;
    memset(pre,-1,sizeof(pre)), memset(ed,-1,sizeof(ed));
    memset(be,0,sizeof(be)), memset(f,0,sizeof(f));
    for(int i=0;i<(int)st.size();i++) {
        int x=st[i]-'a';
        if(!be[x]) f[i]=1 ,be[x]=1;
        ed[x]=i;
        if(i) {
            for(int j=0;j<26;j++) pre[i][j]=pre[i-1][j];
            pre[i][st[i-1]-'a']=i-1;
        }
    }
    for(int i=0;i<(int)st.size();i++) {
        int x=st[i]-'a';
        for(int j=0;j<26;j++) if((~pre[i][j])&&pre[i][j]>=pre[i][x]) {
            f[i]=(f[i]+f[pre[i][j]])%Mod;
        }
    }
    ll ans=0;
    for(int i=0;i<26;i++) if(~ed[i]) ans=(ans+f[ed[i]])%Mod;
    cout<<ans<<endl;
}
bool mem2;
int main() {
    freopen("subseq.in","r",stdin), freopen("subseq.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}