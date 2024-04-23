#include<bits/stdc++.h>
#include<omp.h>

using namespace std;

// bfs
class node{
    public : 
    node *left , *right;
    int data;
};

node *insert(node *head , int data){
    if(!head){
        // create a new node 
        head = new node;
        head->data = data;
        head->left = NULL ;
        head->right = NULL;
        return head;
    }

    queue<node *>q;
    q.push(head);

    while(!q.empty()){
        node *currNode = q.front();
        q.pop();
        if(currNode->left==NULL){
            // create a new node 
            currNode->left = new node;
            currNode->left->data = data;
            currNode->left->left = NULL;
            currNode->left->right = NULL;
            return head;
        }else{
            q.push(currNode->left);
        }

        if(currNode->right==NULL){
            currNode->left = new node;
            currNode->left->data = data;
            currNode->left->left = NULL;
            currNode->left->right = NULL;
            return head;
        }else{
            q.push(currNode->right);
        }
    }
    return head;
}


void bfs(node *head){
    queue<node *>q;
    q.push(head);

    while(!q.empty()){
        node *currNode = q.front();
        q.pop();

        cout<<currNode->data<<", ";

        if(currNode->left){
            q.push(currNode->left);
        }

        if(currNode->right){
            q.push(currNode->right);
        }

    }
}


int main(){
    long int n ;
    double start_time , end_time;
    cout<<"Enter the number of elements ; ";
    cin>>n;

    node *root = NULL;
    node *root2 = NULL;

    for(long int i=0;i<n;i++){
        int random_value = (rand() % (999999 - 999 + 1)) + 9999;
        root = insert(root , random_value);
        root2 = insert(root2 , random_value);
    }

    // sequential 
    start_time = omp_get_wtime();
    bfs(root);
    end_time = omp_get_wtime();
    double seq_time = end_time - start_time;

    // parallel time 
    queue<node *>q;
    q.push(root2);
    bool empty_flag = false;

    start_time = omp_get_wtime();

    #pragma omp parallel
    {
        while(true){
            node *currNode;
            bool local_empty_flag = false;

            #pragma omp critical
            if(!q.empty()){
                currNode = q.front();
                q.pop();
            }else{
                local_empty_flag = true;
            }


            #pragma omp critical
            {
                empty_flag = empty_flag || local_empty_flag;
            }

            if(empty_flag){
                break;
            }

            #pragma omp single nowait
            {
                cout<<"\t"<<currNode->data;
            }

            #pragma omp critical
            {
                if(currNode->left){
                    q.push(currNode->left);
                }

                if(currNode->right){
                    q.push(currNode->right);
                }
            }
        }
    }

    end_time = omp_get_wtime();
    double parallel_time = end_time - start_time;

    cout<<"\nseq time : "<<seq_time;
    cout<<"\nparallel time : "<<parallel_time;
    cout<<"\n";

    return 0;
}

