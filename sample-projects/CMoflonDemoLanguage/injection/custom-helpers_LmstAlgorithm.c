LIST(list_tree_entries);

const char* LMST_ERROR_PREFIX = "ERROR[topologycontrol-lmst]: ";

/**
 * Initializes the auxiliary data structures required by LMST
 */
static bool lmstAlgorithm_init(LMSTALGORITHM_T* this) {
  /*
   * Init tree
   */
  TREE_T* tree = (TREE_T*) malloc(sizeof(TREE_T));
  if (tree == NULL) {
    printf("%sCould not allocate memory for tree\n", LMST_ERROR_PREFIX);
    return false;
  }
  tree->algo = this;
  list_init(list_tree_entries);

  /*
   * Add TreeEntries for all incident nodes node1/node2 of links in the neighborhoo
   */
  LINK_T* item_neighbor;
  for (item_neighbor = list_head(component_neighbordiscovery_neighbors());
       item_neighbor != NULL;
       item_neighbor = list_item_next(item_neighbor)) {
    TREEENTRY_T *item_node;

    unsigned char node_index;
    for (node_index = 0; node_index < 2; ++node_index) {
      NODE_T *neighbor_node = (node_index == 0) ? item_neighbor->node1 : item_neighbor->node2;

      bool found = false;
      // After this loop, found == true iff there is a TreeEntry for neighbor_node
      for (item_node = list_head(list_tree_entries);
           item_node != NULL && !found;
           item_node = list_item_next(item_node)) {
        found = networkaddr_equal(neighbor_node, item_node->node);
      }

      if (!found) {
        item_node=(TREEENTRY_T*)malloc(sizeof(TREEENTRY_T));
        if (item_node == NULL) {
          printf("%scannot allocate memory for tree entry num. %d\n", LMST_ERROR_PREFIX, list_length(list_tree_entries));
          return false;
        } else {
          item_node->node = neighbor_node;
          item_node->parent = NULL;
          item_node->tree = tree;
          // The owner node of the local view is in the tree from the beginning, all other nodes are not.
          item_node->isInTree = networkaddr_equal(networkaddr_node_addr(), neighbor_node);

          list_add(list_tree_entries, item_node);
        }
      }
    }
  }
  const unsigned int treeSize = sizeof(TREE_T) + list_length(list_tree_entries) * sizeof(TREEENTRY_T);
  printf("[topologycontrol-lmst] void*/TREE_T/TREEENTRY_T/tree object size: %d/%d/%d/%d Byte\n", sizeof(void *), sizeof(TREE_T), sizeof(TREEENTRY_T), treeSize);
  tree->entries = list_tree_entries;
  this->tree = tree;
  return true;
}

/**
 * Clears the auxiliary data structures required by LMST
 */
static void lmstAlgorithm_cleanup(LMSTALGORITHM_T* this) {

	// Free TreeEntries
	list_t entryList = this->tree->entries;
	while(list_length(entryList) > 0) {
		free(list_pop(entryList));
	}

	// Free Tree
	free(this->tree);
	this->tree = NULL;

}

static NODE_T* lmstAlgorithm_getNode(LMSTALGORITHM_T* _this) {
	return _this->node;
}

static TREE_T* lmstAlgorithm_getTree(LMSTALGORITHM_T* _this) {
	return _this->tree;
}

static list_t tree_getEntries(TREE_T* _this) {
	return _this->entries;
}

static bool tree_isEntries(void* candidate, void* _this) {
	return true;
}

static LINK_T* tree_getBestCandidate(TREE_T* _this) {
  return _this->bestCandidate;
}

static void tree_setBestCandidate(TREE_T* _this, LINK_T* bestCandidate) {
  _this->bestCandidate = bestCandidate;
}

static TREE_T* treeEntry_getTree(TREEENTRY_T* _this) {
	return _this->tree;
}

static NODE_T* treeEntry_getNode(TREEENTRY_T* _this) {
	return _this->node;
}
static void treeEntry_setNode(TREEENTRY_T* _this, NODE_T* value) {
	_this->node = value;
}

static LINK_T* treeEntry_getParent(TREEENTRY_T* _this) {
	return _this->parent;
}

static void treeEntry_setParent(TREEENTRY_T* _this, LINK_T* value) {
	_this->parent = value;
}

static bool treeEntry_isIsInTree(TREEENTRY_T* _this) {
	return _this->isInTree;
}

static void treeEntry_setIsInTree(TREEENTRY_T* _this, EBoolean value) {
	_this->isInTree = value;
}

static bool treeEntry_equals(TREEENTRY_T* _this, TREEENTRY_T* other) {
	bool result = true;
	result &= node_equals(_this->node, other->node);
	result &= link_equals(_this->parent, other->parent);
	return result;
}
