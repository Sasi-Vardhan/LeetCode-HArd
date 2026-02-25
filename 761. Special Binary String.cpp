class Solution {
public:
    string makeLargestSpecial(string s) {
        priority_queue<string>pq;
        int count=0;
        //go through the Question properly we can conclude that string starts with 1 and ends with 0
        //we will find each Special String and try to break it and form it in such a way it is maximum
        int start=0;
        for(int i=0;i<s.size();i++){
            if(s[i]=='1')count++;
            else count--;
            if(count==0){
                string temp="1"+makeLargestSpecial(s.substr(start+1,i-start-1))+"0";//i-start-1 tells take string upto character before last character
                start=i+1;
                pq.push(temp);
            }
        }
        string ans="";
        while(!pq.empty()){
            ans+=pq.top();
            pq.pop();
        }
        return ans;
    }
};
