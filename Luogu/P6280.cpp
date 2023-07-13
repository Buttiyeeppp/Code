#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e4+10;
const int M=2e3+10;
bool mem1;
ll n,Mod,f[M][N];
int prime[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!prime[i]) {
			P.push_back(i), prime[i]=i;
		}
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			prime[now*i]=now;
			if(i%now==0) break;
		}
	}
}
void Add(ll &x,ll y) { return x=(x+y>=Mod? x+y-Mod:x+y), void(); }
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	cin>>n>>Mod;
	f[0][0]=1;
	for(int i=1;i<=P.size();i++)
		for(int j=0;j<=n;j++) {
			f[i][j]=f[i-1][j];
			int w=P[i-1];
			while(j>=w&&w>0) {
				Add(f[i][j],f[i-1][j-w]*w%Mod);
				w*=P[i-1];
			}
		}
	ll ans=0;
	for(int i=0;i<=n;i++) Add(ans,f[P.size()][i]);
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
