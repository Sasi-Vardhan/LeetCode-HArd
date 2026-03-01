class Solution {
public:
    long long countSubarrays(vector<int>& nums, int k, int m) {
        long long int count=0;
        int distinct=0;
        int good=0;
        unordered_map<int,int>mp;
        int i=0;
        long long int prefix = 0;

    
        for(int j=0;j<nums.size();j++){
            if(mp.find(nums[j])==mp.end()){
                mp[nums[j]]=1;
                distinct+=1;
                if(mp[nums[j]]==m)good+=1;
            }
            else {
                mp[nums[j]]+=1;
                if(mp[nums[j]]==m)good+=1;
            }
            while (distinct > k) {
                if (mp[nums[i]] == m) good--;
                mp[nums[i]]--;
                if (mp[nums[i]] == 0) {
                    mp.erase(nums[i]);
                    distinct--;
                }
                i++;
                prefix = 0;
            }
            //here prefix tracks from how many places we can open window upto j so we will have those many window starts 
            //you may think why we are not using j because if i crosses j mp[nums[i]] and distinct these will change and will break loops
            while (distinct == k && mp[nums[i]] > m) {
                mp[nums[i]]--;
                i++;
                prefix++;
            }
            // you may have doubt why did we do prefix+1 so to tell this look above loop we will select elements with frequency mp[nums[i]] > m not >= because when ==m it will decrease count of nums[i] to m-1 in next window so to avoid it we will stop 
//when ever mp[nums[i]]==m it is the valid window and we cannot find another start next to it
            if (distinct == k && good == k) {
                count += prefix + 1;
            }
        }
        
        return count;
    }
};©leetcode
/*
  nums = [1,1,1,2,2]
k = 2, m = 2

We track when window first becomes valid.

j = 0 → [1]

Not valid (need 2 distinct)
prefix = 0

j = 1 → [1,1]

Still not valid
prefix = 0

j = 2 → [1,1,1]

Still not valid (only 1 distinct)
prefix = 0

j = 3 → [1,1,1,2]

freq:

1 → 3  
2 → 1

Not valid (2 appears only once)
prefix = 0

🔥 j = 4 → [1,1,1,2,2]

Now:

1 → 3
2 → 2

Valid ✅

Now compute prefix (IMPORTANT)

We check from current left i.

Initial window:

[1,1,1,2,2]
Try removing left

Left = index 0 → value 1

freq[1] = 3 > m(2) ✅

We can remove.

prefix becomes 1

Window becomes:

[1,1,2,2]
Try removing again

Left = index 1 → value 1

freq[1] = 2 == m ❌

STOP.

✅ Final prefix at j=4
prefix = 1

NOT 2.

🚨 Your misunderstanding

You said:

at index 0 prefix increased 1
at index 1 prefix increased 2

❌ This would only happen if:

freq[1] > m after first removal

But after first removal:

freq[1] becomes exactly m

So second removal is illegal.

🔑 Golden Rule

Prefix increases ONLY while:

freq[nums[i]] > m

The moment it becomes:

freq == m

you MUST stop.

🧠 Mental model

Think of each number needing a minimum reserve of m copies.

Extra copies = removable.

Here:

1 has 3 copies
needs to keep 2
extra = 1 only

So prefix can only be 1.*/
