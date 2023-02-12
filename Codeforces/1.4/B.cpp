#include<bits/stdc++.h>
using namespace std;
#define ll long long
void solve() {
    int n; ll a=0, b=0;
    cin>>n;
    for(int i=1,v;i<=n;i++) 
        cin>>v, a+=v, b^=v;
    printf("2\n%lld %lld\n",b,a+b);
}
int main() {
    int T; cin>>T;
    while(T--) solve();
    return 0;
}