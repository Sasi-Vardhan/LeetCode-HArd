/*
  this problem solution intution is taken from code story with mike
where the observation should be maximum with more example to formulate optimal approach

*/

class Solution {
public:
    vector<int> minBitwiseArray(vector<int>& nums) {
        unordered_map<int,int>seen;
        vector<int>ans;
        for(int i=0;i<nums.size();i++){
            if(nums[i]==2)ans.push_back(-1);
            else{
                for(int j=0;j<32;j++){
                    if((nums[i] & (1<<j)) > 0){
                        continue;
                    }
                    //the bit is 0 then the previous bit to be set as 0 to ans[i] for this lets use XOR which make 1 1 as 0 and 0 0 as 0 
                    ans.push_back(nums[i] ^ (1<<(j-1)));
                    break;
                }
            }
        }
        return ans;
    }
};
