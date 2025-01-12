#include<bits/stdc++.h>
using namespace std;
#define ull unsigned long long
const int N=5e3+10;
const int M=2e2+10;
const int P=13331;
const int Mod=2e6+3;
int d,n,m,fa[M][N],sz[M][N];
vector<int> node[M][N];
ull z[N],mul[M];
struct HashTable {
    int head[Mod],nxt[Mod],cnt[Mod],tot;
    ull v[Mod];
    HashTable() {for(int i=0;i<Mod;i++) head[i]=nxt[i]=v[i]=-1, cnt[i]=0;}
    int Modify(ull val,int op) {
        int p=head[val%Mod],l=-1;
        while((~p)&&v[p]!=val) l=p, p=nxt[p];
        if(v[p]==val) {
            cnt[p]+=op;
            if(!cnt[p]) {
                if(~l)nxt[l]=nxt[p]; else head[val%Mod]=nxt[p];
                nxt[p]=v[p]=-1;
            }
            return cnt[p];
        }
        p=++tot;
        // if(~l) p=(l+1)%Mod; else p=val%Mod;
        // while(~v[p]) p=(p+1)%Mod;
        if(~l) nxt[l]=p; else head[val%Mod]=p;
        cnt[p]+=op, v[p]=val;
        return cnt[p];
    }
}hs;
int main() {
    scanf("%d%d%d",&d,&n,&m);
    mul[0]=1;
    for(int i=1;i<=d;i++) mul[i]=mul[i-1]*P;
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=d;j++) {
            fa[j][i]=i, sz[j][i]=1, node[j][i].emplace_back(i);
            z[i]+=mul[j]*i;
        }
        hs.Modify(z[i],1);
    }
    int ans=n;
    for(int i=1,a,b,k;i<=m;i++) {
        scanf("%d%d%d",&a,&b,&k);
        a=fa[k][a], b=fa[k][b];
        if(a==b) {printf("%d\n",ans); continue;}
        if(sz[k][a]<sz[k][b]) swap(a,b);
        sz[k][a]+=sz[k][b]; sz[k][b]=0;
        ull tmp=mul[k]*(a-b);
        for(auto now:node[k][b]) {
            node[k][a].emplace_back(now), fa[k][now]=a;
            ans-=hs.Modify(z[now],-1)*2;
            ans+=(hs.Modify(z[now]+tmp,1)-1)*2;
            z[now]+=tmp;
        }
        node[k][b].clear();
    	printf("%d\n",ans);
    }
    return 0;
}
