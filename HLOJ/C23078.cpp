#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e2+10;
bool mem1;
int n,m,l[5]={1,3,5,2,4},a[N][N];
int work(int x,int y) {
	int res=0;
	for(int i=x;i<=x+n-1;i++)
		for(int j=y;j<=y+m-1;j++) res+=a[i][j];
	return res;
}
void out(int x,int y) {
	for(int i=x;i<=x+n-1;i++) {
		for(int j=y;j<=y+m-1;j++) cout<<a[i][j];
		cout<<endl;
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<N;i++)
		for(int j=l[(i-1)%5];j<N;j+=5) a[i][j]=1;
	int mn=INT_MAX;
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++) mn=min(mn,work(i,j));
	cout<<mn<<endl;
	for(int i=1;i<=5;i++)
		for(int j=1;j<=5;j++) if(mn==work(i,j)) return out(i,j), 0;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

