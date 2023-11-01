#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
vector<int> eg[N];
int n,f[N][22];
void dfs(int x,int from) {
    int s[22];
    memset(s,0,sizeof(s));
    for(auto y:eg[x]) if(y!=from) {
        dfs(y,x);
        for(int i=1;i<=20;i++) s[i]+=f[y][i];
    }
    int p=1;
    for(int i=1;i<=20;i++) if(s[i]>=2) p=i;
    for(int i=p;i<=20;i++) if(!s[i]) {
        f[x][i]=1;
        for(int j=i+1;j<=20;j++) f[x][j]+=s[j];
        return;
    }
}
bool mem2;
int main() {
    freopen("tree.in","r",stdin);
    freopen("tree.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1,x,y;i<n;i++) {
        cin>>x>>y;
        eg[x].push_back(y), eg[y].push_back(x);
    }
    dfs(1,0);
    int ans=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=20;j++) if(f[i][j]) ans=max(ans,j);
    cout<<ans<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}
/*
设每个点删除时间为t_i,
搬到树上看，合法等价于对于任意i,j满足t_i=t_j，i,j路径上存在k，t_k>t_i
按照点分治的思想，可以做到树高为log级别，因此答案是log级别。
设f_{i,s}为点i，它子树内还未满足条件的点集（即未找到对应的路径上的k）
贪心的思想，其实每次我们都会填能填的点中最小的，转移就不难了。
*/