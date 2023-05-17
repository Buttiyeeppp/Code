#include<bits/stdc++.h>
using namespace std;
#define clo clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
const int M=5e3+10;
bool mem1;
int n,m,Q,ans[M],vis[N][N],tot,s[N][N];
int fx[4][2]={{0,1},{1,0},{0,-1},{-1,0}};
PII pos[N*N];
string a[N];
void bfs(int x,int y) {
	queue<PII> que;
	que.emplace(x,y), vis[x][y]=tot;
	while(que.size()) {
		PII now=que.front(); que.pop();
		for(int i=0;i<4;i++) {
			int newx=now.first+fx[i][0];
			int newy=now.second+fx[i][1];
			if(newx>=1&&newx<=n&&newy>=1&&newy<=m&&!vis[newx][newy]&&a[newx][newy]==a[now.first][now.second]) 
                que.emplace(newx,newy), vis[newx][newy]=tot;
		}
	}
}
bool in(PII now,int x1,int y1,int x2,int y2) {
	if(now.first<x1||now.first>x2) return true;
	return (now.second<y1||now.second>y2);
}
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);

	cin>>n>>m;
	for(int i=1;i<=n;i++) cin>>a[i], a[i]=" "+a[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) {
			if(!vis[i][j]) tot++, bfs(i,j), pos[tot]=make_pair(i,j), s[i][j]=1;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++) s[i][j]+=s[i-1][j]+s[i][j-1]-s[i-1][j-1];
	cin>>Q;
	set<int> st; 
	for(int i=1,x1,y1,x2,y2;i<=Q;i++) {
        st.clear();
		cin>>x1>>y1>>x2>>y2;
		if(x1>x2) swap(x1,x2);
		if(y1>y2) swap(y1,y2);
		for(int i=x1;i<=x2;i++) {
			if(y1>1&&a[i][y1-1]==a[i][y1]&&in(pos[vis[i][y1]],x1,y1,x2,y2)) st.insert(vis[i][y1]);
			if(y2<m&&a[i][y2+1]==a[i][y2]&&in(pos[vis[i][y2]],x1,y1,x2,y2)) st.insert(vis[i][y2]);
		}
		for(int i=y1;i<=y2;i++) {
			if(x1>1&&a[x1-1][i]==a[x1][i]&&in(pos[vis[x1][i]],x1,y1,x2,y2)) st.insert(vis[x1][i]);
			if(x2<n&&a[x2+1][i]==a[x2][i]&&in(pos[vis[x2][i]],x1,y1,x2,y2)) st.insert(vis[x2][i]);
		}
		cout<<st.size()+s[x2][y2]-s[x1-1][y2]-s[x2][y1-1]+s[x1-1][y1-1]<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}