#include<bits/stdc++.h>
using namespace std;
#define ll long long
const ll Mod=998244353;
const int N=2e5+10;
ll h[N],ans;
int n,dep[N];
vector<int> g[N];
void dfs(int x) {
    for(auto y:g[x]) {
        dep[y]=dep[x]+1;
        dfs(y);
    }
}
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return sum;
}
int main() {
    scanf("%d",&n);
    for(int i=2,f;i<=n;i++) {
        scanf("%d",&f);
        g[f].emplace_back(i);
    }
    dep[1]=1, dfs(1);
    for(int i=1;i<=n;i++) h[i]=(h[i-1]+Mul(i,Mod-2))%Mod;
    for(int i=1;i<=n;i++) ans=(ans+h[dep[i]])%Mod;
    printf("%lld",ans);
    return 0;
}