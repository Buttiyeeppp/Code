#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=5e6+10;
const ll P=20007;
const ll Mod=1e9+7;
bool mem1;
int n,m,a[N],b[N],c1,c2;
ll Pow[N],hs[N],hsc[N];
struct node {
	int c,t;
}x[N],y[N];
int gcd(int x,int y) {
	if(!x) return y;
	return gcd(y%x,x);
}
ll Hash(ll h[],int l,int r) {
	return (h[r]-h[l-1]*Pow[r-l+1]%Mod+Mod)%Mod;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i];
		if(i==1||a[i]!=a[i-1]) x[++c1]={a[i],1};
		else x[c1].t++;
	}
	for(int i=1;i<=m;i++) {
		cin>>b[i];
		if(i==1||b[i]!=b[i-1]) y[++c2]={b[i],1};
		else y[c2].t++;
	}
	ll G=y[1].t;
	for(int i=2;i<=c2;i++) G=gcd(G,y[i].t);
	for(int i=1;i<=c2;i++) y[i].t/=G;
	if(c2==1) { //SubA
		ll ans=0;
		for(int i=1;i<=c1;i++)
			if(x[i].c==y[1].c) ans+=1ll*x[i].t*(x[i].t-1)/2+x[i].t;
		cout<<ans<<endl;
		return 0;
	}
	if(c2==2) { //subB
		ll ans=0;
		for(int i=1;i<c1;i++) {
			if(x[i].c==y[1].c&&x[i+1].c==y[2].c)
				ans+=min(x[i].t/y[1].t,x[i+1].t/y[2].t);
		}
		cout<<ans<<endl;
		return 0;
	}
	Pow[0]=1;
	for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*P%Mod;
	ll temp=0,tc=0,ans=0;
	for(int i=1;i<=c2;i++) tc=(tc*P+y[i].c)%Mod;
	for(int i=2;i<c2;i++) temp=(temp*P+y[i].t)%Mod;
	for(int i=1;i<=c1;i++) 
		hs[i]=(hs[i-1]*P+x[i].t)%Mod, hsc[i]=(hsc[i-1]*P+x[i].c)%Mod;
	for(int i=1;i+c2-1<=c1;i++) {
		ll del=x[i+1].t/y[2].t;
		if(x[i+1].t%y[2].t==0&&Hash(hs,i+1,i+c2-2)==temp*del%Mod&&Hash(hsc,i,i+c2-1)==tc)
			if(x[i].t>=y[1].t*del&&x[i+c2-1].t>=y[c2].t*del) ans++;
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}
