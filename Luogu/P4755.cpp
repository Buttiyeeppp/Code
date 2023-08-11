#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,a[N],mx[N][20],X[N],tot,b[N],Log[N];
int s[N*30],rt[N],ls[N*30],rs[N*30],cnt;
void Modify(int &id1,int id2,int l,int r,int x) {
	id1=++cnt, ls[id1]=ls[id2], rs[id1]=rs[id2], s[id1]=s[id2]+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	if(x<=mid) Modify(ls[id1],ls[id2],l,mid,x);
	else Modify(rs[id1],rs[id2],mid+1,r,x);
}
int Query(int id1,int id2,int l,int r,int x,int y) {
	if(!id2) return 0;
	if(x<=l&&y>=r) return s[id2]-s[id1];
	int mid=(l+r)>>1;
	int res=0;
	if(x<=mid) res+=Query(ls[id1],ls[id2],l,mid,x,y);
	if(y>mid) res+=Query(rs[id1],rs[id2],mid+1,r,x,y);
	return res;
}
ll ans;
int qry(int l,int r) {
	int _log=Log[r-l+1], L=mx[l][_log], R=mx[r-(1<<_log)+1][_log];
	return (a[L]>=a[R])? L:R;
}
void solve(int l,int r) {
	if(l==r) return ans+=(a[l]==1), void();
	int mid=qry(l,r);
	if(l<=mid-1) solve(l,mid-1);
	if(mid+1<=r) solve(mid+1,r);
	if(mid-l+1<=r-mid+1) {
		for(int i=l;i<=mid;i++) {
			int p=upper_bound(X+1,X+tot+1,a[mid]/a[i])-X-1;
			ans+=Query(rt[mid-1],rt[r],1,tot,1,p);
		}
	}
	else {
		for(int i=mid;i<=r;i++) {
			int p=upper_bound(X+1,X+tot+1,a[mid]/a[i])-X-1;
			ans+=Query(rt[l-1],rt[mid],1,tot,1,p);
		}
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], mx[i][0]=i, X[i]=a[i];
	for(int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) {
			int l=mx[i][j-1], r=mx[i+(1<<(j-1))][j-1];
			mx[i][j]=(a[l]>=a[r])? l:r;
		}
	sort(X+1,X+n+1); tot=unique(X+1,X+n+1)-X-1;
	for(int i=1;i<=n;i++) b[i]=lower_bound(X+1,X+tot+1,a[i])-X;
	for(int i=1;i<=n;i++) Modify(rt[i],rt[i-1],1,tot,b[i]);
	solve(1,n);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

