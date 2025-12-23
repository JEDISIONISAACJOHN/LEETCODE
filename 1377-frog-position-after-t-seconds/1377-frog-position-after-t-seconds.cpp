class Solution {
public:
double ans;

    bool dfs(int node,unordered_map<int,vector<int>> &mpp,double prob,int t,int target,int cnt){
        if(cnt>t)return false;
        if(node==target){
            if(cnt<t){
                if(mpp[node].size()==0){
                    ans=prob;
                    return true;
                }
                else if(mpp[node].size()!=0)return false;
            }
            else if(cnt==t){
                ans=prob;
                return true;
            }
        }
        int temp=mpp[node].size();
        
        
        for(int i=0;i<temp;i++){
            if(dfs(mpp[node][i],mpp,prob/(double)temp,t,target,cnt+1)){
                return true;
            }
        }
        return false;
    }

    double frogPosition(int a, vector<vector<int>>& edges, int t, int target) {
        int n=edges.size();
        unordered_map<int,vector<int>> mpp;
        unordered_set<int> st;
        st.insert(1);
        for(int i=0;i<n;i++){
            int a=edges[i][0];
            int b=edges[i][1];
            if(st.find(a)!=st.end()){
                mpp[a].push_back(b);
                st.insert(b);
            }
            else if(st.find(b)!=st.end()){
                mpp[b].push_back(a);
                st.insert(a);
            }
        }

        if(!dfs(1,mpp,1,t,target,0)){return 0;}
        return ans;
    }
};