# Arrays & Strings

### 1) Maximum subarray sum (Kadane’s Algorithm)

- Idea: keep current running sum, reset when negative, track max.

```cpp
#include <bits/stdc++.h>
using namespace std;
int maxSubArray(vector<int>& a){
    int max_ending = a[0], max_so_far = a[0];
    for(size_t i=1;i<a.size();++i){
        max_ending = max(a[i], max_ending + a[i]);
        max_so_far = max(max_so_far, max_ending);
    }
    return max_so_far;
}
int main(){
    vector<int> v = {-2,1,-3,4,-1,2,1,-5,4};
    cout<<maxSubArray(v)<<"\n"; // prints 6
}
```

---

### 2) Two Sum — return indices

- Idea: hash map of value → index (check complement).

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> twoSum(vector<int>& nums, int target){
    unordered_map<int,int> mp;
    for(int i=0;i<nums.size();++i){
        int need = target - nums[i];
        if(mp.count(need)) return {mp[need], i};
        mp[nums[i]] = i;
    }
    return {};
}
int main(){
    vector<int> v={2,7,11,15};
    auto ans = twoSum(v,9);
    cout<<ans[0]<<" "<<ans[1]<<"\n"; // 0 1
}
```

---

### 3) Merge two sorted arrays without extra space

- If both arrays are contiguous and you must not use extra memory: use gap method (Shell-sort like) or insert into first if it has extra space. Here’s the gap method for two arrays `a` and `b`:

```cpp
#include <bits/stdc++.h>
using namespace std;
int nextGap(int g){ if(g<=1) return 0; return (g+1)/2; }
void mergeWithoutExtra(vector<int>& a, vector<int>& b){
    int n=a.size(), m=b.size();
    int gap = nextGap(n+m);
    while(gap){
        int i=0;
        while(i+gap < n+m){
            int j = i+gap;
            int *xi = (i<n)? &a[i] : &b[i-n];
            int *xj = (j<n)? &a[j] : &b[j-n];
            if(*xi > *xj) swap(*xi,*xj);
            ++i;
        }
        gap = nextGap(gap);
    }
}
int main(){
    vector<int> a={1,4,7,8,10}, b={2,3,9};
    mergeWithoutExtra(a,b);
    for(int x:a) cout<<x<<" "; for(int x:b) cout<<x<<" "; cout<<"\n";
}
```

---

### 4) Find the missing number in array 1..n

- Use XOR or sum formula. XOR is safer for overflow.

```cpp
#include <bits/stdc++.h>
using namespace std;
int missingNumber(vector<int>& nums){ // nums size n-1, numbers 1..n
    int n = nums.size()+1;
    int xr = 0;
    for(int i=1;i<=n;i++) xr ^= i;
    for(int v: nums) xr ^= v;
    return xr;
}
int main(){
    vector<int> v={1,2,4,5}; // n=5 missing 3
    cout<<missingNumber(v)<<"\n";
}
```

---

### 5) Rotate array by k positions (right rotation)

- Use reverse trick: reverse whole, reverse first k, reverse rest.

```cpp
#include <bits/stdc++.h>
using namespace std;
void rotateRight(vector<int>& a, int k){
    int n = a.size(); k %= n;
    reverse(a.begin(), a.end());
    reverse(a.begin(), a.begin()+k);
    reverse(a.begin()+k, a.end());
}
int main(){
    vector<int> v={1,2,3,4,5,6,7};
    rotateRight(v,3);
    for(int x:v) cout<<x<<" "; cout<<"\n"; // 5 6 7 1 2 3 4
}
```

---

### 6) Move all zeros to the end

- Two-pointer in-place stable method.

```cpp
#include <bits/stdc++.h>
using namespace std;
void moveZeros(vector<int>& a){
    int pos = 0;
    for(int x: a) if(x!=0) a[pos++] = x;
    while(pos < a.size()) a[pos++] = 0;
}
int main(){
    vector<int> v={0,1,0,3,12};
    moveZeros(v);
    for(int x:v) cout<<x<<" "; cout<<"\n"; // 1 3 12 0 0
}
```

---

### 7) Longest substring without repeating characters

- Sliding window with map of last index.

```cpp
#include <bits/stdc++.h>
using namespace std;
int lengthOfLongestSubstring(string s){
    vector<int> last(256, -1);
    int start=0, maxlen=0;
    for(int i=0;i<s.size();++i){
        start = max(start, last[s[i]] + 1);
        maxlen = max(maxlen, i - start + 1);
        last[s[i]] = i;
    }
    return maxlen;
}
int main(){
    cout<<lengthOfLongestSubstring("abcabcbb")<<"\n"; // 3
}
```

---

### 8) Check if two strings are anagrams

- Count-based or sorting. Counting O(n).

```cpp
#include <bits/stdc++.h>
using namespace std;
bool areAnagrams(string a, string b){
    if(a.size()!=b.size()) return false;
    vector<int> cnt(256,0);
    for(char c: a) cnt[(unsigned char)c]++;
    for(char c: b) if(--cnt[(unsigned char)c] < 0) return false;
    return true;
}
int main(){
    cout<<areAnagrams("listen","silent")<<"\n"; // 1
}
```

---

### 9) Implement strstr() / substring search (naive and KMP)

- Short KMP implementation (returns first index or -1).

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> buildLPS(const string &p){
    int n=p.size(); vector<int> lps(n,0);
    for(int i=1,len=0;i<n;){
        if(p[i]==p[len]) lps[i++]=++len;
        else if(len) len = lps[len-1];
        else lps[i++]=0;
    }
    return lps;
}
int kmpSearch(const string &s, const string &p){
    if(p.empty()) return 0;
    auto lps = buildLPS(p);
    for(int i=0,j=0;i<s.size();){
        if(s[i]==p[j]){ i++; j++; if(j==p.size()) return i-j; }
        else if(j) j = lps[j-1];
        else i++;
    }
    return -1;
}
int main(){
    cout<<kmpSearch("hello world", "world")<<"\n"; // 6
}
```

---

### 10) Trapping Rainwater

- Use two-pointer approach O(n), O(1) extra.

