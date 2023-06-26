#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
const ll Mod=1e9+7;
const int N=1e4+10;
int h,w,m,n,X[N],Y[N],mx[N][N];
struct Matrix {
	int xa,xb,ya,yb,v;
}a[N];
ll Pow(ll x,ll y) {
	ll res=1;
	while(y) {
		if(y&1) res=res*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return res;
}
void solve() {
	cin>>h>>w>>m>>n;
	for(int i=1;i<=n;i++) {
		cin>>a[i].xa>>a[i].ya>>a[i].xb>>a[i].yb>>a[i].v;
		a[i].xb++, a[i].yb++;
		X[i]=a[i].xa, X[i+n]=a[i].xb;
		Y[i]=a[i].ya, Y[i+n]=a[i].yb;
	}
	X[(n<<1)+1]=1, X[(n<<1)+2]=h+1;
	Y[(n<<1)+1]=1, Y[(n<<1)+2]=w+1;
	sort(X+1,X+(n<<1)+3), sort(Y+1,Y+(n<<1)+3);
	int tot1=unique(X+1,X+(n<<1)+3)-X-1, tot2=unique(Y+1,Y+(n<<1)+3)-Y-1;
	ll ans=0;
	for(int s=0;s<(1<<n);s++) {
		for(int i=1;i<=tot1;i++)
			for(int j=1;j<=tot2;j++) mx[i][j]=m;
		int cnt=0;
		for(int i=1;i<=n;i++) {
			int val=((1<<(i-1))&s)? a[i].v-1:a[i].v;
			if((1<<(i-1))&s) cnt++;
			for(int j=lower_bound(X+1,X+tot1+1,a[i].xa)-X;X[j]!=a[i].xb;j++)
				for(int k=lower_bound(Y+1,Y+tot2+1,a[i].ya)-Y;Y[k]!=a[i].yb;k++) {
					mx[j][k]=min(mx[j][k],val);
				}
		}
		ll res=1;
		for(int j=1;j<tot1;j++)
			for(int k=1;k<tot2;k++)
				res=res*Pow(mx[j][k],(X[j+1]-X[j])*(Y[k+1]-Y[k])%Mod)%Mod;
		ans=(ans+(cnt%2==0? 1:-1)*res+Mod)%Mod;
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int T; cin>>T;
	while(T--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

