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
const int N=1e3+10;
bool mem1;
int a[N][N],n,r[N],c[N],ans=INT_MAX,X[3*N*N],m;
struct node {
	int i,j,z;
	bool operator<(const node &q)const {
		return z<q.z;
	}
}v[N*N];
struct SegmentTree {
	int z[N<<2];
	void Build(int id,int l,int r,int v) {
		z[id]=v;
		if(l==r) return;
		int mid=(l+r)>>1;
		Build(ls,l,mid,v), Build(rs,mid+1,r,v);
	}
	void Modify(int id,int l,int r,int x,int v) {
		if(l==r) return z[id]+=v, void();
		int mid=(l+r)>>1;
		if(x<=mid) Modify(ls,l,mid,x,v);
		else Modify(rs,mid+1,r,x,v);
		z[id]=min(z[ls],z[rs]);
	}
}s1,s2;
int p1=1,p2=0,p3=0,p4=1;
void calc(int x) {
	/*
		res1= [p1,n]
		res2= [1,p2]
	*/
	while(p1<=n&&r[p1]<=x) p1++;
	while(p2<n&&c[p2+1]<x) p2++;
	while(p3<m&&v[p3+1].z<x) {
		p3++;
		s1.Modify(1,1,n,v[p3].i,1);
	}
	while(p4<=m&&v[p4].z<=x) {
		s2.Modify(1,1,n,v[p4].j,-1);
		p4++;
	}
	int res1=n-p1+1, res2=p2, v1=s1.z[1], v2=s2.z[1];
	ans=min(ans,(res1? res1:v1)+(res2? res2:v2));
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) cin>>a[i][j], v[++m]={i,j,a[i][j]};
	}
	for(int i=1;i<=n;i++) {
		r[i]=INT_MAX;
		for(int j=1;j<=n;j++) r[i]=min(r[i],a[i][j]);
	}
	for(int j=1;j<=n;j++) {
		c[j]=-1;
		for(int i=1;i<=n;i++) c[j]=max(c[j],a[i][j]);
	}
	int tot=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) X[++tot]=a[i][j], X[++tot]=a[i][j]-1, X[++tot]=a[i][j]+1;
	sort(X+1,X+tot+1); tot=unique(X+1,X+tot+1)-X-1;
	sort(r+1,r+n+1), sort(c+1,c+n+1), sort(v+1,v+m+1);
	s1.Build(1,1,n,0), s2.Build(1,1,n,n);
	for(int i=1;i<=tot;i++) calc(X[i]);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

