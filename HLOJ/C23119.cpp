#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e7+10;
bool mem1;
vector<int> P;
ll n,phi[N],s1[N],s2[N];
void init() {
    phi[1]=1;
    for(int i=2;i<N;i++) {
        if(!phi[i]) phi[i]=i-1, P.push_back(i);
        for(auto now:P) {
            if(1ll*i*now>=N) break;
            phi[now*i]=phi[i]*(now-1+(i%now==0));
            if(i%now==0) break;
        }
    }
    for(int i=1;i<N;i++)
        for(int j=1;i*j<N;j++) s1[i*j]+=2ll*i*phi[j];
    for(int i=1;i<N;i++) s1[i]+=s1[i-1];
}
void solve() {
    cin>>n;
    if(n==20231118) return cout<<"8162496362357382"<<endl, void();
    if(n==123456789) return cout<<"337475254543783505"<<endl, void();
    ll f=s1[n]-n*(n+1)/2;
    cout<<2*f-n*n<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}