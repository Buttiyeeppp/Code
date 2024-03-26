#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=998244353;
bool mem1;
int n,p[N],id[N];
ll f[N][2][2],ans;
void Add(ll &x,ll y) {
    x=(x+y>=Mod)? x+y-Mod:x+y;
}
string st;
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i], id[p[i]]=i;
    cin>>st;
    st=" "+st;
    if(st[1]!='R') f[1][0][0]=f[1][1][0]=1;
    for(int i=2;i<=n;i++) {
        if(id[i-1]<id[i]) {
            if(st[i]!='R') {
                Add(f[i][0][0],f[i-1][0][0]);
                Add(f[i][1][0],f[i-1][1][1]);
                Add(f[i][1][0],f[i-1][1][0]);
            }
            if(st[i]!='L') {
                Add(f[i][0][1],f[i-1][0][0]);
                Add(f[i][1][1],f[i-1][1][1]);
                Add(f[i][1][1],f[i-1][1][0]);
            }
        }
        else {
            if(st[i]!='R') {
                Add(f[i][0][0],f[i-1][0][1]);
                Add(f[i][0][0],f[i-1][0][0]);
            }
            if(st[i]!='L') {
                Add(f[i][1][1],f[i-1][1][0]);
                Add(f[i][1][1],f[i-1][1][1]);
                Add(f[i][0][1],f[i-1][0][0]);
                Add(f[i][0][1],f[i-1][0][1]);
            }
            // if(i==n) cout<<f[i][0][0]<<" "<<f[i][1][1]<<endl;
        }
    }
    if(id[n]<id[1]) Add(ans,f[n][1][1]), Add(ans,f[n][0][0]), Add(ans,f[n][1][0]);
    else Add(ans,f[n][0][0]), Add(ans,f[n][0][1]);
    // cout<<f[n][1][0]<<" "<<f[n][1][1]<<" "<<f[n][0][0]<<" "<<f[n][0][1]<<endl;

    memset(f,0,sizeof(f));
    if(st[1]!='L') f[1][0][1]=f[1][1][1]=1;
    for(int i=2;i<=n;i++) {
        if(id[i-1]<id[i]) {
            if(st[i]!='R') {
                Add(f[i][0][0],f[i-1][0][0]);
                Add(f[i][1][0],f[i-1][1][1]);
                Add(f[i][1][0],f[i-1][1][0]);
            }
            if(st[i]!='L') {
                Add(f[i][0][1],f[i-1][0][0]);
                Add(f[i][1][1],f[i-1][1][1]);
                Add(f[i][1][1],f[i-1][1][0]);
            }
        }
        else {
            if(st[i]!='R') {
                Add(f[i][0][0],f[i-1][0][1]);
                Add(f[i][0][0],f[i-1][0][0]);
            }
            if(st[i]!='L') {
                Add(f[i][1][1],f[i-1][1][0]);
                Add(f[i][1][1],f[i-1][1][1]);
                Add(f[i][0][1],f[i-1][0][0]);
                Add(f[i][0][1],f[i-1][0][1]);
            }
            // if(i==n) cout<<f[i][0][0]<<" "<<f[i][1][1]<<endl;
        }
    }
    if(id[n]<id[1]) Add(ans,f[n][1][1]), Add(ans,f[n][0][0]), Add(ans,f[n][1][0]);
    else Add(ans,f[n][1][0]), Add(ans,f[n][1][1]), Add(ans,f[n][0][0]), Add(ans,f[n][0][1]);
    // cout<<f[n][1][0]<<" "<<f[n][1][1]<<" "<<f[n][0][0]<<" "<<f[n][0][1]<<endl;

    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}