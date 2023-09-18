#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,k,a[N],yep[N],mn[N],f[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>a[i];
    for(int i=1;i<=n;i++) {
        f[i]=1;
        if(i>1&&a[i]>a[i-1]) f[i]=f[i-1]+1;
        if(f[i]>=k) {
            for(int i=1;i<=n;i++) cout<<a[i]<<" ";
            cout<<endl;
            return 0; 
        } 
    }
    yep[n-k]=yep[n-k+1]=1;
    for(int i=n-k-1;i>=1;i--) yep[i]=yep[i+1]&(a[i]<a[i+1]);
    mn[n-k+1]=a[n-k+1];
    for(int i=n-k+2;i<=n;i++) mn[i]=min(mn[i-1],a[i]);
    for(int i=n-k+1,j=i-k+1;i<=n;i++,j++) {
        if(j>=1&&yep[j]&&(i==n||a[n-k]<mn[i])) {
            sort(a+j,a+i+1);
            for(int i=1;i<=n;i++) cout<<a[i]<<" ";
            cout<<endl;
            return 0; 
        }
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}