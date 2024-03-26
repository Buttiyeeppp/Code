#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,l[N],r[N],pl[N],pr[N],a[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>l[i]>>r[i], pl[i]=l[i], pr[i]=r[i];
    for(int i=n-1;i>=1;i--) {
        if(l[i]>r[i+1]) r[i]=l[i];
        else if(r[i]<l[i+1]) l[i]=r[i];
        else l[i]=max(l[i],l[i+1]), r[i]=min(r[i],r[i+1]);
    }
	a[1]=l[1];
	for(int i=2;i<=n;i++) a[i]=a[i-1], a[i]=max(a[i],pl[i]), a[i]=min(a[i],r[i]);
    for(int i=1;i<=n;i++) cout<<a[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}