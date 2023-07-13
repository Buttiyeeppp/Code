#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e3+10;
bool mem1;
int n,v,s,ns=1;
double f[N][N][2],sum[N],sum1,x[N];
struct node {
	int x,c,d;
	bool operator<(const node &q)const { return x<q.x; }
}nd[N];
void solve() {
	if(n==0&&v==0&&s==0) return;
	for(int i=1;i<=n;i++) cin>>nd[i].x>>nd[i].c>>nd[i].d;
	sort(nd+1,nd+n+1);
	for(int i=1;i<=n;i++) {
		if(nd[i].x<=s) x[i+1]=s, x[i]=nd[i].x, ns=i+1, sum[i+1]=sum[i]=sum[i-1]+nd[i].d;
		else x[i+1]=nd[i].x, sum[i+1]=sum[i]+nd[i].d;
		sum1+=nd[i].c;
	}
	n++;
	for(int i=1;i<=n;i++) f[i][i][0]=f[i][i][1]=1e17;
//	cout<<ns<<" "<<v<<endl;
//	cout<<"Sum "; for(int i=1;i<=n;i++) cout<<sum[i]<<" "; cout<<endl;
//	cout<<"X "; for(int i=1;i<=n;i++) cout<<x[i]<<" "; cout<<endl;
	f[ns][ns][0]=f[ns][ns][1]=0;
	for(int len=2;len<=n;len++)
		for(int i=1;i+len-1<=n;i++) {
			int j=i+len-1;
			// left:0
			f[i][j][1]=f[i][j][0]=1e17;
			f[i][j][1]=min({
							f[i][j][1],
							f[i][j-1][1]+(x[j]-x[j-1])*(sum[n]-sum[j-1]+sum[i-1]),
							f[i][j-1][0]+(x[j]-x[i])*(sum[n]-sum[j-1]+sum[i-1])
							});
			f[i][j][0]=min({
							f[i][j][0],
							f[i+1][j][1]+(x[j]-x[i])*(sum[n]-sum[j]+sum[i]),
							f[i+1][j][0]+(x[i+1]-x[i])*(sum[n]-sum[j]+sum[i])
							});
			f[i][j][1]=min(f[i][j][1],f[i][j][0]+(x[j]-x[i])*(sum[n]-sum[j]+sum[i-1]));
			f[i][j][0]=min(f[i][j][0],f[i][j][1]+(x[j]-x[i])*(sum[n]-sum[j]+sum[i-1]));
		}
	cout<<(int)(min(f[1][n][0],f[1][n][0])/v+sum1)<<endl;
}
bool mem2;
int main() {
//	freopen("a.txt","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);
	
	while(cin>>n>>v>>s) {
		sum1=0, ns=1, x[1]=s;
		solve();
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
