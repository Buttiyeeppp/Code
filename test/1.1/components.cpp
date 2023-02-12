#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,Q,l,r,vis[4][N];
char a[4][N];
void dfs(int x,int y) {
    if(x<1||x>3||y<l||y>r||a[x][y]!='1'||vis[x][y])return;
    vis[x][y]=1;
    dfs(x-1,y), dfs(x+1,y), dfs(x,y-1), dfs(x,y+1);
}
int main() {
    freopen("components.in","r",stdin);
    freopen("components.out","w",stdout);
    scanf("%d%s%s%s%d",&n,a[1]+1,a[2]+1,a[3]+1,&Q);
    while(Q--) {
        scanf("%d%d",&l,&r);
        memset(vis,0,sizeof(vis));
        int cnt=0;
        for(int i=1;i<=3;i++) for(int j=l;j<=r;j++)
            if(!vis[i][j]&&a[i][j]=='1') dfs(i,j),cnt++;
        printf("%d\n",cnt);
    }
    return 0;
}