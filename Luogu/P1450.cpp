#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
const int N=1e5+10;
int c[5],n,d[5],v;
ll f[N];
void solve() {
	ll ans=0;
	cin>>d[1]>>d[2]>>d[3]>>d[4]>>v;
	for(int s=0;s<(1<<4);s++) {
		int sum=v, tot=0;
		for(int j=1;j<=4;j++)
			if((1<<(j-1))&s) sum-=(d[j]+1)*c[j], tot++;
		if(sum>=0) ans+=(tot%2==0? 1:-1)*f[sum];
	}
	cout<<ans<<endl;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>c[1]>>c[2]>>c[3]>>c[4]>>n;
	f[0]=1;
	for(int i=1;i<=4;i++) {
		for(int j=c[i];j<N;j++) f[j]+=f[j-c[i]];
	}
	while(n--) solve();
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

