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
string s;
int g[N][2][2][2][2][2][2];
void Add(int &x,int y) { return x=(x+y>=Mod? x+y-Mod:x+y), void(); }
int dfs(int p,int a,int b,int c,int d,int e,int f) {
    if(~g[p][a][b][c][d][e][f]) return g[p][a][b][c][d][e][f];
    if(p==(int)s.size()) return g[p][a][b][c][d][e][f]=(d&e&f);
    int v=s[p]-'0', res=0;
    for(int i=0;i<=((!a)?1:v);i++) for(int j=0;j<=((!b)?1:v);j++) for(int k=0;k<=((!c)?1:v);k++) {
        int cnt=i+j+k;
        Add(res,dfs(p+1,(a?(i==v):0),(b?(j==v):0),(c?(k==v):0),(d|(cnt==1&&i)|(cnt==2&&!i)),(e|(cnt==1&&j)|(cnt==2&&!j)),(f|(cnt==1&&k)|(cnt==2&&!k))));
    }
    return g[p][a][b][c][d][e][f]=res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>s; s=' '+s;
    memset(g,-1,sizeof(g));
    cout<<dfs(1,1,1,1,0,0,0)<<endl;

    #ifdef xxzx
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    #endif
    return 0;
}