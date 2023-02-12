#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
int n,a[N];
map<ll,int> cnt;
ll pre[N];
void solve() {
    cin>>n;
    vector<int> pos;
    for(int i=1;i<=n;i++) {
        cin>>a[i];
        pre[i]=pre[i-1]+a[i];
        if(!a[i]) pos.push_back(i);
    }
    pos.push_back(n+1);
    int ans=0;
    for(int i=1;i<pos[0];i++) ans+=(pre[i]==0);
    for(int i=0;i+1<(int)pos.size();i++) {
        cnt.clear();
        int mx=-1;
        for(int j=pos[i];j<pos[i+1];j++) cnt[pre[j]]++, mx=max(mx,cnt[pre[j]]);
        ans+=mx;
    }
    cout<<ans<<endl;
    return;
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}