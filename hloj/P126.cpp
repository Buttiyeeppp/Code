#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
int n,k,p[N],tot;
int yep[10],cnt,a[10];
struct Segment {
    int len,op,v,l;
}d[N],b[N];
void reverse(int l,int r) {
    for(int i=1;i<=(r-l+2)/2;i++) swap(b[l+i-1],b[r-i+1]);
    for(int i=l;i<=r;i++) {
        b[i].op*=-1;
        if(i==1) b[i].l=1;
        else b[i].l=b[i-1].l+b[i-1].len;
    }
}
struct optition {
    int l,r;
}c[10];
void _dfs(int step) {
	int ok=1;
    for(int i=1;i<=cnt;i++) if(!((i==1||b[i].v>b[i-1].v)&&b[i].op>=0)) {
    	if(step==k+1) return;
    	else {ok=0; break;}
	}
	if(ok) {
        puts("TAK");
        for(int i=1;i<step;i++) printf("%d %d\n",c[i].l,c[i].r);
        for(int i=step;i<=k;i++) puts("1 1");
        exit(0);
	}
    for(int i=1;i<=cnt;i++)
        for(int j=i;j<=cnt;j++) {
            c[step]=optition{b[i].l,b[j].l+b[j].len-1}, reverse(i,j);
            _dfs(step+1);
            reverse(i,j);
        }
}
void dfs(int step) {
    if(step==tot+1) {
        cnt=0;
        for(int i=1;i<=tot;i++) {
            if(!yep[i]) b[++cnt]=d[i];
            else {
                int s=d[i].v;
                for(int j=1;j<=d[i].len;j++) b[++cnt]=Segment{1,0,s,0}, s+=d[i].op;
            }	
        }
        if(cnt>2*k+1) return; 
        for(int i=1;i<=cnt;i++) {
            if(i==1) b[i].l=1;
            else b[i].l=b[i-1].l+b[i-1].len;
        }
        _dfs(1);
        return;
    }
    yep[step]=1;
    dfs(step+1);
    yep[step]=0;
    dfs(step+1);
}
int main() {
    freopen("rev.in","r",stdin);
    freopen("rev.out","w",stdout);
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++) {
        scanf("%d",&p[i]);
        if(p[i]==p[i-1]+1&&tot&&d[tot].op>=0) d[tot].len++, d[tot].op=1;
        else if(p[i]==p[i-1]-1&&tot&&d[tot].op<=0) d[tot].len++, d[tot].op=-1;
        else d[++tot]=Segment{1,0,p[i],0};
    }
    // for(int i=1;i<=tot;i++) cout<<"Seg "<<d[i].op<<" "<<d[i].mn<<" "<<d[i].len<<endl;
    if(tot>2*k+1) {puts("NIE"); return 0;}
    dfs(1);
    puts("NIE");
    return 0;
}