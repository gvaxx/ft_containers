#ifndef FT_MAP
#define FT_MAP
#include <iostream>
#include <sstream>
#include <typeinfo>
#include <limits>
#include <map>
#include "helper.hpp"
#include "tree.hpp"

namespace ft {
	template <
		class Key,
		class T,
		class Compare = std::less<Key>
	>
	class map {
	public:
		typedef Key											key_type;
		typedef T											mapped_type;
		typedef std::pair<const key_type, mapped_type>		value_type;
		typedef Compare										key_compare;
		typedef std::size_t									size_type;
		typedef std::ptrdiff_t								difference_type;
		typedef	value_type&									reference;
		typedef	const value_type&							const_reference;
		typedef	value_type*									pointer;
		typedef	const value_type*							const_pointer;
		typedef TreeNode<value_type>						__node;
		typedef __node*										__node_pointer;
		typedef std::pair<Key,T>							__pair;
		typedef Tree<value_type, key_compare>				__base_tree;

    class BidirectionalTreeIterator: public std::iterator<
        std::bidirectional_iterator_tag,
        value_type,
        std::ptrdiff_t,
        value_type*,
        value_type&
    >
    {
		friend class map<Key, T>;

    protected:
		typedef TreeNode<value_type> node_type;
		node_type*					p;

    public:
        BidirectionalTreeIterator(): p(NULL) {}
        BidirectionalTreeIterator(node_type* p) : p(p) {};
        BidirectionalTreeIterator(const BidirectionalTreeIterator &it) :p(it.p) {};
        ~BidirectionalTreeIterator(void) {}

		BidirectionalTreeIterator					&operator=(const BidirectionalTreeIterator &rhs)
		{
			this->p = rhs.p;
			return (*this);
		}

		BidirectionalTreeIterator					&operator++(void)
		{
			if (p->right) {
				p = p->right;
				while (p->left)
					p = p->left;
			} else {
				node_type* tmp = p;
				p = p->parent;
				while (p && tmp == p->right) {
					tmp = p;
					p = p->parent;
				}
			}
			return (*this);
		}

		BidirectionalTreeIterator					operator++(int)
		{
			BidirectionalTreeIterator tmp = *this;
			this->operator++();	
			return (tmp);
		}

		BidirectionalTreeIterator					&operator--(void)
		{
			if (p->left) {
				p = p->left;
				while (p->right)
					p = p->right;
			} else {
				node_type* tmp = p;
				p = p->parent;
				while (p && tmp == p->left)
					tmp = p;
					p = p->parent;
			}
			return (*this);
		}

		BidirectionalTreeIterator					operator--(int)
		{
			BidirectionalTreeIterator tmp = *this;
			this->operator--();
			return (tmp);
		}

		bool						operator==(const BidirectionalTreeIterator &rhs) const
		{
			return (p == rhs.p);
		}

		bool						operator!=(const BidirectionalTreeIterator &rhs) const
		{
			return !(p == rhs.p);
		}

		value_type					&operator*(void)
		{
			return (p->value);
		}

		value_type					*operator->(void)
		{ 
			return &this->operator*();
		}
		private:
			node_type* getTreeNode()
			{
				return (p);
			}
	};

    class BidirectionalTreeReverseIterator : public BidirectionalTreeIterator
    {
    public:
	    BidirectionalTreeReverseIterator():BidirectionalTreeIterator() {}
	    BidirectionalTreeReverseIterator(value_type* p): BidirectionalTreeIterator(p) {}
        BidirectionalTreeReverseIterator(const BidirectionalTreeReverseIterator &it):BidirectionalTreeIterator(it) {}
        ~BidirectionalTreeReverseIterator(void) {}

		BidirectionalTreeReverseIterator					&operator++(void)
		{
			if (this->p->left) {
				this->p = this->p->left;
				while (this->p->right)
					this->p = this->p->right;
			} else {
				TreeNode<value_type>* tmp = this->p;
				this->p = this->p->parent;
				while (this->p && tmp == this->p->left)
					tmp = this->p;
					this->p = this->p->parent;
			}
		}

