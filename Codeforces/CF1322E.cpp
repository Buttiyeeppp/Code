#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int n,a[N],yep[N],ans[N],t,X[N];
vector<int> pos[N];
set<int> p,f;
void ins(int x) {
    yep[x]=1;
    if(x>1&&!yep[x-1]) p.erase(x-1); else p.insert(x-1);
    if(x<n&&!yep[x+1]) p.erase(x); else p.insert(x);
}
void calc2(int l,int r,int val) {
    set<int>::iterator it=f.lower_bound(l);
    int z;
    while(it!=f.end()&&*it<=r) z=*it, ans[z]=val, it++, f.erase(z);
}
void calc(int x,int val) {
    if(x<0||x>n) return;
    set<int>::iterator it=p.lower_bound(x);
    int r=*it, l=(*(--it))+1;
    t=max(t,(r-l)/2);
    if(yep[l]) calc2(l,(l+r)/2,val);
    if(yep[r]) calc2((l+r)/2+1,r,val);
}
int main() {
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%d",&a[i]), X[i]=a[i];
    sort(X+1,X+n+1); int tot=unique(X+1,X+n+1)-X-1;
    p.insert(0);
    for(int i=1;i<=n;i++) {
        a[i]=lower_bound(X+1,X+tot+1,a[i])-X;
        p.insert(i), f.insert(i), pos[a[i]].push_back(i);
    }
    for(int i=1;i<=tot;i++) {
        for(auto now:pos[i]) ins(now);
        for(auto now:pos[i]) calc(now,X[i]), calc(now-1,X[i]), calc(now+1,X[i]);
    }
    printf("%d\n",t);
    for(int i=1;i<=n;i++) printf("%d ",ans[i]);
    return 0;
}