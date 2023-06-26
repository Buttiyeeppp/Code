#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=4e4+10;
const int M=2e2+10;
bool mem1;
int n,m,a[N],X[N],cnt[N],num[M][M];
vector<int> pos[N];
int mx,ans;
int Sum(int x,int l,int r) {
	return upper_bound(pos[x].begin(),pos[x].end(),r)-
			lower_bound(pos[x].begin(),pos[x].end(),l);
}
void Update(int x,int l,int r) {
	int sum=Sum(x,l,r);
	if(sum==mx&&x<ans) ans=x;
	else if(sum>mx) mx=sum, ans=x;
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i], X[i]=a[i];
	sort(X+1,X+n+1);
	int tot=unique(X+1,X+n+1)-X-1, B=sqrt(n);
	for(int i=1;i<=n;i++) a[i]=lower_bound(X+1,X+tot+1,a[i])-X, pos[a[i]].push_back(i);
	for(int i=0;i*B+1<=n;i++) {
		int p=-1;
		for(int j=i*B+1;j<=n;j++) {
			cnt[a[j]]++;
			if(p==-1||cnt[a[j]]>cnt[p]||(cnt[a[j]]==cnt[p]&&a[j]<p)) p=a[j];
			if(j%B==0) num[i][j/B-1]=p;
		}
		for(int j=i*B+1;j<=n;j++) cnt[a[j]]--;
	}
	int l,r;
	while(m--) {
		cin>>l>>r;
		l=(l+ans-1)%n+1, r=(r+ans-1)%n+1;
		if(l>r) swap(l,r);
		int bl=(l-1)/B, br=(r-1)/B; mx=-1, ans=-1;
		if(bl==br) for(int i=l;i<=r;i++) Update(a[i],l,r);
		else {
			if(bl+1<br) Update(num[bl+1][br-1],l,r);
			for(int i=l;i<=(bl+1)*B;i++) Update(a[i],l,r);
			for(int i=br*B+1;i<=r;i++) Update(a[i],l,r);
		}
		ans=X[ans];
		cout<<ans<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
