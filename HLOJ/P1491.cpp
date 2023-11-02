#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
const ll Mod=998244353;
bool mem1;
int n,q,B;
vector<ll> v[N];
map<PII,ll> mp;
ll calc(int x,int y) {
    if(x>y) swap(x,y);
    if(mp[make_pair(x,y)]) return mp[make_pair(x,y)];
    int l=max(v[x].size(),v[y].size())-1;
    ll res=0;
    for(int i=0;i<=l;i++)
        res=(res+v[x][i%v[x].size()]*v[y][i%v[y].size()])%Mod;
    return mp[make_pair(x,y)]=res;
}
vector<vector<ll>> s[N];
bool mem2;
int main() {
    freopen("list.in","r",stdin);
    freopen("list.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    for(int i=1,l;i<=n;i++) {
        cin>>l;
        for(int j=1,x;j<=l;j++) 
            cin>>x, v[i].push_back(x);
    }
    cin>>q;
    B=sqrt(q);
    for(int i=1;i<=n;i++) if((int)v[i].size()>B) {
        s[i].resize(B+1);
        for(int l=1;l<=B;l++) {
            s[i][l].resize(B+1);
           for(int j=0;j<(int)v[i].size();j++) {
                s[i][l][j%l]=(s[i][l][j%l]+v[i][j])%Mod;
            }
        }
    }
    for(int i=1,x,y;i<=q;i++) {
        cin>>x>>y;
        if(v[x].size()>v[y].size()) swap(x,y);
        if((int)v[x].size()<=B&&(int)v[y].size()>B) {
            ll res=0;
            for(int j=0;j<(int)v[x].size();j++)
                res=(res+v[x][j]*s[y][v[x].size()][j])%Mod;
            cout<<res<<endl;
        }
        else cout<<calc(x,y)<<endl;
    }

    #ifdef xxzx
    cerr<<"Time "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}