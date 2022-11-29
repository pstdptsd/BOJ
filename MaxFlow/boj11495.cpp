// 11495. 격자 0 만들기

#include<bits/stdc++.h>

using namespace std;

int dv[]={0,1,0,-1,0};

struct MF {
    struct edge{
        int to,cap,flow,rev;
    };
    int sz,Src,Ter;
    vector<vector<edge>> adj;
    vector<int> level,work;
    
    MF(int sz,int S,int T):sz{sz},Src{S},Ter{T} {
        adj=vector<vector<edge>>(sz);
    }
    
    bool bfs(){
        level=vector<int>(sz,-1);
        level[Src]=0;
        queue<int> q;
        q.push(Src);
        while(!q.empty() && level[Ter]==-1){
            int cur=q.front();
            q.pop();
            for(int i=0;i<adj[cur].size();i++){
                edge te=adj[cur][i];
                int nxt=te.to;
                if(level[nxt]==-1 && te.cap-te.flow>0){
                    level[nxt]=level[cur]+1;
                    if(nxt==Ter) break;
                    q.push(nxt);
                }
            }
        }
        return level[Ter]!=-1;
    }
    
    int dfs(int cur,int flow){
        if(cur==Ter) return flow;
        for(int &i=work[cur];i<adj[cur].size();i++){
            edge te=adj[cur][i];
            int nxt=te.to;
            if(level[nxt]==level[cur]+1 && te.cap-te.flow>0){
                int f=dfs(nxt, min(flow, te.cap-te.flow));
                if(!f) continue;
                
                adj[cur][i].flow+=f;
                adj[nxt][te.rev].flow-=f;
                return f;
            }
        }
        return 0;
    }
    
    int solve(){
        int tFlow=0;
        while(bfs()){
            work=vector<int>(sz,0);
            while(1) {
                int flow=dfs(Src,INT_MAX);
                if(!flow) break;
                tFlow+=flow;
            }
        }
        return tFlow;
    }
    
    void link(int u,int v,int c){
        adj[u].push_back({v,c,0,(int)adj[v].size()});
        adj[v].push_back({u,0,0,(int)adj[u].size()-1});
    }
};

int main(){
    int T; scanf("%d",&T);
    while(T--){
        int n,m; scanf("%d%d",&n,&m);
        int S=n*m, T=n*m+1;
        MF mf(2+n*m, S, T);
        
        int ts=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                int c; scanf("%d",&c);
                ts+=c;
                if((i+j)%2){
                    mf.link(i*m+j,T,c);
                    continue;
                } 
                mf.link(S,i*m+j,c);
                for(int k=0;k<4;k++){
                    int y=i+dv[k],x=j+dv[k+1];
                    if(y<0 || y>=n || x<0 || x>=m) continue;
                    mf.link(i*m+j, y*m+x, INT_MAX);
                }               
            }
        }
        
        printf("%d\n", ts-mf.solve());
    }
}