#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4100;
bool mem1;
struct node {
    int n;
    vector<int> a,p;
    vector<vector<int>> bh;
    node(){ n=0; }
};
int n,Q,a[N],p[N],cnt;
vector<PII> op;
void sol(node &nd,int l,int r) {
    int m=nd.n;
    nd.bh.resize(m+1);
    for(int i=1;i<=m;i++) nd.bh[i].resize(m+1);
    if(m==1) return nd.bh[1][1]=nd.p[1], void();
    int mid=(l+r)>>1;
    node x,y; 
    x.a.resize(1), y.a.resize(1);
    x.p.resize(1), y.p.resize(1);
    for(int i=1;i<=m;i++) {
        if(nd.a[i]<=mid) x.a.push_back(nd.a[i]), x.p.push_back(nd.p[i]);
        else y.a.push_back(nd.a[i]), y.p.push_back(nd.p[i]);
    }
    x.n=x.a.size()-1, y.n=y.a.size()-1;
    sol(x,l,mid), sol(y,mid+1,r);
    
    for(int i=1;i<=m;i++) {
        int l1=1,l2=1;
        while(l1<=x.n&&x.p[l1]<nd.p[i]) l1++;
        while(l2<=y.n&&y.p[l2]<nd.p[i]) l2++;
        int r1=l1-1,r2=l2-1;
        for(int j=i;j<=m;j++) {
            while(r1<x.n&&x.p[r1+1]<=nd.p[j]) r1++;
            while(r2<y.n&&y.p[r2+1]<=nd.p[j]) r2++;
            if(l1<=r1&&l2<=r2) {
                op.emplace_back(x.bh[l1][r1],y.bh[l2][r2]);
                nd.bh[i][j]=++cnt;
            }
            else if(l1<=r1) nd.bh[i][j]=x.bh[l1][r1];
            else nd.bh[i][j]=y.bh[l2][r2];
        }
    }
}
node d[N];
int pre[N][N],suf[N][N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>Q;
    int B=sqrt(Q)+1; cnt=n;
    for(int i=1;i<=n;i++) cin>>a[i], p[i]=i;
    sort(p+1,p+n+1,[](const int &x,const int &y){ return a[x]<a[y]; });
    for(int l=1,r=min(B,n);l<=n;l=r+1,r=min(l+B-1,n)) {
        int L=a[p[l]],R=a[p[r]],f=(l-1)/B;
        sort(p+l,p+r+1);
        d[f].a.resize(1), d[f].p.resize(1), d[f].n=r-l+1;
        for(int i=l;i<=r;i++) d[f].a.push_back(a[p[i]]), d[f].p.push_back(p[i]);
        sol(d[f],L,R);

        pre[f][0]=1, suf[f][n+1]=r-l+1;
        for(int i=1;i<=n;i++) {
            pre[f][i]=pre[f][i-1];
            while(pre[f][i]<=d[f].n&&d[f].p[pre[f][i]]<i)  pre[f][i]++;
        }
        for(int i=n;i>=1;i--) {
            suf[f][i]=suf[f][i+1];
            while(suf[f][i]>=1&&d[f].p[suf[f][i]]>i) suf[f][i]--;
        }
    }
    vector<int> ans;
    for(int i=1,l,r;i<=Q;i++) {
        cin>>l>>r;
        int now=-1;
        for(int j=0;j<=(n-1)/B;j++) {
            int L=pre[j][l], R=suf[j][r];
            if(L<=R) {
                if(~now) op.emplace_back(now,d[j].bh[L][R]), now=++cnt;
                else now=d[j].bh[L][R];
            }
        }
        ans.push_back(now);
    }
    cout<<cnt<<endl;
    for(auto i:op) cout<<i.first<<" "<<i.second<<endl;
    for(auto i:ans) cout<<i<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}