/*
they have asked use to find 3 lexico graphically string suggestions at each node 
idea is we are adding a word to trie then that word has prefix upto that node so the thing is we can store it in a que which is by default a max heap so we will pop lexicographically string when the size() queue is > 3 so
this is the idea for this Question
*/

class Solution {
public:
    
    class trie{
        public:
        char node;
        priority_queue<string>que;//to store next three lexically smallest strings 
        vector<trie*>children;//connections to next node

        trie(){
            node='-';
            children.assign(26,nullptr);
        }
    };

    void form(vector<trie*>&temp){
        for(int i=0;i<26;i++){
            temp[i]=new trie();
        }
    }

    void insert(trie *&root,string word){
        int len=word.size();
        
        if(root->children[word[0]-97]==NULL){
            root->children[word[0]-97]=new trie();
        }

        trie* curr=root->children[word[0]-97];
        for(int i=0;i<len;i++){
            if(curr->node=='-'){
                curr->node=word[i];
                // form(curr->children);
            }
            curr->que.push(word);
            while(curr->que.size() > 3){
                curr->que.pop();
            }
            if(i<(len-1)){
                if(curr->children[word[i+1]-97]==NULL){
                    curr->children[word[i+1]-97]=new trie();
                }
            curr=curr->children[word[i+1]-97];
            }
            else return;
        }
        return;
    }


   
    vector<vector<string>> suggestedProducts(vector<string>& products, string searchWord) {
        int length=searchWord.size();
        vector<vector<string>>ans(length,vector<string>());
        trie*root=new trie();
        for(auto word:products){
            insert(root,word);
        }
        // cout<<root->children[products[0][0]-'a']->children[products[0][1]-'a']->que.size()<<endl;
        trie *curr=root->children[searchWord[0]-'a'];
        // cout<<curr->node<<endl;
        if(curr==NULL || curr->node=='-')return ans;
        for(int i=0;i<length;i++){
            if(curr==NULL || curr->node=='-')return ans;
            while(!curr->que.empty()){
                ans[i].push_back(curr->que.top());
                curr->que.pop();
                sort(ans[i].begin(),ans[i].end());
            }
            if(i < (length-1)){
                curr=curr->children[searchWord[i+1]-'a'];
            }
            else return ans;
        }
        return {};
    }
};
