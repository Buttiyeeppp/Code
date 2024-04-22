#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using PII=pair<int,int>;
bool memory1;
int qry1(int x,int y) {
    cout<<1<<" "<<x-1<<" "<<y-1<<endl;
    int c; return cin>>c, c;
}
int li[110],nl[110],m;
int qry2(int x,int y) {
    cout<<2<<" "<<li[x]-1<<" "<<y<<" ";
    for(int i=1;i<=y;i++) cout<<li[i]-1<<" ";
    cout<<endl;
    int c; return cin>>c, c;
}
void ins(int pos,int x) {
    nl[pos]=x, m++;
    for(int i=1;i<pos;i++) nl[i]=li[i];
    for(int i=pos;i<=m;i++) nl[i+1]=li[i];
    for(int i=1;i<=m;i++) li[i]=nl[i];
}
int pre[110],id[110],vis[110];
void solve() {
    int n; cin>>n;
    m=0, li[++m]=1;
    for(int i=2;i<=n;i++) {
        int l=0,r=m+1;
        while(l+1<r) {
            int mid=(l+r)>>1;
            if(qry1(i,li[mid])) r=mid;
            else l=mid;
        }
        if(r==m+1) li[++m]=i;
        else ins(r,i);
    }
    for(int i=1;i<=n;i++) pre[i]=i;
    memset(vis,0,sizeof(vis));
    for(int i=n;i>=2;i--) {
        int pd=0;
        for(int j=1;j<=n;j++) if(pre[j]==i&&!vis[j]) {
            if(qry2(j,pre[j]-1)) {pd=1;break;}
            else vis[j]=1;
        }
        if(!pd) continue;
        for(int j=1;j<=n;j++) if(pre[j]==i) pre[j]=i-1;
    }

    // cout<<"Chk"<<endl;
    // for(int i=1;i<=n;i++) cout<<li[i]<<" "; cout<<endl;
    // for(int i=1;i<=n;i++) cout<<pre[i]<<" "; cout<<endl;

    for(int i=1;i<=n;i++) id[li[i]]=i;
    cout<<3<<endl;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cout<<(pre[id[i]]<=id[j]);
        }
        cout<<endl;
    }
    int res; cin>>res;
}
bool memory2;
int main() {

    int T; cin>>T;
    while(T--) solve();

    return 0;
}