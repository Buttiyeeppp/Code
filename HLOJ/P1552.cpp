#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n,m,k;
vector<PII> nd[2];
const int N=2e3+10;
int a[N][N];
bool chk() {
    if((int)nd[0].size()+(int)nd[1].size()!=n*m) return false;
    int cnt=0;
    for(int f:{0,1})
        for(auto i:nd[f]) a[i.first][i.second]=f, cnt+=f;
    cnt=min(cnt,n*m-cnt);
    if(cnt!=n*m/2) return false;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            if(i+k-1<=n) {
                int pd=1;
                for(int d=0;d<k;d++) pd&=a[i+d][j];
                if(pd) return false;
            }
            if(j+k-1<=m) {
                int pd=1;
                for(int d=0;d<k;d++) pd&=a[i][j+d];
                if(pd) return false;
            }
            if(i+k-1<=n&&j+k-1<=m) {
                int pd=1;
                for(int d=0;d<k;d++) pd&=a[i+d][j+d];
                if(pd) return false;
            }
            if(i-k+1<=n&&j+k-1<=m) {
                int pd=1;
                for(int d=0;d<k;d++) pd&=a[i-d][j+d];
                if(pd) return false;
            }
        }
    return true;
}
void out() {
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) {
            // int f=(((j-1)/2)&1)^(i&1);
            int f=(i+j/2)%2;
            // cerr<<j<<" "<<f<<endl;
            nd[f].emplace_back(i,j);
        }
    if(nd[0].size()>nd[1].size()) swap(nd[0],nd[1]);
    if(nd[0].size()<nd[1].size()) cout<<nd[1].back().first<<" "<<nd[1].back().second<<endl;
    for(int i=0;i<(int)nd[0].size();i++)
        cout<<nd[0][i].first<<" "<<nd[0][i].second<<endl,
        cout<<nd[1][i].first<<" "<<nd[1][i].second<<endl;
    // if(!chk()) cout<<"Wrong"<<endl;
}
bool mem2;
int main() {
    freopen("gomoku.in","r",stdin);
    freopen("gomoku.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>k;
    if(k==1) cout<<-1<<endl;
    else if(n==1) {
        for(int i=1;i<=m;i++) cout<<"1 "<<i<<endl;
    }
    else if(m==1) {
        for(int i=1;i<=n;i++) cout<<i<<" 1"<<endl;
    }
    else if(k==2) cout<<-1<<endl;   
    else out();

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}