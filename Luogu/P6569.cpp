#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
int n,m,q;
struct Matrix {
	ll a[N][N];
	Matrix() { memset(a,0,sizeof(a)); }
	Matrix operator*(const Matrix q)const {
		Matrix res;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				for(int k=1;k<=n;k++) res.a[i][j]^=a[i][k]*q.a[k][j];
		return res;
	}
	Matrix operator^(const Matrix q)const {
		Matrix res;
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++) res.a[1][j]^=a[1][k]*q.a[k][j];
		return res;
	}
}A,B[40];	
bool mem2;
int main() {
//	freopen("P6569_3.in","r",stdin);
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n>>m>>q;
	for(int i=1;i<=n;i++) cin>>A.a[1][i];
	for(int i=1,x,y;i<=m;i++) cin>>x>>y, B[0].a[x][y]=B[0].a[y][x]=1;
	for(int i=1;i<=39;i++) B[i]=B[i-1]*B[i-1];
	for(int i=1;i<=q;i++) {
		ll x; cin>>x;
		Matrix res=A;
		for(int j=0;x;j++,x>>=1)
			if(x&1) res=res^B[j];
		cout<<res.a[1][1]<<endl;
	}

	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}