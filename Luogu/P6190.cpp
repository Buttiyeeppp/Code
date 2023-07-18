#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
#define fi first
#define se second
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
const int M=3e3+10;
bool mem1;
int n,m,k;
struct edge { int x,y,z; } eg[M];	
struct Matrix {
	ll a[N][N];
	Matrix() { memset(a,0x3f,sizeof(a)); }
	Matrix operator*(const Matrix q)const {
		Matrix res;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) {
				for(int k=1;k<=n;k++) res.a[i][j]=min(res.a[i][j],a[i][k]+q.a[k][j]);
			}
		return res;
	}
}A,B;
Matrix Pow(Matrix x,int y) {
	Matrix res;
	for(int i=1;i<=n;i++) res.a[i][i]=0;
	while(y) {
		if(y&1) res=res*x;
		x=x*x, y>>=1;
	}
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m>>k;
	for(int i=1;i<=n;i++) A.a[i][i]=0;
	for(int i=1,x,y,z;i<=m;i++) {
		cin>>x>>y>>z;
		eg[i]=edge{x,y,z};
		A.a[x][y]=min(A.a[x][y],(ll)z);
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++) A.a[i][j]=min(A.a[i][j],A.a[i][k]+A.a[k][j]);
	if(!k) return cout<<A.a[1][n]<<endl, 0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) {
			B.a[i][j]=A.a[i][j];
			for(int k=1;k<=m;k++) {
				B.a[i][j]=min(B.a[i][j],A.a[i][eg[k].x]-eg[k].z+A.a[eg[k].y][j]);
			}
		}
	cout<<Pow(B,k).a[1][n]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}