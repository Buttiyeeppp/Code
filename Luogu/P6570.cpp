#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const ll Mod=1e9+7;
const int N=5.5e5;
bool mem1;
int n,cnt[N],b[N],p[N],phi[N];
ll f[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!phi[i]) P.push_back(i), phi[i]=i-1;
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			if(i%now==0) { phi[now*i]=phi[i]*now; break; }
			phi[now*i]=phi[i]*(now-1);
		}
	}
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	cin>>n;
	for(int i=1,x;i<=n;i++) cin>>x, cnt[x]++;
	for(int i=0;i<(1<<19);i++) {
		b[i]=(b[i>>1]<<1)|1;
		if(cnt[i]) {
			int u=i^b[i];
			f[i]+=cnt[i];
			for(int s=u;s;s=(s-1)&u) f[s|i]=(f[s|i]+f[s]*cnt[i])%Mod;
		}
	}
	ll ans=1;
	for(int i=0;i<(1<<19);i++) ans=(ans+f[i]*phi[i+1])%Mod;
	while(cnt[0]--) ans=ans*2%Mod;
	cout<<ans<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
