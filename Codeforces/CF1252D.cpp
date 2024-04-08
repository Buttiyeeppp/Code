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
int n,m,Q,ch[N][30],fail[N],tot,ed[N];
string a[N];
void insert(string &s,int f) {
    int p=0;
    for(int i=0;i<(int)s.size();i++) {
        if(!ch[p][s[i]-'A']) ch[p][s[i]-'A']=++tot;
        p=ch[p][s[i]-'A'];
    }
    ed[f]=p;
}
vector<int> eg[N];
void Buildfail() {
    queue<int> q;
    for(int i=0;i<26;i++)
        if(ch[0][i]) q.push(ch[0][i]);
    while(q.size()) {
        int x=q.front(); q.pop();
        for(int i=0;i<26;i++) {
            if(ch[x][i]) fail[ch[x][i]]=ch[fail[x]][i], q.push(ch[x][i]);
            else ch[x][i]=ch[fail[x]][i];
        }
    }
}
int v[N];
void calc(char *s,int len,int f) {
    int p=0;
    for(int i=1;i<=len;i++) {
        p=ch[p][s[i]-'A'];
        v[p]+=f;
    }
}
void dfs(int x) { for(auto y:eg[x]) dfs(y), v[x]+=v[y]; }
char A[N],B[N],C[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>Q;
    for(int i=1;i<=n;i++) cin>>a[i], a[i]=" "+a[i];
    for(int i=1;i<=Q;i++) {
        string s; cin>>s;
        insert(s,i);
    }
    Buildfail();
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m;j++) {
            int l1=0,l2=0,l3=0;
            for(int k=1;k<j;k++) A[++l1]=a[i][k], C[++l3]=a[i][k];
            C[++l3]=a[i][j];
            for(int k=i+1;k<=n;k++) B[++l2]=a[k][j], C[++l3]=a[k][j];
            calc(C,l3,+1), calc(A,l1,-1), calc(B,l2,-1);
        }
    }
    for(int i=1;i<=tot;i++) eg[fail[i]].push_back(i);
    dfs(0);
    for(int i=1;i<=Q;i++) cout<<v[ed[i]]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}