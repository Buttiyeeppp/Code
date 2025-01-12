#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e4+10;
const ll P=1331;
const ll Mod=998244353;
bool memory1;
string s;
int n,a[N],b[N];
ll hs[N],Pow[N];
ll Hash(int l,int r) {
    return (hs[r]-hs[l-1]*Pow[r-l+1]%Mod+Mod)%Mod;
}
void sol(int *f) {
    for(int i=1;i<=n;i++) hs[i]=(hs[i-1]*P+s[i-1]-'a'+1)%Mod;
    // cerr<<Hash(1,3)<<" "<<Hash(3,5)<<endl;
    for(int len=1;len<=n;len++) {
        for(int i=1,j=len+1;j<=n;i+=len,j+=len) if(s[i-1]==s[j-1]) {
            int l=1,r=len+1;
            while(l+1<r) {
                int mid=(l+r)>>1;
                if(i-mid+1>=1&&Hash(i-mid+1,i)==Hash(j-mid+1,j)) l=mid;
                else r=mid;
            }
            int t1=l;
            l=1,r=len+1;
            while(l+1<r) {
                int mid=(l+r)>>1;
                if(j+mid-1<=n&&Hash(i,i+mid-1)==Hash(j,j+mid-1)) l=mid;
                else r=mid;
            }
            int t2=l;
            int L=len-t2+1,R=t1;
                // cerr<<len<<" "<<i<<" "<<i-R+1<<" "<<i-L+1<<" "<<t1<<" "<<t2<<endl;
            if(L<=R) {
                f[i-R+1]++,f[i-L+1+1]--;
            }
        }
    }
    for(int i=1;i<=n;i++) f[i]+=f[i-1];
}
void solve() {
    cin>>s;
    n=s.size();
    memset(a,0,sizeof(a)),memset(b,0,sizeof(b));
    sol(a);
    reverse(s.begin(),s.end());
    sol(b);
    reverse(b+1,b+n+1);
    // for(int i=1;i<=n;i++) cerr<<a[i]<<" "; cerr<<endl;
    // for(int i=1;i<=n;i++) cerr<<b[i]<<" "; cerr<<endl;
    ll ans=0;
    for(int i=2;i<=n;i++) ans+=1ll*a[i]*b[i-1];
    cout<<ans<<endl;
}
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    Pow[0]=1;
    for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*P%Mod;
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}