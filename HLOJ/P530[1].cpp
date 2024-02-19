#include <bits/stdc++.h>
#include <clocale>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;

typedef unsigned int uint;
int T, n, m, t; uint seed;
const int N=5e3+10;
bool a[N][N];

bool Rand(uint &x) {
    x^=x<<16;
    x^=x>>5;
    x^=x<<1;
    return (x&65535)<(uint)t;
}

int p[N][2],pre[N],nxt[N],d[N][N],cnt[N],gs[N];
int w(int x) {
    if(!cnt[x]) return 0;
    int r=(cnt[x]==1)? nxt[x]:x;
    return (x-pre[x])*(m-r+1);
}
bool mem2;
int main() {
    freopen("potato.in","r",stdin);
    freopen("potato.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>t>>seed;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) a[i][j]=Rand(seed);

    ll ans=0;
    for(int i=1;i<=n;i++) {
        int ed=0;
        for(int j=1;j<=m;j++) {
            if(a[i][j]) p[j][1]=p[j][0], p[j][0]=i;
            if(p[j][0]) {
                if(p[j][1]) d[p[j][1]][++gs[p[j][1]]]=j, cnt[j]++;
                d[p[j][0]][++gs[p[j][0]]]=j, cnt[j]++;
                nxt[ed]=j, pre[j]=ed, ed=j;
            }
        }
        nxt[ed]=m+1, pre[m+1]=ed;
        ll res=0;
        for(int j=1;j<=m;j++) if(cnt[j]) res+=w(j);
        for(int j=1;j<=i;j++) {
            ans+=res;
            while(gs[j]) {
                int l=d[j][gs[j]--];
                if(cnt[l]==2) {
                    res-=w(l), cnt[l]--, res+=w(l);
                }
                else {
                    res-=w(l)+w(pre[l])+w(nxt[l]);
                    cnt[l]--, nxt[pre[l]]=nxt[l], pre[nxt[l]]=pre[l];
                    res+=w(pre[l])+w(nxt[l]);
                    pre[l]=nxt[l]=0;
                }
            }
        }
    }
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}