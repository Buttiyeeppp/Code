#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=1e5+10;
bool mem1;
int n,f[N],ans[N];
vector<int> g[N];
int prime[N];
vector<int> P;
void Get_Prime() {
	for(int i=2;i<N;i++) {
		if(!prime[i]) {
			P.push_back(i), prime[i]=i;
		}
		for(auto now:P) {
			if(1ll*now*i>=N) break;
			prime[now*i]=now;
			if(i%now==0) break;
		}
	}
}
bool dfs(int x,int from,int k) {
	vector<int> w;
	for(auto y:g[x]) if(y!=from) {
		if(!dfs(y,x,k)) return false;
		if(f[y]!=k) w.push_back(f[y]);
	}
	sort(w.begin(),w.end());
	int p1=0, p2=w.size()-1, cnt=0; f[x]=0;
	if(p1==p2) f[x]=w[0];
	while(p1<p2&&p1<w.size()&&p2>=0) {
		if(w[p1]+w[p2]==k) {
			p1++, p2--, cnt++;
			if(p1==p2) f[x]=w[p1];	
		}
		else if(w[p1]+w[p2]>k) f[x]=w[p2--];
		else f[x]=w[p1++];
	}
	f[x]++;
	return (cnt*2+1>=(int)w.size());
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	Get_Prime();
	cin>>n;
	for(int i=1,x,y;i<n;i++) {
		cin>>x>>y;
		g[x].push_back(y), g[y].push_back(x);
	}
	for(int k=1;k<n;k++) {
		if(((n-1)%k==0)&&(k==1||ans[k/prime[k]])) {
			if(dfs(1,0,k)&&f[1]==1) { putchar('1'); ans[k]=1; continue; }
		}
		putchar('0');
	}
	putchar('\n');
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}
