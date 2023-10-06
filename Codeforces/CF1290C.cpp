#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=7e5+10;
bool mem1;
int n,k,to[2][N],sz[2][N],fa[N],ans;
string st;
int find(int x) {
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
    x=find(x), y=find(y);
    if(x==y) return;
    ans-=min(sz[0][x],sz[1][x])+min(sz[0][y],sz[1][y]);
    sz[0][y]+=sz[0][x], sz[1][y]+=sz[1][x], fa[x]=y;
    ans+=min(sz[0][y],sz[1][y]);
    // cerr<<"Chk "<<min(sz[0][y],sz[1][y])<<" "<<x<<" "<<y<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>k>>st;
    for(int i=1,l;i<=k;i++) {
        cin>>l;
        for(int j=1,x;j<=l;j++) {
            cin>>x;
            if(to[0][x]) to[1][x]=i;
            else to[0][x]=i;
        }
    }
    k++;
    for(int i=0;i<k;i++) fa[i]=i, sz[0][i]=1;
    for(int i=k;i<(k<<1);i++) fa[i]=i, sz[1][i]=1;
    for(int i=1;i<=n;i++) {
        if(st[i-1]-'0') {
            merge(to[0][i],to[1][i]);
            merge(to[0][i]+k,to[1][i]+k);
        }
        else {
            merge(to[0][i]+k,to[1][i]);
            merge(to[0][i],to[1][i]+k);
        }
        int res=ans>>1, f=find(0);
        if(sz[0][f]<sz[1][f]) res+=sz[1][f]-sz[0][f];
        cout<<res<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}