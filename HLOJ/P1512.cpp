#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
const int M=5e3+10;
bool mem1;
int n,w,k,a[N],b[N];
struct node {
    int v[M];
    void clear() {
        memset(v,0x3f,sizeof(v));
        v[0]=0;
    }
    void insert(int a,int b) {
        for(int i=M-1;i>=a;i--) {
            v[i]=min(v[i],v[i-a]+b);
        }
    }
}fl[N],fr[N];
bool check(int l,int r) {
    for(int i=0;i<=w;i++)
        if(fl[l].v[i]+fr[r].v[w-i]<=k) return true;
    return false;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>w>>k;
    for(int i=1;i<=n;i++) cin>>a[i]>>b[i];
    for(int i=0;i<=n+1;i++) fl[i].clear(), fr[i].clear();
    int ans=INT_MAX;
    for(int i=1,r1=0,r2=0;i<=n;i++) {
        int pd=0;
        while(r2<i||!check(i,r2)) {
            if(r2==n) { pd=1; break; }
            r2++, fr[r2]=fr[r2-1];
            fr[r2].insert(a[r2],b[r2]);
        }
        if(pd) break;
        ans=min(ans,r2-i+1);
        if(i>r1) {
            fl[r2].insert(a[r2],b[r2]);
            for(int j=r2-1;j>=r1+1;j--)
                fl[j]=fl[j+1], fl[j].insert(a[j],b[j]);
            r1=r2;
            fr[r2].clear();
        }
    }
    cout<<((ans==INT_MAX)? -1:ans)<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}