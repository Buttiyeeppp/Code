#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
bool mem1;
int n,a[N],b[N],ls[N],rs[N],st[N],top,fa[N],sig[N];
ll s[N],ans[N];
void dfs(int x) {
    if(!(x&1)) s[x]=a[x/2];
    if(ls[x]) dfs(ls[x]), s[x]+=s[ls[x]];
    if(rs[x]) dfs(rs[x]), s[x]+=s[rs[x]];
    if(!sig[x]) ans[x]=max(b[fa[x]]-s[x],0ll);
}
void dfs1(int x) {
    ans[x]=max(ans[x],ans[fa[x]]);
    if(ls[x]) dfs1(ls[x]);
    if(rs[x]) dfs1(rs[x]);
}
bool mem2;
int main() {
    freopen("room.in","r",stdin);
    freopen("room.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=2*n+1;i+=2) cin>>b[i];
    for(int i=1;i<=2*n+1;i++) {
        int p=0;
        while(top&&b[st[top]]<=b[i]) p=st[top--];
        ls[i]=p, fa[p]=i;
        if(top) rs[st[top]]=i, fa[i]=st[top];
        st[++top]=i;
    }
    // for(int i=1;i<=2*n+1;i++) cout<<i<<" "<<ls[i]<<" "<<rs[i]<<endl;
    for(int i=1;i;i=fa[i]) sig[i]=1;
    for(int i=2*n+1;i;i=fa[i]) sig[i]=1;
    dfs(st[1]), dfs1(st[1]);
    for(int i=2;i<=2*n;i+=2) cout<<ans[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}