		BidirectionalTreeReverseIterator					operator++(int)
		{
			BidirectionalTreeReverseIterator tmp = *this;
			this->operator++();
			return (tmp);
		}

		BidirectionalTreeReverseIterator					&operator--(void)
		{
			if (this->p->right) {
				this->p = this->p->right;
				while (this->p->left)
					this->p = this->p->left;
			} else {
				TreeNode<value_type>* tmp = this->p;
				this->p = this->p->parent;
				while (this->p && tmp == this->p->right)
					tmp = this->p;
					this->p = this->p->parent;
			}
			return (*this);
		}

		BidirectionalTreeReverseIterator					operator--(int)
		{
			BidirectionalTreeReverseIterator tmp = *this;
			this->operator--();
			return (tmp);
		}
	};

	class value_compare
	{

	// in C++98, it is required to inherit binary_function<value_type,value_type,bool>
  	friend class map;

	protected:
		Compare comp;
		value_compare (Compare c) : comp(c) {}  // constructed with map's comparison object

	public:
		typedef bool result_type;
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;

		bool operator() (const value_type& x, const value_type& y) const
		{
			return comp(x.first, y.first);
		}
	};

	typedef BidirectionalTreeIterator				iterator;
	typedef BidirectionalTreeIterator			const_iterator;
	typedef BidirectionalTreeReverseIterator			reverse_iterator;
	typedef BidirectionalTreeReverseIterator	const_reverse_iterator;
		
	private:
		Compare		__comparator;
		__base_tree	*__tree;
		size_type	__size;
			
	public:

		explicit map(const key_compare& comp = key_compare())
		{
			__base_construct(comp);
		}

		~map()
		{
			clear();
			delete __tree;
		}

		template <class InputIterator>
		map(InputIterator first, InputIterator last, const key_compare& comp = key_compare())
		{
			__base_construct(comp);
			while (first != last) {
				insert(*first++);
			}
		}

		map(const map& x)
		{
			__base_construct();
			__tree->copy(*(x.__tree));
			__size = x.__size;
		}
		void print()
		{
			__tree->print_binary_tree(__tree->__end);
		}

		void	clear(void)
		{
			if(__size)
				erase(begin(), end());
		}

		map& operator=(const map& x)
		{
			if (this != &x)
			{
				clear();
				__tree->copy(*(x.__tree));
				__size = x.__size;
			}
			return *this;
		}

		iterator begin()
		{
			return iterator(__tree->__start);
		}

		const_iterator begin() const
		{
			return const_iterator(__tree->__start);
		}

		iterator end()
		{
			return iterator(__tree->__end);
		}

		const_iterator end() const
		{
			return const_iterator(__tree->__end);
		}

		reverse_iterator rbegin()
		{
			return reverse_iterator(__tree->__back);
		}

		const_reverse_iterator rbegin() const
		{
			return const_reverse_iterator(__tree->__back);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(__tree->__end);
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(__tree->__end);
		}

		bool empty() const
		{
			return !__size;
		}

		size_type size() const
		{
			return __size;
		}

		size_type size()
		{
			return __size;
		}

		size_type	max_size() const
		{
			return std::numeric_limits<difference_type>::max();
		}

		mapped_type &operator[](key_type const &k)
		{
			__node *node = __tree->search_by_key(__root(), k);
			if (node)
				return (node->value.second);
			__size++;
			return (__tree->insert(std::make_pair(k, mapped_type()))->value.second);
		}

		std::pair<iterator,bool> insert(const value_type& val)
		{
			__node *node = __tree->search_by_key(__root(), val.first);
			if (node)
				return std::make_pair(iterator(node), false);
			__size++;
			return std::make_pair(iterator(__tree->insert(val)), true);
		}

		iterator insert(iterator position, const value_type& val)
		{
			__node *node = __tree->search_by_key(__root(), val.first);
			if (node)
				return iterator(node);
			__size++;
			return iterator(__tree->insert(val));
		}

		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
				insert(*first++);
		}

		void erase(iterator position)
		{
			erase(position->first);
		}

		size_type erase(const key_type& k)
		{
			size_type is_erase = size_type(__tree->delete_by_key(k));
			if (is_erase)
				__size--;
			return is_erase;
		}

