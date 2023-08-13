#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
int n,m,p[N];
double c[N],s[N][N],f[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>c[i]>>p[i];
		int tot=0;
		for(int j=1,x;j<=p[i];j++) {
			cin>>x;
			if(x) s[i][++tot]=x;
		}
		c[i]*=(double)p[i]/tot, p[i]=tot;
	}
	for(int i=m-1;i>=0;i--) {
		f[i]=1e9;
		for(int j=1;j<=n;j++) if(p[j]) {
			double v=0;
			for(int k=1;k<=p[j];k++) if(i+s[j][k]<m) v+=f[i+(int)s[j][k]];
			f[i]=min(f[i],c[j]+v/p[j]);
		}
	}
	cout<<fixed<<setprecision(10)<<f[0]<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

