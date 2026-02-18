//this is for findinng sum in certain interval better we can create for finding max number in certain interval

class Solution {
public:
    struct segmentTree{
        int start;
        int end;
        int sum=0;
        segmentTree*left;
        segmentTree*right;
    };
    
    int Construct(vector<int>&nums,segmentTree*&root){
        if(root->start==root->end){
            return root->sum=nums[root->start];
        }
        int mid=(root->start+root->end)>>1;
        // cout<<mid<<endl;
        //left sub-tree
        root->left=new segmentTree();
        root->left->start=root->start;
        root->left->end=mid;
        ///right sub tree
        root->right=new segmentTree();
        root->right->start=mid+1;
        root->right->end=root->end;
        return root->sum=Construct(nums,root->left)+Construct(nums,root->right);
    }

    int Query(segmentTree*root,int start,int end){
        if(root==NULL)return 0;
        if(root->start==start && root->end==end)return root->sum;
        int mid = (root->start + root->end) >> 1;

        // cout<<mid<<endl;
        if(end > mid && start <= mid){
            // cout<<start<<" "<<end<<endl;
            int L=Query(root->left,start,mid);
            int R=Query(root->right,mid+1,end);
            // cout<<" L"<<L<< " /"<<" R "<<R<<endl; 
            return L+R;
        }
        if(start > mid){
            return Query(root->right,mid+1,end);
        }
        // cout<<start<<end<<endl;
        return Query(root->left,start,end);
    }
