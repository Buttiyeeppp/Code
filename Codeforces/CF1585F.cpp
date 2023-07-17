#include<bits/stdc++.h>
using namespace std;
#define clo 1.0*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
const int N=2e5+10;
const ll Mod=998244353;
bool mem1;
int n,a[N],st[N],top;
ll f[N][2],s[N][2];
void Add(ll &x,ll y) { return x=(x+y>=Mod? x+y-Mod:x+y), void(); }
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n;
	for(int i=1;i<=n;i++) cin>>a[i];
	f[0][0]=s[0][0]=1;
	for(int i=1;i<=n;i++) {
		while(top&&a[st[top]]>=a[i]) top--;
		for(int op=0;op<=1;op++) {
			if(!top) Add(f[i][op],s[i-1][op^1]*a[i]%Mod);
			else {
				Add(f[i][op],f[st[top]][op]);
				Add(f[i][op],(s[i-1][op^1]-s[st[top]-1][op^1]+Mod)%Mod*a[i]%Mod);
			}
			s[i][op]=(s[i-1][op]+f[i][op])%Mod;	
		}
		st[++top]=i;
	}
	if(n&1) cout<<(f[n][1]-f[n][0]+Mod)%Mod<<endl;
	else cout<<(f[n][0]-f[n][1]+Mod)%Mod<<endl;

	cerr<<"Time "<<clo<<" MS"<<endl;
	cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}