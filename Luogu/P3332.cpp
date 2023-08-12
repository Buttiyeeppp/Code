#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
#define ls (id<<1)
#define rs (id<<1|1)
#define int long long
using ll=long long;
using PII=pair<int,int>;
const int N=5e4+10;
bool mem1;
int n,m,ans[N];
struct query {
	int id,op,l,r; ll c;
}q[N],a[N],b[N];
ll s[N<<2],lz[N<<2];
void pushdown(int id,int l,int r) {
	if(!lz[id]) return;
	ll v=lz[id], mid=(l+r)>>1; lz[id]=0;
	lz[ls]+=v, s[ls]+=(mid-l+1)*v;
	lz[rs]+=v, s[rs]+=(r-mid)*v;
}
void Modify(int id,int l,int r,int x,int y,ll v) {
	if(x<=l&&y>=r) return s[id]+=(r-l+1)*v, lz[id]+=v, void();
	pushdown(id,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x,y,v);
	if(y>mid) Modify(rs,mid+1,r,x,y,v);
	s[id]=s[ls]+s[rs];
}
ll Query(int id,int l,int r,int x,int y) {
	if(x<=l&&y>=r) return s[id];
	pushdown(id,l,r);
	int mid=(l+r)>>1;
	if(y<=mid) return Query(ls,l,mid,x,y);
	else if(x>mid) return Query(rs,mid+1,r,x,y);
	else return Query(ls,l,mid,x,y)+Query(rs,mid+1,r,x,y);
}
void sol(int st,int ed,int l,int r) {
	if(l==r) {
		for(int i=st;i<=ed;i++)
			if(q[i].op==2) ans[q[i].id]=l;
		return;
	}
	int mid=(l+r)>>1, tot1=0, tot2=0;
	for(int i=st;i<=ed;i++) {
		if(q[i].op==1) {
			if(q[i].c>mid) {
				Modify(1,1,n,q[i].l,q[i].r,1);
				b[++tot2]=q[i];
			}
			else a[++tot1]=q[i];
		}
		else {
			ll v=Query(1,1,n,q[i].l,q[i].r);
			if(v>=q[i].c) b[++tot2]=q[i];
			else q[i].c-=v, a[++tot1]=q[i];
		}
	}
	for(int i=1;i<=tot2;i++) if(b[i].op==1) Modify(1,1,n,b[i].l,b[i].r,-1);
	for(int i=1;i<=tot1;i++) q[st+i-1]=a[i];
	for(int i=1;i<=tot2;i++) q[st+tot1+i-1]=b[i];
	if(tot1) sol(st,st+tot1-1,l,mid);
	if(tot2) sol(st+tot1,ed,mid+1,r);
}
bool mem2;
signed main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int Q=0;
	for(int i=1;i<=m;i++) {
		cin>>q[i].op>>q[i].l>>q[i].r>>q[i].c;
		if(q[i].op==2) q[i].id=++Q;
	}
	sol(1,m,-n,n);
	for(int i=1;i<=Q;i++) cout<<ans[i]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
