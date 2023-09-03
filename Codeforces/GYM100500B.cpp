#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using ull=unsigned long long;
using PII=pair<int,int>;
const int N=1e3+10;
const ll P=1331;
bool mem1;
int n,a[5][N],c[N];
map<ull,bool> mp;
void solve() {
	cin>>n;
	for(int i=1;i<=4;i++)
		for(int j=0;j<n;j++) cin>>a[i][j];
	for(int i=0;i<n;i++) {
		ull v=0;
		for(int j=0,p=i;j<n;j++,p++) {
			if(p==n) p=0;
			v=v*P+a[4][p];
		}
		mp[v]=1;
	}
	for(int i1=0;i1<n;i1++) {
		for(int p1=0,p2=i1;p1<n;p1++,p2++) {
			if(p2==n) p2=0;
			c[p1]=a[1][p1]+a[2][p2]+a[3][p1];
		}
		ull v=0;
		for(int i=0;i<n;i++) v=v*P+c[n-1]-c[i];
		for(int i2=0;i2<n;i2++) {
			if(i2) {
//				v=v+c[i2-1]*(pow[])
			}
		}
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cout<<((ull)-1)<<endl;
	return 0;
	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

