#include<bits/stdc++.h>
using namespace std;
const int N=5e6+10;
vector<int> g[5],P;
int prime[N];
void Get_Prime(){
    for(int i=2;i<=N-7;i++) {
        if(!prime[i]) g[i%4].push_back(i), P.push_back(i);
        for(auto now:P) {
            if(1ll*now*i>N-7) break;
            prime[now*i]=1;
            if(i%now==0) break;
        }
    }
}
void solve() {
    int n, mn=INT_MAX, op=-1;
    scanf("%d",&n);
    for(int i=1,x,step;i<=n;i++) {
        scanf("%d",&x);
        if(x%4) {
            step=(x-*(upper_bound(g[x%4].begin(),g[x%4].end(),x)-1))/2+1;
            step/=2;
            if(step<mn) mn=step, op=1;
        }
        else {
            step=x/4;
            if(step<mn) mn=step,  op=2;
        }
    }
    if(op==1) puts("Farmer John");
    else puts("Farmer Nhoj");
}
int main() {
    Get_Prime();
    int T;
    scanf("%d",&T);
    while(T--) solve();
    return 0;
}