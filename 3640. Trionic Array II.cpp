Intuition
A trionic subarray follows a very specific pattern—think of it like a roller coaster 🎢:

Strictly increasing ⬆️
Strictly decreasing ⬇️
Strictly increasing again ⬆️
So the shape is: climb → drop → climb.

To reason about this cleanly, we imagine walking through the array while being in one of four states:

State 0: Not started yet (still skipping elements)
State 1: In the first increasing segment
State 2: In the decreasing segment
State 3: In the second increasing segment (a valid trionic subarray is formed)
The key idea is to track which phase we’re currently in and only allow transitions that preserve the trionic shape.

Approach
We use recursive dynamic programming with memoization.

Let dp[index][state] represent the maximum sum we can get starting from index while currently in state.

At each index, we decide whether we can take the current element and move forward, depending on the current state and the comparison with the next element.

State Transitions
State 0 (Not started)

Skip the element
Start the first increasing segment if nums[i+1] > nums[i] → move to State 1
State 1 (First increasing)

Continue increasing if nums[i+1] > nums[i] → stay in State 1
Start decreasing if nums[i+1] < nums[i] → move to State 2
State 2 (Decreasing)

Continue decreasing if nums[i+1] < nums[i] → stay in State 2
Start second increasing if nums[i+1] > nums[i] → move to State 3
State 3 (Second increasing)

Continue increasing if nums[i+1] > nums[i] → stay in State 3
This state represents a valid trionic subarray

class Solution {
public:
    long long NEG = -100000000000000LL;
    vector<vector<long long>> dp;
    vector<vector<bool>> vis;

    long long findAns(vector<int>& nums, int pos, int state) {

        if (pos == nums.size()) {
            if (state == 3) return 0;
            return NEG;
        }

        if (vis[pos][state]) return dp[pos][state];
        vis[pos][state] = true;

        long long take = NEG;
        long long notTake = NEG;

        if (state == 0) {
            notTake = findAns(nums, pos + 1, state);
        }

        if (state == 3) {
            take = nums[pos];
        }

        if (pos + 1 < nums.size()) {

            if (nums[pos] < nums[pos + 1] && state == 0) {
                take = max(take,
                           nums[pos] + findAns(nums, pos + 1, 1));
            }
            else if (nums[pos] < nums[pos + 1] && state == 1) {
                take = max(take,
                           nums[pos] + findAns(nums, pos + 1, 1));
            }
            else if (nums[pos] > nums[pos + 1] && state == 1) {
                take = max(take,
                           nums[pos] + findAns(nums, pos + 1, 2));
            }
            else if (nums[pos] > nums[pos + 1] && state == 2) {
                take = max(take,
                           nums[pos] + findAns(nums, pos + 1, 2));
            }
            else if (nums[pos] < nums[pos + 1] && state == 2) {
                take = max(take,
                           nums[pos] + findAns(nums, pos + 1, 3));
            }
            else if (nums[pos] < nums[pos + 1] && state == 3) {
                take = max(take,
                           nums[pos] + findAns(nums, pos + 1, 3));
            }
        }

        return dp[pos][state] = max(take, notTake);
    }

    long long maxSumTrionic(vector<int>& nums) {
        int n = nums.size();
        dp.assign(n, vector<long long>(4, 0));
        vis.assign(n, vector<bool>(4, false));
        return findAns(nums, 0, 0);
    }
};
