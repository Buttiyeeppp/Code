#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=30;
bool mem1;
int n,a[N],b[N],c[N],ta[N],tb[N],A[N],B[N];
int t1,t2,t3,ans=INT_MAX,l1,l2;
int calc() {
	int v1=0,v2=0,mx=0;
	for(int i=1;i<=l1;i++) v1+=ta[A[i]];
	for(int i=1;i<=l2;i++) {
		v2+=tb[B[i]];
		if(v1>v2) v1+=ta[B[i]];
		else v1=v2+ta[B[i]];
	}
	mx=max(v1,v2);
	v1=v2=0;	
	for(int i=1;i<=l2;i++) v2+=tb[B[i]];
	for(int i=1;i<=l1;i++) {
		v1+=ta[A[i]];
		if(v2>v1) v2+=tb[A[i]];
		else v2=v1+tb[A[i]];
	}
	return max({mx,v1,v2});
}
void sol(int S) {
	l1=l2=0;
	for(int i=1;i<=t1;i++) A[++l1]=a[i];
	for(int i=1;i<=t2;i++) B[++l2]=b[i];
	for(int i=1;i<=t3;i++) {
		if((1<<(i-1))&S) A[++l1]=c[i];
		else B[++l2]=c[i];	
	}
	sort(A+1,A+l1+1,[](const int &x,const int &y){ return tb[x]>tb[y]; });
	sort(B+1,B+l2+1,[](const int &x,const int &y){ return ta[x]>ta[y]; });
	int res=calc();
	int T=3000;
	mt19937 rd(20080618);
	while(T--) {
		int xa,ya,xb,yb;
		if(l1) swap(A[xa=rd()%l1+1],A[ya=rd()%l1+1]);
		if(l2) swap(B[xb=rd()%l2+1],B[yb=rd()%l2+1]);
		int now=calc();
		if(now>res) {
			if(l1) swap(A[xa],A[ya]);
			if(l2) swap(B[xb],B[yb]);
		}
		else res=now;
	}
	ans=min(ans,res);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1,op;i<=n;i++) {
		cin>>op>>ta[i]>>tb[i];
		if(op==1) a[++t1]=i;
		else if(op==2) b[++t2]=i;
		else c[++t3]=i;
	}
	for(int s=0;s<(1<<t3);s++) sol(s);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

