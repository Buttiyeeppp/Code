#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=4e5+10;
bool mem1;
int n,m,ans[N];
struct {
	int op,x,y,s;
}q[N],a[N],b[N];
int s[N];
int lowbit(int x) { return x&-x; }
void add(int x,int v) { for(int i=x;i<=200000;i+=lowbit(i)) s[i]+=v; }
int qry(int x) {
	if(!x) return 0;
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
void solve(int st,int ed,int l,int r) {
	if(l==r) {
		for(int i=st;i<=ed;i++) ans[l]+=(!q[i].op);
		return;
	}
	int mid=(l+r)>>1,tot1=0,tot2=0;
	for(int i=st;i<=ed;i++) {
		if(q[i].op) {
			if(q[i].y<=mid) add(q[i].x,1), a[++tot1]=q[i];
			else b[++tot2]=q[i];
		}
		else {
			int v=qry(q[i].y)-qry(q[i].x-1);
			if(v<q[i].s) q[i].s-=v, b[++tot2]=q[i];
			else a[++tot1]=q[i];
		}
	}
	for(int i=1;i<=tot1;i++) if(a[i].op) add(a[i].x,-1);
	for(int i=1;i<=tot1;i++) q[i+st-1]=a[i];
	for(int i=1;i<=tot2;i++) q[i+st+tot1-1]=b[i];
	if(tot1) solve(st,st+tot1-1,l,mid);
	if(tot2) solve(st+tot1,ed,mid+1,r);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=m+1;i<=m+n;i++) cin>>q[i].x>>q[i].y>>q[i].s, q[i].op=0;
	for(int i=1;i<=m;i++) cin>>q[i].x, q[i].op=1, q[i].y=i;
	solve(1,n+m,1,m+1);
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

