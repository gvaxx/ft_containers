
#ifndef FT_LIST
#define FT_LIST
#include <iostream>
#include <typeinfo>
#include <limits>
#include "helper.hpp"
#include "bidirectional_iterator.hpp"

namespace ft {
	template <class T >
	class list {
	public:
		typedef T										value_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef	value_type&								reference;
		typedef	const value_type&						const_reference;
		typedef	value_type*								pointer;
		typedef	const value_type*						const_pointer;
		typedef BidirectionalIterator<T>				iterator;
		typedef const BidirectionalIterator<T>			const_iterator;
		typedef BidirectionalReverseIterator<T>			reverse_iterator;
		typedef const BidirectionalReverseIterator<T>	const_reverse_iterator;

		private:
		typedef Node<T>									__node;
		typedef __node*									__node_pointer;
		__node_pointer									__end;
		size_type										__size;
			
		public:
			explicit list()
			{
				__base_construct();
			}

			~list()
			{
				// clear();
				// ::operator delete(_array);
			}

			explicit list(size_type n, const value_type& val = value_type())
			{
				__base_construct();
				for (size_type i = 0 ; i < n; i++)
					push_back(val);
			}

			template <class InputIterator>
			list(InputIterator first, InputIterator last)
			{
				__base_construct();
				while (first != last) {
					push_back(*first);
					__size++;
				}
			}

			list(const list& x)
			{
				__base_construct();
				if (!x.empty()) {
					iterator first = x.begin();
					iterator last = x.end();
					for (; first != last; first++)
						push_back(*first);
				}
			}

			size_type size() const
			{
				return __size;
			}

			list& operator=(const list& x)
			{
				if (this != &x)
				{
					clear();
					iterator it_beg = x.begin();
					iterator it_end = x.end();
					for (; it_beg != it_end; ++it_beg)
						push_back(*it_beg);
				}
				return *this;
			}

			void push_back(const value_type& val)
			{
				__node_pointer tmp = __create_node(val);
				__link_nodes(__end, tmp, tmp);
				__size++;
			}

			void push_front(const value_type& val)
			{
				__node_pointer tmp = __create_node(val);
				__link_nodes(__end->next, tmp, tmp);
				__size++;
			}

			void clear()
			{
				__node_pointer first_node = __end->next;
				__node_pointer tmp = first_node;
				while (first_node != __end) {
					tmp = first_node;
					first_node = first_node->next;
					__destroy_node(tmp);
				}
				__destroy_node(__end);
				__base_construct();
			}

			size_type max__size() const
			{
				return std::numeric_limits<difference_type>::max();
			}

			iterator begin()
			{
				return iterator(__end->next);
			}

			const_iterator begin() const
			{
				return const_iterator(__end->next);
			}

			iterator end()
			{
				return iterator(__end);
			}

			const_iterator end() const
			{
				return const_iterator(__end);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(__end->prev);
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(__end->prev);
			}

			reverse_iterator rend()
			{
				return reverse_iterator(__end);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(__end);
			}

			// void resize(size_type n, value_type val = value_type())
			// {
			// 	while(n > __size)
			// 		push_back(val);
			// 	if (n < __size) {
			// 		size_type tmp = __size;
			// 		_capacity = 1;
			// 		reserve(n);
			// 	}
			// 	return ;
			// }

			bool empty() const
			{
				return !__size;
			}

			reference front()
			{
				return __end->next->value;
			}

			const_reference front() const
			{
				return __end->next->value;
			}

			reference back()
			{
				return __end->prev->value;
			}

			const_reference back() const
			{
				return __end->prev->value;
			}

			void pop_back()
			{
				if (empty())
					return ;
				__node_pointer last_node = __end->prev;
				__unlink_nodes(last_node, last_node);
				__destroy_node(last_node);
				__size--;
			}

			void pop_front()
			{
				if (empty())
					return ;
				__node_pointer first_node = __end->next;
				__unlink_nodes(first_node, first_node);
				__destroy_node(first_node);
				__size--;
			}

			iterator insert(iterator position, const value_type& val)
			{
				__node_pointer insert_node = __create_node(val);
				__link_nodes(position.getNode(), insert_node, insert_node);
				__size++;
				return iterator(insert_node);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n) {
					__node_pointer first_node, last_node;
					first_node = last_node = __create_node(val) ;
					for (size_type i = 1; i < n; i++) {
						last_node->next = __create_node(val);
						last_node->next->prev = last_node;
						last_node = last_node->next;
					}
					__link_nodes(position.getNode(), first_node, last_node);
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				if (first != last) {
					__node_pointer first_node, last_node;
					first_node = last_node = __create_node(*first) ;
					for (++first; first != last; first++) {
						last_node->next = __create_node(*first);
						last_node->next->prev = last_node;
						last_node = last_node->next;
					}
					__link_nodes(position.getNode(), first_node, last_node);
				}
			}
			

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				iterator index = begin();
				iterator end = end();
				for (; first != last && index != end; ++first, ++index)
					*index = *first;
				if (index == end)
					insert(end, first, last);
				else
					erase(index, end);
			}

			void assign(size_type n, const value_type& val)
			{
				iterator index = begin();
				iterator end = end();
				for (; n > 0 && index != end; --n, ++index)
					*index = val;
				if (index == end)
					insert(end, n, val);
				else
					erase(index, end);
			}

