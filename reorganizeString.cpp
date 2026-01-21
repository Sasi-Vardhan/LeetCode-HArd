/*

the Questions says to make string in such a way that there should be no two same adjacent Characters
brute force is to iterate all the possibilites and test each string

which will give time limit Exceeded

Optimal approach is :

Solution
make dict like this {char:count}
next find char with highest frequency if frequency > (length+1) return
else
c1=firstChar with highest frequency pop that c1 out
c2=secondChar with second highest frequencycheck if the dict is empty or not before hand)
pop c2
ans=ans+c1+c2
next insert c1,c2 with decreased frequencies

*/

class Solution {
public:
    string reorganizeString(string s) {
        priority_queue<pair<int,char>>alt;
        unordered_map<char,int>mp;
        for(auto c:s){
            mp[c]++;
            if(mp[c] > (s.size()+1)/2)return "";
        }
        cout<<""<<endl;
        for(auto it=mp.begin();it!=mp.end();it++){
            alt.push({it->second,it->first});
        }

        string ans="";
        while(!alt.empty()){

            pair<int,char>temp=alt.top();
            // cout<<temp.first<<" "<<temp.second<<endl;
            alt.pop();//pop that character to find next character
            //find second character which can fit the task
            char t2='-';
            if(!alt.empty()){
                pair<int,char>temp2=alt.top();
                t2=temp2.second;
                alt.pop();
                if((temp2.first)-1 > 0)
                    alt.push({--temp2.first,t2});
            }
            char t1=temp.second;
            // cout<<ans<<endl;
            
            ans=ans+t1;
            if(t2!='-')ans+=t2;
            if((temp.first)-1 > 0)
            alt.push({--temp.first,t1});
        }
        cout<<ans<<endl;
        return ans;
    }
};
