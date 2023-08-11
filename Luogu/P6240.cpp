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
const int N=2e5+10;
bool mem1;
int n,m,h[N],w[N],L[N],R[N],t[N],f[N][210],ans[N];
vector<int> seg[N<<2];
void insert(int id,int l,int r,int v) {
	int mid=(l+r)>>1;
	if(l==r) seg[id].push_back(v);
	else if(R[v]<=mid) insert(ls,l,mid,v);
	else if(L[v]>mid) insert(rs,mid+1,r,v);
	else seg[id].push_back(v);
}
void solve(int id,int l,int r) {
	if(l==r) {
		for(auto i:seg[id]) ans[i]=(t[i]>=h[l])? w[l]:0;
		return;
	}
	int mid=(l+r)>>1;
	solve(ls,l,mid), solve(rs,mid+1,r);
	for(int i=0;i<=200;i++) {
		f[mid][i]=f[mid+1][i]=0;
		if(i>=h[mid]) f[mid][i]=w[mid];
		if(i>=h[mid+1]) f[mid+1][i]=w[mid+1];
	}
	for(int i=mid-1;i>=l;i--) {
		for(int j=0;j<=200;j++) f[i][j]=f[i+1][j];
		for(int j=h[i];j<=200;j++) f[i][j]=max(f[i][j],f[i+1][j-h[i]]+w[i]);
	}
	for(int i=mid+2;i<=r;i++) {
		for(int j=0;j<=200;j++) f[i][j]=f[i-1][j];
		for(int j=h[i];j<=200;j++) f[i][j]=max(f[i][j],f[i-1][j-h[i]]+w[i]);
	}
	for(auto i:seg[id]) {
		for(int j=0;j<=t[i];j++) ans[i]=max(ans[i],f[L[i]][j]+f[R[i]][t[i]-j]);
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>h[i];
	for(int i=1;i<=n;i++) cin>>w[i];
	for(int i=1;i<=m;i++) {
		cin>>L[i]>>R[i]>>t[i];
		insert(1,1,n,i);
	}
	solve(1,1,n);
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

