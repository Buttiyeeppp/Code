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
int n,a[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    sort(a+1,a+n+1,[](const int &x,const int &y) { return x>y; });
    int p=1,d1=0,d2;
    while(p<n&&p+1<a[p+1]+1) p++;
    while(a[p+d1]+1>p&&p+d1<=n) d1++;
    d2=a[p]+1-p;
    cout<<(((d1%2==0)||(d2%2==0))? "First":"Second")<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}