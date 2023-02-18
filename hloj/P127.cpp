#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,c[N],f[N],cnt[N];
vector<int> g[N];
void dfs(int x) {
    if(c[x]<=0) return;
    for(auto y:g[x]) {
        dfs(y);
        cnt[x]+=f[y];
    }
    if(cnt[x]>=1) f[x]=1;
    else if(cnt[x]<=-1) f[x]=-1;
    else f[x]=0;
}
vector<int> ans;
void _dfs(int x) {
    if(c[x]==0) ans.push_back(x);
    for(auto y:g[x]) {
        if(cnt[y]==-1||f[y]==0) _dfs(y);
    }
}
int main() {
    freopen("color.in","r",stdin);
    freopen("color.out","w",stdout);
    scanf("%d",&n);
    for(int i=1;i<=n;i++) {
        scanf("%d",&c[i]);
        if(c[i]>0) {
            for(int j=1,x;j<=c[i];j++)
            scanf("%d",&x), g[i].push_back(x);
        }
        else{
            if(c[i]==-2) f[i]=1;
            else if(c[i]==-1) f[i]=-1;
            else f[i]=0;
        }
    }
    dfs(1);
    if(f[1]==-1) {puts("Bob"); return 0;}
    puts("Alice");
    if(f[1]) {for(int i=1;i<=n;i++) if(!c[i]) ans.push_back(i);}
    else _dfs(1);
    sort(ans.begin(),ans.end());
    printf("%d\n",(int)ans.size());
    for(auto now:ans) printf("%d ",now);
    return 0;
}