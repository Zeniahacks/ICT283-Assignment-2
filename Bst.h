#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>

/// @class Node
/// @brief Template node class for Binary Search Tree
template <class T>
class Node {
public:
	T* data;  ///< Store pointer to the data element.
	Node<T>* left;  ///< Pointer to the left child node.
	Node<T>* right;  ///< Pointer to the right child node.

	/**
	 * @brief Constructs a Node, taking ownership of the provided data pointer.
	 * @param value The pointer to the data element.
	 */
	Node(T* value) : data(value), left(nullptr), right(nullptr) {}

	/**
	 * @brief Destructor. Deletes the owned data element.
	 */
	~Node() { delete data; }
};

/// @class Bst
/// @brief Template Binary Search Tree with function pointers for traversal
template <class T>
class Bst {
private:
	Node<T>* root; ///< Pointer to the root node of the tree.

	// Private recursive helper methods
	/**
	 * @brief Recursively inserts a new node containing the value.
	 * @param node The current node being examined.
	 * @param value The pointer to the data value to insert.
	 * @return Node<T>* The updated root of the subtree.
	 */
	Node<T>* insertRec(Node<T>* node, T* value);

	/**
	 * @brief Recursively searches for a node containing the value.
	 * @param node The current node being examined.
	 * @param value The pointer to the data value to search for.
	 * @return Node<T>* The node containing the value, or nullptr if not found.
	 */
	Node<T>* searchRec(Node<T>* node, T* value) const;

	// Traversal methods with function pointers
	/**
	 * @brief Performs recursive in-order traversal and applies the visit function.
	 * @param node The current node being examined.
	 * @param visit The function pointer to apply to each node's data.
	 */
	void inOrderRec(Node<T>* node, void (*visit)(const T*)) const;

	/**
	 * @brief Performs recursive pre-order traversal and applies the visit function.
	 * @param node The current node being examined.
	 * @param visit The function pointer to apply to each node's data.
	 */
	void preOrderRec(Node<T>* node, void (*visit)(const T*)) const;

	/**
	 * @brief Performs recursive post-order traversal and applies the visit function.
	 * @param node The current node being examined.
	 * @param visit The function pointer to apply to each node's data.
	 */
	void postOrderRec(Node<T>* node, void (*visit)(const T*)) const;

	// Traversal methods that collect data
	/**
	 * @brief Performs recursive in-order traversal, applying the visit function with a context pointer.
	 *
	 * This is typically used for collection logic where data is stored in the context struct.
	 *
	 * @param node The current node being examined.
	 * @param visit The function pointer to apply (accepts data pointer and context pointer).
	 * @param context Opaque pointer to the context/collector struct.
	 */
	void inOrderRec(Node<T>* node, void (*visit)(const T*, void*), void* context) const;

	/**
	 * @brief Recursively deletes all nodes in the tree, cleaning up memory.
	 * @param node The current node to delete (and its children).
	 */
	void deleteTreeRec(Node<T>* node);

	/**
	 * @brief Recursively checks the Binary Search Tree invariant.
	 * @param node The current node being checked.
	 * @param min A pointer to the minimum allowed value for the subtree.
	 * @param max A pointer to the maximum allowed value for the subtree.
	 * @return bool True if the invariant holds, false otherwise.
	 */
	bool checkInvariantRec(Node<T>* node, const T* min, const T* max) const;

	/**
	 * @brief Recursively creates a deep copy of the tree structure.
	 * @param node The root of the tree/subtree to copy.
	 * @return Node<T>* The root of the newly copied tree/subtree.
	 */
	Node<T>* copyTreeRec(Node<T>* node);

public:
	/**
	 * @brief Default constructor. Initializes an empty tree.
	 */
	Bst();

	/**
	 * @brief Destructor. Cleans up the entire tree structure.
	 */
	~Bst();

	/**
	 * @brief Copy constructor. Performs a deep copy of the tree structure.
	 * @param other The Bst object to copy from.
	 */
	Bst(const Bst<T>& other);

	/**
	 * @brief Assignment operator. Handles self-assignment and performs a deep copy assignment.
	 * @param other The Bst object to assign from.
	 * @return Bst<T>& Reference to the updated object.
	 */
	Bst<T>& operator=(const Bst<T>& other);

