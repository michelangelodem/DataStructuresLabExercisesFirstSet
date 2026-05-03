#include "RecreateComparison.h"

// Forward declaration for hash function
unsigned int intHashFunction(const IntHashTable* ht, int key);

// Θελουμε να δουμε μονο την ταχυτητα που μας προσφερει η βελτιωση.
// Οχι αν ειναι λειτουργικος ο κωδικας, αυτο θα το δουμε στα τεστ του LabEx5-0 και LabEx5-1. 
// Εδω απλα συγκρινουμε τις εκτελεσεις των δυο εκδοσεων για μεγαλο μεγεθος δεντρου.
// Οποτε για ευκολια θα εργαστουμε μονο με την δημιουργια δεντρων απο preorder + inorder.

void printArray(const int* array, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void) {
    printf("=============================================================================\n");
    printf("  Exercise 5: Binary Tree Reconstruction - Optimized vs Unoptimized\n");
    printf("=============================================================================\n\n");
    
    int length = 524287;  // Use 524288 nodes (2^19 -1) for testing
    
    int* arr = createSortedArray(length);
    int* preorder = (int*)malloc(sizeof(int) * length);
    int* inorder = (int*)malloc(sizeof(int) * length);
    if (arr == NULL || preorder == NULL || inorder == NULL) {
        fprintf(stderr, "Memory allocation failed.\n");
        free(arr);
        free(preorder);
        free(inorder);
        return 1;
    }

    Node* root = createTree(length, 0, arr);
    if (root == NULL) {
        fprintf(stderr, "Failed to create the initial tree.\n");
        free(arr);
        free(preorder);
        free(inorder);
        return 1;
    }

    int idx = 0;
    generatePreOrderArray(root, preorder, &idx);
    idx = 0;
    generateInOrderArray(root, inorder, &idx);

    free(arr);

    printf("Tree Size: %d nodes (Complete Binary Tree)\n", length);
    printf("--- Preorder + Inorder Reconstruction ---\n");
    
    // Unoptimized version
    printf("Unoptimized (O(n^2) - Linear Search):\n");
    int preIndex_unopt = 0;
    clock_t begin_unopt = clock();
    Node* root_unopt = buildTreeFromPreInUnoptimized(preorder, inorder, 0, length - 1, &preIndex_unopt);
    clock_t end_unopt = clock();
    double time_unopt = (double)(end_unopt - begin_unopt) / CLOCKS_PER_SEC;
    int nodes_unopt = countNodes(root_unopt);
    
    printf("  Nodes reconstructed: %d / %d\n", nodes_unopt, length);
    printf("  Execution time (reconstruction only): %.9f seconds\n", time_unopt);

    printf("\nOptimized (O(n) - Hash Table):\n");
    int preIndex_opt = 0;
    
    IntHashTable* ht = (IntHashTable*)malloc(sizeof(IntHashTable));
    if (ht == NULL) {
        fprintf(stderr, "Memory allocation failed for hash table.\n");
        return 1;
    }
    
    // Use larger hash table to reduce collisions (next prime after 2*length)
    int hash_table_size = 1048573;  // Prime number larger than 2*524287
    
    clock_t begin_opt_total = clock();
    initIntHashTable(ht, hash_table_size);
    
    // Count collisions during hash table build
    int total_collisions = 0;
    int max_chain_length = 0;
    for (int i = 0; i < length; i++) {
        unsigned int index = intHashFunction(ht, inorder[i]);
        int chain_length = 0;
        IntHashNode* current = ht->table[index];
        while (current != NULL) {
            chain_length++;
            current = current->next;
        }
        if (chain_length > 0) total_collisions++;
        if (chain_length > max_chain_length) max_chain_length = chain_length;
        
        insertIntHashNode(ht, inorder[i], i);
    }
    clock_t end_hashtable = clock();
    double time_hashtable = (double)(end_hashtable - begin_opt_total) / CLOCKS_PER_SEC;
    
    printf("  Hash table stats: %d buckets, %d collisions, max chain length: %d\n", ht->size, total_collisions, max_chain_length);
    
    clock_t begin_opt = clock();
    Node* root_opt = buildTreeFromPreInOptimized(preorder, inorder, 0, length - 1, ht, &preIndex_opt);
    clock_t end_opt = clock();
    double time_opt = (double)(end_opt - begin_opt) / CLOCKS_PER_SEC;
    double time_opt_total = (double)(end_opt - begin_opt_total) / CLOCKS_PER_SEC;
    int nodes_opt = countNodes(root_opt);
    
    printf("  Hash table build time:        %.9f seconds\n", time_hashtable);
    printf("  Reconstruction time only:     %.9f seconds\n", time_opt);
    printf("  Total time (with hash table): %.9f seconds\n", time_opt_total);
    printf("  Nodes reconstructed: %d / %d\n", nodes_opt, length);

    // Timing comparison
    printf("\n--- Timing Comparison ---\n");
    printf("Unoptimized time:                   %.9f seconds\n", time_unopt);
    printf("Optimized reconstruction only:      %.9f seconds\n", time_opt);
    printf("Optimized total (incl. hash table): %.9f seconds\n", time_opt_total);
    if (time_unopt > 0) {
        printf("Speedup (reconstruction only):       %.2f times\n", time_unopt / time_opt);
    }
    if (time_opt_total > 0) {
        printf("Speedup (total with hash table):    %.2f times\n", time_unopt / time_opt_total);
    }

    // Verify both produce the same structure
    printf("\n--- Verification ---\n");
    if (root_unopt != NULL && root_opt != NULL && root_unopt->data == root_opt->data) {
        printf("Pass: Both versions reconstruct the same tree structure.\n");
    } else {
        printf("Fail: Tree structures differ or are NULL!\n");
    }
    
    printf("Unoptimized: %d nodes reconstructed (%d%%)\n", nodes_unopt, (int)(100.0 * nodes_unopt / length));
    printf("Optimized:   %d nodes reconstructed (%d%%)\n", nodes_opt, (int)(100.0 * nodes_opt / length));

    // Cleanup
    freeTree(root_unopt);
    freeTree(root_opt);
    freeIntHashTable(ht);
    free(preorder);
    free(inorder);

    return 0;
}
