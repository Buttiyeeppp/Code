#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
bool mem1;
int n,dfn[N],low[N],tim,sta[N],top,col[N],tot;
vector<int> eg[N];
void tarjan(int x) {
    dfn[x]=low[x]=++tim;
    sta[++top]=x;
    for(auto y:eg[x]) {
        if(!dfn[y]) {
            tarjan(y);
            low[x]=min(low[x],low[y]);
        }
        else if(!col[y]) low[x]=min(low[x],dfn[y]);
    }
    if(dfn[x]==low[x]) {
        tot++;
        while(sta[top+1]!=x) {
            col[sta[top--]]=tot;
        }
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++)
        for(int j=1,x;j<=n;j++) {
            cin>>x;
            if(x) eg[i].push_back(j);
        }
    for(int i=1;i<=n;i++) if(!dfn[i]) tarjan(i);
    cout<<((tot==1)? "YES":"NO")<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}