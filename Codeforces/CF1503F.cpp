#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool memory1;
int n,a[N],b[N],pos[2][N],to[N][2],in[N][2],d[N][3],tot;
void out(int x) {
    if(x<=n) return cout<<a[x]<<" "<<b[x]<<endl, void();
    for(int i=0;i<3;i++) out(d[x][i]);
}
int vis[N];
void chin(int x,int y,int z) { for(int f:{0,1}) if(in[z][f]==x) in[z][f]=y; }
void chto(int x,int y,int z) { for(int f:{0,1}) if(to[z][f]==x) to[z][f]=y; }
void merge(int i,int j,int k) {
    // cerr<<"Merge "<<i<<" "<<j<<" "<<k<<endl;
    tot++, d[tot][0]=i, d[tot][1]=j, d[tot][2]=k;
    vis[i]=vis[j]=vis[k]=1;
    int c1=0,c2=0;
    for(int f:{0,1}) {
        if(to[i][f]&&to[i][f]!=j) to[tot][c1++]=to[i][f], chin(i,tot,to[i][f]);
        if(in[k][f]&&in[k][f]!=j) in[tot][c2++]=in[k][f], chto(k,tot,in[k][f]);
        if(to[k][f])              to[tot][c1++]=to[k][f], chin(k,tot,to[k][f]);
        if(in[i][f])              in[tot][c2++]=in[i][f], chto(i,tot,in[i][f]);
    }
    // cerr<<tot<<endl;
    // for(int f:{0,1}) cerr<<to[tot][f]<<" "; cerr<<endl;
    // for(int f:{0,1}) cerr<<in[tot][f]<<" "; cerr<<endl;
}
bool memory2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    n<<=1, tot=n;
    for(int i=1;i<=n;i++) 
        cin>>a[i]>>b[i], pos[0][a[i]+n]=i, pos[1][b[i]+n]=i;
    for(int i=1;i<=n;i++) {
        (a[i]>0? to[i][0]:in[i][0])=pos[0][-a[i]+n];
        (b[i]>0? to[i][1]:in[i][1])=pos[1][-b[i]+n];
    }
    for(int j=1;j<=tot;j++) {
        for(int f1:{0,1}) for(int f2:{0,1}) if(!vis[j]) {
            int i=in[j][f1], k=to[j][f2];
            if(!i||!k||i==k) continue;
            merge(i,j,k);
        }
    }
    for(int i=1;i<=tot;i++) if(!vis[i]) {
        if(!to[i][0]&&!to[i][1]) continue;
        if(to[i][0]!=to[i][1]) return cout<<"NO"<<endl, 0;
    }
    cout<<"YES"<<endl;
    for(int i=1;i<=tot;i++) if(!vis[i]) {
        if(!to[i][0]&&!to[i][1]) continue;
        out(i), out(to[i][0]);
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&memory1-&memory2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}