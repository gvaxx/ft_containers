#ifndef HELPER
#define HELPER
#include <iostream>

namespace ft
{
	template <class T>
	void swap_value(T & x, T & y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}

	template <class T>
	struct Node
	{
		Node	*prev;
		Node	*next;
		T		value;
	};

	template <class T>
	struct TreeNode
	{
		TreeNode	*parent;
		TreeNode	*left;
		TreeNode	*right;
		T			value;
		TreeNode(TreeNode *p,TreeNode *l,TreeNode *r, T v) : parent(p), left(l), right(r), value(v){}
		TreeNode(TreeNode const &x) : parent(x.parent), left(x.left), right(x.right), value(x.value){}
	};

	template<class value_type>
	bool equal(value_type const &a, value_type const &b) {
		return (a == b);
	}

	template<class value_type>
	bool less(value_type const &a, value_type const &b) {
		return (a < b);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal ( InputIterator1 first1, InputIterator1 last1, InputIterator2 first2 )
	{
		while (first1!=last1) {
			if (!(*first1 == *first2))
				return false;
			++first1;
			++first2;
		}
		return true;
	}
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
									InputIterator2 first2, InputIterator2 last2)
	{
		while (first1!=last1)
		{
			if (first2==last2 || *first2<*first1) return false;
			else if (*first1<*first2) return true;
			++first1;
			++first2;
		}
		return (first2!=last2);
	}
} // namespace ft

void print_error(std::string error_string);

void print_success();

void print_fail();

#endif
