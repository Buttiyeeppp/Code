#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
const int N=2e3+10;
bool mem1;
int n,m,bj[2][N],cnt[30][N],cnt2[30][N],vis[2][N],sc[N][N];
string a[N];
bool mem2;
int main() {
	ios::sync_with_stdio(false), cin.tie(0);
	
	cin>>n>>m;
	for(int i=1;i<=n;i++) {
		cin>>a[i]; a[i]=" "+a[i];
		for(int j=1;j<=m;j++) {
			cnt[a[i][j]-'a'][i]++, cnt2[a[i][j]-'a'][j]++, cnt[26][i]++, cnt2[26][j]++;	
		}
	}
	int pd=1;
	while(pd) {
		pd=0;
		for(int i=1;i<=n;i++) if(!vis[0][i]) {
		 	for(int c=0;c<26;c++) {
				if(cnt[c][i]==cnt[26][i]&&cnt[c][i]>=2) { bj[0][i]=vis[0][i]=1, pd=1; break; }
			}
		}
		for(int j=1;j<=m;j++) if(!vis[1][j]) {
			for(int c=0;c<26;c++){
				if(cnt2[c][j]==cnt2[26][j]&&cnt2[c][j]>=2){ bj[1][j]=vis[1][j]=1, pd=1; break; } 
			}
		}
		for(int i=1;i<=n;i++) if(bj[0][i]) {
			bj[0][i]=0;
			for(int j=1;j<=m;j++) if(!sc[i][j]) {
				sc[i][j]=1;
				cnt[a[i][j]-'a'][i]--, cnt[26][i]--, cnt2[a[i][j]-'a'][j]--, cnt2[26][j]--;
			}
		}
		for(int j=1;j<=m;j++) if(bj[1][j]) {
			bj[1][j]=0;
			for(int i=1;i<=n;i++) if(!sc[i][j]) {
				sc[i][j]=1;
				cnt[a[i][j]-'a'][i]--, cnt[26][i]--, cnt2[a[i][j]-'a'][j]--, cnt2[26][j]--;	
			}
		}
		if(!pd) break;
	}
	int ans=0;
	for(int i=1;i<=n;i++) 
		for(int j=1;j<=m;j++) ans+=(sc[i][j]==0);
	cout<<ans<<endl;
	
	#ifdef xxzx
	cerr<<"Time: "<<clo<<"Ms"<<endl;
	cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
	#endif
	return 0;
}

