// Required because generated code is replicated to all algorithms (but will not influence the size of the generated image)
static EBoolean lStarKtcAlgorithm_evaluateHopcountConstraint(EInt hopCount1,
		EInt hopCount2, EInt hopCount3, EDouble stretchFactor);


/**
 * Returns whether the given hop counts fulfill the l*-kTC predicate
 */
static EBoolean lStarKtcAlgorithm_evaluateHopcountConstraint(EInt hopCount1,
		EInt hopCount2, EInt hopCount3, EDouble stretchFactor) {
	if (min(hopCount1, min(hopCount2, hopCount3)) < 0)
		return false;
	bool result = true;
	result &= (!(hopCount1 == hopCount2) || true);
	result &= (!(hopCount1 != hopCount2) || ((hopCount3 + 1) * 1.0 / max(hopCount1, hopCount2) < stretchFactor));
	return result;
}

static EInt node_getHopcount(NODE_T* _this) {
	if (networkaddr_equal(networkaddr_node_addr(), _this))
		return my_hopcount;

	hopcount_t *item;
	for (item = list_head(list_hopcount); item != NULL;
			item = list_item_next(item)) {
		if (networkaddr_equal(item->address, _this)) {
			return item->hopcount;
		}
	}

	return -1;
}

static NODE_T* lStarKtcAlgorithm_getNode(LSTARKTCALGORITHM_T* _this) {
	return _this->node;
}

static EDouble lStarKtcAlgorithm_getK(LSTARKTCALGORITHM_T* _this) {
	return _this->k;
}

static EDouble lStarKtcAlgorithm_getStretchFactor(LSTARKTCALGORITHM_T* _this) {
	return _this->stretchFactor;
}
