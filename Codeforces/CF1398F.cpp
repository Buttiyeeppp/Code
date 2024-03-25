#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e6+10;
bool mem1;
int n,suf[N][4],fa[N];
string st;
vector<int> vc[N];
int find(int x) {
    if(x==fa[x]) return x;
    return fa[x]=find(fa[x]);
}
void merge(int x,int y) {
    fa[find(x)]=find(y);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>st;
    st=" "+st;
    suf[n+1][0]=suf[n+1][1]=suf[n+1][2]=n+1;
    for(int i=n;i>=1;i--) {
        if(st[i]=='?') st[i]='2';
        for(int j=0;j<=2;j++) suf[i][j]=suf[i+1][j];
        suf[i][st[i]-'0']=i;
    }
    for(int i=1;i<=n;i++) {
        int op=st[i]-'0';
        if(op==2) op=((suf[i][0]<suf[i][1])? 0:1);
        vc[suf[i][op^1]-i].push_back(i);
    }
    for(int i=1;i<=n+1;i++) fa[i]=i;
    for(int i=1;i<=n;i++) {
        int p=1,res=0;
        while(p<=n) {
            p=find(p);
            if(p>n) break;
            res++, p=p+i;
        }
        cout<<res<<" ";
        for(auto j:vc[i]) merge(j,j+1);
    }
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}