LIST(list_tree_entries);

/**
 * Initializes the auxiliary data structures required by LMST
 */
static bool lmstAlgorithm_init(LMSTALGORITHM_T* this) {
	TREE_T* tree = (TREE_T*) malloc(sizeof(TREE_T));
	if (tree == NULL) {
		printf("ERROR[topologycontrol][LMST]: Could not allocate memory for tree\n");
		return false;
	}
	tree->algo = this;
	list_init(list_tree_entries);

	// add all nodes to list
	LINK_T* item_neighbor;
	for (item_neighbor = list_head(component_neighbordiscovery_neighbors());
			item_neighbor != NULL;
			item_neighbor = list_item_next(item_neighbor)) {
		TREEENTRY_T *item_node;
		bool found = false;

		// check for node1
		for (item_node = list_head(list_tree_entries); item_node != NULL;
				item_node = list_item_next(item_node)) {
			if (networkaddr_equal(item_neighbor->node1, item_node->node)) {
				found = true;
				break;
			}
		}
		if (!found) {
			item_node=(TREEENTRY_T*)malloc(sizeof(TREEENTRY_T));
			if (item_node == NULL) {
				printf("ERROR[topologycontrol][LMST]: node list is full (%s:%d)\n", __FILE__, __LINE__);
				return false;
			} else {
				item_node->node = item_neighbor->node1;
				item_node->parent = NULL;
				item_node->tree = tree;
				if (networkaddr_equal(networkaddr_node_addr(),
						item_neighbor->node1))
					item_node->isInTree = true;
				else
					item_node->isInTree = false;
				list_add(list_tree_entries, item_node);
			}
		}

		// check for node2
		found = false;
		for (item_node = list_head(list_tree_entries); item_node != NULL;
				item_node = list_item_next(item_node)) {
			if (networkaddr_equal(item_neighbor->node2, item_node->node)) {
				found = true;
				break;
			}
		}
		if (!found) {
			item_node=(TREEENTRY_T*)malloc(sizeof(TREEENTRY_T));
			if (item_node == NULL) {
				printf("ERROR[topologycontrol][LMST]: node list is full (%s:%d)\n", __FILE__, __LINE__);
				return false;
			} else {
				item_node->node = item_neighbor->node2;
				item_node->parent = NULL;
				item_node->tree = tree;
				if (networkaddr_equal(networkaddr_node_addr(),
						item_neighbor->node2))
					item_node->isInTree = true;
				else
					item_node->isInTree = false;
				list_add(list_tree_entries, item_node);
			}
		}
	}
	tree->entries = list_tree_entries;
	this->tree = tree;
	return true;
}

/**
 * Clears the auxiliary data structures required by LMST
 */
static void lmstAlgorithm_cleanup(LMSTALGORITHM_T* this) {
	list_t entryList = this->tree->entries;
	while(list_length(entryList) > 0) {
		free(list_pop(entryList));
	}
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
