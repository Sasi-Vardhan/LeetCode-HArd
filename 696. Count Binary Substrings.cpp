class Solution {
public:
    int countBinarySubstrings(string s) {
        /*Eg: "00011100" --> [3 zeroes, 3 ones, 2 zeroes] --> [3,3,2] --> Ans = min(3,3) + min(3,2) = 5 Total Substrings*/
        vector<int>sequence;
        int cont=1;
        char start=s[0];
        // sequence.push_back(cont);
        for(int i=1;i<s.size();i++){
            if(start==s[i]){
                cont++;
                // sequence.push_back(cont);
            }
            else {
                sequence.push_back(cont);
                cont=1;
                start=s[i];
                
            }
        }
        sequence.push_back(cont);
        int ans=0;
        for(int i=0;i<sequence.size()-1;i++){
            ans+=min(sequence[i],sequence[i+1]);
        }
        return ans;
    }
};
