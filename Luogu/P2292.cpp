#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int nxt[N][30],tot,ed[N],fail[N],len[N];
unsigned int g[N];
void insert(string st) {
    int p=0;
    for(int i=0;i<(int)st.size();i++) {
        if(!nxt[p][st[i]-'a'])
            nxt[p][st[i]-'a']=++tot, len[nxt[p][st[i]-'a']]=len[p]+1;
        p=nxt[p][st[i]-'a'];
    }
    g[p]=1<<(st.size()-1);
}
void build() {
    queue<int> q;
    for(int i=0;i<26;i++) if(nxt[0][i]) q.push(nxt[0][i]);
    while(q.size()) {
        int p=q.front(); q.pop();
        g[p]|=g[fail[p]];
        for(int i=0;i<26;i++) {
            if(nxt[p][i]) fail[nxt[p][i]]=nxt[fail[p]][i], q.push(nxt[p][i]);
            if(!nxt[p][i]) nxt[p][i]=nxt[fail[p]][i];
        }
    }
}
int calc(string st) {
    unsigned int now=1;
    int p=0,mx=-1;
    for(int i=0;i<(int)st.size();i++) {
        p=nxt[p][st[i]-'a'];
        if(now&g[p]) mx=i, now=now<<1|1;
        else now<<=1;
    }
    return mx+1;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    int n,m; string s;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>s, insert(s);
    build();
    while(m--) {
        cin>>s;
        cout<<calc(s)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}