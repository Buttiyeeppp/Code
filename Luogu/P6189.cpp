#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
const int M=1e3+10;
bool mem1;
ll n,Mod,f[N],g[M][N],s[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>Mod;
	int B=sqrt(n)+1;
	f[0]=1;
	for(int i=1;i<B;i++)
		for(int j=i;j<=n;j++) f[j]=(f[j]+f[j-i])%Mod;
	g[0][0]=s[0]=1;
	for(int i=1;i<=B;i++)
		for(int j=i;j<=n;j++) {
			g[i][j]=g[i][j-i];
			if(j>=B) g[i][j]=(g[i][j]+g[i-1][j-B])%Mod;
			s[j]=(s[j]+g[i][j])%Mod;
		}
	ll ans=0;
	for(int i=0;i<=n;i++) ans=(ans+f[i]*s[n-i])%Mod;
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

