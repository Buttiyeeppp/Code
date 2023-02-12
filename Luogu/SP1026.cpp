#include<bits/stdc++.h>
using namespace std;
#define ld long double
const int N=1e3+10;
ld h[N];
int t,n;
int main() {
    for(int i=1;i<N;i++) h[i]=h[i-1]+1.0/i;
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&n);
        printf("%.2Lf\n",h[n]*n);
    }
    return 0;
}