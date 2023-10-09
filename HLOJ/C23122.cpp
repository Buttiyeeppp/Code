#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const ll P=1331;
const ll Mod=1e9+7;
bool mem1;
string s;
ll p[N],hs[N],Pow[N],n;
ll Hash(int x,int y) {
    return (hs[y]-hs[x-1]*Pow[y-x+1]%Mod+Mod)%Mod;
}
bool small(int x,int y) { // [x,n]<[y,n]
    int l=0,r=min(n-x+1,n-y+1)+1;
    while(l+1<r) {
        int mid=(l+r)>>1;
        if(Hash(x,x+mid-1)==Hash(y,y+mid-1)) l=mid;
        else r=mid;
    }
    if(x+l-1==n||y+l-1==n) return (x+l-1==n);
    return (s[x+l]<s[y+l]);
}
bool small2(int op,int x,int y) { // [y,n]+[y,n]
    int l=0,r=min(n-x+1,2*(n-y+1))+1;
    while(l+1<r) {
        int mid=(l+r)>>1;
        if(y+mid-1<=n) {
            if(Hash(x,x+mid-1)==Hash(y,y+mid-1)) l=mid;
            else r=mid;
        }
        else {
            if(Hash(x,x+mid-1)==(Hash(y,n)*Pow[y+mid-1-n]+Hash(y,y+(y+mid-1-n)-1))%Mod) l=mid;
            else r=mid;
        }
    }
    if(l==(n-y+1)*2) return op;
    if(x+l-1==n) return true;
    if(y+l<=n) return (s[x+l]<s[y+l]);
    else return (s[x+l]<s[y+(y+l-n)-1]);
}
vector<PII> q[N];
int v[N],ans[N];
void Add(int x,int val) {
    for(int i=x;i<=n;i+=i&-i) v[i]+=val;
}
int Qry(int x) {
    int res=0;
    for(int i=x;i;i-=i&-i) res+=v[i];
    return res;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>s;
    n=s.size(); s=" "+s;
    Pow[0]=1;
    for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*P%Mod;
    for(int i=1;i<=n;i++) p[i]=i, hs[i]=(hs[i-1]*P+(s[i]-'a'+1))%Mod;
    sort(p+1,p+n+1,[](const int &x,const int &y) {return small(x,y); });
    for(int i=n;i>=1&&(n-i+1)*3<n;i--) {
        int l=0,r=n+1;
        while(l+1<r) {
            int mid=(l+r)>>1;
            if(small2(0,p[mid],i)) l=mid;
            else r=mid;
        }
        q[l+1].push_back({1,n-i+1});
        // cerr<<"< "<<i<<" "<<l<<endl;
        l=0,r=n+1;
        while(l+1<r) {
            int mid=(l+r)>>1;
            if(small2(1,p[mid],i)) l=mid;
            else r=mid;
        }
        q[l+1].push_back({-1,n-i+1});
        // cerr<<"<= "<<i<<" "<<l<<endl;
    }
    for(int i=1;i<=n;i++) {
        for(auto now:q[i]) {
            Add(3*now.second,now.first);
        }
        ans[p[i]]=Qry(n-p[i]);
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    cout<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}