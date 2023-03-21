#include<bits/stdc++.h>
using namespace std;
#define clo 1000.0*clock()/CLOCKS_PER_SEC
#define ll long long
const ll Mod=1e9+7;
const int N=2e3+10;
bool qq;
ll Pow(ll x,ll y) {
	ll sum=1;
	while(y) {
		if(y&1) sum=sum*x%Mod;
		x=x*x%Mod, y>>=1;
	}
	return sum;
}
int n,m,cnt[5],op[5],vis[N],yep[N];
char a[N][N],ch[5];
vector<int> g[N];
void dfs(int x) {
    vis[x]=1;
    for(auto y:g[x]) if(!vis[y]) dfs(y);
}
bool pp;
int main() {
	freopen("square.in","r",stdin);
	freopen("square.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++) scanf("%s",a[i]+1);
	ll ans=1;
	if(m&1) {
		int ok=0, j=m/2+1;
		for(int k=1;k<=n/2;k++) if(a[k][j]!=a[n+1-k][j]) { ok=1; break; }
		if(ok) ans=ans*2%Mod;
	}
	if(n&1) {
		int ok=0, i=n/2+1;
		for(int k=1;k<=m/2;k++) if(a[i][k]!=a[i][m+1-k]) { ok=1; break; }
		if(ok) ans=ans*2%Mod;
	}
    int v=0;
    for(int i=1;i<=n/2;i++) {
        for(int j=1;j<=m/2;j++) {
            ch[1]=a[i][j], ch[2]=a[i][m+1-j], ch[3]=a[n+1-i][j], ch[4]=a[n+1-i][m+1-j];
            for(int k=1;k<=4;k++) {
                cnt[k]=op[k]=0;
                for(int d=1;d<=k;d++) if(ch[d]==ch[k]) { cnt[d]++; break; }
            }
            for(int k=1;k<=4;k++) op[cnt[k]]++;
            if(op[1]==4) g[i].push_back(n/2+j), g[n/2+j].push_back(i), yep[i]=yep[n/2+j]=1, ans=ans*12%Mod;
            else if(op[2]==1) ans=ans*12%Mod;
            else if(op[2]==2) ans=ans*6%Mod;
            else if(op[3]==1) ans=ans*4%Mod;
        }
    }
    for(int i=1;i<=n/2+m/2;i++) if(yep[i]){
        v++;
        if(!vis[i]) v--, dfs(i);
    }
    ans=ans*Pow(2,v)%Mod;
	printf("%lld\n",ans);
	cerr<<"Time: "<<clo<<endl;
	cerr<<"Me: "<<abs(&pp-&qq)/1024./1024.<<endl;
	return 0;
}