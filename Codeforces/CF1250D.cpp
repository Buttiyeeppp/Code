#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
bool mem1;
int n,f[N][210],L[N],R[N],val[N][N],yep[N],cnt[N];
struct Segment {
    int l,r,c;
    friend bool operator<(const Segment &x,const Segment &y) {
        return x.l<y.l;
    }
}sg[N];
void Max(int &x,int y) { if(y>x) x=y; } 
void solve() {
    cin>>n;
    for(int i=1;i<=n;i++) 
        cin>>sg[i].l>>sg[i].r>>sg[i].c;
    sort(sg+1,sg+n+1);
    for(int i=1;i<=n;i++) {
        for(int j=i;j<=n;j++) 
            if(sg[i].r>=sg[j].l) R[i]=j;
        for(int j=i;j>=1;j--)
            if(sg[j].r>=sg[i].l) L[i]=j;
    }
    memset(val,0,sizeof(val));
    memset(cnt,0,sizeof(cnt));
    for(int i=n;i>=1;i--) {
        for(int j=R[i];j<=n;j++) cnt[j]++;
        for(int j=i;j<=n;j++) val[i][j]+=cnt[j];
    }
    for(int i=1;i<=n;i++) {
        int col=0,pd=1;
        for(int j=1;j<=i;j++) if(sg[j].r>=sg[i].l) {
            if(sg[j].c) {
                if(col&&sg[j].c!=col) { pd=0; break; }
                col=sg[j].c;
            }
        }
        if(!pd) yep[i]=-1;
        else yep[i]=col;
    }
    memset(f,-0x3f,sizeof(f));
    f[0][0]=0;
    int ans=0;
    for(int i=0;i<=n;i++)
        for(int c=1;c<=200;c++) {
            if(yep[i]==c||!yep[i]) {
                if(!yep[i]) Max(f[i][c],f[i][0]);
                Max(ans,f[i][c]);
                for(int j=i+1;j<=n;j++) {
                    if(!(yep[j]==c||!yep[j]))  break;
                    Max(f[j][c],f[i][c]+val[i+1][j]+(R[i]>i&&R[i]<=j));
                }
                for(int j=i+1;j<=n;j++) if(~yep[j]) {
                    if(L[j]>i) Max(f[j][yep[j]],f[i][c]+(R[j]==j));
                    else if(sg[j].c==c||!sg[j].c) Max(f[j][c],f[i][c]+(R[j]==j));
                }
            }
        }
    cout<<ans<<endl;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int T; cin>>T;
    while(T--) solve();

    #ifdef xxzx
   cerr<<"Time: "<<clo<<"MS"<<endl;
   cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
1
6
132 426 147
93 136 141
55 70 0
345 429 183
138 205 0
28 265 147

1
6
5 11 2
4 6 1
2 3 0
10 12 3
7 8 0
1 9 2

1
5
2 3 1
8 9 1
5 7 2
1 10 1
4 6 3
*/