#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
// #define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int n,m,p;
ll s1[N],s2[N],a[N][N],temp;
bool check() {
    if(p>1&&p<n) return (s2[p-1]+s2[p+1]-2*s2[p]==temp);
    if(p==1) return (s2[1]+s2[3]-2*s2[2]==temp);
    else return (s2[n-2]+s2[n]-2*s2[n-1]==temp);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>m>>n;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) 
            cin>>a[i][j], s1[i]+=a[i][j], s2[i]+=a[i][j]*a[i][j];
    if(s1[2]-s1[1]!=s1[n]-s1[n-1]) {
        temp=s1[4]-s1[3];
        if(s1[2]-s1[1]!=temp) {
            if(s1[3]-s1[2]!=temp) p=2;
            else p=1;
        }
        else {
            if(s1[n-1]-s1[n-2]!=temp) p=n-1;
            else p=n;
        }
    }
    else {
        temp=s1[2]-s1[1];
        for(int i=2;i<n;i++) if(s1[i]-s1[i-1]!=temp&&s1[i+1]-s1[i]!=temp) p=i;
    }
    cout<<p-1<<" ";
    ll del=-s1[p];
    if(p>1&&p<n) del+=(s1[p-1]+s1[p+1])/2;
    else if(p==1) del+=s1[2]-(s1[3]-s1[2]);
    else del+=s1[n-1]+(s1[n-1]-s1[n-2]);
    if(p>3) temp=s2[1]+s2[3]-2*s2[2];
    else temp=s2[n-2]+s2[n]-2*s2[n-1];
    for(int i=1;i<=m;i++) {
        s2[p]+=-a[p][i]*a[p][i]+(a[p][i]+del)*(a[p][i]+del);
        if(check()) return cout<<a[p][i]+del<<endl, 0;
        s2[p]+=+a[p][i]*a[p][i]-(a[p][i]+del)*(a[p][i]+del);
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}