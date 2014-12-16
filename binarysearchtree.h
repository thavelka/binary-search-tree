//  binarysearchtree.h
//  PA4


#ifndef __PA4__binarysearchtree__
#define __PA4__binarysearchtree__

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <queue>
#include <string>

using namespace std;

class BinarySearchTree {
private:
    
    struct TreeNode {
        int key;
        int cost;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;
    };
    
    double count;
    double totalcost;
    TreeNode* root;
    string filename;
    ofstream out;
    streambuf *coutbuf;
    
public:
    
    //default constructor
    BinarySearchTree() {
        root = nullptr;
        count = 0;
    }
    
    //auto tree
    BinarySearchTree(string f) { //f is the filename to read in from
        root = nullptr;
        count = 0;
        totalcost = 0;
        filename = f;
        read_in(f);
        get_data(root);
        double avcost = totalcost/count;
        cout<<setw(15)<<filename<<setw(15)<<count<<setw(15)<<totalcost<<setw(15)<<avcost<<endl;
    }
    
    //helper functions
    bool is_empty() const {return root==NULL;}
    int getcount() {return count;}
    
    
    //read in
    void read_in(string f) {
        filename = f;
        ifstream file(f);
        int tmp;
        while (file>>tmp) {
            insert(tmp);
        }
    }
    
    //search function
    TreeNode* search(int k) {
        TreeNode* tmp = root;
        tmp = root;
        bool found = false;
        
        while (tmp!=nullptr) {
            if(tmp->key == k)
            {
                found = true;
                return tmp;
            }
            else
            {
                if(k > tmp->key) tmp = tmp->right;
                else tmp = tmp->left;
            }
        }
        if (!found) {
            cerr<<"error: no matching data";
        }
        return tmp;
    }
    
    //insertion function
    void insert(int k) { //int argument serves as key for new node
        
        TreeNode* t = new TreeNode;
        TreeNode* parent = nullptr;
        
        t->key = k;
        t->cost = 0;
        t->left = nullptr;
        t->right = nullptr;
        t->parent = nullptr;
        
        
        if (is_empty()) {
            root = t; //if only a null root, sets root key to argument
            count++; //increase node count
            root->cost++;
        } else {
            TreeNode* tmp; //used to iterate down tree
            tmp = root;
            
            while (tmp) {
                t->parent = tmp;
                if (t->key > tmp->key) {
                    tmp = tmp->right;
                } else {
                    tmp = tmp->left;
                }
                t->cost++; //comparison made, add 1 to search cost
            }
            
            if (t->key <= t->parent->key) {
                t->parent->left = t;
            } else {
                t->parent->right = t;
            }
            t->cost++; //comparison made, add 1 to search cost
            count++; //increase node count
        }
        
        
    }
    
    
    
    //prompt to remove
    void prompt_remove() {
        int delkey;
        cout<<"\nEnter key of node to remove: ";
        cin>>delkey;
        remove(delkey);
    }
    
    //deletion function
    void remove(int k) {
        TreeNode* del = search(k); //sets pointer del to found node
        
        
        //applies only to nodes with one child
        if ((!(del->left) && (del->right)) || ((del->left) && !(del->right))) {
            if (!(del->left) && (del->right)) {
                if (del->parent->left == del) {
                    del->parent->left = del->right;
                    del->right->parent = del->parent;
                    decrement(del->right);
                    delete del;
                    count--;
                } else {
                    del->parent->right = del->right;
                    del->right->parent = del->parent;
                    decrement(del->right);
                    delete del;
                    count--;
                }
            } else {
                if (del->parent->left == del) {
                    del->parent->left = del->left;
                    del->left->parent = del->parent;
                    decrement(del->left);
                    delete del;
                    count--;
                } else {
                    del->parent->right = del->left;
                    del->left->parent = del->parent;
                    decrement(del->left);
                    delete del;
                    count--;
                }
            }
            
        }
        
        //applies only to leaf, aka node with no children
        if (!(del->left) && !(del->right)) {
            if (del->parent->left == del) {
                del->parent->left = nullptr;
                delete del;
            } else {
                del->parent->right = nullptr;
                delete del;
            }
            count--;
        }
        
        //applies to node with two children
        if (del->left && del->right) {
            TreeNode* tmp;
            tmp = del->right;
            
            if (!(tmp->left) && !(tmp->right)) {
                del->key = tmp->key;
                del->right = nullptr;
                delete tmp;
                count--;
            } else {
                while (tmp->left) {
                    tmp = tmp->left;
                }
                if (tmp->parent->left == tmp)
                    tmp->parent->left = nullptr;
                
                del = tmp;
                if (!(del->parent)) {
                    root = del;
                }
                delete tmp;
                count--;
            }
        }
        
        
    
    }
    
    //decrements the cost of all sub-nodes
    void decrement(TreeNode* tmp) {
        tmp->cost--;
        if (tmp->left)
            decrement(tmp->left);
        if (tmp->right)
            decrement(tmp->right);
    }
    
