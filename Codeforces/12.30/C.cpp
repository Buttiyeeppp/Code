#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=2e5+10;
const ll Mod=998244353;
ll fac[N],inv[N];
int n,m,s[N],t[N],cnt[N],cc[N];
int lowbit(int x){return x&-x;}
void Modify(int x,int val) {
    for(int i=x;i<N;i+=lowbit(i)) cnt[i]+=val;
}
int Query(int x) {
    int sum=0;
    for(int i=x;i;i-=lowbit(i)) sum+=cnt[i];
    return sum;
}
ll Mul(ll x,ll y) {
    ll sum=1;
    while(y) {
        if(y&1) sum=sum*x%Mod;
        x=x*x%Mod;
        y>>=1;
    }
    return sum;
}
void solve() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>s[i], Modify(s[i],1), cc[s[i]]++;
    for(int i=1;i<=m;i++) cin>>t[i];
    ll k=fac[n],ans=0;
    for(int i=1;i<N;i++) if(cc[i]) k=k*inv[cc[i]]%Mod;
    for(int i=1;i<=min(n,m);i++) {
        if(i!=1) {
            if(cc[t[i-1]]==0) {break;}
            k=k*cc[t[i-1]]%Mod*Mul(n-i+2,Mod-2)%Mod;
            Modify(t[i-1],-1), cc[t[i-1]]--;
        }
        ll sum=Query(t[i]-1);
        ans=(ans+sum*k%Mod*Mul(n-i+1,Mod-2)%Mod)%Mod;
        if(n<m&&i==n&&cc[t[i]]) ans=(ans+1)%Mod;
    }
    cout<<ans<<endl;
}
int main() {
    fac[0]=1;
    for(int i=1;i<N;i++) fac[i]=fac[i-1]*i%Mod;
    inv[N-1]=Mul(fac[N-1],Mod-2);
    for(int i=N-2;i>=0;i--) inv[i]=inv[i+1]*(i+1)%Mod;
    int t=1;
    while(t--) solve();
    return 0;
}