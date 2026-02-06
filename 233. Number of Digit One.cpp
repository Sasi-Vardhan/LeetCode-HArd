/*

this done as we will keep track of each position in the length 
with states including pos, flag refeers to if it can take any value from 0 to 9 intially pos=0 should have flag=1 and cnt_of_1 it tracks how many 1's are there before the current position

doubt may be why is it required 
think of 21 and 31 and do a dry run yoou fill end error


  */

class Solution {
public:

    int dp[12][2][11];

    //nums will have the limit for the value it can take 

    int findSolution(vector<int>&nums,int pos,int end,int flag,int cnt_of_1){
        if(pos==end)return cnt_of_1;
        if(dp[pos][flag][cnt_of_1]!=-1)return dp[pos][flag][cnt_of_1];
        int res=0;
        if(flag==0){
            for(int i=0;i<=9;i++){
                res+=(i==1)?findSolution(nums,pos+1,end,flag,cnt_of_1+1):findSolution(nums,pos+1,end,flag,cnt_of_1);
            }
        }
        if(flag==1){
             for(int i=0;i<=nums[pos];i++){
               
                    if(i==nums[pos])flag=1;
                    else flag=0;
                    res+=(i==1)?findSolution(nums,pos+1,end,flag,cnt_of_1+1):findSolution(nums,pos+1,end,flag,cnt_of_1);
                
            }
        }
        return dp[pos][flag][cnt_of_1]=res;
        }
        
    

    int countDigitOne(int n) {
        //digit dp for solving problem
        memset(dp,-1,sizeof(dp));
        int temp=n;
        vector<int>nums;
        while(temp>0){
            nums.push_back(temp%10);
            temp=temp/10;
        }
        reverse(nums.begin(),nums.end());
        int size=nums.size();
        int flag=1;
        int pos=0;
        int cnt_of_1=0;
        return findSolution(nums,pos,size,flag,cnt_of_1);
    }
};
