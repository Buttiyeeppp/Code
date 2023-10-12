#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,nxt[N][30],fail[N],tot,bh[N];
string t[N],s;
void insert(string st,int x) {
    int p=0;
    for(int i=0;i<(int)st.size();i++) {
        if(!nxt[p][st[i]-'a']) nxt[p][st[i]-'a']=++tot;
        p=nxt[p][st[i]-'a'];
    }
    bh[x]=p;
}
vector<int> eg[N];
void build() {
    queue<int> q;
    for(int i=0;i<26;i++) if(nxt[0][i]) q.push(nxt[0][i]);
    while(q.size()) {
        int p=q.front(); q.pop();
        eg[fail[p]].push_back(p);
        for(int i=0;i<26;i++) {
            if(nxt[p][i]) fail[nxt[p][i]]=nxt[fail[p]][i], q.push(nxt[p][i]);
            if(!nxt[p][i]) nxt[p][i]=nxt[fail[p]][i];
        }
    }
}
int v[N];
void calc() {
    int p=0;
    for(int i=0;i<(int)s.size();i++) {
        p=nxt[p][s[i]-'a'];
        v[p]++;
    }
}
void dfs(int x) {
    for(auto y:eg[x]) {
        dfs(y);
        v[x]+=v[y];
    }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1;i<=n;i++) cin>>t[i], insert(t[i],i);
    build();
    cin>>s;
    calc(), dfs(0);
    for(int i=1;i<=n;i++) cout<<v[bh[i]]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}