	/**
	 * @brief Inserts a data value into the BST. Takes ownership of the pointer.
	 * @param value The pointer to the data value to insert.
	 */
	void insert(T* value);

	/**
	 * @brief Searches for a data value in the BST.
	 * @param value The pointer to the data value (used for comparison key).
	 * @return Node<T>* The node containing the value, or nullptr if not found.
	 */
	Node<T>* search(T* value) const;

	// Traversal methods with function pointers
	/**
	 * @brief Initiates an in-order traversal, applying the visit function to each node.
	 * @param visit The function pointer to apply to each node's data.
	 */
	void inOrder(void (*visit)(const T*)) const;

	/**
	 * @brief Initiates a pre-order traversal, applying the visit function to each node.
	 * @param visit The function pointer to apply to each node's data.
	 */
	void preOrder(void (*visit)(const T*)) const;

	/**
	 * @brief Initiates a post-order traversal, applying the visit function to each node.
	 * @param visit The function pointer to apply to each node's data.
	 */
	void postOrder(void (*visit)(const T*)) const;

	// Traversal methods that collect data into context
	/**
	 * @brief Initiates an in-order traversal that uses a context pointer for collection.
	 * @param visit The function pointer to apply (accepts data pointer and context pointer).
	 * @param context Opaque pointer to the context/collector struct.
	 */
	void inOrder(void (*visit)(const T*, void*), void* context) const;

	// Simple traversals (for backward compatibility)
	/**
	 * @brief Simple in-order traversal that prints the data (requires operator<< for T).
	 */
	void inOrder() const;

	/**
	 * @brief Simple pre-order traversal that prints the data (requires operator<< for T).
	 */
	void preOrder() const;

	/**
	 * @brief Simple post-order traversal that prints the data (requires operator<< for T).
	 */
	void postOrder() const;

	/**
	 * @brief Checks if the tree satisfies the Binary Search Tree invariant.
	 * @return bool True if the invariant holds, false otherwise.
	 */
	bool checkInvariant() const;

	/**
	 * @brief Checks if the tree is empty.
	 * @return bool True if the root is null.
	 */
	bool isEmpty() const;

	/**
	 * @brief Gets the total number of nodes in the tree.
	 * @return int The size of the tree.
	 */
	int size() const;

	/**
	 * @brief Gets the height of the tree (number of edges on the longest path from the root to a leaf).
	 * @return int The height of the tree, or -1 if the tree is empty.
	 */
	int height() const;

private:
	/**
	 * @brief Recursively calculates the size of the subtree rooted at node.
	 * @param node The root of the subtree.
	 * @return int The size of the subtree.
	 */
	int sizeRec(Node<T>* node) const;

	/**
	 * @brief Recursively calculates the height of the subtree rooted at node.
	 * @param node The root of the subtree.
	 * @return int The height of the subtree.
	 */
	int heightRec(Node<T>* node) const;
};

// Template implementation

/**
 * @brief Default constructor implementation.
 */
template <class T>
Bst<T>::Bst() : root(nullptr) {}

/**
 * @brief Destructor implementation. Calls recursive delete function.
 */
template <class T>
Bst<T>::~Bst() {
	deleteTreeRec(root);
}

/**
 * @brief Copy constructor implementation. Calls recursive copy function.
 * @param other The Bst object to copy from.
 */
template <class T>
Bst<T>::Bst(const Bst<T>& other) : root(nullptr) {
	root = copyTreeRec(other.root);
}

/**
 * @brief Assignment operator implementation. Handles cleanup and deep copy.
 * @param other The Bst object to assign from.
 * @return Bst<T>& Reference to the updated object.
 */
template <class T>
Bst<T>& Bst<T>::operator=(const Bst<T>& other) {
	if (this != &other) {
		deleteTreeRec(root);
		root = copyTreeRec(other.root);
	}
	return *this;
}

/**
 * @brief Recursively creates a deep copy of the tree structure.
 * @param node The root of the tree/subtree to copy.
 * @return Node<T>* The root of the newly copied tree/subtree.
 */
