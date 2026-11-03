
#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Node structure
struct Node {
    char ch;
    int freq;
    Node *left, *right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Min-priority queue comparator
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Helper 1: Calculate character frequencies
unordered_map<char, int> getFrequency(string text) {
    unordered_map<char, int> freq;

    for (char ch : text)
        freq[ch]++;

    return freq;
}

// Helper 2: Build Huffman tree
Node* buildHuffmanTree(unordered_map<char, int>& freq) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto p : freq)
        pq.push(new Node(p.first, p.second));

    while (pq.size() > 1) {
        Node* left = pq.top();
        pq.pop();

        Node* right = pq.top();
        pq.pop();

        Node* parent = new Node(
            '\0', left->freq + right->freq
        );

        parent->left = left;
        parent->right = right;

        pq.push(parent);
    }

    return pq.top();
}

// Helper 3: Generate Huffman codes
void generateCodes(Node* root, string code,
                   unordered_map<char, string>& codes) {
    if (root == nullptr)
        return;

    if (root->left == nullptr && root->right == nullptr) {
         codes[root->ch] = code;

      if (code == "")
        codes[root->ch] = "0";
        return;
    }

    generateCodes(root->left, code + "0", codes);
    generateCodes(root->right, code + "1", codes);
}

// Helper 4: Print Huffman codes
void printCodes(unordered_map<char, string>& codes) {
    cout << "\nHuffman Codes:\n";

    for (auto p : codes) {
        if (p.first == ' ')
            cout << "[space] : " << p.second << endl;
        else
            cout << p.first << " : " << p.second << endl;
    }
}

// Helper 5: Encode input string
string encode(string text, unordered_map<char, string>& codes) {
    string encoded = "";

    for (char ch : text)
        encoded += codes.at(ch);

    return encoded;
}

// Main function
int main() {
    string text;

    cout << "Enter the string: ";
    getline(cin, text);

    if (text.empty()) {
        cout << "String cannot be empty." << endl;
        return 0;
    }

    // Calculate frequencies
    unordered_map<char, int> freq = getFrequency(text);

    cout << "\nCharacter Frequencies:\n";
    for (auto p : freq) {
        if (p.first == ' ')
            cout << "[space] : " << p.second << endl;
        else
            cout << p.first << " : " << p.second << endl;
    }

    // Build tree and generate codes
    Node* root = buildHuffmanTree(freq);

    unordered_map<char, string> codes;
    generateCodes(root, "", codes);

    printCodes(codes);

    // Encode original string
    string encoded = encode(text, codes);

    cout << "\nOriginal String: " << text << endl;
    cout << "Encoded String: " << encoded << endl;
    cout << "Original Size: " << text.length() * 8 << " bits" << endl;
    cout << "Encoded Size: " << encoded.length() << " bits" << endl;

    return 0;
}

