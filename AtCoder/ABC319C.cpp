#include <bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int a[10][10],vis[10][10],ans;
void dfs(int step) {
    if(step==10) {
        for(int i=1;i<=3;i++) {
            for(int j=1;j<=3;j++) {
                int temp=0, pd=1;
                for(int k=1;k<=3;k++) if(k!=j) {
                    if(!temp) temp=a[i][k];
                    else if(a[i][k]!=temp) pd=0;
                    if(vis[i][j]<vis[i][k]) pd=0;
                }
                if(pd) return ans++, void();
            }
            for(int j=1;j<=3;j++) {
                int temp=0, pd=1;
                for(int k=1;k<=3;k++) if(k!=j) {
                    if(!temp) temp=a[k][i];
                    else if(a[k][i]!=temp) pd=0;
                    if(vis[j][i]<vis[k][i]) pd=0;
                }
                if(pd) return ans++, void();
            }
        }
        for(int i=1;i<=3;i++) {
            int temp=0, pd=1;
            for(int j=1;j<=3;j++) if(i!=j) {
                if(!temp) temp=a[j][j];
                else if(a[j][j]!=temp) pd=0;
                if(vis[i][i]<vis[j][j]) pd=0;
            }
            if(pd) return ans++, void();
        }
        for(int i=1;i<=3;i++) {
            int temp=0, pd=1;
            for(int j=1;j<=3;j++) if(i!=j) {
                if(!temp) temp=a[j][4-j];
                else if(a[j][4-j]!=temp) pd=0;
                if(vis[i][4-i]<vis[j][4-j]) pd=0;
            }
            if(pd) return ans++, void();
        }        
        return;
    }
    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++) if(!vis[i][j]) {
            vis[i][j]=step;
            dfs(step+1);
            vis[i][j]=0;
        }
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    for(int i=1;i<=3;i++)
        for(int j=1;j<=3;j++) cin>>a[i][j];
    dfs(1);
    cerr<<ans<<endl;
    int v=1;
    for(int i=2;i<=9;i++) v*=i;
    cout<<fixed<<setprecision(10)<<1.*(v-ans)/v<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}