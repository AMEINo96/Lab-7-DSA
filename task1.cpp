#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <map>
#include <algorithm>

struct TreeNode {
    char val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char v) : val(v), left(nullptr), right(nullptr) {}
};

struct BSTNode {
    int val;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int v) : val(v), left(nullptr), right(nullptr) {}
};


TreeNode* parseTreeHelper(const std::string& s, int& index) {
    if (index >= s.length() || s[index] == ',' || s[index] == ')') {
        return nullptr;
    }
    
    TreeNode* node = new TreeNode(s[index++]);
    
    if (index < s.length() && s[index] == '(') {
        index++; 
        node->left = parseTreeHelper(s, index);
        
        if (index < s.length() && s[index] == ',') {
            index++; 
            node->right = parseTreeHelper(s, index);
        }
        
        if (index < s.length() && s[index] == ')') {
            index++;
        }
    }
    return node;
}

TreeNode* buildTreeFromString(const std::string& s) {
    int index = 0;
    return parseTreeHelper(s, index);
}

void preorderRecursive(TreeNode* root) {
    if (!root) return;
    std::cout << root->val << " ";
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

void inorderIterative(TreeNode* root) {
    std::stack<TreeNode*> s;
    TreeNode* curr = root;
    
    while (curr != nullptr || !s.empty()) {
        while (curr != nullptr) {
            s.push(curr);
            curr = curr->left;
        }
        curr = s.top();
        s.pop();
        
        std::cout << curr->val << " ";
        curr = curr->right;
    }
}

void postorderIterative(TreeNode* root) {
    if (!root) return;
    
    std::stack<TreeNode*> s1, s2;
    s1.push(root);
    
    while (!s1.empty()) {
        TreeNode* node = s1.top();
        s1.pop();
        s2.push(node);
        
        if (node->left) s1.push(node->left);
        if (node->right) s1.push(node->right);
    }
    
    while (!s2.empty()) {
        std::cout << s2.top()->val << " ";
        s2.pop();
    }
}

bool validateTreeString(const std::string& s) {
    std::stack<char> parens;
    std::vector<int> commaCounts;
    
    for (char c : s) {
        if (c == '(') {
            parens.push('(');
            commaCounts.push_back(0);
        } else if (c == ',') {
            if (parens.empty()) return false;
            commaCounts.back()++;
            if (commaCounts.back() > 1) return false;
        } else if (c == ')') {
            if (parens.empty()) return false;
            parens.pop();
            commaCounts.pop_back();
        }
    }
    return parens.empty();
}

int getHeight(TreeNode* root) {
    if (!root) return -1; 
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

void getDepths(TreeNode* root, int currentDepth, std::map<char, int>& depthsMap) {
    if (!root) return;
    depthsMap[root->val] = currentDepth;
    getDepths(root->left, currentDepth + 1, depthsMap);
    getDepths(root->right, currentDepth + 1, depthsMap);
}

BSTNode* insertBST(BSTNode* root, int val) {
    if (!root) return new BSTNode(val);
    if (val < root->val) {
        root->left = insertBST(root->left, val);
    } else {
        root->right = insertBST(root->right, val);
    }
    return root;
}

void bstInorder(BSTNode* root) {
    if (!root) return;
    bstInorder(root->left);
    std::cout << root->val << " ";
    bstInorder(root->right);
}

int main() {
    std::string treeStr = "a(b(d,e),c(,f(g,)))";
    
    std::cout << "Tree String: " << treeStr << "\n\n";

   
    bool isValid = validateTreeString(treeStr);
    std::cout << "Task 5: Is valid tree string? " << (isValid ? "True" : "False") << "\n";

    
    TreeNode* root = buildTreeFromString(treeStr);

    
    std::cout << "Task 2: Preorder (Recursive): ";
    preorderRecursive(root);
    std::cout << "\n";

   
    std::cout << "Task 3: Inorder (Iterative):  ";
    inorderIterative(root);
    std::cout << "\n";

   
    std::cout << "Task 4: Postorder (Iterative):";
    postorderIterative(root);
    std::cout << "\n";

    
    int height = getHeight(root);
    std::cout << "Task 6: Tree Height: " << height << "\n";
    
    std::map<char, int> depthsMap;
    getDepths(root, 0, depthsMap);
    std::cout << "Task 6: Node Depths:\n";
    for (auto const& pair : depthsMap) {
        std::cout << "  Node '" << pair.first << "' -> Depth: " << pair.second << "\n";
    }

  
    std::vector<int> bstSequence = {50, 30, 70, 20, 40, 60, 80};
    BSTNode* bstRoot = nullptr;
    for (int val : bstSequence) {
        bstRoot = insertBST(bstRoot, val);
    }
    
    std::cout << "\nTask 7: BST Sequence: [50, 30, 70, 20, 40, 60, 80]\n";
    std::cout << "Task 7: BST Inorder Traversal: ";
    bstInorder(bstRoot);
    std::cout << "\n";

    return 0;
}