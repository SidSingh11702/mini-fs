#include <bits/stdc++.h>
using namespace std;

// Node class
class Node {
    public:
    
    string data;
    vector<Node*> children;
    
    Node(string data){
        this->data = data;
    }
};

// Converts the absolute path to node
Node* convertToNode(Node* root, string path){
    vector<string> _path;
    
    int n = path.size(), start_index = 0;
    
    for(auto i=0; i<n; i++) {
        if(path[i] == '/') {
            _path.push_back(path.substr(start_index,i-start_index));
            start_index = i+1;
        }
    }
    
    // Insert the last node
    _path.push_back(path.substr(start_index,n-start_index));
    
    for(auto node : _path) {
        for(auto child : root->children) {
            if(child->data == node) {
                root = child;
            }
        }
    }
    
    return root;
}

// Part A - Count descendants
int countDescendants(Node* root){
    if(root == nullptr) {
        return 0;
    }
        
    int ans = 0;
    
    for(auto child: root->children) {
        ans += (countDescendants(child) + 1);
    }
        
    return ans;
}
   
// Return the parent of node
Node* findParent(Node* root, Node* node){
    if(root == nullptr || node == nullptr) {
        return nullptr;
    }
    
    for(auto child : root->children) { 
        if(child == node) {
            return root;
        }
    }
        
    for(auto child : root->children){
        auto rec_res = findParent(child, node);
        if(rec_res != nullptr) {
            return rec_res;
        }
    }
    
    return nullptr;
}

// Part B - Cut and paste directory
void cutPaste(Node* root, string src, string destn){
    Node *_src = convertToNode(root, src), *_destn = convertToNode(root, destn);
    
    // Cut 
    Node* parent_of_src = findParent(root, _src);
    if(parent_of_src){
        cout << "Parent of " << src << " is " << parent_of_src->data << endl;
        vector<Node*>& children = parent_of_src->children;
        children.erase(remove(children.begin(), children.end(), _src), children.end());
    }
    
    // Paste 
    _destn->children.push_back(_src);
}
   
// Make a deep copy of tree rooted at "root"
Node* deepCopy(Node* root){
    if(root == nullptr) {
        return nullptr;
    }
        
    Node* _root = new Node(root->data);
    
    for(auto child : root->children) {
        _root->children.push_back(deepCopy(child));
    }
    
    return _root;
}

// Part C - Copy and paste directory
void copyPaste(Node* root, string src, string destn){
    Node *_src = convertToNode(root, src), *_destn = convertToNode(root, destn);
    
    // Copy 
    Node* copy_of_src = deepCopy(_src);
    
    // Paste 
    _destn->children.push_back(copy_of_src);
}
    
// Print the tree
void printTree(Node* root){
    if(root) {
        for(auto child : root->children) {
            if(child) {
                cout << "Value: " << root->data << ", child: " << child->data << endl;
            }
        }
    }
        
    for(auto child : root->children) {
        printTree(child);
    }
}

string getLast(string absolutePath){
    int n = absolutePath.size();
    for(auto i=n-1; i>=0; i--) {
        if(absolutePath[i] == '/') {
            return absolutePath.substr(i+1,n-i-1);
        }
    }
    
    return absolutePath;
}

/** Main function **/
int main(){
    
    int n,q;
    cin >> n >> q;
    
    cin.ignore();  // ignore leftover newline
    
    // Root of the tree
    Node* root;
    
    // stores the map from the string to the corresponding node
    map<string, Node*> mp;
    
    // Build tree
    for(auto i=0; i<n; i++){
        string line;
        getline(cin, line);
        istringstream iss(line);
        
        // It will store the strings in the line
        string token;
        
        bool isParent = true; 
        
        Node *parent, *child;
        
        while(iss >> token){
            // Get the last node
            token = getLast(token);
            
            if(isParent){
                if(mp.count(token)){
                    parent = mp[token];
                }else{
                    parent = new Node(token);
                    mp[token] = parent;
                }
                isParent = false;
            }else{
                if(mp.count(token)){
                    child = mp[token];
                }else{
                    child = new Node(token);
                    mp[token] = child;
                }
                parent->children.push_back(child);
            }
        }
        
        // Set the root
        if(i == 0) {
            root = parent;
        }
    }
    

    cout << "Printing the initial directory structure\n";
    printTree(root);
    cout << "****************" << endl;
    
    // Run queries
    while(q--){
        string line;
        getline(cin, line);
        istringstream iss(line);
        
        // It will store the strings in the line
        string token;
        
        bool isProblemA = false, isProblemB = false, isProblemC = false;
        
        vector<string> args;
        
        while(iss >> token){
            if(token == "countDescendants"){
                isProblemA = true;
            }else if(token == "cutPaste"){
                isProblemB = true;
            }else if(token == "copyPaste"){
                isProblemC = true;
            }else{
                args.push_back(token);    
            }
        }
        
        if(isProblemA){
            cout << "Number of descendants of " << args[0] << ": "<< countDescendants(convertToNode(root,args[0])) << endl;
            cout << "****************" << endl;
        }else if(isProblemB){
            cutPaste(root,args[0],args[1]);
            cout << "Printing directory after cut-paste of " << args[0] << " to " << args[1] << endl; 
            printTree(root);
            cout << "****************" << endl;
        }else if(isProblemC){
            copyPaste(root,args[0],args[1]);
            cout << "Printing directory after copy-paste of " << args[0] << " to " << args[1] << endl; 
            printTree(root);
            cout << "****************" << endl;
        }
    }
    
    return 0;
}