    //print tree
    void print_in_order() {
        
        coutbuf = cout.rdbuf();
        if (count>16) {
            out.open("output.txt");
            cout.rdbuf(out.rdbuf());
        }
        totalcost = 0;
        cout<<"\nPrinting "<<count<<" nodes in order:\n"<<endl;
        traverse_in_order(root);
        double averagecost = totalcost/count;
        cout<<"\nNode count: "<<count<<"\nTotal cost: "<<totalcost<<endl;
        cout<<"Average cost: "<<averagecost<<endl;
        if (count>16) {
            out.close();
        }
        
        cout.rdbuf(coutbuf);
       
    }
    
    void print_preorder() {
        
        coutbuf = cout.rdbuf();
        if (count>16) {
            out.open("output.txt");
            cout.rdbuf(out.rdbuf());
        }
        totalcost = 0;
        cout<<"\nPrinting "<<count<<" nodes pre order:\n"<<endl;
        traverse_preorder(root);
        double averagecost = totalcost/count;
        cout<<"\nNode count: "<<count<<"\nTotal cost: "<<totalcost<<endl;
        cout<<"Average cost: "<<averagecost<<endl;
        if (count>16) {
            out.close();
        }
        
        cout.rdbuf(coutbuf);
    }
    
    void print_postorder() {
        coutbuf = cout.rdbuf();
        if (count>16) {
            out.open("output.txt");
            cout.rdbuf(out.rdbuf());
        }
        totalcost = 0;
        cout<<"\nPrinting "<<count<<" nodes post order:\n"<<endl;
        traverse_postorder(root);
        double averagecost = totalcost/count;
        cout<<"\nNode count: "<<count<<"\nTotal cost: "<<totalcost<<endl;
        cout<<"Average cost: "<<averagecost<<endl;
        if (count>16) {
            out.close();
        }
        
        cout.rdbuf(coutbuf);
    }
    
    //print level
    void print_by_level() {
        coutbuf = cout.rdbuf();
        if (count>16) {
            out.open("output.txt");
            cout.rdbuf(out.rdbuf());
        }
        cout<<"\nPrinting "<<count<<" nodes by level:\n"<<endl;
        level_by_level(root);
        
        if (count>16) {
            out.close();
        }
        
        cout.rdbuf(coutbuf);
    }
    
    //queue level by level
    void level_by_level(TreeNode* root) {
        TreeNode* nullnode = new TreeNode;
        nullnode->key = -1;
        nullnode->parent = nullptr;
        nullnode->left = nullptr;
        nullnode->right = nullptr;
        bool nullchk = false;
        
        if (!root) return;
        queue<TreeNode*> currlevel, nextlevel;
        currlevel.push(root);
        while (!currlevel.empty()) {
            TreeNode* tmp = currlevel.front();
            currlevel.pop();
            if (tmp) {
                if (tmp==nullnode){
                    cout<<"X ";
                } else {
                    cout<<tmp->key<<" ";
                    
                }
                if (tmp->left==nullptr) {
                    nextlevel.push(nullnode);
                } else {
                    nextlevel.push(tmp->left);
                    nullchk=false;
                }
                if (tmp->right==nullptr) {
                    nextlevel.push(nullnode);
                } else {
                    nextlevel.push(tmp->right);
                    nullchk=false;
                }
            }
            if (currlevel.empty()&&nullchk==false) {
                cout << endl;
                swap(currlevel, nextlevel);
                nullchk=true;
            } else if (currlevel.empty()&&nullchk==true){
                cout<<endl;
                return;
            }
        }
    }
    
    
    //get results
    void get_data(TreeNode* t) {
        if (t!=nullptr) {
            totalcost += t->cost;
            if (t->left)
                get_data(t->left);
            if (t->right)
                get_data(t->right);
            
        } else return;
    }
    
    
    
    //traversal functions
    
    //in order traversal
    void traverse_in_order(TreeNode* t) {
        if (t!=nullptr) {
            if (t->left)
                traverse_in_order(t->left);
            totalcost += t->cost;
            cout<<t->key<<'['<<t->cost<<"] ";
            if (t->right)
                traverse_in_order(t->right);
        } else return;
    }
    
    //preorder traversal
    void traverse_preorder(TreeNode* t) {
        if (t!=nullptr) {
            
            totalcost += t->cost;
            cout<<t->key<<'['<<t->cost<<"] ";
            
            if (t->left)
                traverse_preorder(t->left);
            
            if (t->right)
                traverse_preorder(t->right);
        } else return;
    }
    
    //in order traversal
    void traverse_postorder(TreeNode* t) {
        if (t!=nullptr) {
            if (t->left)
                traverse_postorder(t->left);
    
            if (t->right)
                traverse_postorder(t->right);
            
            totalcost += t->cost;
            cout<<t->key<<'['<<t->cost<<"] ";
        } else return;
    }
    
};
#endif /* defined(__PA4__binarysearchtree__) */
