#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=60;
int n;
ll a[N];
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        if(i!=1) a[1]*=a[i];
    }
    cout<<(a[1]+n-1)*2022<<endl;
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}