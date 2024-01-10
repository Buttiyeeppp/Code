#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,k,fa[N];
int lowbit(int x) { return x&-x; }
bool full(int x) { return (x+1==lowbit(x+1)); }
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    if(n%2==0||k>max((n-3)/2,0)) return cout<<"NO"<<endl, 0;
    if(n==9&&k==2) return cout<<"NO"<<endl, 0;
    if(full(n)&&k==1) return cout<<"NO"<<endl, 0;
    if(!full(n)&&!k) return cout<<"NO"<<endl, 0;
    int b=max(2*(k-1),0);
    for(int i=2;i<=b;i++) fa[i]=i-1-(i&1);
    for(int i=1;i<=n-b;i++) {
        if(i==1) fa[i+b]=max(b-1,0);
        else fa[i+b]=i/2+b;
    }
    if(full(n-b)&&k) fa[n]=fa[n-1]=2;
    cout<<"YES"<<endl;
    for(int i=1;i<=n;i++) cout<<fa[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}