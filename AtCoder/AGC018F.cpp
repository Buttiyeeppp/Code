#include<bits/stdc++.h>
using namespace std;
#define endl '\n'
using ll=long long;
const int N=2e5+10;
int n,fa[N],deg[N],head[N],tot=1,a[N],vis[N<<2];
struct Edge{
	int to,nxt;
}e[N<<2];
void add(int x,int y) {
	e[++tot]=(Edge){y,head[x]};
	head[x]=tot;
	e[++tot]=(Edge){x,head[y]};
	head[y]=tot;
}
void dfs(int x) {
	for(int i=head[x];i>1;i=head[x]) {
        head[x]=e[i].nxt;
        if(!vis[i]){
            vis[i]=1, vis[i^1]=-1;
            dfs(e[i].to);
        }
	}
}
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	cin>>n;
	for(int i=1;i<=n;i++) cin>>fa[i], fa[i]=(fa[i]==-1? 0:fa[i]), deg[fa[i]]++, add(fa[i],i);
	for(int i=n+1;i<=(n<<1);i++) cin>>fa[i], fa[i]=(fa[i]==-1? 0:fa[i]+n), deg[fa[i]]++, add(fa[i],i);
	for(int i=1;i<=n;i++) {
		if(deg[i]%2!=deg[i+n]%2) return cout<<"IMPOSSIBLE\n", 0;
		if(deg[i]%2==0) add(i,i+n);
	}
	dfs(0);
	for(int i=4*n+2;i<=tot;i+=2) {
		int u=e[i].to-n;
		a[u]=(vis[i]==1? 1:-1);
	}
	cout<<"POSSIBLE\n";
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
	return 0;
}