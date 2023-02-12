#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+10;
int n,m,deg[N],yep[N],s[N],mn[N];
int fa[N],sz[N];
vector<int> g[N];
int find(int x) {
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int mx=1;
void merge(int x,int y) {
    int fx=find(x), fy=find(y);
    if(fx!=fy) fa[fy]=fx, sz[fx]+=sz[fy], mx=max(mx,sz[fx]);
}
int main() {
    scanf("%d%d",&n,&m);
    for(int i=1,u,v;i<=m;i++) {
        scanf("%d%d",&u,&v);
        g[u].push_back(v), g[v].push_back(u);
        deg[u]++, deg[v]++;
    }
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(yep[j]) continue;
            if(!s[i]||deg[j]<deg[s[i]]) s[i]=j;
        }
        mn[i]=deg[s[i]];
        yep[s[i]]=1;
        for(auto now:g[s[i]])
            if(!yep[now]) deg[now]--;
    }
    for(int i=1;i<=n;i++) sz[i]=1, fa[i]=i;
    memset(yep,0,sizeof(yep));
    ll ans=0;
    for(int i=n;i>=1;i--) {
        yep[s[i]]=1;
        for(auto now:g[s[i]]) {
            if(!yep[now]) continue;
            merge(s[i],now);
        }
        ans=max(ans,1ll*mx*mn[i]);
    }
    printf("%lld",ans);
    return 0;
}