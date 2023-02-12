#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int N=5e4+10;
int n,L,sta[N];
ll s[N],dp[N];
ll a(int i) { return s[i]+i; }
ll b(int i) { return s[i]+i+L+1; }
ll x(int i) { return b(i); }
ll y(int i) { return dp[i]+b(i)*b(i); }
double slope(int i,int j) { 
    return 1.0*(y(j)-y(i))/(x(j)-x(i));
}
int main() {
    cin>>n>>L;
    for(int i=1,c;i<=n;i++) {
        cin>>c;
        s[i]=s[i-1]+c;
    }
    int head=0,tail=0;
    for(int i=1;i<=n;i++) {
        while(head<tail&&slope(sta[head],sta[head+1])<2*a(i)) head++;
        int j=sta[head];
        dp[i]=dp[j]+(a(i)-b(j))*(a(i)-b(j));
        while(head<tail&&slope(i,sta[tail-1])<=slope(sta[tail-1],sta[tail])) tail--;
        sta[++tail]=i;
    }
    cout<<dp[n];
    return 0;
}