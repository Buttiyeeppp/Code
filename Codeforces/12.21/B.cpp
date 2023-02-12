#include<bits/stdc++.h>
using namespace std;
#define int long long
const int N=1e5+10;
int n,k;
struct D {
    int h,p;
}d[N];
bool cmp(D a,D b) {
    return a.p<b.p;
}
int sum;
bool check(int x,int i) {
    return x*k-x*(x-1)/2*d[i].p>=d[i].h-sum;
}
void solve() {
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;i++) scanf("%lld",&d[i].h);
    for(int i=1;i<=n;i++) scanf("%lld",&d[i].p);
    sort(d+1,d+n+1,cmp);
    sum=0;
    for(int i=1;i<=n;i++) {
        if(d[i].h<=sum) continue;
        if(k<=0) {puts("NO"); return;}
        int head=1,tail=k/d[i].p+1;
        while(head+1<tail) {
            int mid=(head+tail)>>1;
            if(check(mid,i)) tail=mid;
            else head=mid;
        }
        int mem;
        if(check(head,i)) mem=head;
        else if(check(tail,i)) mem=tail;
        else {puts("NO"); return;}
        sum+=mem*k-mem*(mem-1)/2*d[i].p;
        k-=mem*d[i].p;
    }
    puts("YES");
}
signed main() {
    int T; scanf("%lld",&T);
    while(T--) solve();
    return 0;
}