/*
The idea first lets fix one number and check how many possible combinations are there
Ex:
lets n=4, k=9
[1,2,3,4] this is the smallest number possible 

fix 1 in first pos
so we will have 3 numbers after 1 so the number of permutations with 1 in first position  are 6
but we have k > 6
so lets move 6 positions down it becomes so k=k-6
now for 2 as first number the number of permutations with 2 in first position  are 6
here 6 > k
so 2 is the first digit
next digit can be 1,3,4
and we need to find 3rd number in the 6 numbers starting with 2
so k value wont change here
 agin lets repeat task fix 1 in position we will have 3,4 so 2! ways 
 but k > 2!
 so k=k-2
 lets move 2 positions down
 now k=1
 for 3 there will 1,4 so 2! ways
 2! > k
 so 3 will in next position
 2,3,[1,4]
 now repeat 1 in next position 1! ways as we have only 4
 so 1! >= k
 so lets fix 1 in nxt postion
 next move to 4 similar will have 
 atlast we will have all the positions fixed with k=1

  */

class Solution {
public:
  
    unordered_map<int,int>store;
     int fact(int num){
        if(num==0)return 1;
        if(store.find(num)!=store.end())return store[num];
        int product=1;
        for(int i=2;i <= num;i++){
            product*=i;
        }
        return store[num]=product;
     }
    
    void findCombinations(int n,vector<int>&visited,int &avl,int &k,int &pos){
        if(k <=0 )return;
        for(int i=1;i<=n && k > 0;i++){
            if(fact(avl) >= k && visited[i]==0){
                // cout<<"Num : "<<i<<" K :"<<k<<" Pos :"<<pos<<" Avl : "<<avl<<endl;
                visited[i]=pos;
                avl--;
                pos++;
                findCombinations(n,visited,avl,k,pos);
                break;
            }
            else if(visited[i]==0){
                // cout<<"Not Accepted -> "<<"Num : "<<i<<" K :"<<k<<" Pos :"<<pos<<" Avl : "<<avl<<endl;
                k-=fact(avl);
            }
        }
        return;
    }

    string getPermutation(int n, int k) {
        int pos=1;
        vector<int>visited(n+1,0);
        int avail=n-1;
        findCombinations(n,visited,avail,k,pos);
        string ans="";
        for(int i=1;i<=n;i++){
            ans+="-";
            // cout<<i<<" Pos : "<<visited[i]<<endl;
        }
        int tr=0;
        for(int i=1;i<=n;i++){
           if(visited[i]!=0){
            tr++;
            ans[visited[i]-1]=(char)(48+i);
           }
        }
        return ans;
    }
};
