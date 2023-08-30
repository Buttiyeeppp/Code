#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2;
bool mem1;
int n,d,a[N][N],col[N],f[N][N],ans=INT_MAX;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>d;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) cin>>a[i][j];
	int T=5000;
	mt19937 rd(20080618);
	while(T--) {
		for(int i=1;i<=n;i++) col[i]=rd()%2;
		memset(f,0x3f,sizeof(f));
		f[0][1]=0;
		for(int k=0;k<d;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++) 
					if(col[i]!=col[j]) f[k+1][j]=min(f[k+1][j],f[k][i]+a[i][j]);	
		ans=min(ans,f[d][1]);
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

