#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,a[N],mx[N][20],Log[N],pre[N],pos[N];
int qry(int l,int r) {
	int _log=Log[r-l+1], L=mx[l][_log], R=mx[r-(1<<_log)+1][_log];
	return (a[L]>=a[R])? L:R;
}
ll ans;
void solve(int l,int r) {
	if(l==r) return ans+=(a[l]==1), void();
	int mid=qry(l,r);
	if(l<=mid-1) solve(l,mid-1);
	if(mid+1<=r) solve(mid+1,r);
	if(mid-l+1<=r-mid+1) {
		for(int i=max(l,mid-a[mid]+1);i<=mid&&i+a[mid]-1<=r;i++) ans+=(pre[i+a[mid]-1]<i);
	}
	else {
		for(int i=max(mid,l+a[mid]-1);i<=r&&i-a[mid]+1<=mid;i++) ans+=(pre[i]<(i-a[mid]+1)); 
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i], pre[i]=max(pre[i-1],pos[a[i]]), pos[a[i]]=i, mx[i][0]=i;
	for(int i=2;i<=n;i++) Log[i]=Log[i>>1]+1;
	for(int j=1;j<20;j++)
		for(int i=1;i+(1<<j)-1<=n;i++) {
			int l=mx[i][j-1], r=mx[i+(1<<(j-1))][j-1];
			mx[i][j]=(a[l]>=a[r])? l:r;
		}
	solve(1,n);
	cout<<ans<<endl;
		
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

