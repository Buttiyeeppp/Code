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
const ll Mod=1e9;
const int N=5e5+10;
bool mem1;
int n,a[N],st[2][N],top[2];
int lzmn[N<<2],lzmx[N<<2];
int s[N<<2],smx[N<<2],smn[N<<2];
int q[N<<2],qmx[N<<2],qmn[N<<2];
void pushdown(int id,int l,int r) {
	if(!lzmn[id]&&!lzmx[id]) return;
	int mid=(l+r)>>1;
	if(lzmx[id]) {
		ll v=lzmx[id]; lzmx[id]=0;
		lzmx[ls]=v, smx[ls]=v*(mid-l+1)%Mod, s[ls]=smn[ls]*v%Mod;
		qmx[ls]=(v*(l+mid)*(mid-l+1)/2)%Mod, q[ls]=qmn[ls]*v%Mod;
		lzmx[rs]=v, smx[rs]=v*(r-mid)%Mod, s[rs]=smn[rs]*v%Mod;
		qmx[rs]=(v*(mid+1+r)*(r-mid)/2)%Mod, q[rs]=qmn[rs]*v%Mod;
	}
	if(lzmn[id]) {
		ll v=lzmn[id]; lzmn[id]=0;
		lzmn[ls]=v, smn[ls]=v*(mid-l+1)%Mod, s[ls]=smx[ls]*v%Mod;
		qmn[ls]=(v*(l+mid)*(mid-l+1)/2)%Mod, q[ls]=qmx[ls]*v%Mod;
		lzmn[rs]=v, smn[rs]=v*(r-mid)%Mod, s[rs]=smx[rs]*v%Mod;
		qmn[rs]=(v*(mid+1+r)*(r-mid)/2)%Mod, q[rs]=qmx[rs]*v%Mod;
	}
}
void Modify(int id,int l,int r,int x,int y,ll v,int op) {
	if(x<=l&&y>=r) {
		if(!op) lzmx[id]=v, smx[id]=v*(r-l+1)%Mod, s[id]=smn[id]*v%Mod,
				qmx[id]=(v*(l+r)*(r-l+1)/2)%Mod, q[id]=qmn[id]*v%Mod;
		else lzmn[id]=v, smn[id]=v*(r-l+1)%Mod, s[id]=smx[id]*v%Mod,
			qmn[id]=(v*(l+r)*(r-l+1)/2)%Mod, q[id]=qmx[id]*v%Mod;
		return;
	}
	pushdown(id,l,r);
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls,l,mid,x,y,v,op);
	if(y>mid) Modify(rs,mid+1,r,x,y,v,op);
	smn[id]=(smn[ls]+smn[rs])%Mod, smx[id]=(smx[ls]+smx[rs])%Mod;
	s[id]=(s[ls]+s[rs])%Mod;
	qmn[id]=(qmn[ls]+qmn[rs])%Mod, qmx[id]=(qmx[ls]+qmx[rs])%Mod;
	q[id]=(q[ls]+q[rs])%Mod;
}
ll Query(int id,int l,int r,int x,int y,int op) {
	if(x<=l&&y>=r) return (!op)? s[id]:q[id];
	int mid=(l+r)>>1;
	pushdown(id,l,r);
	if(y<=mid) return Query(ls,l,mid,x,y,op);
	else if(x>mid) return Query(rs,mid+1,r,x,y,op);
	else return (Query(ls,l,mid,x,y,op)+Query(rs,mid+1,r,x,y,op))%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	ll ans=0;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		while(top[0]&&a[st[0][top[0]]]<a[i]) top[0]--;
		while(top[1]&&a[st[1][top[1]]]>a[i]) top[1]--;
		Modify(1,1,n,st[0][top[0]]+1,i,a[i],0);
		Modify(1,1,n,st[1][top[1]]+1,i,a[i],1);
		st[0][++top[0]]=st[1][++top[1]]=i;
		ans=(ans+(i+1)*Query(1,1,n,1,i,0))%Mod;
		ans=(ans-Query(1,1,n,1,i,1)+Mod)%Mod;
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
