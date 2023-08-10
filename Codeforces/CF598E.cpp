#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int f[32][32][52];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=30;i++)
		for(int j=1;j<=30;j++) f[i][j][0]=0;
	for(int i=1;i<=30;i++)
		for(int j=1;j<=30;j++)
			for(int k=1;k<=min(i*j,50);k++) {
				if(k==i*j) { f[i][j][k]=0; continue; }
				for(int x=1;x<i;x++)
					for(int y=0;y<=min(x*j,k);y++) f[i][j][k]=min(f[i][j][k],j*j+f[x][j][y]+f[i-x][j][k-y]);
				for(int x=1;x<j;x++)
					for(int y=0;y<=min(x*i,k);y++) f[i][j][k]=min(f[i][j][k],i*i+f[i][x][y]+f[i][j-x][k-y]);
			}
	int Q,n,m,k;
	cin>>Q;
	while(Q--) {
		cin>>n>>m>>k;
		cout<<f[n][m][k]<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