```cpp
#include <bits/stdc++.h>
using namespace std;
int trap(vector<int>& h){
    int l=0,r=h.size()-1;
    int leftMax=0,rightMax=0, ans=0;
    while(l<r){
        if(h[l] < h[r]){
            if(h[l] >= leftMax) leftMax = h[l];
            else ans += leftMax - h[l];
            ++l;
        } else {
            if(h[r] >= rightMax) rightMax = h[r];
            else ans += rightMax - h[r];
            --r;
        }
    }
    return ans;
}
int main(){
    vector<int> v={0,1,0,2,1,0,1,3,2,1,2,1};
    cout<<trap(v)<<"\n"; // 6
}
```

---

# Linked Lists

- *(Using a simple singly-linked list node)*

```cpp
struct Node {
    int val;
    Node* next;
    Node(int x): val(x), next(nullptr) {}
};
```

---

### 11) Reverse a linked list (iterative & recursive)

- Iterative:

```cpp
Node* reverseIter(Node* head){
    Node *prev=nullptr, *cur=head;
    while(cur){
        Node* nxt = cur->next;
        cur->next = prev;
        prev = cur;
        cur = nxt;
    }
    return prev;
}
```

- Recursive:

```cpp
Node* reverseRec(Node* head){
    if(!head || !head->next) return head;
    Node* rest = reverseRec(head->next);
    head->next->next = head;
    head->next = nullptr;
    return rest;
}
```

---

### 12) Detect and remove cycle (Floyd’s algorithm)

- Detect with slow/fast, then find start, optionally remove.

```cpp
Node* detectCycle(Node* head){
    Node *slow=head, *fast=head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
        if(slow==fast) {
            // find start
            slow = head;
            while(slow != fast){
                slow = slow->next;
                fast = fast->next;
            }
            return slow; // start of cycle
        }
    }
    return nullptr;
}
void removeCycle(Node* head){
    Node* start = detectCycle(head);
    if(!start) return;
    Node* p = start;
    while(p->next != start) p = p->next;
    p->next = nullptr;
}
```

---

### 13) Find middle node of linked list

- Use slow/fast: slow will be middle (for even length, returns second middle typically).

```cpp
Node* middleNode(Node* head){
    Node *slow=head, *fast=head;
    while(fast && fast->next){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
```

---

### 14) Merge two sorted linked lists

- Classic iterative merge.

```cpp
Node* mergeTwoLists(Node* a, Node* b){
    Node dummy(0); Node* tail = &dummy;
    while(a && b){
        if(a->val < b->val){ tail->next=a; a=a->next; }
        else { tail->next=b; b=b->next; }
        tail = tail->next;
    }
    tail->next = a ? a : b;
    return dummy.next;
}
```

---

### 15) Check if a linked list is palindrome

- Use fast/slow to find mid, reverse second half, compare, restore.

```cpp
bool isPalindrome(Node* head){
    if(!head || !head->next) return true;
    Node *slow=head, *fast=head;
    while(fast && fast->next){ slow=slow->next; fast=fast->next->next; }
    // reverse second half
    Node *prev=nullptr, *cur=slow;
    while(cur){ Node*nxt=cur->next; cur->next=prev; prev=cur; cur=nxt; }
    // compare
    Node *p=head, *q=prev;
    bool ok=true;
    while(q){ if(p->val!=q->val){ ok=false; break; } p=p->next; q=q->next; }
    // (optional) restore second half
    return ok;
}
```

---

### 16) Remove nth node from end

- Use two pointers with gap n.

```cpp
Node* removeNthFromEnd(Node* head, int n){
    Node dummy(0); dummy.next=head;
    Node *first=&dummy, *second=&dummy;
    for(int i=0;i<=n;i++) first = first->next;
    while(first){ first=first->next; second=second->next; }
    Node* toDel = second->next;
    second->next = second->next->next;
    // delete toDel; // optional in interview pseudo
    return dummy.next;
}
```

---

### 17) Intersection point of two linked lists

- Use two-pointer switching trick (O(m+n), O(1)).

```cpp
Node* getIntersection(Node* a, Node* b){
    if(!a || !b) return nullptr;
    Node *p=a, *q=b;
    while(p!=q){
        p = p ? p->next : b;
        q = q ? q->next : a;
    }
    return p; // null if no intersection or intersection node
}
```

---

### 18) Add two numbers represented as linked lists

- Digits stored in reverse order (LeetCode style).

```cpp
Node* addTwoNumbers(Node* l1, Node* l2){
    Node dummy(0); Node* tail=&dummy; int carry=0;
    while(l1 || l2 || carry){
        int sum = carry + (l1?l1->val:0) + (l2?l2->val:0);
        carry = sum/10;
        tail->next = new Node(sum%10);
        tail = tail->next;
        if(l1) l1=l1->next; if(l2) l2=l2->next;
    }
    return dummy.next;
}
```

---

# Stacks & Queues

### 19) Implement stack using queues

- Two approaches. Example: push costly using one queue as buffer.

```cpp
#include <queue>
using namespace std;
class StackUsingQueues {
    queue<int> q;
public:
    void push(int x){
        q.push(x);
        int sz = q.size();
        while(sz-- > 1){ q.push(q.front()); q.pop(); }
    }
    void pop(){ if(!q.empty()) q.pop(); }
    int top(){ return q.empty()? -1 : q.front(); }
    bool empty(){ return q.empty(); }
};
```

---

### 20) Implement queue using stacks

- Two-stack approach (amortized O(1)).

```cpp
#include <stack>
using namespace std;
class QueueUsingStacks {
    stack<int> s1, s2;
    void pour(){ while(!s1.empty()){ s2.push(s1.top()); s1.pop(); } }
public:
    void push(int x){ s1.push(x); }
    void pop(){
        if(s2.empty()) pour();
        if(!s2.empty()) s2.pop();
    }
    int front(){
        if(s2.empty()) pour();
        return s2.empty()? -1 : s2.top();
    }
    bool empty(){ return s1.empty() && s2.empty(); }
};
```

---

### 21) Evaluate postfix (Reverse Polish) expression

- Stack-based evaluate.

```cpp
#include <bits/stdc++.h>
using namespace std;
int evalRPN(vector<string>& tokens){
    stack<int> st;
    for(auto &t : tokens){
        if(t=="+"||t=="-"||t=="*"||t=="/"){
            int b=st.top(); st.pop();
            int a=st.top(); st.pop();
            if(t=="+") st.push(a+b);
            else if(t=="-") st.push(a-b);
            else if(t=="*") st.push(a*b);
            else st.push(a/b);
        } else st.push(stoi(t));
    }
    return st.top();
}
int main(){
    vector<string> tok={"2","1","+","3","*"};
    cout<<evalRPN(tok)<<"\n"; // 9
}
```

