#include <bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,m,s[N<<2];
double mx[N<<2];
int update(double x,int id,int l,int r) {
    if(l==r) return (mx[id]>x);
    int mid=(l+r)>>1;
    if(mx[ls]<=x) return update(x,rs,mid+1,r);
    else return update(x,ls,l,mid)+s[id]-s[ls];
}
void Modify(int id,int l,int r,int x,int y) {
    if(l==r) return mx[id]=1.*y/l, s[id]=1, void();
    int mid=(l+r)>>1;
    if(x<=mid) Modify(ls,l,mid,x,y);
    else Modify(rs,mid+1,r,x,y);
    mx[id]=max(mx[ls],mx[rs]);
    s[id]=s[ls]+update(mx[ls],rs,mid+1,r);
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m;
    for(int i=1,x,y;i<=m;i++) {
        cin>>x>>y;
        Modify(1,1,n,x,y);
        cout<<s[1]<<endl;
    }

    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    cerr<<"Time "<<clo<<"MS"<<endl;
    return 0;
}