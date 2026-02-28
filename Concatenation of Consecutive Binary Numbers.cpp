class Solution {
public:
int mod=1e9+7;
    int binaryLength(int n){
        int L=0;
        while(n>0){
            n=n/2;
            L++;
        }
        return L;
    }
    int concatenatedBinary(int n) {
        // cout<<binaryLength(10)<<endl;
        long long int ans=0;
        for(int i=1;i<=n;i++){
            int len=binaryLength(i);
            ans = ((ans << len) % mod + i) % mod;
        }
        return (int)ans;
        // return 1;
    }
};