---

### 22) Check balanced parentheses

- Use stack to match pairs.

```cpp
#include <bits/stdc++.h>
using namespace std;
bool isValid(string s){
    unordered_map<char,char> mp = {{')','('},{']','['},{'}','{'}};
    stack<char> st;
    for(char c:s){
        if(c=='('||c=='['||c=='{') st.push(c);
        else {
            if(st.empty() || st.top() != mp[c]) return false;
            st.pop();
        }
    }
    return st.empty();
}
int main(){ cout<<isValid("({[]})")<<"\n"; }
```

---

### 23) Next greater element

- Use monotonic stack; for each element find next greater to right.

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> nextGreater(vector<int>& a){
    int n=a.size();
    vector<int> res(n, -1);
    stack<int> st; // indices
    for(int i=0;i<n;++i){
        while(!st.empty() && a[i] > a[st.top()]){
            res[st.top()] = a[i];
            st.pop();
        }
        st.push(i);
    }
    return res;
}
int main(){
    vector<int> v={4,5,2,25};
    auto r = nextGreater(v);
    for(int x:r) cout<<x<<" "; cout<<"\n"; // 5 25 25 -1
}
```

---

### 24) LRU Cache design (using unordered_map + list)

- Compact LRU (get & put O(1)).

```cpp
#include <bits/stdc++.h>
using namespace std;
class LRUCache {
    int cap;
    list<pair<int,int>> dll; // key, val
    unordered_map<int, list<pair<int,int>>::iterator> mp;
public:
    LRUCache(int capacity): cap(capacity) {}
    int get(int key){
        if(mp.find(key)==mp.end()) return -1;
        auto it = mp[key];
        int val = it->second;
        dll.erase(it);
        dll.push_front({key,val});
        mp[key] = dll.begin();
        return val;
    }
    void put(int key, int value){
        if(mp.find(key)!=mp.end()){
            dll.erase(mp[key]);
        } else if(dll.size() == cap){
            auto last = dll.back();
            mp.erase(last.first);
            dll.pop_back();
        }
        dll.push_front({key,value});
        mp[key] = dll.begin();
    }
};
```

---

### 25) Min stack — return min in O(1)

- Keep auxiliary stack of mins or store pairs.

```cpp
#include <stack>
using namespace std;
class MinStack {
    stack<pair<int,int>> st; // value, current min
public:
    void push(int x){ 
        if(st.empty()) st.push({x,x});
        else st.push({x, min(x, st.top().second)});
    }
    void pop(){ if(!st.empty()) st.pop(); }
    int top(){ return st.top().first; }
    int getMin(){ return st.top().second; }
};
```

---

### 26) Sliding window maximum (deque)

- Use deque of indices maintaining decreasing order.

```cpp
#include <bits/stdc++.h>
using namespace std;
vector<int> slidingWindowMax(vector<int>& a, int k){
    deque<int> dq; vector<int> res;
    for(int i=0;i<a.size();++i){
        while(!dq.empty() && dq.front() <= i-k) dq.pop_front();
        while(!dq.empty() && a[dq.back()] <= a[i]) dq.pop_back();
        dq.push_back(i);
        if(i>=k-1) res.push_back(a[dq.front()]);
    }
    return res;
}
int main(){
    vector<int> v={1,3,-1,-3,5,3,6,7};
    auto r = slidingWindowMax(v,3);
    for(int x:r) cout<<x<<" "; cout<<"\n"; // 3 3 5 5 6 7
}
```

---

# Trees & Binary Trees

### 27) Inorder / Preorder / Postorder traversal (recursive + iterative inorder)

```cpp
#include <bits/stdc++.h>
using namespace std;
struct Tree{int val; Tree* l; Tree* r; Tree(int v):val(v),l(nullptr),r(nullptr){}};

