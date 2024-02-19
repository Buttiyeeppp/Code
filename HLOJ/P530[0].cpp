#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*clock()/CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;

typedef unsigned int uint;
int T, n, m, t; uint seed;
const int N=5e3+10;
bool a[N][N];

bool Rand(uint &x) {
    x^=x<<16;
    x^=x>>5;
    x^=x<<1;
    return (x&65535)<(uint)t;
}

namespace zero {
    int p[N],st[N];
    ll calc() {
        ll ans=0;
        for(int i=1;i<=n;i++) p[i]=m+1;
        for(int j=m;j>=1;j--) {
            ll res=0, top=0;
            st[++top]=n+1;
            for(int i=n;i>=1;i--) {
                if(a[i][j]) p[i]=j;
                while(top>1&&p[i]<=p[st[top]]) {
                    res-=(p[st[top]]-j)*(st[top-1]-st[top]);
                    top--;
                }
                st[++top]=i;
                res+=(p[st[top]]-j)*(st[top-1]-st[top]);
                ans+=res;
            }
        }
        return ans;
    }
}

namespace one {
    int p[N][2],mp[N];
    ll res=0;
    struct Stack {
        int st[N],c[N],top;
        // void push(int x,int val) { st[++top]=x; c[top]=val; res+=val; }
        // void pop() { res-=c[top], top--; }
        // int front() { return st[top]; }
    }l,r;
    void Rinsert(int i) {
        while(r.top>1&&p[i][1]<=p[r.st[r.top]][1]) {
            res-=r.c[r.top--];
        }
        int val=p[i][1]*(r.st[r.top]-i);
        r.st[++r.top]=i, r.c[r.top]=val, res+=val;
    }
    // void Min(int &x,int y) { if(y<x) x=y; }
    ll calc() {
        ll ans=0;
        for(int i=1;i<=n;i++) p[i][0]=p[i][1]=mp[i]=m+1;
        for(int j=m;j>=1;j--) {
            res=l.top=r.top=0;
            l.st[++l.top]=n+1, r.st[++r.top]=n+1;
            for(int i=n;i>=1;i--) {
                if(a[i][j]) p[i][1]=p[i][0], p[i][0]=j;
                mp[i]=p[i][1];
                vector<int> vc;
                int lst=0;
                while(l.top>1&&p[i][0]<=p[l.st[l.top]][0]) {
                    vc.push_back(l.st[l.top]);
                    // Min(p[l.st[l.top]][1],p[l.st[l.top]][0]);
                    if(p[l.st[l.top]][0]<p[l.st[l.top]][1]) p[l.st[l.top]][1]=p[l.st[l.top]][0];
                    lst=l.st[l.top-1]-1;
                    res-=l.c[l.top--];
                }

                int val=-p[i][0]*(l.st[l.top]-i);
                l.st[++l.top]=i, l.c[l.top]=val, res+=val;

                while(vc.size()&&r.top>1&&r.st[r.top]<=lst) res-=r.c[r.top--];

                if(l.top>2) {
                    vc.push_back(l.st[l.top-1]);
                    // Min(p[l.st[l.top-1]][1],p[l.st[l.top]][0]);
                    if(p[l.st[l.top]][0]<p[l.st[l.top-1]][1]) p[l.st[l.top-1]][1]=p[l.st[l.top]][0];
                }

                for(int k=vc.size()-1;k>=0;k--) Rinsert(vc[k]);
                Rinsert(i);
                ans+=res;
            }
            for(int i=1;i<=n;i++) p[i][1]=mp[i];
        }
        return ans;
    }
}

bool mem2;
int main() {
    freopen("potato.in","r",stdin);
    freopen("potato.out","w",stdout);
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n>>m>>t>>seed;
    ll z=0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++) 
            a[i][j]=Rand(seed), z+=(n-i+1)*(m-j+1);

    // one::calc();
    // return cout<<one::calc()<<" "<<zero::calc()<<endl, 0;

    cout<<z-zero::calc()-one::calc()<<endl;

    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}