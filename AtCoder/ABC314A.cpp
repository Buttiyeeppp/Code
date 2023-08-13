#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	int n; cin>>n;
	string a="1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679";
	cout<<"3.";
	for(int i=0;i<n;i++) cout<<a[i];
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

