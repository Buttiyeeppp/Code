#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
const int N=1e3+10;
int n,a[N],vis[N],tot=1,b[N],mem[N];
char d[N][N];
vector<int> node;
void dfs(int x) {
    vis[x]=1, node.push_back(x);
    if(!vis[a[x]]) dfs(a[x]);
}
void out(int x) {
    cout<<x<<endl;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) cout<<d[i][j];
        cout<<endl;
    }
}
void mk() {
    for(int i=1;i<=n;i++) if(!vis[i]&&(i<a[i])) {
        int p=i;
        while(a[p]!=i) {
            if(p==1) { p=a[p]; continue; }
            vis[p]=1, b[p]=++tot;
            if(p<a[p]) d[tot][p]=d[tot][a[p]]='/';
            else d[tot][p]=d[tot][a[p]]='\\';
            p=a[p];
        }
        if(!(a[p]==i&&p!=1)) continue;
        vis[p]=1, b[p]=++tot;
        d[tot][p]=d[tot][1]='\\', d[b[i]][1]='/';
    }
}
int main() {
    ios::sync_with_stdio(false), cin.tie(0);
    cin>>n;
    int ok=1;
    for(int i=1;i<=n;i++) cin>>a[i], vis[i]=(i==a[i]), ok&=vis[i];
    for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) d[i][j]='.';
    if(ok) return out(n), 0;
    mk();
    return out(n-1), 0;
}