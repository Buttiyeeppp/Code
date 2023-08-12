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
int n,a[N],s[N];
int lowbit(int x) { return x&-x; }
void add(int x,int v) { for(int i=x;i<=n;i+=lowbit(i)) s[i]+=v; }
int qry(int x) {
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	while(cin>>n) {
		int pd=0;
		for(int i=1;i<=n;i++) {
			cin>>a[i];
			if((a[i]%2)!=(i%2)) pd=1;
		}
		if(pd) { cout<<"No"<<endl; continue; }
		ll cnt1=0,cnt2=0,cnt3=0;
		for(int i=n-(n%2==0);i>=1;i-=2) cnt1+=qry(a[i]), add(a[i],1);
		for(int i=n-(n%2==0);i>=1;i-=2) add(a[i],-1);
		for(int i=n-(n%2==1);i>=1;i-=2) cnt2+=qry(a[i]), add(a[i],1);
		for(int i=n-(n%2==1);i>=1;i-=2) add(a[i],-1);
		for(int i=n;i>=1;i--) cnt3+=qry(a[i]), add(a[i],1);
		for(int i=n;i>=1;i--) add(a[i],-1);
		cout<<(((cnt1+cnt2)*3==cnt3)? "Yes":"No")<<endl; 
	}
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