void inorder(Tree* root){
    if(!root) return;
    inorder(root->l); cout<<root->val<<" "; inorder(root->r);
}
void preorder(Tree* root){
    if(!root) return;
    cout<<root->val<<" "; preorder(root->l); preorder(root->r);
}
void postorder(Tree* root){
    if(!root) return;
    postorder(root->l); postorder(root->r); cout<<root->val<<" ";
}
// iterative inorder
vector<int> inorderIter(Tree* root){
    vector<int> res; stack<Tree*> st; Tree* cur=root;
    while(cur || !st.empty()){
        while(cur){ st.push(cur); cur=cur->l; }
        cur = st.top(); st.pop();
        res.push_back(cur->val);
        cur = cur->r;
    }
    return res;
}
```

### 28) Level-order traversal (BFS)

```cpp
vector<vector<int>> levelOrder(Tree* root){
    vector<vector<int>> res;
    if(!root) return res;
    queue<Tree*> q; q.push(root);
    while(!q.empty()){
        int sz=q.size(); res.emplace_back();
        while(sz--){
            Tree* t=q.front(); q.pop();
            res.back().push_back(t->val);
            if(t->l) q.push(t->l);
            if(t->r) q.push(t->r);
        }
    }
    return res;
}
```

### 29) Height of a tree (recursive)

```cpp
int height(Tree* root){
    if(!root) return 0;
    return 1 + max(height(root->l), height(root->r));
}
```

### 30) Lowest Common Ancestor (LCA) — binary tree (not BST)

```cpp
Tree* lca(Tree* root, Tree* p, Tree* q){
    if(!root || root==p || root==q) return root;
    Tree* left = lca(root->l, p, q);
    Tree* right = lca(root->r, p, q);
    if(left && right) return root;
    return left ? left : right;
}
```

### 31) Check if two trees are identical

```cpp
bool isSame(Tree* a, Tree* b){
    if(!a && !b) return true;
    if(!a || !b) return false;
    return a->val==b->val && isSame(a->l,b->l) && isSame(a->r,b->r);
}
```

### 32) Diameter of a binary tree (longest path)

```cpp
int diamUtil(Tree* root, int &ans){
    if(!root) return 0;
    int L = diamUtil(root->l, ans);
    int R = diamUtil(root->r, ans);
    ans = max(ans, L+R); // edges count; +1 for nodes if desired
    return 1 + max(L,R);
}
int diameter(Tree* root){ int ans=0; diamUtil(root, ans); return ans; }
```

### 33) Check if a tree is balanced (height-balanced)

```cpp
int checkHeight(Tree* root){
    if(!root) return 0;
    int lh = checkHeight(root->l);
    if(lh==-1) return -1;
    int rh = checkHeight(root->r);
    if(rh==-1) return -1;
    if(abs(lh-rh)>1) return -1;
    return 1 + max(lh,rh);
}
bool isBalanced(Tree* root){ return checkHeight(root) != -1; }
```

### 34) Serialize and deserialize binary tree (preorder with nulls)

```cpp
// serialize to string using pre-order with '#'
void serialize(Tree* root, ostream &out){
    if(!root){ out << "# "; return; }
    out << root->val << ' ';
    serialize(root->l, out);
    serialize(root->r, out);
}
Tree* deserialize(istringstream &in){
    string token; if(!(in>>token)) return nullptr;
    if(token=="#") return nullptr;
    Tree* node = new Tree(stoi(token));
    node->l = deserialize(in);
    node->r = deserialize(in);
    return node;
}
// Usage: string s; ostringstream oss; serialize(root, oss); s=oss.str();
// To read: istringstream iss(s); root = deserialize(iss);
```

### 35) Boundary traversal of a binary tree (left boundary, leaves, right boundary)

```cpp
void addLeft(Tree* root, vector<int>& ans){
    Tree* cur = root->l;
    while(cur){
        if(cur->l || cur->r) ans.push_back(cur->val);
        if(cur->l) cur = cur->l; else cur = cur->r;
    }
}
void addRight(Tree* root, vector<int>& ans){
    vector<int> tmp; Tree* cur=root->r;
    while(cur){
        if(cur->l || cur->r) tmp.push_back(cur->val);
        if(cur->r) cur=cur->r; else cur=cur->l;
    }
    for(auto it=tmp.rbegin(); it!=tmp.rend(); ++it) ans.push_back(*it);
}
void addLeaves(Tree* root, vector<int>& ans){
    if(!root) return;
    if(!root->l && !root->r){ ans.push_back(root->val); return; }
    addLeaves(root->l, ans); addLeaves(root->r, ans);
}
vector<int> boundary(Tree* root){
    vector<int> ans;
    if(!root) return ans;
    ans.push_back(root->val);
    addLeft(root, ans);
    addLeaves(root, ans);
    addRight(root, ans);
    return ans;
}
```

# Binary Search Trees (BST)

### 36) Search / Insert / Delete in BST

```cpp
Tree* bstSearch(Tree* root, int key){
    if(!root) return nullptr;
    if(root->val==key) return root;
    return key < root->val ? bstSearch(root->l, key) : bstSearch(root->r, key);
}
Tree* bstInsert(Tree* root, int key){
    if(!root) return new Tree(key);
    if(key < root->val) root->l = bstInsert(root->l, key);
    else root->r = bstInsert(root->r, key);
    return root;
}
Tree* findMin(Tree* root){ while(root->l) root=root->l; return root; }
Tree* bstDelete(Tree* root, int key){
    if(!root) return nullptr;
    if(key < root->val) root->l = bstDelete(root->l, key);
    else if(key > root->val) root->r = bstDelete(root->r, key);
    else {
        if(!root->l){ Tree* r=root->r; delete root; return r; }
        if(!root->r){ Tree* l=root->l; delete root; return l; }
        Tree* succ = findMin(root->r);
        root->val = succ->val;
        root->r = bstDelete(root->r, succ->val);
    }
    return root;
}
```

### 37) Kth smallest & largest element in BST (inorder)

```cpp
int kthSmall(Tree* root, int &k){
    if(!root) return -1;
    int left = kthSmall(root->l, k);
    if(left!=-1) return left;
    if(--k==0) return root->val;
    return kthSmall(root->r, k);
}
int kthLargest(Tree* root, int &k){
    if(!root) return -1;
    int r = kthLargest(root->r, k);
    if(r!=-1) return r;
    if(--k==0) return root->val;
    return kthLargest(root->l, k);
}
```

### 38) Validate a BST

```cpp
bool isValidBST(Tree* root, long long low=LLONG_MIN, long long high=LLONG_MAX){
    if(!root) return true;
    if(root->val <= low || root->val >= high) return false;
    return isValidBST(root->l, low, root->val) && isValidBST(root->r, root->val, high);
}
```

### 39) Convert sorted array to BST (height-balanced)

```cpp
Tree* sortedToBST(vector<int>& a, int l, int r){
    if(l>r) return nullptr;
    int m = (l+r)/2;
    Tree* root = new Tree(a[m]);
    root->l = sortedToBST(a,l,m-1);
    root->r = sortedToBST(a,m+1,r);
    return root;
}
```

### 40) Inorder successor in BST

```cpp
Tree* inorderSuccessor(Tree* root, Tree* p){
    Tree* succ = nullptr;
    while(root){
        if(p->val < root->val){ succ = root; root = root->l; }
        else root = root->r;
    }
    return succ;
}
```

# Heaps / Priority Queues

### 41) Kth largest / smallest element (heap or nth_element)

```cpp
int kthLargest(vector<int>& a, int k){
    priority_queue<int, vector<int>, greater<int>> pq;
    for(int x:a){
        pq.push(x);
        if(pq.size()>k) pq.pop();
    }
    return pq.top();
}
// kth smallest -> min-heap variant or use nth_element:
int kthSmallest_nth(vector<int>& a, int k){
    nth_element(a.begin(), a.begin()+k-1, a.end());
    return a[k-1];
}
```

### 42) Merge k sorted arrays (min-heap)

```cpp
vector<int> mergeK(vector<vector<int>>& lists){
    using T = tuple<int,int,int>; // val, listIdx, elementIdx
    priority_queue<T, vector<T>, greater<T>> pq;
    for(int i=0;i<lists.size();++i) if(!lists[i].empty()) pq.emplace(lists[i][0], i, 0);
    vector<int> res;
    while(!pq.empty()){
        auto [val, li, ei] = pq.top(); pq.pop();
        res.push_back(val);
        if(ei+1 < lists[li].size()) pq.emplace(lists[li][ei+1], li, ei+1);
    }
    return res;
}
```

### 43) Build a heap from an array (std::make_heap)

```cpp
vector<int> a = {3,1,4,1,5};
make_heap(a.begin(), a.end()); // max-heap by default
pop_heap(a.begin(), a.end()); // move max to end
a.pop_back();
```

### 44) Median in a data stream (two heaps)

```cpp
class MedianFinder {
    priority_queue<int> lo; // max-heap
    priority_queue<int, vector<int>, greater<int>> hi; // min-heap
public:
    void addNum(int x){
        if(lo.empty() || x <= lo.top()) lo.push(x);
        else hi.push(x);
        if(lo.size() > hi.size()+1){ hi.push(lo.top()); lo.pop(); }
        else if(hi.size() > lo.size()){ lo.push(hi.top()); hi.pop(); }
    }
    double findMedian(){
        if(lo.size() == hi.size()) return (lo.top() + hi.top())/2.0;
        return lo.top();
    }
};
```

### 45) Top k frequent elements (heap or bucket)

```cpp
vector<int> topKFrequent(vector<int>& nums, int k){
    unordered_map<int,int> cnt;
    for(int x:nums) cnt[x]++;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    for(auto &p:cnt){
        pq.emplace(p.second, p.first);
        if(pq.size()>k) pq.pop();
    }
    vector<int> res;
    while(!pq.empty()){ res.push_back(pq.top().second); pq.pop(); }
    reverse(res.begin(), res.end());
    return res;
}
```

# Graphs

- (Using adjacency list `vector<vector<pair<int,int>>>` for weighted; `vector<vector<int>>` for unweighted)

### 46) BFS and DFS traversal

```cpp
void bfs(int s, vector<vector<int>>& adj){
    int n=adj.size(); vector<int> vis(n);
    queue<int> q; q.push(s); vis[s]=1;
    while(!q.empty()){
        int u=q.front(); q.pop(); cout<<u<<" ";
        for(int v: adj[u]) if(!vis[v]){ vis[v]=1; q.push(v); }
    }
}

