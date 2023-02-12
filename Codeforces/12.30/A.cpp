#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=1e5+10;
int n,cnt[13];
char s[N];
void solve() {
    scanf("%d%s",&n,s+1);
    int ans=0,sum;
    for(int i=1;i<=n;i++) {
        sum=0, memset(cnt,0,sizeof(cnt));
        for(int j=i;j<=min(n,i+100);j++) {
            if(!cnt[s[j]-'0']) sum++;
            cnt[s[j]-'0']++;
            bool ok=1;
            for(int j=0;j<=9;j++) ok&=(cnt[j]<=sum);
            if(ok) ans++;
        }
    }
    cout<<ans<<endl;
}
int main() {
    int t;
    cin>>t;
    while(t--) solve();
    return 0;
}