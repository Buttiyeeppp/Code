#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
// const int m=122;
bool memory1;
string s;
int sa[N],x[N],y[N],buc[N],m=122;
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>s;
    int n=s.size();
    for(int i=1;i<=n;i++) x[i]=s[i-1],buc[x[i]]++;
    for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
    for(int i=n;i>=1;i--) sa[buc[x[i]]--]=i;
    for(int i=1;i<=m;i++) buc[i]=0;
    for(int l=1;l<=n;l<<=1) {
        int tot=0;
        for(int i=n-l+1;i<=n;i++) y[++tot]=i;
        for(int i=1;i<=n;i++) if(sa[i]>l) y[++tot]=sa[i]-l;
        for(int i=0;i<=m;i++) buc[i]=0;
        for(int i=1;i<=n;i++) buc[x[i]]++;
        for(int i=1;i<=m;i++) buc[i]+=buc[i-1];
        for(int i=n;i>=1;i--) sa[buc[x[y[i]]]--]=y[i];
        m=0;
        for(int i=1;i<=n;i++) {
            if(i==1||x[sa[i]]!=x[sa[i-1]]||x[sa[i]+l]!=x[sa[i-1]+l]) m++;
            y[sa[i]]=m;
        }
        swap(x,y);
    }
    for(int i=1;i<=n;i++) cout<<sa[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}