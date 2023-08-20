#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=3e5+10;
bool mem1;
int n,mx1[N],mx2[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	memset(mx1,-0x3f,sizeof(mx1)), memset(mx2,-0x3f,sizeof(mx2));
	for(int i=1,x,y;i<=n;i++) {
		cin>>x>>y;
		if(y>mx1[x]) mx2[x]=mx1[x], mx1[x]=y;
		else if(y>mx2[x]) mx2[x]=y;
	}
	int ans=0,v1=-0x3f3f3f3f,v2=-0x3f3f3f3f;
	for(int x=1;x<=n;x++) {
		if(mx1[x]>v1) v2=v1, v1=mx1[x];
		else if(mx1[x]>v2) v2=mx1[x];
		ans=max(ans,mx1[x]+mx2[x]/2);
	}
	ans=max(ans,v1+v2);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

