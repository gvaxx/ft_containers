#include <list>
#include <iostream>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>

template <class T, class Compare>
class Tree
{
public:
	ft::TreeNode<T> *__end;
	ft::TreeNode<T> *__start;
	ft::TreeNode<T> *__back;
	Compare		__comp;
	Tree()
	{
		__end = __new_node();
	}

	Tree(const Compare& comp = Compare())
	{
		__comp = comp;
		__end = __new_node();
	}

	~Tree()
	{
		__start = NULL;
		__back = NULL;
		delete __end;
	}

	ft::TreeNode<T> *__root()
	{
		return __end->left;
	}

	ft::TreeNode<T> *__root() const
	{
		return __end->left;
	}
private:
	bool is_left_child(ft::TreeNode<T> *n)
	{
		return n->parent->left == n;
	}

	ft::TreeNode<T> *__give_only_one_child(ft::TreeNode<T> *n)
	{
		if (n->left && !n->right)
			return n->left;
		if (n->right && !n->left)
			return n->right;
		return NULL;
	}

	void __after_insert(ft::TreeNode<T> *n)
	{
		if (n == __end->left) {
			__start = __back = __end->left;
			return;
		}
		if (__start->left) {
			__start = __start->left;
			return;
		}
		if (__back->right){
			return ;
			__back = __back->right;
		}
	}

	void __after_remove(ft::TreeNode<T> *node)
	{
		if(!__end->left) {
			__start = __back =__end;
			return ;
		}
		if (node == __start)
			__start = minimum(__end->left);
		else if (node == __back)
			__back = maximum(__end->left);
	}

public:
	ft::TreeNode<T> *__new_node(T value = T())
	{
		ft::TreeNode<T> *t = new ft::TreeNode<T>(NULL, NULL, NULL, value);
		return t;
	}

	Compare key_comp()
	{
		return __comp;
	}

	ft::TreeNode<T> *insert(T value) {
		ft::TreeNode<T> *t = __new_node(value);
		ft::TreeNode<T> *root = __end->left;
		if (!root) {
			root = t;
			root->parent = __end;
			__end->left = root;
		}
		else {
			ft::TreeNode<T> *p = root;
			ft::TreeNode<T> *q = NULL;
			while (p) {
				q = p;
				if (__comp(p->value.first,t->value.first))
					p = p->right;
				else
					p = p->left;
			} 
			t->parent = q;
			if (__comp(q->value.first,t->value.first))
				q->right = t;
			else
				q->left = t;
		}
		__after_insert(t);
		return t;
	}

	template <class Key>
	ft::TreeNode<T> *search_by_key(ft::TreeNode<T> *node, Key n) {
		while (node && n != node->value.first) {
			if (__comp(n, node->value.first))
				node = node->left;
			else
				node = node->right;
		}
		return node;
	}

	ft::TreeNode<T> *minimum(ft::TreeNode<T> *node)
	{
		while (node->left != NULL) {
			node = node->left;
		}
		return node;
	}

	ft::TreeNode<T> *maximum(ft::TreeNode<T> *node)
	{
		while (node->right != NULL) {
			node = node->right;
		}
		return node;
	}

	ft::TreeNode<T> *remove(ft::TreeNode<T>*node)
	{
		ft::TreeNode<T> *child, *parent;
		bool is_black;
		if (node->left != NULL && node->right != NULL)
		{
			ft::TreeNode<T> *replace_node = node;
			// Найти узел-преемник (самый нижний левый узел правого поддерева текущего узла)
			replace_node = node->right;
			while (replace_node->left != NULL)
			{
				replace_node = replace_node->left;
			}
			if (node->parent->left == node)
				node->parent->left = replace_node;
			else
				node->parent->right = replace_node;
			// child - это правильный узел, который заменяет узел и является узлом, который требует последующей корректировки
			// Поскольку замена является преемником, он не может иметь левого дочернего узла
			// Аналогично, у узла-предшественника не может быть правого дочернего узла
			child = replace_node->right;
			parent = replace_node->parent;
			
			// Удаленный узел является родительским узлом замещающего узла (repalce)
			if (parent == node)
				parent = replace_node;
			else
			{
				// Существование дочернего узла
				if (child != NULL)
					child->parent = parent;
				parent->left = child;

				replace_node->right = node->right;
				node->right->parent = replace_node;
			}
			replace_node->parent = node->parent;
			replace_node->left = node->left;
			node->left->parent = replace_node;

			__after_remove(node);
			if (node == __start)
				__start = minimum(__end->left);
			else if (node == __back)
				__back = maximum(__end->left);

			delete node;
			return replace_node;
		}
		// Когда в удаленном узле только левый (правый) узел пуст, найдите дочерний узел удаленного узла
		if (node->left != NULL)    
			child = node->left;
		else
			child = node->right;

		parent = node->parent;
		if (child) 
			child->parent = parent;

		// Удаленный узел не является корневым узлом
		if (node == parent->left)
			parent->left = child;
		else
			parent->right = child;

		__after_remove(node);
		delete node;
		return child ? child : parent;
	}

	template <class Key>
	ft::TreeNode<T> *delete_by_key(Key key)
	{
		ft::TreeNode<T> *node = search_by_key(__end->left, key);
		if (node)
			node = remove(node);
		return node;
	}

	void	copy(Tree<T, Compare> const &other) {
		__comp = other.__comp;
		ft::TreeNode<T> *other_root = other.__root();
		if (other_root == NULL) {
			__after_remove(NULL);
			return ;
		}

		ft::TreeNode<T> *root = new ft::TreeNode<T>(*other_root);
		if (other_root->left) {
			copy_node_recurse(&root->left, other_root->left, other.__end);
			root->left->parent = root;
		}
		if (other_root->right) {
			copy_node_recurse(&root->right, other_root->right, other.__end);
			root->right->parent = root;
		}
		__end->left = root;
		root->parent = __end;
		__start = minimum(root);
		__back  = maximum(root);
	}

	void	copy(Tree<T, Compare> const &other) const {
		__comp = other.__comp;
		ft::TreeNode<T> *other_root = other.__root();
		if (other_root == NULL) {
			__after_remove(NULL);
			return ;
		}

		ft::TreeNode<T> *root = __root();
		if (other_root->left) {
			copy_node_recurse(&root->left, other_root->left, other.__end);
			root->left->parent = root;
		}
		if (other_root->right) {
			copy_node_recurse(&root->right, other_root->right, other.__end);
			root->right->parent = root;
		}
		__end->left = root;
		root->parent = __end;
		__start = minimum(root);
		__back  = maximum(root);
	}

	void copy_node_recurse(ft::TreeNode<T> **destination, ft::TreeNode<T> *source, ft::TreeNode<T> *end) {
		if (!source)
			return ;
		*destination = new ft::TreeNode<T>(*source);
		if (source->left) {
			copy_node_recurse(&(*destination)->left, source->left, end);
			(*destination)->left->parent = *destination;
		}
		if (source->right && source->right != end) {
			copy_node_recurse(&(*destination)->right, source->right, end);
			(*destination)->right->parent = *destination;
		}
	}
};
