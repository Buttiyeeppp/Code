#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=5e5+10;
const ll P=17;
const ll Mod=998244353;
bool mem1;
int n,a[N];
ll Pow[N];
struct SegmentTree {
	ll fi,se;
}s[N<<2];
void Build(int id,int l,int r) {
	s[id]={0,0};
	if(l==r) return;
	int mid=(l+r)>>1;
	Build(ls,l,mid), Build(rs,mid+1,r);
}
SegmentTree Plus(SegmentTree l,SegmentTree r,int x,int y) {
	return {(l.fi*Pow[y]+r.fi)%Mod,(l.se+r.se*Pow[x])%Mod};
}
void Modify(int id,int l,int r,int x) {
	if(l==r) return s[id]={1,1}, void();
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x);
	else Modify(rs,mid+1,r,x);
	s[id]=Plus(s[ls],s[rs],mid-l+1,r-mid);
}
SegmentTree Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return s[id];
	int mid=(l+r)>>1;
	if(y<=mid) return Query(ls,l,mid,x,y);
	if(x>mid) return Query(rs,mid+1,r,x,y);
	return Plus(Query(ls,l,mid,x,y),Query(rs,mid+1,r,x,y),mid-max(l,x)+1,min(r,y)-mid);
}
void solve() {
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	int pd=0;
	Build(1,1,n);
	for(int i=1;i<=n;i++) {
		ll l=min(a[i]-1,n-a[i]);
		if(l) {
			ll lhs=Query(1,1,n,a[i]-l,a[i]-1).fi, rhs=Query(1,1,n,a[i]+1,a[i]+l).se;
			pd|=(lhs!=rhs);
		}
		Modify(1,1,n,a[i]);
	}
	cout<<(pd? 'Y':'N')<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Pow[0]=1;
	for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*P%Mod;
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

