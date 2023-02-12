#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int n,m;
bool check(int l,vector<vector<int>> a) {
    vector<vector<int>> d(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) d[i][j]=(a[i][j]>=l);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) d[i][j]+=d[i-1][j]+d[i][j-1]-d[i-1][j-1];
    for(int i=l;i<=n;i++)   
        for(int j=l;j<=m;j++) {
            if(d[i][j]-d[i-l][j]-d[i][j-l]+d[i-l][j-l]==l*l) return true;
        }
    return false;
}
void solve() {
    cin>>n>>m;
    vector<vector<int>> a(n+1,vector<int>(m+1));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) cin>>a[i][j];
    check(3,a);
    int l=0,r=min(n,m);
    while(l+1<r) {
        int mid=(l+r)>>1;
        if(check(mid,a)) l=mid;
        else r=mid;
    }
    if(check(r,a)) cout<<r<<endl;
    else cout<<l<<endl;
}
int main() {
    int T; cin>>T;
    while(T--) solve();
    return 0;
}
