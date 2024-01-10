#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e2;
bool mem1;
int n,m,a[N][N],b[N][N],v[N*N],p;
void px(int x,int y) {
	for(int i=y-1;i>=1;i--) {
		while(v[p]) p--;
		b[x][i]=p--;
	}
}
void py(int x,int y) {
	for(int i=x-1;i>=1;i--) {
		while(v[p]) p--;
		b[i][y]=p--;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(nullptr);

	cin>>n>>m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) cin>>a[i][j];
	for(int i=1;i<=n;i++) {
		int val=0;
		for(int j=1;j<=m;j++) val=max(val,a[i][j]);
		v[val]+=1;
	}
	for(int j=1;j<=m;j++) {
		int val=0;
		for(int i=1;i<=n;i++) val=max(val,a[i][j]);
		v[val]+=2;
	}
	vector<int> nd;
	for(int i=1;i<=n*m;i++) if(v[i]) nd.push_back(i);
	sort(nd.begin(),nd.end(),[](const int &x,const int &y) { return x>y; });
	int x=0, y=0; p=n*m;
	for(auto i:nd) {
		if(v[i]==1||v[i]==3) x++;
		if(v[i]==2||v[i]==3) y++;
		if(v[i]==1||v[i]==3) px(x,y);
		if(v[i]==2||v[i]==3) py(x,y);
		b[x][y]=i;
	}
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=m;j++) cout<<b[i][j]<<" ";
		cout<<endl;
	}
	
	#ifdef xxzx
	cerr<<"Time "<<clo<<"MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}