			iterator erase (iterator position)
			{				
				__node_pointer delete_node = position.getNode();
				iterator return_iterator = iterator(delete_node->next);
				__unlink_nodes(delete_node, delete_node);
				__destroy_node(delete_node);
				__size--;
				return return_iterator;
			}

			iterator erase (iterator first, iterator last)
			{
				iterator return_iterator = iterator(last.getNode());
				__unlink_nodes(first.getNode(), (last.getNode())->prev);
				while (first != last)
				{
					__node_pointer delete_node = first.getNode();
					++first;
					--__size;
					__destroy_node(delete_node);
				}
				return return_iterator;
			}

			void splice(iterator position, list& x)
			{
				if (!x.empty())
				{
					__node_pointer first = x.__end->next;
					__node_pointer last = x.__end->prev;
					__unlink_nodes(first, last);
					__link_nodes(position.getNode(), first, last);
					__size += x.size();
					x.__size = 0;
				}
			}
			void splice (iterator position, list& x, iterator i)
			{
				__node_pointer node_pos = position.getNode();
				if (node_pos != i.getNode() && node_pos != (i.getNode())->next)
				{
					__node_pointer first = i.getNode();
					__unlink_nodes(first, first);
					__link_nodes(node_pos, first, first);
					--x.__size;
					++__size;
				}
			}

			void splice (iterator position, list& x, iterator first, iterator last)
			{
				if (first != last)
				{
					__node_pointer first_node = first.getNode();
					__node_pointer last_node = (last.getNode())->prev;
					if (this != &x)
					{
						size_type distance = __distance(first, last);
						x.__size -= distance;
						__size += distance;
					}
					__unlink_nodes(first_node, last_node);
					__link_nodes(position.getNode(), first_node, last_node);
				}
			}

			void remove (const value_type& val)
			{
				if (__size)
				{
					iterator	first = begin() ;
					iterator	last = end();
					iterator	tmp;
					while (first != last)
					{
						tmp = first++;
						if (*tmp == val)
							this->erase(tmp);
					}
				}
			}

			template <class Predicate>
			void remove_if (Predicate pred)
			{
				if (__size)
				{
					iterator	first = begin() ;
					iterator	last = end();
					iterator	tmp;
					while (first != last)
					{
						tmp = first++;
						if (pred(*tmp))
							this->erase(tmp);
					}
				}
			}
/*

			void swap (list& x)
			{
				swap_value(x._array, _array);
				swap_value(x.__size, __size);
				swap_value(x._capacity, _capacity);
			}*/
		private:
			__node_pointer *__insert_node_before_el(__node_pointer *el, const value_type& val = value_type())
			{
				__node_pointer *tmp = __create_node(val);
				tmp->next = el;
				tmp->prev = el->prev;
				el->prev->next = tmp;
				el->prev = tmp;
				return tmp;
			}

			void __link_nodes(__node_pointer __position, __node_pointer __first, __node_pointer __last)
			{
				__position->prev->next = __first;
				__first->prev = __position->prev;
				__position->prev = __last;
				__last->next = __position;
			}

			void __base_construct()
			{
				__end = __create_node();
				__end->next = __end;
				__end->prev = __end;
				__size = 0;
			}

			__node_pointer __create_node(T value = value_type())
			{
				__node_pointer node = new __node;
				node->value = value;
				return node;
			}
			
			template <class InputIterator>
			size_type __distance(InputIterator first, InputIterator last)
			{
				size_type distance = 0;
				while (first++ != last)
					distance++;
				return distance;
			}

			void	__unlink_nodes(__node_pointer __first, __node_pointer __last)
			{
				__first->prev->next = __last->next;
				__last->next->prev = __first->prev;
			}

			void	__destroy_node(__node_pointer node)
			{
				node->value.value_type::~value_type();
				node->__node::~__node();
			}
	};

	template <class T>
  	void swap (list<T>& x, list<T>& y)
	{
		x.swap(y);
	}

	template <class T>
	bool operator==(const list<T>& lhs, const list<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		unsigned long size = lhs.size();
		for (unsigned long i = 0; i < size; i++)
			if (lhs[i] != rhs[i]) 
				return false;
		return true;
	}

	template <class T>
	bool operator!=(const list<T>& lhs, const list<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return true;
		unsigned long size = lhs.size();
		for (unsigned long i = 0; i < size; i++)
			if (lhs[i] == rhs[i]) 
				return false;
		return true;
	}

	template <class T>
	bool operator<(const list<T>& lhs, const list<T>& rhs)
	{
		unsigned long size = lhs.size();
		if (size > rhs.size()) size = rhs.size();
		for (unsigned long i = 0; i < size; i++)
			if (lhs[i] != rhs[i])
				return (lhs[i] < rhs[i]);
		return lhs.size() < rhs.size();
	
	}

	template <class T>
	bool operator<=(const list<T>& lhs, const list<T>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T>
	bool operator>(const list<T>& lhs, const list<T>& rhs)
	{
		unsigned long size = lhs.size();
		if (size > rhs.size()) size = rhs.size();
		for (unsigned long i = 0; i < size; i++)
			if (lhs[i] != rhs[i])
				return (lhs[i] > rhs[i]);
		return lhs.size() > rhs.size();
	}

	template <class T>
	bool operator>=(const list<T>& lhs, const list<T>& rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}
}

#endif