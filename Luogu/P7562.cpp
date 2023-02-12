#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k,l[N],r[N],f[N][20],X[N<<1];
typedef pair<int,int> PII;
set<PII> s;
int query(int l,int r) {
    int cnt=0;
    for(int i=19;i>=0;i--) if(f[l][i]<=r) cnt+=(1<<i), l=f[l][i];
    return cnt;
}
int main() {
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {
        scanf("%d%d",&l[i],&r[i]);
        X[i]=l[i], X[i+n]=r[i];
    }
    sort(X+1,X+2*n+1); int tot=unique(X+1,X+2*n+1)-X-1;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) {
        l[i]=lower_bound(X+1,X+tot+1,l[i])-X, r[i]=lower_bound(X+1,X+tot+1,r[i])-X;
        f[l[i]][0]=min(f[l[i]][0],r[i]);
    }
    for(int i=n;i>=1;i--) {
        f[i][0]=min(f[i][0],f[i+1][0]);
        for(int j=1;j<20;j++) f[i][j]=min(f[i][j-1],f[f[i][j-1]][j-1]);
    }
    if(query(1,tot)<k) {puts("-1"); return 0;} 
    s.insert(make_pair(1,tot));
    int cnt=0;
    for(int i=1;i<=n;i++) {
        set<PII>::iterator it=s.upper_bound(make_pair(l[i],r[i]-1));
        
        PII now=*(--it);
        if(now.first<=l[i]&&now.second>=r[i]-1) {
            if(query(now.first,l[i])+query(r[i],now.second+1)+1>=k) {
                printf("%d\n",i);
                cnt++, s.erase(now);
                if(cnt==k) return 0;
                if(now.first<=l[i]-1) s.insert(make_pair(now.first,l[i]-1));
                if(r[i]<=now.second) s.insert(make_pair(r[i],now.second));
            }
        }
    }
    return 0;
}