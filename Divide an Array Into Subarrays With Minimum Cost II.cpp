/*
I see where your logic is headed! You're thinking: "If the set size drops below $k-1$ after a pop, 
the next insert call will just put the new element right in."While that's true, there is a hidden trap in that logic. 
Here is the exact scenario where that fails:The "Better Candidate" ScenarioImagine $k-1 = 2$ and $dist = 3$.Your window currently covers 4 elements: [10, 20, 30, 40].
Your high set: {10, 20} (Sum = 30)Elements outside your set: 30, 40 (These are in the window, but your code "forgot" them).Now, the window slides. 10 is popped.
After Pop: Your set is {20}. Sum = 20.Next Element: The new element entering the window is 50.The Insert: Your code sees the set size is $1 < 2$, so it inserts 50.
The Result: Your set is now {20, 50}. Sum = 70.The Failure: The actual smallest two elements in the current window are 20 and 30. 
But because your code didn't "remember" that 30 was a candidate, it missed it and picked 50 instead.Why Two Multisets are MandatoryTo solve this, 
you need to keep track of the elements that are in the window but NOT in the top $k-1$.In the example above, 
a two-set system would work like this:Set A (Smallest): {10, 20}Set B (Backup): {30, 40}When 10 is popped from Set A, the system immediately looks at Set B, sees 30 is the smallest backup,
and promotes it to Set A.New Set A: {20, 30}New Set B: {40}Then, when 50 comes in, 
it's compared against the largest in Set A (30). Since 50 is larger, it just goes into Set B.
*/

class Solution {
public:
    // low  -> smallest k-1 elements (selected)
    // high -> remaining elements in the window

    void insert(
        multiset<pair<int,int>>& low,
        multiset<pair<int,int>>& high,
        int element,
        int pos,
        int k,
        long long& sum
    ) {
        pair<int,int> cur = {element, pos};

        if ((int)low.size() < k) {
            low.insert(cur);
            sum += element;
        } else {
            auto it = prev(low.end()); // largest in low
            if (it->first > element) {
                sum -= it->first;
                high.insert(*it);
                low.erase(it);

                low.insert(cur);
                sum += element;
            } else {
                high.insert(cur);
            }
        }
    }

    void pop(
        multiset<pair<int,int>>& low,
        multiset<pair<int,int>>& high,
        int element,
        int pos,
        int k,
        long long& sum
    ) {
        pair<int,int> cur = {element, pos};

        auto itLow = low.find(cur);
        if (itLow != low.end()) {
            // removing a selected element
            sum -= element;
            low.erase(itLow);

            // promote smallest from high
            if (!high.empty()) {
                auto it = high.begin();
                low.insert(*it);
                sum += it->first;
                high.erase(it);
            }
        } else {
            // removing a non-selected element
            auto itHigh = high.find(cur);
            if (itHigh != high.end()) {
                high.erase(itHigh);
            }
        }
    }

    long long minimumCost(vector<int>& nums, int k, int dist) {
        int n = nums.size();

        long long sum = nums[0]; // nums[0] always included
        multiset<pair<int,int>> low, high;

        // initial window: [1 .. dist+1]
        for (int i = 1; i <= dist + 1 && i < n; i++) {
            insert(low, high, nums[i], i, k - 1, sum);
        }

        long long ans = LLONG_MAX;
        int stop = n - (k - 2);

        for (int i = 1; i < stop; i++) {
            ans = min(ans, sum);

            // remove outgoing element
            pop(low, high, nums[i], i, k - 1, sum);

            // insert incoming element
            int next = i + dist + 1;
            if (next < n) {
                insert(low, high, nums[next], next, k - 1, sum);
            }
        }

        return ans;
    }
};