void dfsUtil(int u, vector<vector<int>>& adj, vector<int>& vis){
    vis[u]=1; cout<<u<<" ";
    for(int v: adj[u]) if(!vis[v]) dfsUtil(v, adj, vis);
}
void dfs(int s, vector<vector<int>>& adj){
    vector<int> vis(adj.size());
    dfsUtil(s, adj, vis);
}
```

### 47) Detect cycle in graph (directed: DFS + coloring; undirected: parent check)

```cpp
// directed
bool dfsCycleDir(int u, vector<vector<int>>& adj, vector<int>& state){
    state[u]=1;
    for(int v: adj[u]){
        if(state[v]==1) return true;
        if(state[v]==0 && dfsCycleDir(v,adj,state)) return true;
    }
    state[u]=2;
    return false;
}
bool hasCycleDirected(vector<vector<int>>& adj){
    int n=adj.size(); vector<int> state(n,0);
    for(int i=0;i<n;i++) if(state[i]==0 && dfsCycleDir(i,adj,state)) return true;
    return false;
}

// undirected
bool dfsCycleUnd(int u, int p, vector<vector<int>>& adj, vector<int>& vis){
    vis[u]=1;
    for(int v: adj[u]){
        if(!vis[v]){
            if(dfsCycleUnd(v,u,adj,vis)) return true;
        } else if(v!=p) return true;
    }
    return false;
}
```

### 48) Topological sort (Kahn's BFS / DFS)

```cpp
vector<int> topoKahn(vector<vector<int>>& adj){
    int n=adj.size(); vector<int> indeg(n,0);
    for(int u=0;u<n;++u) for(int v: adj[u]) indeg[v]++;
    queue<int> q; for(int i=0;i<n;++i) if(indeg[i]==0) q.push(i);
    vector<int> order;
    while(!q.empty()){
        int u=q.front(); q.pop(); order.push_back(u);
        for(int v: adj[u]) if(--indeg[v]==0) q.push(v);
    }
    return order.size()==n ? order : vector<int>{}; // empty = cycle
}
```

### 49) Dijkstra’s shortest path (non-negative weights)

```cpp
vector<long long> dijkstra(int src, vector<vector<pair<int,int>>>& adj){
    int n=adj.size(); const long long INF = 9e18;
    vector<long long> dist(n, INF); dist[src]=0;
    priority_queue<pair<long long,int>, vector<pair<long long,int>>, greater<>> pq;
    pq.emplace(0, src);
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        for(auto [v,w]: adj[u]){
            if(dist[v] > d + w){
                dist[v] = d + w;
                pq.emplace(dist[v], v);
            }
        }
    }
    return dist;
}
```

### 50) Bellman-Ford (handles negative weights, detect negative cycle)

```cpp
vector<long long> bellmanFord(int n, int src, vector<tuple<int,int,int>>& edges){
    const long long INF = 9e18;
    vector<long long> dist(n, INF); dist[src]=0;
    for(int i=1;i<n;i++){
        for(auto &e: edges){
            int u,v,w; tie(u,v,w)=e;
            if(dist[u]!=INF && dist[v] > dist[u]+w) dist[v] = dist[u] + w;
        }
    }
    // detect negative cycle
    for(auto &e: edges){
        int u,v,w; tie(u,v,w)=e;
        if(dist[u]!=INF && dist[v] > dist[u]+w) return {}; // empty -> negative cycle
    }
    return dist;
}
```

### 51) Floyd–Warshall (all-pairs shortest paths)

```cpp
vector<vector<long long>> floydWarshall(int n, vector<vector<long long>>& mat){
    const long long INF = 9e18;
    auto dist = mat;
    for(int k=0;k<n;++k)
        for(int i=0;i<n;++i)
            for(int j=0;j<n;++j)
                if(dist[i][k]<INF && dist[k][j]<INF)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    return dist;
}
```

### 52) Minimum spanning tree (Kruskal & Prim)

```cpp
// Kruskal (DSU)
struct DSU{ vector<int> p, r; DSU(int n):p(n),r(n){iota(p.begin(),p.end(),0);} 
int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
bool unite(int a,int b){ a=find(a); b=find(b); if(a==b) return false; if(r[a]<r[b]) swap(a,b); p[b]=a; if(r[a]==r[b]) r[a]++; return true; }};

