#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e7;
bool mem1;
string a;
int n,r[N],p; 
char st[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>a;
    st[++n]='!';
    for(int i=0;i<(int)a.size();i++) st[++n]=a[i], st[++n]='!';
    int ans=0;
    for(int i=1;i<=n;i++) {
        r[i]=1;
        if(i<=p+r[p]-1) r[i]=min(r[2*p-i],p+r[p]-i);
        while(i+r[i]<=n&&i-r[i]>=1&&st[i+r[i]]==st[i-r[i]]) r[i]++;
        if(i+r[i]>p+r[p]) p=i;
        ans=max(ans,r[i]-1);
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}