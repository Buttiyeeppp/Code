#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,k,f[N][110];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>k>>n;
	for(int i=1;i<N;i++)
		for(int j=1;j<=k;j++) {
			if(i==1) f[i][j]=1;
			else if(j==1) f[i][j]=i;
			else f[i][j]=f[i-1][j]+f[i-1][j-1]+1;
		}
	int i=1;
	for(;f[i][k]<n;i++);
	cout<<i<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

