#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const int N=1e5+10;
int n,a[N],q,k;
ll sum[N],Ans[N];
bool cmp(int x,int y) { return x>y; }
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++) sum[i]=sum[i-1]+a[i];
    scanf("%d",&q);
    while(q--) {
        scanf("%d",&k);
        if(Ans[k]) { printf("%lld ",Ans[k]); continue; }
        ll ans=0, len=1, mem;
        for(ll i=k,cnt=1;;i*=k,cnt++) {
            mem=len, len=min(len+i,(ll)n);
            ans+=cnt*(sum[len]-sum[mem]);
            if(len==n) break;
        }
        Ans[k]=ans;
        printf("%lld ",ans);
    }
    return 0;
}