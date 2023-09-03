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
int n,p[N][N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,a,b,c,d;i<=n;i++) {
		cin>>a>>b>>c>>d;
		a++, c++;
		for(int x=a;x<=b;x++)
			for(int y=c;y<=d;y++) p[x][y]++;
	}
	int ans=0;
	for(int i=0;i<=100;i++)
		for(int j=0;j<=100;j++) ans+=(p[i][j]!=0);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

