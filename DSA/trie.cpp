struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];

    // This will keep track of number of strings that are
    // stored in the Trie from root node to any Trie node.
    int wordCount = 0;
};


void insert_key(TrieNode* root, string& key)
{
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (auto c : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->childNode[c - 'a'] == NULL) {

            // If node for current character does not exist
            // then make a new node
            TrieNode* newNode = new TrieNode();

            // Keep the reference for the newly created
            // node.
            currentNode->childNode[c - 'a'] = newNode;
        }

        // Now, move the current node pointer to the newly
        // created node.
        currentNode = currentNode->childNode[c - 'a'];
    }

    // Increment the wordEndCount for the last currentNode
    // pointer this implies that there is a string ending at
    // currentNode.
    currentNode->wordCount++;
}


bool isPrefixExist(TrieNode* root, string& key)
{
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (auto c : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->childNode[c - 'a'] == NULL) {
          
            // Given word as a prefix does not exist in Trie
            return false;
        }

        // Move the currentNode pointer to the already 
        // existing node for current character.
        currentNode = currentNode->childNode[c - 'a'];
    }
 
      // Prefix exist in the Trie
    return true;
}


bool search_key(TrieNode* root, string& key)
{
    // Initialize the currentNode pointer
    // with the root node
    TrieNode* currentNode = root;

    // Iterate across the length of the string
    for (auto c : key) {

        // Check if the node exist for the current
        // character in the Trie.
        if (currentNode->childNode[c - 'a'] == NULL) {
          
            // Given word does not exist in Trie
            return false;
        }

        // Move the currentNode pointer to the already 
        // existing node for current character.
        currentNode = currentNode->childNode[c - 'a'];
    }
 
    return (currentNode->wordCount > 0);
}


bool delete_key(TrieNode* root, string& word)
{
    TrieNode* currentNode = root;
    TrieNode* lastBranchNode = NULL;
    char lastBranchChar = 'a';

    for (auto c : word) {
        if (currentNode->childNode[c - 'a'] == NULL) {
            return false;
        }
        else {
            int count = 0;
            for (int i = 0; i < 26; i++) {
                if (currentNode->childNode[i] != NULL)
                    count++;
            }

            if (count > 1) {
                lastBranchNode = currentNode;
                lastBranchChar = c;
            }
            currentNode = currentNode->childNode[c - 'a'];
        }
    }

    int count = 0;
    for (int i = 0; i < 26; i++) {
        if (currentNode->childNode[i] != NULL)
            count++;
    }

    // Case 1: The deleted word is a prefix of other words
    // in Trie.
    if (count > 0) {
        currentNode->wordCount--;
        return true;
    }

    // Case 2: The deleted word shares a common prefix with
    // other words in Trie.
    if (lastBranchNode != NULL) {
        lastBranchNode->childNode[lastBranchChar] = NULL;
        return true;
    }
    // Case 3: The deleted word does not share any common
    // prefix with other words in Trie.
    else {
        root->childNode[word[0]] = NULL;
        return true;
    }
}



