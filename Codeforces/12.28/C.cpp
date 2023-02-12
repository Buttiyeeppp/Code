#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
const int M=2e6+10;
#define ll long long
int n,a[N],appear[M];
void solve() {
    cin>>n;
    ll sum=0;
    for(int i=1;i<=n;i++) {cin>>a[i]; a[i]^=a[i-1];}
    appear[0]=1;
    for(int i=1;i<=n;i++) {
        for(int j=0;j<=1000;j++) sum+=appear[(j*j)^a[i]];
        appear[a[i]]++;
    }
    for(int i=1;i<=n;i++) appear[a[i]]=0;
    cout<<1ll*n*(n+1)/2-sum<<endl;
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}
