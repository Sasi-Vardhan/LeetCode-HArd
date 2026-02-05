/*
the idea is to find all the points in a straight line with similar slope from a point and 
Edge cases all points horizantlly collinear and vertically collinear 
and handle division with double for maximum precision
  */

class Solution {
public:
    
    pair<int,int> findSlope(vector<int>& x, vector<int>& y) {
        return { (y[1] - x[1]), (y[0] - x[0]) };
    }

    int maxPoints(vector<vector<int>>& points) {
        unordered_map<int, unordered_map<string, int>> store;
        int ans = INT_MIN;

        int end = points.size();
        for (int i = 0; i < end; i++) {
            for (int j = i + 1; j < end; j++) {
                if (i != j) {
                    pair<int,int> slope = findSlope(points[i], points[j]);

                    string idx = to_string(slope.first) + "_" + to_string(slope.second);

                    if (slope.first == 0) {
                        store[i]["V"]++;
                        ans = max(ans, store[i]["V"]);
                    }
                    else if (slope.second == 0) {
                        store[i]["H"]++;
                        ans = max(ans, store[i]["H"]);
                    }
                    else {
                        double temp=(double)slope.first/slope.second;
                        string idx = to_string(temp);
                        store[i][idx]++;
                        ans = max(ans, store[i][idx]);
                    }
                }
            }
        }

        cout << ans << endl;
        return ans==INT_MIN?1:ans+1;
    }
};
