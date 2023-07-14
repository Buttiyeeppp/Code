#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
#define ls (id<<1)
#define rs (id<<1|1)
using ll=long long;
using PII=pair<int,int>;
const int N=60;
const int M=2e4+10;
bool mem1;
int n,m,k,a[N][M],s[N][M],f[N][M],v[M<<2],lz[M<<2];
void Build(int id,int l,int r,int i) {
	lz[id]=0;
	if(l==r)
		return v[id]=f[i-1][l]-(l>k? 0:s[i][k]-s[i][l-1]), void();
	int mid=(l+r)>>1;
	Build(ls,l,mid,i), Build(rs,mid+1,r,i);
	v[id]=max(v[ls],v[rs]);
}
void pushdown(int id) {
	if(!lz[id]) return;
	int val=lz[id]; lz[id]=0;
	v[ls]+=val, lz[ls]+=val;
	v[rs]+=val, lz[rs]+=val;
}
void Modify(int id,int l,int r,int x,int y,int val) {
	if(x<=l&&y>=r) return v[id]+=val, lz[id]+=val, void();
	int mid=(l+r)>>1;
	pushdown(id);
	if(x<=mid) Modify(ls,l,mid,x,y,val);
	if(y>mid) Modify(rs,mid+1,r,x,y,val);
	v[id]=max(v[ls],v[rs]);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>a[i][j], s[i][j]=s[i][j-1]+a[i][j];
	for(int i=1;i+k-1<=m;i++) f[1][i]=s[1][i+k-1]-s[1][i-1]+s[2][i+k-1]-s[2][i-1];
	for(int i=2;i<=n;i++) {
		Build(1,1,m-k+1,i);
		for(int j=1;j+k-1<=m;j++) {
			f[i][j]=s[i][j+k-1]-s[i][j-1]+s[i+1][j+k-1]-s[i+1][j-1]+v[1];
//			cerr<<i<<" "<<j<<" "<<f[i][j]<<" "<<v[1]<<endl;
			if(j+k-1<m) {
				Modify(1,1,m-k+1,max(1,j-k+1),j,a[i][j]);
				Modify(1,1,m-k+1,j+1,min(j+k,m-k+1),-a[i][j+k]);
			}
		}
	}
	int ans=0;
	for(int i=1;i+k-1<=m;i++) ans=max(ans,f[n][i]);
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

