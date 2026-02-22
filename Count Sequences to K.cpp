/*
============================================================
🧠 COUNT SEQUENCES USING EXACT RATIONAL DP + MEMOIZATION
------------------------------------------------------------
We start with value = 1 and for each nums[i] we can:

    1) multiply
    2) divide
    3) skip

We must count how many sequences end with value == k.

------------------------------------------------------------
❌ Why NOT use double?
Floating point accumulates precision errors after many
multiply/divide operations → leads to Wrong Answer.

------------------------------------------------------------
✅ Our Solution
• Represent value exactly as a fraction (num/den)
• Always reduce using gcd
• Use cross-reduction to avoid overflow
• Memoize on (position, fraction)

------------------------------------------------------------
🔐 Key Safety Features
• No floating point
• Overflow-safe multiply/divide
• Custom strong hash for unordered_map
• Deterministic and exact

------------------------------------------------------------
⏱ Complexity
Time:   O(n × number_of_states)
Space:  depends on fraction states

Works well for n ≤ ~20.
============================================================
*/

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:

    // ============================================================
    // Fraction structure (always kept reduced)
    // ============================================================
    struct Frac {
        long long num, den;

        Frac(long long n = 0, long long d = 1) {
            long long g = gcd(llabs(n), llabs(d));
            num = n / g;
            den = d / g;
            if (den < 0) {
                den *= -1;
                num *= -1;
            }
        }

        bool operator==(const Frac& other) const {
            return num == other.num && den == other.den;
        }
    };

    // ============================================================
    // Custom hash for (position, fraction)
    // Uses boost-style hash combine (safe & strong)
    // ============================================================
    struct HashFrac {
        size_t operator()(const pair<int, Frac>& p) const {
            size_t h1 = hash<int>()(p.first);
            size_t h2 = hash<long long>()(p.second.num);
            size_t h3 = hash<long long>()(p.second.den);

            size_t res = h1;
            res ^= h2 + 0x9e3779b97f4a7c15ULL + (res << 6) + (res >> 2);
            res ^= h3 + 0x9e3779b97f4a7c15ULL + (res << 6) + (res >> 2);
            return res;
        }
    };

    // ============================================================
    // SAFE multiply using cross reduction
    // Prevents overflow before multiplication
    // ============================================================
    Frac multiply(const Frac& f, long long x) {
        long long g = gcd(llabs(x), llabs(f.den));
        long long newNum = f.num * (x / g);
        long long newDen = f.den / g;
        return Frac(newNum, newDen);
    }

    // ============================================================
    // SAFE divide using cross reduction
    // ============================================================
    Frac divide(const Frac& f, long long x) {
        long long g = gcd(llabs(x), llabs(f.num));
        long long newNum = f.num / g;
        long long newDen = f.den * (x / g);
        return Frac(newNum, newDen);
    }

    // ============================================================
    // DFS + Memoization
    // ============================================================
    int findAll(vector<int>& nums,
                int pos,
                Frac val,
                long long k,
                unordered_map<pair<int, Frac>, int, HashFrac>& mp) {

        // Base case: all elements processed
        if (pos == nums.size()) {
            return (val.den == 1 && val.num == k);
        }

        auto key = make_pair(pos, val);
        if (mp.count(key)) return mp[key];

        // Option 1: multiply
        Frac mul = multiply(val, nums[pos]);
        int op1 = findAll(nums, pos + 1, mul, k, mp);

        // Option 2: divide
        Frac div = divide(val, nums[pos]);
        int op2 = findAll(nums, pos + 1, div, k, mp);

        // Option 3: skip
        int op3 = findAll(nums, pos + 1, val, k, mp);

        return mp[key] = op1 + op2 + op3;
    }

    // ============================================================
    // Entry point
    // ============================================================
    int countSequences(vector<int>& nums, long long k) {
        unordered_map<pair<int, Frac>, int, HashFrac> mp;
        return findAll(nums, 0, Frac(1, 1), k, mp);
    }
};
