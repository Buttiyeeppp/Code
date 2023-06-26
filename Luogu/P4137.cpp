#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e5+10;
bool mem1;
int n,m,a[N],cnt[N],ans[N],tot[N];
struct query {
	int l,r,blo,op;
	friend bool operator<(const query &x,const query &y) {
		return (x.blo==y.blo)? x.r>y.r:x.blo<y.blo;
	}
}q[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	int B=1.*n/sqrt(m)+1;
	for(int i=1;i<=n;i++) cin>>a[i];
	for(int i=1;i<=m;i++) cin>>q[i].l>>q[i].r, q[i].blo=(q[i].l-1)/B, q[i].op=i;
	sort(q+1,q+m+1);
	for(int i=1,r,mem;i<=m;i++) {
		if(i==1||q[i].blo!=q[i-1].blo) {
			if(i!=1) for(int j=q[i-1].blo*B+1;j<=r;j++) cnt[a[j]]=0;
			for(int j=q[i].blo*B+1;j<=n;j++) cnt[a[j]]++;
			r=n, mem=0;
			while(cnt[mem]) mem++;
		}
		if(q[i].blo==(q[i].r-1)/B) {
			for(int j=q[i].l;j<=q[i].r;j++) tot[a[j]]++;
			int p=0;
			while(tot[p]) p++;
			ans[q[i].op]=p;
			for(int j=q[i].l;j<=q[i].r;j++) tot[a[j]]--;
			continue;
		}
		while(r>q[i].r) {
			cnt[a[r]]--;
			if(!cnt[a[r]]&&a[r]<mem) mem=a[r];
			r--;
		}
		int Ans=mem;
		for(int j=q[i].blo*B+1;j<q[i].l;j++) {
			cnt[a[j]]--;
			if(!cnt[a[j]]&&a[j]<Ans) Ans=a[j];
		}
		ans[q[i].op]=Ans;
		for(int j=q[i].blo*B+1;j<q[i].l;j++) cnt[a[j]]++;
	}
	for(int i=1;i<=m;i++) cout<<ans[i]<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}

