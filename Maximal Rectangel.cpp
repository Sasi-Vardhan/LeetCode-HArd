class Solution {
public:
vector<int>leftMaximums(vector<int>&nums,int size){
        vector<int>ans(size,0);
        ans[0]=0;
        stack<int>s;
        s.push(0);
        for(int i=1;i<size;i++){
            int pos=i;
            while(!(s.empty()) && nums[s.top()] >= nums[i] && s.top() != -1){
                pos=s.top();
                s.pop();
            }
           ans[i]=s.empty()?0:s.top()+1;
           s.push(i);
        }
        return ans;
    }

   int rightMaximums(vector<int>&nums,int size,vector<int>&left){
        // vector<int>ans(size,0);
        stack<int>s;
        // ans[size-1]=size-1;
        // s.push(size-1);
        int res=INT_MIN;
        for(int i=size-1;i>=0;i--){
            int pos=i;
            while(!(s.empty()) && s.top() != -1 && nums[s.top()] >= nums[i]) {
                
                s.pop();
            }
            // ans[i]=s.empty()?size-1:s.top()-1;
            res=max(res,((s.empty()?size-1:s.top()-1)-left[i]+1)*nums[i]);
            s.push(i);
        }
        return res;
    }

    int largestRectangleArea(vector<int>& heights) {
        vector<int>lefts;
        vector<int>rights;
        lefts=leftMaximums(heights,heights.size());
        return rightMaximums(heights,heights.size(),lefts);
    }
    int maximalRectangle(vector<vector<char>>& matrix) {
        int cols=matrix[0].size();
        vector<int>row(cols,0);
        int rows=matrix.size();
        int ans=INT_MIN;
        for(int i=0;i<rows;i++){
            for(int j=0;j<cols;j++){
                if(matrix[i][j]=='0'){
                    row[j]=0;
                }
                else{
                    row[j]+=1;
                }
            }
            ans=max(ans,largestRectangleArea(row));
            // cout<<ans<<endl;
        }
        return ans;
    }
};
