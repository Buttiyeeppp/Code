#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=1e2+10;
bool mem1;
int n,a[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	int s=0;
	for(int i=1;i<=n;i++) cin>>a[i], s+=a[i];
	s=(s+1)/2;
	for(int i=1;i<=n;i++) {
		if(s>a[i]) s-=a[i];
		else return cout<<i<<" "<<s<<endl, 0;
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

