#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e6+10;
const ll Mod=998244353;
const ll inv=499122177;
bool mem1;
ll n,na[N],nb[N],a[N],b[N];
void FWTor(ll *a,int f) {
    for(int i=1;i<n;i<<=1) {
        for(int j=0;j<n;j+=2*i) {
            for(int k=j;k<j+i;k++)
                a[i+k]=(a[i+k]+f*a[k]+Mod)%Mod;
        }
    }
}
void FWTand(ll *a,int f) {
    for(int i=1;i<n;i<<=1) {
        for(int j=0;j<n;j+=2*i) {
            for(int k=j;k<j+i;k++)
                a[k]=(a[k]+f*a[i+k]+Mod)%Mod;
        }
    }
}
void FWTxor(ll *a,int f) {
    for(int i=1;i<n;i<<=1) {
        for(int j=0;j<n;j+=2*i) {
            for(int k=j;k<j+i;k++) {
                ll x=a[k], y=a[i+k];
                a[k]=(x+y)%Mod, a[i+k]=(x-y+Mod)%Mod;
                if(f==-1) a[k]=1ll*a[k]*inv%Mod, a[i+k]=1ll*a[i+k]*inv%Mod;
            }
        }
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    n=1<<n;
    for(int i=0;i<n;i++) cin>>na[i];
    for(int i=0;i<n;i++) cin>>nb[i];

    memcpy(a,na,sizeof(a)), memcpy(b,nb,sizeof(b));
    FWTor(a,1), FWTor(b,1);
    for(int i=0;i<n;i++) a[i]=a[i]*b[i]%Mod;
    FWTor(a,-1);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<endl;

    memcpy(a,na,sizeof(a)), memcpy(b,nb,sizeof(b));
    FWTand(a,1), FWTand(b,1);
    for(int i=0;i<n;i++) a[i]=a[i]*b[i]%Mod;
    FWTand(a,-1);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<endl;

    memcpy(a,na,sizeof(a)), memcpy(b,nb,sizeof(b));
    FWTxor(a,1), FWTxor(b,1);
    for(int i=0;i<n;i++) a[i]=a[i]*b[i]%Mod;
    FWTxor(a,-1);
    for(int i=0;i<n;i++) cout<<a[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}