#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
bool mem1;
int n,Q,ch[N][30],fail[N],tot,ed[N];
string s[N];
void insert(string st,int i) {
    int p=0;
    for(int i=0;i<(int)st.size();i++) {
        if(!ch[p][st[i]-'a']) ch[p][st[i]-'a']=++tot;
        p=ch[p][st[i]-'a'];
    }
    ed[i]=p;
}
int dfn[N],mxdfn[N],tim;
vector<int> eg[N];
void BuildFail() {
    queue<int> q;
    for(int i=0;i<26;i++) 
        if(ch[0][i]) q.push(ch[0][i]);
    while(q.size()) {
        int x=q.front(); q.pop();
        for(int i=0;i<26;i++)  {
            if(ch[x][i])
                fail[ch[x][i]]=ch[fail[x]][i], eg[ch[fail[x]][i]].push_back(ch[x][i]), q.push(ch[x][i]);
            else ch[x][i]=ch[fail[x]][i];
        }
    }
}
void dfs(int x) {
    dfn[x]=++tim;
    for(auto y:eg[x]) dfs(y);
    mxdfn[x]=tim;
}
struct BIT {
    ll v[N];
    int lowbit(int x) { return x&-x; }
    void Add(int x,ll val) {
        for(int i=x;i<N;i+=lowbit(i)) v[i]+=val;
    }
    ll Qry(int x) {
        ll res=0;
        for(int i=x;i;i-=lowbit(i)) res+=v[i];
        return res;
    }
}bit;
ll ans[N];
vector<PII> q[N],nq[N];
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr),cout.tie(nullptr);

    cin>>n>>Q;
    int m=0;
    for(int i=1;i<=n;i++) 
        cin>>s[i], insert(s[i],i), m+=s[i].size();
    BuildFail();
    for(int i=1;i<=tot;i++) 
        if(!fail[i]) dfs(i);
    int B=m/sqrt(Q*log(m));
    for(int i=1,l,r,k;i<=Q;i++) {
        cin>>l>>r>>k;
        if((int)s[k].size()<=B) {
            q[l-1].emplace_back(k,-i);
            q[r].emplace_back(k,i);
        }
        else {
            nq[k].emplace_back(l-1,-i);
            nq[k].emplace_back(r,i);
        }
    }
    for(int i=1;i<=n;i++) {
        int p=ed[i];
        bit.Add(dfn[p],1), bit.Add(mxdfn[p]+1,-1);
        for(auto k:q[i]) {
            int tp=k.second, f=1;
            if(tp<0) tp=-tp, f=-1;
            for(int j=0,p=0;j<(int)s[k.first].size();j++) {
                p=ch[p][s[k.first][j]-'a'];
                ans[tp]+=f*bit.Qry(dfn[p]);
            }
        }
    }
    for(int i=1;i<=n;i++) {
        int p=ed[i];
        bit.Add(dfn[p],-1), bit.Add(mxdfn[p]+1,1);
    }
    for(int i=1;i<=n;i++) if(nq[i].size()) {
        for(int j=0,p=0;j<(int)s[i].size();j++) {
            p=ch[p][s[i][j]-'a'];
            bit.Add(dfn[p],1);
        }
        sort(nq[i].begin(),nq[i].end());
        ll l=0,res=0;
        for(auto k:nq[i]) {
            while(l<k.first) {
                int p=ed[++l];
                res+=(bit.Qry(mxdfn[p])-bit.Qry(dfn[p]-1));
            }
            int tp=k.second, f=1;
            if(tp<0) tp=-tp, f=-1;
            ans[tp]+=res*f;
        }
        for(int j=0,p=0;j<(int)s[i].size();j++) {
            p=ch[p][s[i][j]-'a'];
            bit.Add(dfn[p],-1);
        }
    }
    for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}