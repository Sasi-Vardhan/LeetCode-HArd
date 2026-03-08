class Solution {
public:
    int minFlips(string s) {
        int n = s.size();

        int odd_0_s=0, odd_1_s=0;
        int even_0_s=0, even_1_s=0;

        for(int i=0;i<n;i++){
            if(i%2==0){
                if(s[i]=='0') even_0_s++;
                else even_1_s++;
            } else {
                if(s[i]=='0') odd_0_s++;
                else odd_1_s++;
            }
        }

        int res = INT_MAX;

        for(int i=0;i<n;i++){
            //lets without using move 1
            //1 series will have all 1's at even and 0's at odd
            //0 series will have all 0's at even and 1's at odd

            int error = min(odd_1_s + even_0_s, odd_0_s + even_1_s);
            res = min(res,error);

            char c = s[i];//here moved characted should be s[i] because we are moving logically not physical changes in string

            // remove first element contribution in the respective
            
                if(c=='0') even_0_s--;
                else even_1_s--;
            

            // swap parity of remaining elements
            swap(even_0_s, odd_0_s);
            swap(even_1_s, odd_1_s);

            // insert first element at end
            int newPos = n-1;
            if(newPos%2==0){
                if(c=='0') even_0_s++;
                else even_1_s++;
            } else {
                if(c=='0') odd_0_s++;
                else odd_1_s++;
            }
        }

        return res;
    }
};
