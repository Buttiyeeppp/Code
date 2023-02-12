#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
int n,T,s[N],cnt[N*510];
char a[N];
vector<int> pos;
int main() {
    scanf("%s",a+1);
    n=strlen(a+1), T=sqrt(n);
    for(int i=1;i<=n;i++) {
        s[i]=s[i-1]+(a[i]=='1');
        if(a[i]=='1') pos.emplace_back(i);
    }
    pos.emplace_back(n+1);
    ll ans=0;
    cnt[n]=1;
    for(int j=1;j<=T;j++) {
        for(int i=1;i<=n;i++) {
            int z=j*s[i]-i+n;
            ans+=cnt[z], cnt[z]++;
        }
        for(int i=1;i<=n;i++) {
            int z=j*s[i]-i+n; cnt[z]--;
        }
    }
    for(int k=1;k<=min(n/T-(T*T==n),(int)pos.size());k++) {
        int p=k-1;
        for(int i=1;i<=n;i++) {
            if(p>=(int)pos.size()-1) break;
            if((pos[p+1]-i)/k>T) ans+=(pos[p+1]-i)/k-max((pos[p]-i)/k,T);
            if(a[i]=='1') p++;
        }
    }
    cout<<ans<<endl;
    return 0;
}
