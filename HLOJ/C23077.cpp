#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#define endl '\n'
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
bool mem1;
__int128 f[N][N];
void write(__int128 x) {
	if(x<0) putchar('-'),x=-x;
	if(x>=10) write(x/10);
	putchar((x%10)+'0');
}
struct num {
	num() { len=0; memset(x,0,sizeof(x)); }
	int len,x[N];
};
bool mem2;
int main() {
//	ios::sync_with_stdio(false), cin.tie(0);
	
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++) f[i][j]=1e36;
	write(f[0][0]); return 0;
	for(int i=1;i<N;i++) {
		f[i][1]=0;
		if(i==1) f[i][3]=2;
		else if(i<=60) f[i][3]=f[i-1][3]<<1;
	}
	for(int i=1;i<=60;i++) f[i][3]--;
	f[1][2]=f[1][4]=1;
	for(int i=2;i<N;i++)
		for(int k=i-1;i-k<=60&&k>=1;k--) f[i][4]=min(f[i][4],2*f[k][4]+f[i-k][3]);
	for(int j=5;j<N;j++) {
		int p=1;
		for(int i=1;i<N;i++) {
			if(i==1) f[i][j]=1;
			else {
//				for(int k=1;k<i;k++) f[i][j]=min(f[i][j],2*f[k][j]+f[i-k][j-1]);
				if(p+1<i&&2*f[p][j]+f[i-p][j-1]>2*f[p+1][j]+f[i-p-1][j-1]) p++;
				f[i][j]=min(f[i][j],2*f[p][j]+f[i-p][j-1]);
			}
			
		}
	}
	int q; cin>>q;
	for(int i=1,n,m;i<=q;i++) {
		cin>>n>>m;
		if(m==3) {
			num now; now.len=1,now.x[1]=1;
			while(n--) {
				for(int j=1;j<=now.len;j++) now.x[j]*=2;
				for(int j=1;j<=now.len;j++) if(now.x[j]>=10) {
					now.x[j+1]+=now.x[j]/10, now.x[j]%=10;
					if(j==now.len) now.len++;
				}
			}
			now.x[1]--;
			for(int j=now.len;j>=1;j--) cout<<now.x[j];
			cout<<endl;
		}
		else if(f[n][m]==1e36) cout<<"No Solution"<<endl;
		else write(f[n][m]), cout<<endl;
	}
	
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<endl;
	return 0;
}