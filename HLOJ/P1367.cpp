#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
ll n,len[N],p[N],m[N],v[N];
double liml,limr;
double ans;
void calc(int l,int r) {
    if(l>r) return;
    ll nowm=m[r]-m[l-1], nowv=v[r]-v[l-1];
    if(len[r+1]*p[r+1]>=liml-nowm) {
        double c=min(1.*(limr-nowm)/p[r+1],1.*len[r+1]);
        ans=max(ans,1.*(nowm+c*p[r+1])/(nowv+c));
        if(liml>nowm) {
            c=1.*(liml-nowm)/p[r+1];
            ans=max(ans,1.*liml/(nowv+c));
        }
    }
}
void sol() {
    for(int i=1;i<=n;i++) 
        m[i]=m[i-1]+len[i]*p[i], v[i]=v[i-1]+len[i];

    for(int i=1,p1=0,p2=1;i<=n;i++) {
        p1=max(p1,i-1), p2=max(p2,i);
        while(p1<n&&m[p1+1]-m[i-1]<liml) p1++; // <liml
        while(p2<=n&&m[p2]-m[i-1]<=limr) p2++; // >limr
        calc(i,p1), calc(i,p2-1);
    }
}
int que[N];
double a[N];
bool check(double ro) {
    for(int i=1;i<=n;i++) a[i]=len[i]*(p[i]-ro), a[i]+=a[i-1];
    int l=1,r=0;
    for(int i=1,p1=0,p2=1;i<=n;i++) {
        p1=max(p1,i-1), p2=max(p2,i);
        while(p1<n&&m[p1+1]-m[i-1]<liml) p1++;
        while(p2<=n&&m[p2]-m[i-1]<=limr) {
            while(l<=r&&a[que[r]]<=a[p2]) r--;
            que[++r]=p2;
            p2++;
        }
        while(l<=r&&que[l]<=p1) l++;
        if(l<=r&&a[que[l]]-a[i-1]>=0) return true;
    }
    return false;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>liml>>limr;
    for(int i=1;i<=n;i++) cin>>len[i];
    for(int i=1;i<=n;i++) cin>>p[i];
    for(int i=1;i<=n;i++) if(len[i]>=liml) ans=max(ans,1.*p[i]);

    sol();
    reverse(len+1,len+n+1), reverse(p+1,p+n+1);
    sol();

    double l=0,r=1e7,eps=1e-8;
    while(l+eps<r) {
        double mid=(l+r)/2;
        if(check(mid)) l=mid;
        else r=mid;
    }
    ans=max(ans,l);

    cout<<fixed<<setprecision(10)<<ans<<endl;
    
    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}