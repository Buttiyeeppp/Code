#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,m,a,b,x[N],t[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>a>>b;
    for(int i=1,x;i<=m;i++) cin>>x, t[x]++;
    sort(t+1,t+n+1);
    for(int i=1;i<=n;i++) if(t[i]) {
        if(b>=t[i]) a-=t[i], b-=t[i], t[i]=0;
        else { a-=b; break; }
    }
    int k=n;
    for(int i=1;i<=n;i++) if(t[i]&&a) {
        a--, k--;
    }
    cout<<k<<endl;

    #ifdef xxzx
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    #endif
    return 0;
}