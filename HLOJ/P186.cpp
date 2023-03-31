#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define ll long long
const int N=3e3+10;
const ll Mod=998244353;
const ll P=1331;
const ll P1=4001;
bool qq;
int read() {
	int f=1, z=0; char ch=getchar();
	while(ch<'0'||ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0'&&ch<='9') { z=z*10+ch-'0'; ch=getchar(); }
	return f*z;
}
int n,A[N][N],B[N][N],C[N][N];
ll b[2][N],c[2][N],res[2][N];
void solve() {
	n=read();
	for(int i=1;i<=n;i++) b[0][i]=c[0][i]=res[0][i]=0, b[1][i]=c[1][i]=res[1][i]=0;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) A[i][j]=read();
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) B[i][j]=read(), b[0][i]=(b[0][i]*P+B[i][j])%Mod, b[1][i]=(b[1][i]*P1+B[i][j])%Mod;
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) C[i][j]=read(), c[0][i]=(c[0][i]*P+C[i][j])%Mod, c[1][i]=(c[1][i]*P1+C[i][j])%Mod;
	for(int i=1;i<=n;i++) {
		for(int j=1;j<=n;j++) res[0][i]=(res[0][i]+A[i][j]*b[0][j])%Mod, res[1][i]=(res[1][i]+A[i][j]*b[1][j])%Mod;
		if(res[0][i]!=c[0][i]||res[1][i]!=c[1][i]) return puts("No"), void();
	}
	puts("Yes");
	return;
}
bool pp;
int main() {
	freopen("a.txt","r",stdin);
	// freopen("matrix.out","w",stdout);
	double be=clo;
	int T=read();
	while(T--) solve();
	cerr<<"Time: "<<clo-be<<endl;
	cerr<<"Me: "<<(&pp-&qq)/1024./1024.<<endl;
	return 0;
}