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
bool mem1;
int n,a[N],f[N][22],q,L[N],R[N],b[22],ans[N];
vector<int> qry[N<<2];
void insert(int id,int l,int r,int x) {
	int mid=(l+r)>>1;
	if(l==r) qry[id].push_back(x);
	else if(R[x]<=mid) insert(ls,l,mid,x);
	else if(L[x]>mid) insert(rs,mid+1,r,x);
	else qry[id].push_back(x);
}
void solve(int id,int l,int r) {
	if(l==r) {
		for(auto i:qry[id]) ans[i]=a[l];
		return;
	}
	int mid=(l+r)>>1;
	solve(ls,l,mid), solve(rs,mid+1,r);
	for(int i=0;i<=20;i++) f[mid][i]=f[mid+1][i]=0;
	for(int i=20;i>=0;i--)
		if((1<<i)&a[mid]) { f[mid][i]=a[mid]; break; }
	for(int i=20;i>=0;i--)
		if((1<<i)&a[mid+1]) { f[mid+1][i]=a[mid+1]; break; }
	for(int i=mid-1;i>=l;i--) {
		for(int j=0;j<=20;j++) f[i][j]=f[i+1][j];
		int v=a[i];
		for(int j=20;j>=0;j--) if((1<<j)&v) {
			if(f[i][j]) v^=f[i][j];
			else { f[i][j]=v; break; }
		}
	}
	for(int i=mid+2;i<=r;i++) {
		for(int j=0;j<=20;j++) f[i][j]=f[i-1][j];
		int v=a[i];
		for(int j=20;j>=0;j--) if((1<<j)&v) {
			if(f[i][j]) v^=f[i][j];
			else { f[i][j]=v; break; }
		}
	}
	for(auto i:qry[id]) {
		for(int j=0;j<=20;j++) b[j]=f[R[i]][j];
		for(int j=20;j>=0;j--) if(f[L[i]][j]) {
			int v=f[L[i]][j];
			for(int k=20;k>=0;k--) if((1<<k)&v) {
				if(b[k]) v^=b[k];
				else { b[k]=v; break; }
			}
		}
		for(int j=20;j>=0;j--) if(ans[i]<(ans[i]^b[j])) ans[i]^=b[j];
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	cin>>q;
	for(int i=1;i<=q;i++) cin>>L[i]>>R[i], insert(1,1,n,i);
	solve(1,1,n);
	for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