template <class T>
Node<T>* Bst<T>::copyTreeRec(Node<T>* node) {
	if (node == nullptr) return nullptr;

	// Create new node with copied data
	T* newData = new T(*(node->data));  // Copy the data
	Node<T>* newNode = new Node<T>(newData);
	newNode->left = copyTreeRec(node->left);
	newNode->right = copyTreeRec(node->right);
	return newNode;
}

/**
 * @brief Recursively deletes all nodes in the tree, cleaning up memory.
 * @param node The current node to delete (and its children).
 */
template <class T>
void Bst<T>::deleteTreeRec(Node<T>* node) {
	if (node != nullptr) {
		deleteTreeRec(node->left);
		deleteTreeRec(node->right);
		delete node;
	}
}

/**
 * @brief Recursively inserts a new node containing the value.
 * @param node The current node being examined.
 * @param value The pointer to the data value to insert.
 * @return Node<T>* The updated root of the subtree.
 */
template <class T>
Node<T>* Bst<T>::insertRec(Node<T>* node, T* value) {
	if (node == nullptr) {
		return new Node<T>(value);
	}

	if (*value < *(node->data)) {  // Dereference for comparison
		node->left = insertRec(node->left, value);
	} else if (*value > *(node->data)) {  // Dereference for comparison
		node->right = insertRec(node->right, value);
	}
	return node;
}

/**
 * @brief Inserts a data value into the BST. Takes ownership of the pointer.
 * @param value The pointer to the data value to insert.
 */
template <class T>
void Bst<T>::insert(T* value) {
	root = insertRec(root, value);
}

/**
 * @brief Recursively searches for a node containing the value.
 * @param node The current node being examined.
 * @param value The pointer to the data value to search for.
 * @return Node<T>* The node containing the value, or nullptr if not found.
 */
template <class T>
Node<T>* Bst<T>::searchRec(Node<T>* node, T* value) const {
	if (node == nullptr || *(node->data) == *value) {
		return node;
	}

	if (*value < *(node->data)) {
		return searchRec(node->left, value);
	} else {
		return searchRec(node->right, value);
	}
}

/**
 * @brief Searches for a data value in the BST.
 * @param value The pointer to the data value (used for comparison key).
 * @return Node<T>* The node containing the value, or nullptr if not found.
 */
template <class T>
Node<T>* Bst<T>::search(T* value) const {
	return searchRec(root, value);
}

// Traversal with simple function pointer
/**
 * @brief Performs recursive in-order traversal and applies the visit function.
 * @param node The current node being examined.
 * @param visit The function pointer to apply to each node's data.
 */
template <class T>
void Bst<T>::inOrderRec(Node<T>* node, void (*visit)(const T*)) const {
	if (node != nullptr) {
		inOrderRec(node->left, visit);
		visit(node->data);  // Pass pointer
		inOrderRec(node->right, visit);
	}
}

/**
 * @brief Initiates an in-order traversal, applying the visit function to each node.
 * @param visit The function pointer to apply to each node's data.
 */
template <class T>
void Bst<T>::inOrder(void (*visit)(const T*)) const {
	inOrderRec(root, visit);
}

/**
 * @brief Performs recursive pre-order traversal and applies the visit function.
 * @param node The current node being examined.
 * @param visit The function pointer to apply to each node's data.
 */
template <class T>
void Bst<T>::preOrderRec(Node<T>* node, void (*visit)(const T*)) const {
	if (node != nullptr) {
		visit(node->data);  // Pass pointer
		preOrderRec(node->left, visit);
		preOrderRec(node->right, visit);
	}
}

/**
 * @brief Initiates a pre-order traversal, applying the visit function to each node.
 * @param visit The function pointer to apply to each node's data.
 */
template <class T>
void Bst<T>::preOrder(void (*visit)(const T*)) const {
	preOrderRec(root, visit);
}

/**
 * @brief Performs recursive post-order traversal and applies the visit function.
 * @param node The current node being examined.
 * @param visit The function pointer to apply to each node's data.
 */
template <class T>
void Bst<T>::postOrderRec(Node<T>* node, void (*visit)(const T*)) const {
	if (node != nullptr) {
		postOrderRec(node->left, visit);
		postOrderRec(node->right, visit);
		visit(node->data);  // Pass pointer
	}
}

/**
 * @brief Initiates a post-order traversal, applying the visit function to each node.
 * @param visit The function pointer to apply to each node's data.
 */