long long kruskal(int n, vector<tuple<int,int,int>>& edges){
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){ return get<2>(a) < get<2>(b); });
    DSU ds(n); long long cost=0;
    for(auto &e: edges){
        int u,v,w; tie(u,v,w)=e;
        if(ds.unite(u,v)) cost += w;
    }
    return cost;
}

// Prim (priority_queue)
long long prim(int src, vector<vector<pair<int,int>>>& adj){
    int n=adj.size(); vector<int> vis(n);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq; pq.emplace(0, src);
    long long cost=0;
    while(!pq.empty()){
        auto [w,u]=pq.top(); pq.pop();
        if(vis[u]) continue; vis[u]=1; cost+=w;
        for(auto [v,wt]: adj[u]) if(!vis[v]) pq.emplace(wt, v);
    }
    return cost;
}
```

### 53) Number of islands (grid BFS/DFS)

```cpp
int numIslands(vector<vector<char>>& grid){
    int m=grid.size(), n=grid[0].size(), cnt=0;
    function<void(int,int)> dfs=[&](int i,int j){
        if(i<0||j<0||i>=m||j>=n||grid[i][j]=='0') return;
        grid[i][j]='0';
        dfs(i+1,j); dfs(i-1,j); dfs(i,j+1); dfs(i,j-1);
    };
    for(int i=0;i<m;++i) for(int j=0;j<n;++j) if(grid[i][j]=='1'){ cnt++; dfs(i,j); }
    return cnt;
}
```

### 54) Check if graph is bipartite (2-coloring using BFS)

```cpp
bool isBipartite(vector<vector<int>>& adj){
    int n=adj.size();
    vector<int> color(n, -1);
    for(int i=0;i<n;++i) if(color[i]==-1){
        queue<int> q; q.push(i); color[i]=0;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v: adj[u]){
                if(color[v]==-1){ color[v]=color[u]^1; q.push(v); }
                else if(color[v]==color[u]) return false;
            }
        }
    }
    return true;
}
```

### 55) Clone a graph (DFS with map)

```cpp
struct GNode{ int val; vector<GNode*> nbr; GNode(int v):val(v){} };
GNode* cloneGraph(GNode* node){
    if(!node) return nullptr;
    unordered_map<GNode*, GNode*> mp;
    function<GNode*(GNode*)> dfs = [&](GNode* u)->GNode*{
        if(mp.count(u)) return mp[u];
        GNode* copy = new GNode(u->val); mp[u]=copy;
        for(auto v: u->nbr) copy->nbr.push_back(dfs(v));
        return copy;
    };
    return dfs(node);
}
```

# Dynamic Programming (DP)

### 56) Fibonacci using DP (iterative)

```cpp
long long fib(int n){
    if(n<=1) return n;
    long long a=0,b=1;
    for(int i=2;i<=n;++i){ long long c=a+b; a=b; b=c; }
    return b;
}
```

### 57) Longest Increasing Subsequence (LIS) — O(n log n)

```cpp
int LIS(vector<int>& a){
    vector<int> d;
    for(int x: a){
        auto it = lower_bound(d.begin(), d.end(), x);
        if(it==d.end()) d.push_back(x);
        else *it = x;
    }
    return d.size();
}
```

### 58) 0/1 Knapsack (DP table)

```cpp
int knapsack(vector<int>& wt, vector<int>& val, int W){
    int n = wt.size();
    vector<int> dp(W+1, 0);
    for(int i=0;i<n;++i){
        for(int w=W; w>=wt[i]; --w) dp[w] = max(dp[w], dp[w-wt[i]] + val[i]);
    }
    return dp[W];
}
```

### 59) Coin change (min coins)

```cpp
int coinChange(vector<int>& coins, int amount){
    const int INF = 1e9;
    vector<int> dp(amount+1, INF); dp[0]=0;
    for(int c: coins) for(int i=c;i<=amount;++i) dp[i]=min(dp[i], dp[i-c]+1);
    return dp[amount]==INF ? -1 : dp[amount];
}
```

### 60) Longest Common Subsequence (LCS)

```cpp
int lcs(string &a, string &b){
    int n=a.size(), m=b.size();
    vector<int> dp(m+1,0), prev(m+1,0);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            if(a[i-1]==b[j-1]) dp[j] = prev[j-1] + 1;
            else dp[j] = max(prev[j], dp[j-1]);
        }
        swap(dp, prev);
    }
    return prev[m];
}
```

### 61) Edit distance (Levenshtein)

```cpp
int editDistance(string &a, string &b){
    int n=a.size(), m=b.size();
    vector<int> dp(m+1);
    iota(dp.begin(), dp.end(), 0);
    for(int i=1;i<=n;++i){
        vector<int> ndp(m+1); ndp[0]=i;
        for(int j=1;j<=m;++j){
            if(a[i-1]==b[j-1]) ndp[j]=dp[j-1];
            else ndp[j] = 1 + min({dp[j], ndp[j-1], dp[j-1]}); // delete, insert, replace
        }
        dp.swap(ndp);
    }
    return dp[m];
}
```

### 62) Matrix chain multiplication (DP)

```cpp
int matrixChain(vector<int>& dims){
    int n = dims.size()-1;
    vector<vector<int>> dp(n, vector<int>(n, 0));
    for(int len=2; len<=n; ++len){
        for(int i=0;i+len-1<n;++i){
            int j=i+len-1; dp[i][j]=INT_MAX;
            for(int k=i;k<j;++k){
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j] + dims[i]*dims[k+1]*dims[j+1]);
            }
        }
    }
    return dp[0][n-1];
}
```

### 63) House robber (linear DP)

```cpp
int rob(vector<int>& a){
    int n=a.size();
    if(n==0) return 0; if(n==1) return a[0];
    int prev=a[0], cur=max(a[0], a[1]);
    for(int i=2;i<n;++i){ int nxt = max(cur, prev + a[i]); prev=cur; cur=nxt; }
    return cur;
}
```

### 64) Rod cutting

```cpp
int rodCut(vector<int>& price, int n){
    vector<int> dp(n+1, 0);
    for(int len=1; len<=n; ++len){
        for(int cut=1; cut<=len; ++cut) dp[len] = max(dp[len], price[cut-1] + dp[len-cut]);
    }
    return dp[n];
}
```

### 65) Maximum product subarray

```cpp
int maxProduct(vector<int>& a){
    int n=a.size();
    int maxp=a[0], minp=a[0], ans=a[0];
    for(int i=1;i<n;++i){
        if(a[i]<0) swap(maxp,minp);
        maxp = max(a[i], maxp * a[i]);
        minp = min(a[i], minp * a[i]);
        ans = max(ans, maxp);
    }
    return ans;
}
```

# Greedy Algorithms

### 66) Activity selection (select max non-overlapping intervals)

```cpp
int maxActivities(vector<pair<int,int>>& acts){
    sort(acts.begin(), acts.end(), [](auto &a, auto &b){ return a.second < b.second; });
    int cnt=0, last=-1e9;
    for(auto &p: acts) if(p.first >= last){ cnt++; last = p.second; }
    return cnt;
}
```

### 67) Fractional knapsack (greedy by value/weight)

```cpp
double fractionalKnapsack(vector<pair<int,int>>& items, int W){
    vector<pair<double, pair<int,int>>> v;
    for(auto &it: items) v.push_back({(double)it.first/it.second, it});
    sort(v.rbegin(), v.rend());
    double res=0; int curW=0;
    for(auto &p: v){
        int val=p.second.first, wt=p.second.second;
        if(curW + wt <= W){ curW += wt; res += val; }
        else { res += p.first * (W - curW); break; }
    }
    return res;
}
```

### 68) Huffman coding (build tree using min-heap) — skip full decode tree code for brevity

```cpp
// Create min-heap of nodes with frequencies, merge until one remains.
// Not included full tree printing; interview-level explanation + sketch is fine.
```

### 69) Job sequencing with deadlines (max profit)

```cpp
int jobSequence(vector<pair<int,int>>& jobs){ // pair(deadline, profit)
    sort(jobs.begin(), jobs.end(), [](auto &a, auto &b){ return a.second > b.second; });
    int maxd = 0; for(auto &j: jobs) maxd = max(maxd, j.first);
    vector<int> slot(maxd+1, -1);
    int profit=0;
    for(auto &j: jobs){
        for(int d=j.first; d>0; --d){
            if(slot[d]==-1){ slot[d]=1; profit += j.second; break; }
        }
    }
    return profit;
}
```

### 70) Gas station circular tour (greedy O(n))

```cpp
int canCompleteCircuit(vector<int>& gas, vector<int>& cost){
    int n=gas.size(), total=0, tank=0, start=0;
    for(int i=0;i<n;++i){
        int diff = gas[i]-cost[i];
        total += diff; tank += diff;
        if(tank<0){ start = i+1; tank=0; }
    }
    return total>=0 ? start : -1;
}
```

# Searching & Sorting

### 71) Binary search variations (first / last occurrence)

```cpp
int firstOcc(vector<int>& a, int x){
    int l=0, r=a.size()-1, ans=-1;
    while(l<=r){
        int m = l + (r-l)/2;
        if(a[m]==x){ ans=m; r=m-1; }
        else if(a[m] < x) l = m+1;
        else r = m-1;
    }
    return ans;
}
int lastOcc(vector<int>& a, int x){
    int l=0, r=a.size()-1, ans=-1;
    while(l<=r){
        int m = l + (r-l)/2;
        if(a[m]==x){ ans=m; l=m+1; }
        else if(a[m] < x) l = m+1;
        else r = m-1;
    }
    return ans;
}
```

### 72) QuickSort (in-place)

```cpp
int partition(vector<int>& a, int l, int r){
    int pivot = a[r], i=l-1;
    for(int j=l;j<r;++j) if(a[j] <= pivot) swap(a[++i], a[j]);
    swap(a[i+1], a[r]); return i+1;
}
void quickSort(vector<int>& a, int l, int r){
    if(l<r){ int p = partition(a,l,r); quickSort(a,l,p-1); quickSort(a,p+1,r); }
}
```

### 73) MergeSort

```cpp
void mergeSort(vector<int>& a, int l, int r){
    if(l>=r) return;
    int m = (l+r)/2;
    mergeSort(a,l,m); mergeSort(a,m+1,r);
    vector<int> tmp; int i=l,j=m+1;
    while(i<=m && j<=r) tmp.push_back(a[i]<=a[j]?a[i++]:a[j++]);
    while(i<=m) tmp.push_back(a[i++]);
    while(j<=r) tmp.push_back(a[j++]);
    for(int k=0;k<tmp.size();++k) a[l+k]=tmp[k];
}
```

### 74) Count inversions in an array (merge sort)

```cpp
long long mergeCount(vector<int>& a, int l, int r){
    if(l>=r) return 0;
    int m=(l+r)/2; long long cnt=mergeCount(a,l,m)+mergeCount(a,m+1,r);
    vector<int> tmp; int i=l,j=m+1;
    while(i<=m && j<=r){
        if(a[i]<=a[j]) tmp.push_back(a[i++]);
        else { tmp.push_back(a[j++]); cnt += (m - i + 1); }
    }
    while(i<=m) tmp.push_back(a[i++]);
    while(j<=r) tmp.push_back(a[j++]);
    for(int k=0;k<tmp.size();++k) a[l+k]=tmp[k];
    return cnt;
}
```

### 75) Find peak element (element > neighbors) — binary search

```cpp
int findPeak(vector<int>& a){
    int l=0, r=a.size()-1;
    while(l<r){
        int m = l + (r-l)/2;
        if(a[m] < a[m+1]) l = m+1;
        else r = m;
    }
    return l;
}
```

# Hashing

### 76) Two-sum using hash (already shown earlier)

### 77) Longest consecutive subsequence (hash set)

```cpp
int longestConsecutive(vector<int>& a){
    unordered_set<int> s(a.begin(), a.end());
    int best=0;
    for(int x: a){
        if(!s.count(x-1)){
            int cur = x, len = 1;
            while(s.count(cur+1)){ cur++; len++; }
            best = max(best, len);
        }
    }
    return best;
}
```

### 78) Group anagrams

```cpp
vector<vector<string>> groupAnagrams(vector<string>& strs){
    unordered_map<string, vector<string>> mp;
    for(auto &s: strs){
        string t = s; sort(t.begin(), t.end());
        mp[t].push_back(s);
    }
    vector<vector<string>> res;
    for(auto &p: mp) res.push_back(move(p.second));
    return res;
}
```

### 79) Subarray sum equals k (prefix-sum + hash)

```cpp
int subarraySum(vector<int>& a, int k){
    unordered_map<int,int> cnt; cnt[0]=1;
    int sum=0, res=0;
    for(int x: a){
        sum += x;
        if(cnt.count(sum-k)) res += cnt[sum-k];
        cnt[sum]++;
    }
    return res;
}
```

### 80) Find duplicates using hashing

```cpp
vector<int> findDuplicates(vector<int>& a){
    unordered_set<int> seen; vector<int> res;
    for(int x: a){
        if(seen.count(x)) res.push_back(x);
        else seen.insert(x);
    }
    return res;
}
```

# Miscellaneous

### 81) Design TinyURL (high-level)

- Sketch: generate short code via base62 of counter or hash with collision handling; store mapping in DB (key → long URL), TTL optional, analytics via counts. (Interviews expect design discussion rather than full code.)

### 82) Implement Trie (insert / search / delete)

```cpp
struct Trie {
    bool end = false;
    array<Trie*,26> child{};
    Trie(){ child.fill(nullptr); }
};
void insertTrie(Trie* root, const string &s){
    Trie* cur=root;
    for(char c: s){
        int idx=c-'a';
        if(!cur->child[idx]) cur->child[idx] = new Trie();
        cur = cur->child[idx];
    }
    cur->end = true;
}
bool searchTrie(Trie* root, const string &s){
    Trie* cur=root;
    for(char c: s){
        int idx=c-'a';
        if(!cur->child[idx]) return false;
        cur = cur->child[idx];
    }
    return cur->end;
}
```

### 83) Median of two sorted arrays (O(log(min(n,m)))) — classic binary search

```cpp
double findMedianSortedArrays(vector<int>& A, vector<int>& B){
    if(A.size() > B.size()) return findMedianSortedArrays(B, A);
    int n=A.size(), m=B.size(), imin=0, imax=n, half=(n+m+1)/2;
    while(imin<=imax){
        int i=(imin+imax)/2;
        int j=half-i;
        if(i < n && B[j-1] > A[i]) imin = i+1;
        else if(i > 0 && A[i-1] > B[j]) imax = i-1;
        else {
            int maxLeft = 0;
            if(i==0) maxLeft = B[j-1];
            else if(j==0) maxLeft = A[i-1];
            else maxLeft = max(A[i-1], B[j-1]);
            if((n+m)%2==1) return maxLeft;
            int minRight;
            if(i==n) minRight = B[j];
            else if(j==m) minRight = A[i];
            else minRight = min(A[i], B[j]);
            return (maxLeft + minRight) / 2.0;
        }
    }
    return 0.0;
}
```

### 84) Circular buffer (ring buffer) — simple class

```cpp
class CircularBuffer {
    vector<int> buf; int head=0, tail=0, cap=0, sz=0;
public:
    CircularBuffer(int k): buf(k), cap(k) {}
    bool push(int x){ if(sz==cap) return false; buf[tail]=x; tail=(tail+1)%cap; sz++; return true; }
    bool pop(){ if(sz==0) return false; head=(head+1)%cap; sz--; return true; }
    int front(){ return sz? buf[head] : -1; }
    bool empty(){ return sz==0; }
    bool full(){ return sz==cap; }
};
```

### 85) Majority element — Boyer-Moore

```cpp
int majorityElement(vector<int>& a){
    int cand=0, cnt=0;
    for(int x: a){
        if(cnt==0){ cand=x; cnt=1; }
        else if(cand==x) cnt++;
        else cnt--;
    }
    return cand; // verify if required (count occurrences) in interview
}
```

### 86) Detect duplicates in stream (Bloom filter idea / hash set)

- Simple: use unordered_set; for memory-constrained probabilistic detection use Bloom filter (explain tradeoffs in interview).

### 87) Interval merge (merge overlapping intervals)

```cpp
vector<pair<int,int>> mergeIntervals(vector<pair<int,int>>& intervals){
    if(intervals.empty()) return {};
    sort(intervals.begin(), intervals.end());
    vector<pair<int,int>> res; res.push_back(intervals[0]);
    for(int i=1;i<intervals.size();++i){
        if(intervals[i].first <= res.back().second) res.back().second = max(res.back().second, intervals[i].second);
        else res.push_back(intervals[i]);
    }
    return res;
}
```

### 88) Generate permutations & combinations (backtracking)

```cpp
void permute(vector<int>& a, int l, vector<vector<int>>& res){
    if(l==a.size()){ res.push_back(a); return; }
    for(int i=l;i<a.size();++i){ swap(a[l],a[i]); permute(a, l+1, res); swap(a[l],a[i]); }
}
void combinations(int n, int k, int start, vector<int>& cur, vector<vector<int>>& res){
    if(cur.size()==k){ res.push_back(cur); return; }
    for(int i=start;i<=n;i++){ cur.push_back(i); combinations(n,k,i+1,cur,res); cur.pop_back(); }
}
```

### 89) N-Queens (backtracking)

```cpp
bool valid(vector<int>& cols, int r, int c){
    for(int i=0;i<r;i++){
        if(cols[i]==c || abs(cols[i]-c)==r-i) return false;
    }
    return true;
}
void solveNQ(int r, int n, vector<int>& cols, vector<vector<int>>& res){
    if(r==n){ res.push_back(cols); return; }
    for(int c=0;c<n;++c){
        if(valid(cols, r, c)){ cols[r]=c; solveNQ(r+1,n,cols,res); }
    }
}
```

### 90) Sudoku solver (backtracking)

```cpp
bool isValidSudoku(vector<vector<int>>& bd, int r, int c, int val){
    for(int i=0;i<9;i++) if(bd[r][i]==val || bd[i][c]==val) return false;
    int br = (r/3)*3, bc = (c/3)*3;
    for(int i=0;i<3;i++) for(int j=0;j<3;j++) if(bd[br+i][bc+j]==val) return false;
    return true;
}
bool solveSudoku(vector<vector<int>>& bd){
    for(int i=0;i<9;i++) for(int j=0;j<9;j++){
        if(bd[i][j]==0){
            for(int val=1;val<=9;val++){
                if(isValidSudoku(bd,i,j,val)){
                    bd[i][j]=val;
                    if(solveSudoku(bd)) return true;
                    bd[i][j]=0;
                }
            }
            return false;
        }
    }
    return true;
}
```

---