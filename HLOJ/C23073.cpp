#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=5e3+10;
bool mem1;
int n,m,yep[N],f[N][N],que[N];
struct Seg {
	int l,r;
	friend bool operator<(const Seg a,const Seg b) { return a.l<b.l; }
}a[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i].l>>a[i].r;
	vector<int> w;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) if(i!=j) {
			if(a[i].l==a[j].l&&a[i].r==a[j].r&&i<j);
			else if(a[i].l<=a[j].l&&a[i].r>=a[j].r) {
				w.push_back(a[i].r-a[i].l), yep[i]=1; break;	
			}
		}
	int tot=0;
	for(int i=1;i<=n;i++) if(!yep[i]) a[++tot]=a[i];
	n=tot;
	sort(a+1,a+n+1), sort(w.begin(),w.end(),[](const int x,const int y){return x>y;});
	memset(f,-0x3f,sizeof(f)); f[0][0]=0;
	for(int j=1;j<=m;j++) {
		int l=1,r=1; que[1]=0;
		for(int i=1;i<=n;i++) {
//			for(int k=0;k<i;k++) if(a[k+1].r>a[i].l)
//				f[i][j]=max(f[i][j],f[k][j-1]+a[k+1].r-a[i].l);
			while(l<=r&&a[que[l]+1].r<=a[i].l) l++;
			if(l<=r) f[i][j]=max(f[i][j],f[que[l]][j-1]+a[que[l]+1].r-a[i].l);
			while(l<=r&&f[i][j-1]+a[i+1].r>f[que[r]][j-1]+a[que[r]+1].r) r--;
			que[++r]=i;
		}
	}
	int ans=f[n][m];
	for(int i=1;i<w.size();i++) w[i]+=w[i-1];
	for(int i=0;i<min((int)w.size(),m);i++) ans=max(ans,w[i]+f[n][m-i-1]);
	cout<<max(ans,0)<<endl;
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
