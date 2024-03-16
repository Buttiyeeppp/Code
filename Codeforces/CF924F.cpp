#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=2e4+10;
bool mem1;
ll f[10][19][N];
bitset<91> g[N];
map<pair<ull,ull>,int> mp;
pair<ull,ull> hs(bitset<91> x) {
    ull res1=0,res2=0;
    for(int i=0;i<=90;i++) {
        if(i<60) res1=(res1<<1)+x[i];
        else res2=(res2<<1)+x[i];
    }
    return {res1,res2};
}
int len[N],nx[N][10],ans[N],cnt;
int nxt(int x,int c) {
    bitset<91> v1=g[x], v2=(v1<<c)|(v1>>c);
    for(int i=0;i<c;i++) 
        if(v1[i]) v2[c-i]=1;
    if(!mp[hs(v2)]) {
        mp[hs(v2)]=++cnt, g[cnt]=v2;
        len[cnt]=len[x]+1;
        int chk=0;
        for(int i=0;i<=10;i++) if(v2[i]) {
            chk=1;
            ans[cnt]=i; break;
        }
        assert(chk==1);
    }
    return mp[hs(v2)];
}
void init() {
    g[1]=cnt=1, ans[1]=len[1]=0;
    mp[hs(g[1])]=1;
    for(int i=1;i<=cnt;i++) {
        if(len[i]==18) continue;
        for(int c=0;c<=9;c++) nx[i][c]=nxt(i,c);
    }
    vector<int> vc[11];
    for(int i=1;i<=cnt;i++) vc[ans[i]].push_back(i);
    for(int i=0;i<=9;i++) {
        for(int c=0;c<=i;c++) for(auto j:vc[c]) f[i][0][j]=1;
        for(int l=1;l<=18;l++) for(int j=1;j<=cnt;j++) {
            for(int c=0;c<=9;c++) f[i][l][j]+=f[i][l-1][nx[j][c]];
        }
    }
}
ll calc(ll v,int k) {
    if(k>=9) return v;
    vector<int> vc;
    while(v) vc.push_back(v%10), v/=10;
    reverse(vc.begin(),vc.end());
    int p=1;
    ll ans=0;
    for(int i=0;i<(int)vc.size();i++) {
        for(int c=0;c<vc[i];c++) ans+=f[k][vc.size()-i-1][nx[p][c]];
        p=nx[p][vc[i]];
    }
    ans+=f[k][0][p];
    return ans;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    init();
    int T; cin>>T;
    while(T--) {
        ll l,r,k;
        cin>>l>>r>>k;
        cout<<calc(r,k)-calc(l-1,k)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}