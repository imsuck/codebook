struct Node {
    Node *child[26], *go[26], *link;
    int sum, topo;
    vector<int> query;

    Node() {
        for (int i = 0; i < 26; i++) {
            child[i] = go[i] = 0;
        }
        link = 0;
        sum = topo = 0;
    }
};

struct aho_corasick{
    Node *root;
    vector<Node*> v;

    aho_corasick() {
        root = new Node();
        root->link = root;
        for (int i = 0; i < 26; i++) {
            root->child[i] = new Node();
        }
    }

    void add_string(string &s, int id) {
        Node *p = root;
        for (int i = 0; i < (int)s.size(); i++) {
            int c = s[i] - 'a';
            if (p->child[c] == 0) {
                p->child[c] = new Node();
            }
            p = p->child[c];
        }
        p->query.pb(id);
    }

    void bfs() {
        queue<Node*> q;
        q.push(root);
        while (q.size()) {
            Node* u = q.front();
            v.push_back(u);
            q.pop();
            for (int c = 0; c < 26; c++) {
                if (u->child[c]) {
                    u->child[c]->link = u->link->go[c];
                    if (u == root) {
                        u->child[c]->link = root;
                    }
                    u->child[c]->link->topo++;
                    u->go[c] = u->child[c];
                    q.push(u->child[c]);
                }
                else {
                    u->go[c] = u->link->go[c];
                }
            }
        }
    }

    void compute() {
        queue<Node*> q;
        for (auto x : v) {
            if (x->topo == 0) {
                q.push(x);
            }
        }
        while (q.size()) {
            Node* u = q.front();
            for (int x : u->query) {
                ans[x] = u->sum;
            }
            q.pop();
            u->link->topo--;
            u->link->sum += u->sum;
            if (u->link->topo == 0) {
                q.push(u->link);
            }
        }
    }
};
aho_corasick aho;