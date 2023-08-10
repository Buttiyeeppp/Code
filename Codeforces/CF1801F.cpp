#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
const int M=1e4+10;
bool mem1;
int n,k,a[N],mp[10000007];
double f[N][M];
vector<int> val;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>k;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<k;){
		val.push_back((k-1)/i), mp[(k-1)/i]=val.size()-1;
		i=(k-1)/((k-1)/i)+1;
	}
	val.push_back(0), mp[0]=val.size()-1;
	f[0][0]=k;
	for(int i=0;i<n;i++) {
		for(int j=0;j<val.size();j++) {
			for(int l=1;l<=val[j];) {
				int z=val[j]/l, pos=mp[z];
				f[i+1][pos]=max(f[i+1][pos],f[i][j]*(a[i+1]/l)/a[i+1]);
				l=val[j]/z+1;
			}
			f[i+1][val.size()-1]=max(f[i+1][val.size()-1],f[i][j]*(a[i+1]/(val[j]+1))/a[i+1]);
		}
	}
	double ans=f[n][val.size()-1];
	cout<<setprecision(10)<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	#endif
	return 0;
}

