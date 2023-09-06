#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const ll P=13331;
const ll Mod=1e9+7;
const int N=4e5+10;
bool mem1;
string s,t;
ll s_hs[N],t_hs[N],Pow[N];
ll Hash(ll hs[],int l,int r) {
	return (hs[r]-hs[l-1]*Pow[r-l+1]%Mod+Mod)%Mod;
}
int s1[N],s2[N],n,m;
int lowbit(int x) { return x&-x; }
void Add(int s[],int x,int v) {
	for(int i=x;i<=n;i+=lowbit(i)) s[i]+=v;
}
int Qry(int s[],int x) {
	if(x<0) return 0;
	int res=0;
	for(int i=x;i;i-=lowbit(i)) res+=s[i];
	return res;
}
vector<int> ndl[N],ndr[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>s>>t;
	n=s.size(), m=t.size();
	s=" "+s, t=" "+t;
	Pow[0]=1;
	for(int i=1;i<N;i++) Pow[i]=Pow[i-1]*P%Mod;
	for(int i=1;i<=n;i++) s_hs[i]=(s_hs[i-1]*P+s[i]-'a'+1)%Mod;
	for(int i=1;i<=m;i++) t_hs[i]=(t_hs[i-1]*P+t[i]-'a'+1)%Mod;
	ll ans=0; 
	for(int i=1;i<=n;i++) {
		Add(s1,i,1);
		int l=0,r=min(m,n-i+1)+1;
		while(l+1<r) {
			int mid=(l+r)>>1;
			if(Hash(s_hs,i,i+mid-1)==Hash(t_hs,1,mid)) l=mid;
			else r=mid;
		}
		ndl[l].push_back(i);
		if(l==m&&i>1) ans+=1ll*(i-1)*(i-2)/2+i-1;
		l=0,r=min(m,i)+1;
		while(l+1<r) {
			int mid=(l+r)>>1;
			if(Hash(s_hs,i-mid+1,i)==Hash(t_hs,m-mid+1,m)) l=mid;
			else r=mid;
		}
		if(l==m&&i<n) ans+=1ll*(n-i)*(n-i-1)/2+n-i;
		ndr[m-l].push_back(i);
	}
	ll res=0;
	for(int i=0;i<=m;i++) {
		for(auto now:ndr[i]) Add(s2,now,1), res+=Qry(s1,now-m);
		if(i>=1&&i<m) ans+=res;
		for(auto now:ndl[i]) Add(s1,now,-1), res-=Qry(s2,n)-Qry(s2,min(now+m-1,n));
	}
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

