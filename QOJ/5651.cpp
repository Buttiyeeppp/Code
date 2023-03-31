#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,dep[N],ans,f[N][2];
vector<int> g[N];
bool cmp(int x,int y) { return x>y; }
void dfs(int x,int from) {
    dep[x]=dep[from]+1;
    if(g[x].size()<=1||dep[x]%2==0) ans=max(ans,x);
    f[x][dep[x]&1]=x;
    vector<int> s;
    for(auto y:g[x]) if(y!=from){
        dfs(y,x);
        f[x][0]=max(f[x][0],f[y][0]), f[x][1]=max(f[x][1],f[y][1]);
        s.emplace_back(f[y][dep[x]&1]);
    }
    sort(s.begin(),s.end(),cmp);
    if(dep[x]%2&&s.size()>=2&&x!=n) ans=max(ans,s[1]);
    if(s.size()>=3) ans=max(ans,s[2]);
}
int main() {
    scanf("%d",&n);
    for(int i=1,u,v;i<n;i++) {
        scanf("%d%d",&u,&v);
        g[u].emplace_back(v), g[v].emplace_back(u);
    }
    if(n%2==0) return printf("%d\n",n), 0;
    dfs(n,0);
    printf("%d\n",ans);
    return 0;
}