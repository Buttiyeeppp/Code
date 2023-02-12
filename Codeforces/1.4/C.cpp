#include<bits/stdc++.h>
using namespace std;
#define ll long long
void solve() {
    int n,k,ans=0,mx=-1;
    cin>>n>>k;
    for(int i=1,x,y;i<=k+1;i++) {
        cout<<"? ";
        for(int j=1;j<=k+1;j++)
            if(i!=j) cout<<j<<" ";
        puts("");
        cin>>x>>y; 
        if(mx==y) ans++;
        else if(mx<y) mx=y, ans=1;
    }
    cout<<"! "<<ans<<endl;
}
int main() {
    int T=1;
    while(T--) solve();
    return 0;
}