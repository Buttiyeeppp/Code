#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int B=300;
bool mem1;
int t,n,m[N],ans;
vector<vector<int>> a[N],s[N],up[N];
void calc(int l,int r) {
	int mxl1=0,mxl2=0,mxr1=0,mxr2=0,pl1=0,pr1=0;
	int cnt=0,mx=0;
	for(int i=1;i<=t;i++) {
		int sum=0,pd=0;
		for(int j=1;j<=m[i];j++) 
			if(s[i][r][j]-s[i][l-1][j]) pd=1;
		if(!pd) { cnt+=m[i], mx=max(mx,m[i]); continue;} 
		for(int j=1;j<=m[i];j++) {
			if(s[i][r][j]-s[i][l-1][j]==0) {
				sum++;
				mx=max(mx,sum);
				if(j==sum) {
					if(sum>mxl1) mxl2=mxl1,mxl1=sum,pl1=i;
					else if(sum>mxl2) mxl2=sum;
				}
				if(j==m[i]) {
					if(sum>mxr1) mxr2=mxr1,mxr1=sum,pr1=i;
					else if(sum>mxr2) mxr2=sum;
				}
			}
			else sum=0;
		}
	}
	int d=mxl1+mxr1;
	if(pl1==pr1) d=max(mxl1+mxr2,mxl2+mxr1);
	ans=max(ans,max(d+cnt,mx)*(r-l+1));
}
void solve() {
	cin>>t>>n;
	string st;
	for(int i=1;i<=t;i++) {
		cin>>m[i];
		a[i].resize(n+2), s[i].resize(n+2), up[i].resize(n+2);
		for(int j=0;j<=n+1;j++) a[i][j].resize(m[i]+2), s[i][j].resize(m[i]+2), up[i][j].resize(m[i]+2);
		for(int j=1;j<=n;j++) {
			cin>>st;
			for(int k=1;k<=m[i];k++) {
				a[i][j][k]=st[k-1]-'0', s[i][j][k]=s[i][j-1][k]+a[i][j][k], up[i][j][k]=(a[i][j][k]? j:up[i][j-1][k]);
			}
		}
	}
	ans=0;
	if(n<=B) {
		for(int l=1;l<=n;l++)
			for(int r=l;r<=n;r++) calc(l,r);
	}
	else {
		for(int i=1;i<=t;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=m[i];k++) if(up[i][j][k]<j) calc(up[i][j][k]+1,j);	
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();

	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}
