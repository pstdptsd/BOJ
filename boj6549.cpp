// 6549. Largest Rectangle in a Histogram

#include <bits/stdc++.h>

using namespace std;

using ll=long long;

ll arr[100001];
ll ml[100001], mr[100001];

int main() {
    while(1) {
        int n; scanf("%d", &n);
        if(!n) break;
        
        stack<int> st;
        for(int i=1;i<=n;i++){
            scanf("%lld", &arr[i]);
            while(st.size()) {
                int x=st.top();
                if(arr[x]<arr[i]) break;
                st.pop();             
            }
            
            if(st.empty()) ml[i]=0;
            else ml[i]=st.top();
            
            st.push(i);
        }
        
        st=stack<int>();
        for(int i=n;i>=1;i--) {
            while(st.size()) {
                int x=st.top();
                if(arr[x]<arr[i])break;
                st.pop();
            }
            
            if(st.empty()) mr[i]=n;
            else mr[i]=st.top()-1;
            
            st.push(i);
        }
        
        ll res=0;
        for(int i=1;i<=n;i++) {
            res=max(res, (mr[i]-ml[i])*arr[i]);
        }
        
        printf("%lld\n", res);
    }
}