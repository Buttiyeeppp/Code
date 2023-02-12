#include<bits/stdc++.h>
using namespace std;
int cnt[15][3],n;
void solve() {
    memset(cnt,0,sizeof(cnt));
    scanf("%d",&n);
    for(int i=1,x;i<=n;i++) {
        scanf("%d",&x);
        for(int j=0;j<10;j++) {
            cnt[j][(x>>j)&1]=1;
        }
    }
    // for(int j=0;j<10;j++) cout<<cnt[j][0]<<" "<<cnt[j][1]<<endl;
    int ans=0;
    for(int j=0;j<10;j++)
        if(cnt[j][0]&&cnt[j][1]) ans+=(1<<j);
    printf("%d\n",ans);
}
int main() {
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}