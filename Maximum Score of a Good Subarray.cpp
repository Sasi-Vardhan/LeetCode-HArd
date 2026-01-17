//this is solved using cpp and greddy taken intutuin from code story with mike
/*
  in any solution we need to include kth element for sure so lets build subarray from exact kth element 

here there is a Question how make sub array bigger the answer is expand the array in the direction which our answer is least effected so the thing is 

case 1: if left > right 

  in this case if we expand to left answer will change like this ,

  if nums[left] < currentMin , i will become currentMIn we will have new max answer let it be k1 but if we expand right nums[right] < currMin  sp new ans be k2 it will further decrease
and k2  < k1 for sure to avoid this lets move to the side which gives leaset effect

another Question wont length effect "NO" because when we expand we use this (j-i+1) this will include expanded left and expanded right at each stage

*/
class Solution {
public:
    int maximumScore(vector<int>& nums, int k) {
        int i = k, j = k;
        int n = nums.size();
        int mini = nums[k];
        int ans = mini;

        while(i > 0 || j < n - 1) {
            int left  = (i > 0) ? nums[i - 1] : 0;
            int right = (j < n - 1) ? nums[j + 1] : 0;

            // expand safely
            if(left >= right) {
                if(i > 0) {
                    i--;
                    mini = min(mini, nums[i]);
                } else {
                    j++;
                    mini = min(mini, nums[j]);
                }
            } else {
                if(j < n - 1) {
                    j++;
                    mini = min(mini, nums[j]);
                } else {
                    i--;
                    mini = min(mini, nums[i]);
                }
            }

            ans = max(ans, (j - i + 1) * mini);
        }
        return ans;
    }
};
