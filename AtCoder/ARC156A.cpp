#include<bits/stdc++.h>
using namespace std;
int n;
string s;
void solve() {
    cin>>n>>s; s=' '+s;
    int cnt=0,yep=0,ans;
    for(int i=1;i<=n;i++) {
        if(s[i]=='1') cnt++;
        if(i<n&&s[i]=='1'&&s[i+1]=='1') yep=1;
    }
    if(!cnt) return puts("0"), void();
    if(cnt&1) return puts("-1"), void();
    if(n>4) ans=cnt/2+(cnt==2&&yep);
    else if(n==4) {
        if(cnt==4) ans=2;
        else if(cnt==2) {
            if(s[1]=='0'&&s[4]=='0') ans=3;
            else ans=1+yep;
        }
    }
    else if(n==3) {
        if(s[1]=='1'&&s[3]=='1') ans=1;
        else ans=-1;
    }
    else ans=-1;
    printf("%d\n",ans);
}
int main() {
    int T; scanf("%d",&T);
    while(T--) solve();
    return 0;
}