		void erase(iterator first, iterator last)
		{
			bool is_erase = false;
			iterator temp = first;
			while (first != last) {
				temp = first++;
				is_erase = __tree->delete_by_key((*temp).first);
				if (is_erase)
					__size--;
			}
		}

		void swap (map& x)
		{
			swap_value(x.__tree, __tree);
			swap_value(x.__size, __size);
		}

		key_compare key_comp() const
		{
			return __tree->key_comp();
		}

		value_compare value_comp(void) const
		{
			return (this->value_compare);
		}

		iterator find (const key_type& k)
		{
			__node_pointer node = __tree->search_by_key(__root(), k);
			if (node)
				return iterator(node);
			return end();
		}

		const_iterator find (const key_type& k) const
		{
			__node_pointer node = __tree->search_by_key(__root(), k);
			if (node)
				return const_iterator(node);
			return end();
		}

		size_type count (const key_type& k) const
		{
			return static_cast<size_type>(find(k) != end());
		}

		iterator				lower_bound(const key_type &key)
		{
			iterator first = begin();
			iterator last = end();

			while (first != last) {
				if (__comparator((*first).first, key) == false)
					return (iterator(first));
				first++;
			}
			return (end());
		}

		const_iterator			lower_bound(const key_type &key) const
		{
			const_iterator first = begin();
			const_iterator last = end();

			while (first != last) {
				if (__comparator((*first).first, key) == false)
					return (const_iterator(first));
				first++;
			}
			return (end());
		}

		iterator upper_bound(key_type const &key)
		{
			iterator first = begin();
			iterator last = end();

			while (first != last) {
				if (((*first).first == key))
					return (iterator(++first));
				if (__comparator((*first).first, key) == false)
					return (iterator(first));
				++first;
			}
			return (end());
		}

		const_iterator upper_bound(key_type const &key) const
		{
			const_iterator first = begin();
			const_iterator last = end();

			while (first != last) {
				if (((*first).first == key))
					return (const_iterator(++first));
				if (__comparator((*first).first, key) == false)
					return (const_iterator(first));
				++first;
			}
			return (end());
		}

		typename std::pair<iterator, iterator> equal_range(key_type const &key)
		{
			return (std::pair<iterator, iterator>(lower_bound(key), upper_bound(key)));
		}

		typename std::pair<const_iterator, const_iterator> equal_range(key_type const &key) const
		{
			return (std::pair<const_iterator, const_iterator>(lower_bound(key), upper_bound(key)));
		}

	private:
		void __base_construct(const key_compare& comp = key_compare())
		{
			__comparator = comp;
			__tree = new Tree<value_type, key_compare>(comp);
			__size = 0;
		}

		__node_pointer __root()
		{
			return __tree->__end->left;
		}

		__node_pointer __root() const
		{
			return __tree->__end->left;
		}
};

	template <class Key,class T>
  	void swap (map<Key,T>& x, map<Key,T>& y)
	{
		x.swap(y);
	}
}
template <class Key, class T, class Compare>
	bool operator==(const ft::map<Key, T, Compare> &lhs, const ft::map<Key, T, Compare> &rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <class Key, class T, class Compare>
	bool operator!=(const ft::map<Key, T, Compare> &lhs, const ft::map<Key, T, Compare> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Key, class T, class Compare>
	bool operator<(const ft::map<Key, T, Compare> &lhs, const ft::map<Key, T, Compare> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class Key, class T, class Compare>
	bool operator<=(const ft::map<Key, T, Compare> &lhs, const ft::map<Key, T, Compare> &rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class Key, class T, class Compare>
	bool operator>(const ft::map<Key, T, Compare> &lhs, const ft::map<Key, T, Compare> &rhs)
	{	
		return (!(lhs < rhs) && !(lhs == rhs));
	}

	template <class Key, class T, class Compare>
	bool operator>=(const ft::map<Key, T, Compare> &lhs, const ft::map<Key, T, Compare> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Key, class T, class Compare, class Alloc>
	void swap(ft::map<Key, T, Compare> &x, ft::map<Key, T, Compare> &y)
	{
		x.swap(y);
	}

#endif