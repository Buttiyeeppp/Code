#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=1e9+7;
const int N=2e5+10;
int ls[N],rs[N],st[N],top;
int n,m,a[N];
vector<ll> dp[N];
void dfs(int x) {
    if(!x) return;
    dfs(ls[x]), dfs(rs[x]);
    for(int i=1;i<=m;i++) {
        dp[x][i]=dp[ls[x]][i-1]*dp[rs[x]][i]%Mod;
        dp[x][i]=(dp[x][i]+dp[x][i-1])%Mod;
    }
    return;
}
void solve() {
    scanf("%d%d",&n,&m);
    dp[0].clear(), dp[0].resize(m+2); 
	for(int i=0;i<=m;i++) dp[0][i]=1;
	for(int i=1;i<=n;i++) 
		ls[i]=rs[i]=0, dp[i].clear(), dp[i].resize(m+2);
	top=0;
    for(int i=1;i<=n;i++) {
        scanf("%d",&a[i]);
        int k=top;
        while(k&&a[st[k]]<a[i]) k--;
        if(k) rs[st[k]]=i;
        if(k<top) ls[i]=st[k+1];
        st[++k]=i, top=k;
    }
    dfs(st[1]);
    printf("%lld\n",dp[st[1]][m]);
    return;
}
int main() {
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}
