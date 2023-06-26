#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
bool mem1;
const int N=22;
const int M=3e6;
int n,cnt[M];
double p[M];
double Emn(int s) {
	return 1./(1.-p[((1<<n)-1)^s]);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n;
	int res=0;
	for(int i=0;i<(1<<n);i++) cin>>p[i], res|=(p[i]!=0)*i;
	if(res!=(1<<n)-1) return cout<<"INF\n", 0;
	cnt[0]=0;
	for(int i=1;i<M;i++) cnt[i]=cnt[i-(i&-i)]+1;
	for(int i=1;i<=n;i++)
		for(int s=0;s<(1<<n);s++) if((1<<(i-1))&s)
			p[s]+=p[s^(1<<(i-1))];
	double Emx=0;
	for(int s=1;s<(1<<n);s++) Emx+=(cnt[s]%2==1? 1:-1)*Emn(s);
	cout<<fixed<<setprecision(7)<<Emx<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

