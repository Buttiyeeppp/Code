#include<bits/stdc++.h>
using namespace std;
#define clo 1000.*CLOCKS_PER_SEC
#ifndef xxzx
#define endl '\n'
#endif
using ll=long long;
using PII=pair<int,int>;
bool mem1;
int n;
struct node {
    int a,b,c;
};
vector<node> ans;
bool check(int x,int y) {
    if(ans[x].a<ans[y].a) swap(x,y);
    if(ans[x].b<ans[y].b) return true;
    if(ans[x].c<ans[y].c) return true;
    return false;
}
bool mem2;
int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    cin>>n;
    if(n==1) {
        ans.push_back({0,0,1});
        ans.push_back({0,1,0});
        ans.push_back({1,0,0});
    }
    else {
        int v=n+(n+1)/2;
        for(int i=0;i<=n;i++) {
            for(int j=0;j+i<=v&&j<=n;j++) {
                int k=v-i-j;
                if(k<=n) ans.push_back({i,j,k});
            }
        }
    }
    cout<<ans.size()<<endl;
    for(auto now:ans) cout<<now.a<<" "<<now.b<<" "<<now.c<<endl;
    // for(int i=0;i<(int)ans.size();i++)
    //     for(int j=i+1;j<(int)ans.size();j++) if(!check(i,j)) cerr<<"Wrong!"<<endl;
    
    #ifdef xxzx
    cerr<<"Time: "<<clo<<"MS"<<endl;
    cerr<<"Memory: "<<abs(&mem1-&mem2)/1024./1024.<<"MB"<<endl;
    #endif
    return 0;
}