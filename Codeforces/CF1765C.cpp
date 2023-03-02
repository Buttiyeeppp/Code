#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=510;
const int Mod=998244353;
int n,K;
ll f[2][N<<2][N],C[N<<2][N<<2];
ll Pow(ll x,ll y) {
	ll sum=1;
	while(y) {
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return sum;
}
void init() {
    for(int i=0;i<(N<<2);i++) {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++) C[i][j]=(C[i-1][j-1]+C[i-1][j])%Mod;
    }
}
int main() {
	init();
	scanf("%d%d",&n,&K);
	for(int i=0;i<=n;i++) f[1][i][i]=1;
	for(int op=1;op<=3;op++) {
        bool t=op&1;
        memset(f[!t],0,sizeof(f[!t]));
		for(int i=0;i<=min(op*n,K);i++)
			for(int j=0;j<=min(n,i);j++)
				for(int k=0;k<=min(n,K-i);k++) f[!t][i+k][min(j,k)]=(f[!t][i+k][min(j,k)]+f[t][i][j]*C[i+k][k]%Mod*C[op*n-i+n-k][n-k])%Mod;
    }
	ll ans=0;
	for(int i=0;i<=min(K,4*n-1);i++) {
		ll sum=0;
		for(int j=0;j<=min(i,n-1);j++) sum=(sum+f[0][i][j]*(n-j)%Mod*Pow(4*n-i,Mod-2))%Mod;
		if(i==K) ans=(ans+sum*(4*n-K)%Mod)%Mod;
		else ans=(ans+sum)%Mod;
	}
	printf("%lld",ans*Pow(C[4*n][n]*C[3*n][n]%Mod*C[2*n][n]%Mod,Mod-2)%Mod);
	return 0;
}