template <class T>
void Bst<T>::postOrder(void (*visit)(const T*)) const {
	postOrderRec(root, visit);
}

// Traversal with context for data collection
/**
 * @brief Performs recursive in-order traversal, applying the visit function with a context pointer.
 * @param node The current node being examined.
 * @param visit The function pointer to apply (accepts data pointer and context pointer).
 * @param context Opaque pointer to the context/collector struct.
 */
template <class T>
void Bst<T>::inOrderRec(Node<T>* node, void (*visit)(const T*, void*), void* context) const {
	if (node != nullptr) {
		inOrderRec(node->left, visit, context);
		visit(node->data, context);  // Pass pointer
		inOrderRec(node->right, visit, context);
	}
}

/**
 * @brief Initiates an in-order traversal that uses a context pointer for collection.
 * @param visit The function pointer to apply (accepts data pointer and context pointer).
 * @param context Opaque pointer to the context/collector struct.
 */
template <class T>
void Bst<T>::inOrder(void (*visit)(const T*, void*), void* context) const {
	inOrderRec(root, visit, context);
}

// Simple traversals (backward compatibility)
/**
 * @brief Simple in-order traversal that prints the data (requires operator<< for T).
 */
template <class T>
void Bst<T>::inOrder() const {
	inOrder([](const T* value) {
		std::cout << *value << " ";
	});
}

/**
 * @brief Simple pre-order traversal that prints the data (requires operator<< for T).
 */
template <class T>
void Bst<T>::preOrder() const {
	preOrder([](const T* value) {
		std::cout << *value << " ";
	});
}

/**
 * @brief Simple post-order traversal that prints the data (requires operator<< for T).
 */
template <class T>
void Bst<T>::postOrder() const {
	postOrder([](const T* value) {
		std::cout << *value << " ";
	});
}

/**
 * @brief Recursively checks the Binary Search Tree invariant.
 * @param node The current node being checked.
 * @param min A pointer to the minimum allowed value for the subtree.
 * @param max A pointer to the maximum allowed value for the subtree.
 * @return bool True if the invariant holds, false otherwise.
 */
template <class T>
bool Bst<T>::checkInvariantRec(Node<T>* node, const T* min, const T* max) const {
	if (node == nullptr) return true;

	if (!(*(node->data) > *min) || !(*(node->data) < *max)) {
		return false;
	}

	return checkInvariantRec(node->left, min, node->data) &&
			checkInvariantRec(node->right, node->data, max);
}

/**
 * @brief Checks if the tree satisfies the Binary Search Tree invariant.
 * @return bool True if the invariant holds, false otherwise.
 */
template <class T>
bool Bst<T>::checkInvariant() const {
	// For pointer version, we need valid min/max pointers
	// This might need adjustment based on your specific type T
	T defaultMin;
	T defaultMax;
	return checkInvariantRec(root, &defaultMin, &defaultMax);
}

/**
 * @brief Checks if the tree is empty.
 * @return bool True if the root is null.
 */
template <class T>
bool Bst<T>::isEmpty() const {
	return root == nullptr;
}

/**
 * @brief Recursively calculates the size of the subtree rooted at node.
 * @param node The root of the subtree.
 * @return int The size of the subtree.
 */
template <class T>
int Bst<T>::sizeRec(Node<T>* node) const {
	if (node == nullptr) return 0;
	return 1 + sizeRec(node->left) + sizeRec(node->right);
}

/**
 * @brief Gets the total number of nodes in the tree.
 * @return int The size of the tree.
 */
template <class T>
int Bst<T>::size() const {
	return sizeRec(root);
}

/**
 * @brief Recursively calculates the height of the subtree rooted at node.
 * @param node The root of the subtree.
 * @return int The height of the subtree.
 */
template <class T>
int Bst<T>::heightRec(Node<T>* node) const {
	if (node == nullptr) return -1;
	return 1 + std::max(heightRec(node->left), heightRec(node->right));
}

/**
 * @brief Gets the height of the tree.
 * @return int The height of the tree, or -1 if the tree is empty.
 */
template <class T>
int Bst<T>::height() const {
	return heightRec(root);
}

#endif // BST_H
