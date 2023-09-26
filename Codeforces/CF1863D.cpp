#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
bool mem1;
int n,m,x[N],y[N],b[N][N];
string a[N];
void solve() {
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i], a[i]=" "+a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) b[i][j]=-1;
	for(int i=1;i<=max(n,m);i++) x[i]=y[i]=0;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(a[i][j]=='U') {
				if(x[i]) {
					b[i][x[i]]=1, b[i+1][x[i]]=0;
					b[i][j]=0, b[i+1][j]=1;
					x[i]=0;
				}
				else x[i]=j;
			}
			if(a[i][j]=='L') {
				if(y[j]) {
					b[y[j]][j]=1, b[y[j]][j+1]=0;
					b[i][j]=0, b[i][j+1]=1;
					y[j]=0;
				}
				else y[j]=i;
			}
		}
	}
	int pd=1;
	for(int i=1;i<=max(n,m);i++) if(x[i]||y[i]) pd=0;
	if(!pd) return cout<<-1<<endl, void();
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) {
			if(b[i][j]==-1) cout<<".";		
			if(b[i][j]==0) cout<<"W";
			if(b[i][j]==1) cout<<"B";
		}
		cout<<endl;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	int T; cin>>T;
	while(T--) solve();
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
