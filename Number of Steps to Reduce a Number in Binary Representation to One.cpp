class Solution {
public:
    string addition(string s){
        int end=s.size();
        int flag=0;
        for(int i=end-1;i >=0 ;i--){
            if(s[i]=='0'){
                flag=1;
                s[i]='1';
                return s;
            }
            else s[i]='0';
        }
        return "1"+s;
    }

    string division(string s){
        char prev='0';
        char next;
        int end=s.size();
        for(int i=0;i<end;i++){
            next=s[i];
            s[i]=prev;
            prev=next;
        }
        return s;
    }

    bool check_1(string s){
        int flag=0;
        int end=s.size();
        for(int i=0;i<end-1;i++){
            if(s[i]=='1')return false;
        }
        return s[end-1]=='1';
    }

    int numSteps(string s) {
        if(s=="1")return 0;
        // cout<<division(addition(division(addition("111"))));
        int count=0;

        
        
        while(!check_1(s)){
            int end=s.size();
            count++;
            if(s[end-1]=='1'){
                s=addition(s);
                
            }
            else s=division(s);
            // cout<<s<<endl;
        }

        return count;

    }
};
