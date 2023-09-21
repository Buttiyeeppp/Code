#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
const ll P=131;
const ll Mod=1e9+7;
bool mem1;
int n,cs;
ll v[5],Pn,a[5][N];
unordered_set<ll> mp;
void calc(int op,int i) {
    v[op]=((v[op]-Pn*a[op][i]%Mod+Mod)%Mod*P+a[op][i])%Mod;
}
void solve() {
    cin>>n;
    ll sum=0;
    for(int i=1;i<=4;i++)
        for(int j=1;j<=n;j++) cin>>a[i][j], sum+=a[i][j];
    if(sum%n) return cout<<"Case "<<++cs<<": No"<<endl, void();
    sum/=n;
    memset(v,0,sizeof(v));
    for(int op=1;op<=4;op++)
        for(int i=1;i<=n;i++) v[op]=(v[op]*P+a[op][i])%Mod;
    ll m2=v[2],res=0; Pn=1;
    for(int i=1;i<=n;i++) {
        res=(res*P+sum)%Mod;
        if(i<n) Pn=Pn*P%Mod;
    }
    mp.clear();
    for(int i=1;i<=n;i++) mp.insert((v[3]+v[4])%Mod), calc(3,i);
    for(int i=1;i<=n;i++) {
        v[2]=m2;
        for(int j=1;j<=n;j++) {
            if(mp.count((res-(v[1]+v[2])%Mod+Mod)%Mod)) return cout<<"Case "<<++cs<<": Yes"<<endl, void();
            calc(2,j);
        }
        calc(1,i);
    }
    cout<<"Case "<<++cs<<": No"<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}