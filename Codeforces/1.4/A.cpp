#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
int n,a[N],k[3];
void solve() {
    cin>>n;
    int ok=0;
    k[1]=k[2]=0;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(ok) continue;
        for(int j=1;j<=2;j++)
            if(k[j]&&abs(a[i]-a[k[j]])>=i-k[j]+1) {
                puts("YES");
                printf("%d %d\n",k[j],i);
                ok=1; break;
            }
        if(!k[1]||a[i]<a[k[1]]+i-k[1]) k[1]=i;
        if(!k[2]||a[i]+i-k[2]>a[k[2]]) k[2]=i;
    }
    if(!ok) puts("NO");
}
int main() {
    int T; cin>>T;
    while(T--) solve();
    return 0;
}