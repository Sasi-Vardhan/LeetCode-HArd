class Solution {
public:
    long long minimumCost(string source, string target, vector<char>& original, vector<char>& changed, vector<int>& cost) {
        vector<vector<int>>grid(26,vector<int>(26,INT_MAX));

        //creating a grid required for the graph traversal
        auto createGrid=[&grid](vector<char>&src,vector<char>&des,vector<int>&cost){
            int len=src.size();
            for(int i=0;i<len;i++){
                int x=src[i]-97;
                int y=des[i]-97;
                grid[x][y]=min(grid[x][y],cost[i]);
            }
        };
        createGrid(original,changed,cost);



        //lets use dijkstras Algorithms to traverse to traverse each node and find shortest paths from each alphabet
        unordered_map<int,array<int,26>>store;

        auto ShortestPath=[&](int src){
            // cout<<"Came "<<src<<endl;

            vector<int>visited(26,0);
           store[src].fill(INT_MAX);
           array<int, 26>* ptr = &store[src];
           (*ptr)[src]=0;

            visited[src]=1;
            while(src!=-1){
                //update ptr with new distances and find new source in the next step
                int newSrc=-1;
                int newMin=INT_MAX;
                for(int i=0;i<26;i++){
                    if(i!=src && visited[i]!=1 && grid[src][i]!=INT_MAX ){//this updates only src neighbors not entire arrays but dijkstras consider entire global minimum
                        (*ptr)[i]=min((*ptr)[i],(*ptr)[src]+grid[src][i]);
                    }
                }
                for(int i=0;i<26;i++){
                    if(visited[i]!=1 && newMin > (*ptr)[i]){
                        newMin=(*ptr)[i];
                        newSrc=i;
                    }
                }
                if(newSrc==-1)break;
                src=newSrc;
                visited[src]=1;
            }
        };
        for(int i=0;i<26;i++) ShortestPath(i);


        //now we need to claculate the total cost
        long long int costUs=0;
        int end=source.size();
        for(int i=0;i<end;i++){
            if(source[i]==target[i])continue;
            if(store[source[i]-97][target[i]-97]==INT_MAX){
                cout<<source[i]<<" "<<target[i]<<endl;
                return -1;
            }
            costUs+=store[source[i]-97][target[i]-97];
        }
        
        
        return costUs;
    }
};
