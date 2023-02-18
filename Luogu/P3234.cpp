#include<bits/stdc++.h>
using namespace std;
#define uint unsigned int
const int N=1e5+10;
const uint P=1331;
int n,len[N],la[N],lb[N];
string a[N];
vector<vector<uint>> h;
int zh(char x) {
    if(x>='0'&&x<='9') return x-'0'+1;
    else if(x>='a'&&x<='z') return x-'a'+11;
    else return 37;
}
const int M=2e7+10;
uint Pow[M];
uint Hash(int i,int l,int r) {
    return h[i][r]-h[i][l-1]*Pow[r-l+1];
}
void solve() {
    cin>>n;
    int pos=-1,l1=0,l2=0;
    h.resize(n+3);
    for(int i=1;i<=n;i++) {
        cin>>a[i]; len[i]=(int)a[i].size(); a[i]=' '+a[i];
        h[i].resize(len[i]+3);
        for(int j=1;j<=len[i];j++) h[i][j]=h[i][j-1]*P+zh(a[i][j]);
        la[i]=len[i], lb[i]=1;
        for(int j=1;j<=len[i];j++) {
            if(a[i][j]=='*') la[i]=min(la[i],j-1), lb[i]=max(lb[i],j+1);
        }
        if(la[i]==len[i]) pos=i;
        else {
            if(l1<la[i]) l1=la[i], h[n+1]=h[i];
            if(l2<len[i]-lb[i]+1) l2=len[i]-lb[i]+1, h[n+2]=h[i], len[n+2]=len[i];
        }
    }
    if(pos==-1) {
        for(int i=1;i<=n;i++) {
            if((la[i]>=1&&Hash(i,1,la[i])!=Hash(n+1,1,la[i]))||(lb[i]<=len[i]&&Hash(i,lb[i],len[i])!=Hash(n+2,len[n+2]-(len[i]-lb[i]),len[n+2])))
                return cout<<"N\n", void();
        }
    }else {
        for(int i=1;i<=n;i++) {
            if(pos==i) continue;
            if(la[i]==len[i]) {
                if(len[i]!=len[pos]||Hash(i,1,len[i])!=Hash(pos,1,len[i])) return cout<<"N\n", void();
                continue;
            }
            if((la[i]>=1&&(la[i]>len[pos]||Hash(i,1,la[i])!=Hash(pos,1,la[i])))||(lb[i]<=len[i]&&(len[i]-lb[i]+1>len[pos]||Hash(i,lb[i],len[i])!=Hash(pos,len[pos]-(len[i]-lb[i]),len[pos])))) 
                return cout<<"N\n", void();
            int p=la[i]+2,edp,it=la[i]+1;
            while(p<=len[i]) {
                while(p<=len[i]&&a[i][p]=='*') p++;
                if(p>len[i]) break;
                for(edp=p;edp<len[i]&&a[i][edp+1]!='*';edp++);
                for(;it+edp-p<=len[pos]&&Hash(pos,it,it+edp-p)!=Hash(i,p,edp);it++);
                if(it+edp-p>len[pos]) return cout<<"N\n", void();
                p=edp+2, it=it+edp-p+1;
            }
            
            p=lb[i]-2,it=len[pos]-(len[i]-lb[i])-1;
            while(p>=1) {
                while(p>=1&&a[i][p]=='*') p--;
                if(p<1) break;
                for(edp=p;edp>1&&a[i][edp-1]!='*';edp--);
                for(;it+edp-p>=1&&Hash(pos,it+edp-p,it)!=Hash(i,edp,p);it--);
                if(it+edp-p<1) return cout<<"N\n", void();
                p=edp-2, it=it+edp-p-1;
            }
        }
    }
    cout<<"Y\n";
    return;
}
void init() {
    Pow[0]=1; for(int i=1;i<M;i++) Pow[i]=Pow[i-1]*P;
}
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr), cout.tie(nullptr);
    init();
    int T; cin>>T;
    while(T--) solve();
    return 0;
}