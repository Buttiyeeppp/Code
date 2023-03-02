#include<bits/stdc++.h>
using namespace std;
const int M=1e5+10;
const int INF=0x3f3f3f3f;
int n,m,ans[M];
vector<vector<int>> r,d,dis,vis;
struct node { int x,y; };
typedef pair<int,node> PII;
struct road { int id,Xa,Xb,Ya,Yb; }rd[M],now[M];
bool in(int x,int y,int A,int B,int C,int D) { return (x>=A&&x<=C&&y>=B&&y<=D); }
struct cmp {
	bool operator()(PII x,PII y) { return x.first>y.first; }
};
void Dijkstra(int stx,int sty,int A,int B,int C,int D) {
	for(int i=A;i<=C;i++) for(int j=B;j<=D;j++) dis[i][j]=INF, vis[i][j]=0;
	priority_queue<PII,vector<PII>,cmp> q;
	dis[stx][sty]=0; q.emplace(0,(node){stx,sty});
	while(q.size()) {
		node nd=q.top().second; q.pop();
		int x=nd.x, y=nd.y;
		if(vis[x][y]) continue;
		vis[x][y]=1;
		if(in(x-1,y,A,B,C,D)&&dis[x-1][y]>dis[x][y]+d[x-1][y]) dis[x-1][y]=dis[x][y]+d[x-1][y], q.emplace(dis[x-1][y],(node){x-1,y});
		if(in(x,y-1,A,B,C,D)&&dis[x][y-1]>dis[x][y]+r[x][y-1]) dis[x][y-1]=dis[x][y]+r[x][y-1], q.emplace(dis[x][y-1],(node){x,y-1});
		if(in(x+1,y,A,B,C,D)&&dis[x+1][y]>dis[x][y]+d[x][y]) dis[x+1][y]=dis[x][y]+d[x][y], q.emplace(dis[x+1][y],(node){x+1,y});
		if(in(x,y+1,A,B,C,D)&&dis[x][y+1]>dis[x][y]+r[x][y]) dis[x][y+1]=dis[x][y]+r[x][y], q.emplace(dis[x][y+1],(node){x,y+1});
	}
}
void solve(int A,int B,int C,int D,int L,int R) {
	if(A==C&&B==D) {
		for(int i=L;i<=R;i++) ans[rd[i].id]=0;
		return;
	}
	if(C-A<D-B) {
		int mid=(B+D)/2;
		int tot1=0,tot2=0,p1,p2,p3;
		for(int i=L;i<=R;i++) {
			if((rd[i].Ya<=mid)!=(rd[i].Yb<=mid)) tot1++;
			else if(rd[i].Yb<=mid) tot2++;
		}
		p1=L, p2=L+tot1, p3=L+tot1+tot2;
		for(int i=L;i<=R;i++) {
			if((rd[i].Ya<=mid)!=(rd[i].Yb<=mid)) now[p1++]=rd[i];
			else if(rd[i].Yb<=mid) now[p2++]=rd[i];
			else now[p3++]=rd[i];
		}
		for(int i=L;i<=R;i++) rd[i]=now[i];
		for(int i=A;i<=C;i++) {
			Dijkstra(i,mid,A,B,C,D);
			for(int i=L;i<=R;i++) ans[rd[i].id]=min(ans[rd[i].id],dis[rd[i].Xa][rd[i].Ya]+dis[rd[i].Xb][rd[i].Yb]);
		}
		if(tot2&&B<=mid) solve(A,B,C,mid,L+tot1,L+tot1+tot2-1);
		if(L+tot1+tot2<=R&&mid+1<=D) solve(A,mid+1,C,D,L+tot1+tot2,R);
	}
	else {
		int mid=(A+C)/2;
		int tot1=0,tot2=0,p1,p2,p3;
		for(int i=L;i<=R;i++) {
			if((rd[i].Xa<=mid)!=(rd[i].Xb<=mid)) tot1++;
			else if(rd[i].Xb<=mid) tot2++;
		}
		p1=L, p2=L+tot1, p3=L+tot1+tot2;
		for(int i=L;i<=R;i++) {
			if((rd[i].Xa<=mid)!=(rd[i].Xb<=mid)) now[p1++]=rd[i];
			else if(rd[i].Xb<=mid) now[p2++]=rd[i];
			else now[p3++]=rd[i];
		}
		for(int i=L;i<=R;i++) rd[i]=now[i];
		for(int i=B;i<=D;i++) {
			Dijkstra(mid,i,A,B,C,D);
			for(int i=L;i<=R;i++) ans[rd[i].id]=min(ans[rd[i].id],dis[rd[i].Xa][rd[i].Ya]+dis[rd[i].Xb][rd[i].Yb]);
		}
//		cerr<<"Here\n";
		if(tot2&&A<=mid) solve(A,B,mid,D,L+tot1,L+tot1+tot2-1);
		if(L+tot1+tot2<=R&&mid+1<=C) solve(mid+1,B,C,D,L+tot1+tot2,R);		
	}
	
}
int main() {
	scanf("%d%d",&n,&m);
	r.resize(n+1), d.resize(n+1), dis.resize(n+1), vis.resize(n+1);
	for(int i=1;i<=n;i++) r[i].resize(m+1), d[i].resize(m+1), dis[i].resize(m+1), vis[i].resize(m+1);
	for(int i=1;i<=n;i++) for(int j=1;j<m;j++) scanf("%d",&r[i][j]);
	for(int i=1;i<n;i++) for(int j=1;j<=m;j++) scanf("%d",&d[i][j]);
	int q; scanf("%d",&q);
	for(int i=1;i<=q;i++) scanf("%d%d%d%d",&rd[i].Xa,&rd[i].Ya,&rd[i].Xb,&rd[i].Yb), rd[i].id=i, ans[i]=INF;
	solve(1,1,n,m,1,q);
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
	return 0;
}
