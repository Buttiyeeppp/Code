#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int V=1e5;
bool mem1;
int n,a[N];
bool mem2;
int main() {
    freopen("mod.in","r",stdin);
    freopen("mod.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cout<<2*n+1<<endl;
    ll sum=0;
    for(int i=n;i>=1;i--) {
        cout<<"2 "<<i+sum<<endl;
        cout<<"1 "<<a[i]-a[i-1]+V<<endl;
        sum+=a[i]-a[i-1]+V;
    }
    cout<<"2 "<<V<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}