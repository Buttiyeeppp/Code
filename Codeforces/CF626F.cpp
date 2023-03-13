#include<bits/stdc++.h>
using namespace std;
#define ll long long 
const ll Mod=1e9+7;
const int N=210;
int n,v,a[N];
ll f[2][N][N*5];
void Add(ll &x,ll y) { x=(x+y>=Mod? x+y-Mod:x+y); }
int main() {
	scanf("%d%d",&n,&v);
	for(int i=1;i<=n;i++) scanf("%d",&a[i]);
	if(n==1) return puts("1"), 0;
	sort(a+1,a+n+1);
	f[1][0][0]=f[1][1][0]=1;
	for(int i=1;i<n;i++) {
		for(int j=0;j<=i;j++) {
			for(int k=0;k+j*(-a[i]+a[i+1])<=v;k++) {
			    Add(f[(i&1)^1][j][k+j*(-a[i]+a[i+1])],(j+1)*f[i&1][j][k]%Mod);
				if(j) Add(f[(i&1)^1][j-1][k+j*(-a[i]+a[i+1])],j*f[i&1][j][k]%Mod);
				Add(f[(i&1)^1][j+1][k+j*(-a[i]+a[i+1])],f[i&1][j][k]);
			}
		}
        for(int j=0;j<=n;j++) for(int k=0;k<=v;k++) f[i&1][j][k]=0;
    }
	ll ans=0;
	for(int i=0;i<=v;i++) Add(ans,f[n&1][0][i]);
	printf("%lld\n",ans);
	return 0;
}