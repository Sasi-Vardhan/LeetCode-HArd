
class Trie {
public:

//instance variables for the trie
char node;
vector<Trie*>children;
bool isend;

//functions they asked us write

//constructor
    Trie() {
        node='-';
        children.assign(26, nullptr); 
        isend=false;
    }
    
    void form(vector<Trie*>&children){
        for(int i=0;i<26;i++){
            if(children[i] == nullptr)
            children[i]=new Trie();
        }
    }

//for insertion every node will have the children array which will lead to next level of the trie
    
    void insert(string word) {
        cout<<"Insert "<<word<<endl;
        if(this->node=='-'){
            this->node='&';
            form(this->children);
        }
        int length=word.size();
        vector<Trie*>*temp=&children;
        for(int i=0;i<length;i++){
            // cout<<word[i]<<endl;
            if(i==length-1){
                (*temp)[word[i]-97]->isend=true;
                (*temp)[word[i]-97]->node=word[i];
                form((*temp)[word[i]-97]->children);
                return;
            }
            else if((*temp)[word[i]-97]->node == '-'){
                // cout<<"NEw"<<word[i]<<endl;
                (*temp)[word[i]-97]->node=word[i];
                form((*temp)[word[i]-97]->children);
                temp=&(*temp)[word[i]-97]->children;
            }
            else{
                temp=&(*temp)[word[i]-97]->children;
            }
        }
        return ;
    }
    
    bool search(string word) {
        int length=word.size();
        vector<Trie*>*temp=&this->children;
        for(int i=0;i<length;i++){
            if((*temp)[word[i]-97] == NULL)return false;
            if(i==length-1){
                if((*temp)[word[i]-97] == NULL)return false;
                if((*temp)[word[i]-97]->isend==true)return true;
                return false;
            }
            if((*temp)[word[i]-97]->node=='-')return false;
            else temp=&(*temp)[word[i]-97]->children;
        }
        return false;
    }
    
    bool startsWith(string word) {
        int length=word.size();
        vector<Trie*>*temp=&this->children;
        for(int i=0;i<length;i++){
            // cout<<word[i]<<" Child of the node "<<(*temp)[word[i]-97]->node<<endl;
            if((*temp)[word[i]-97] == NULL ||(*temp)[word[i]-97]->node=='-')return false;
            else temp=&(*temp)[word[i]-97]->children;
        }
        return true;
    }
};

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */
