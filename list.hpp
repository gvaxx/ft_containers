
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
			__node_pointer			_end;
			size_type				_size;
			
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
					_size++;
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
				return _size;
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
				__link_nodes(_end, tmp, tmp);
				_size++;
			}

			void push_front(const value_type& val)
			{
				__node_pointer tmp = __create_node(val);
				__link_nodes(_end->next, tmp, tmp);
				_size++;
			}

			void clear()
			{
				__node_pointer first_node = _end->next;
				__node_pointer tmp = first_node;
				while (first_node != _end) {
					tmp = first_node;
					first_node = first_node->next;
					__destroy_node(tmp);
				}
				__destroy_node(_end);
				__base_construct();
			}

			size_type max_size() const
			{
				return std::numeric_limits<difference_type>::max();
			}

			iterator begin()
			{
				return iterator(_end->next);
			}

			const_iterator begin() const
			{
				return const_iterator(_end->next);
			}

			iterator end()
			{
				return iterator(_end);
			}

			const_iterator end() const
			{
				return const_iterator(_end);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(_end->prev);
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(_end->prev);
			}

			reverse_iterator rend()
			{
				return reverse_iterator(_end);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(_end);
			}

			// void resize(size_type n, value_type val = value_type())
			// {
			// 	while(n > _size)
			// 		push_back(val);
			// 	if (n < _size) {
			// 		size_type tmp = _size;
			// 		_capacity = 1;
			// 		reserve(n);
			// 	}
			// 	return ;
			// }

			bool empty() const
			{
				return !_size;
			}

			reference front()
			{
				return _end->next->value;
			}

			const_reference front() const
			{
				return _end->next->value;
			}

			reference back()
			{
				return _end->prev->value;
			}

			const_reference back() const
			{
				return _end->prev->value;
			}

			void pop_back()
			{
				if (empty())
					return ;
				__node_pointer last_node = _end->prev;
				__unlink_nodes(last_node, last_node);
				__destroy_node(last_node);
				_size--;
			}

			void pop_front()
			{
				if (empty())
					return ;
				__node_pointer first_node = _end->next;
				__unlink_nodes(first_node, first_node);
				__destroy_node(first_node);
				_size--;
			}
/*
			iterator insert(iterator position, const value_type& val)
			{
				__node_pointer *insert_node = _head;
				if (_size)
					insert_node = __insert_node_before_el(position.getNode(), val);
				else
					_head->value = val;
				_size++;
				return iterator(insert_node);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				if (n) {
					__node_pointer *insert_node;
					if (_size) {
						for (size_type i = 0; i < n, i++) {
							__insert_node_before_el(position.getNode(), val)
							_size++;
						}
					} else {
						_head->value = val;
						n--;
						_size++;
					}
				}
				size_type index = position - begin();
				__move_elems(position, n);
				for (size_type i = 0; i < n; i++) {
					_array[index + i] = val;
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type index = position - begin();
				size_type quantity = __distance(first, last);
				__move_elems(position, quantity);
				while (first != last) {
					_array[index++] = *first;
					first++;
				}
			}
			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				clear();
				insert(begin(), first, last);
			}

			void assign(size_type n, const value_type& val)
			{
				clear();
				insert(begin(), n, val);
			}
			iterator erase (iterator position)
			{
				__move_elems(position + 1, -1);
				return position;
			}
			iterator erase (iterator first, iterator last)
			{
				__move_elems(last, first - last);
				return first;
			}

			void swap (list& x)
			{
				swap_value(x._array, _array);
				swap_value(x._size, _size);
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
				_end = __create_node();
				_end->next = _end;
				_end->prev = _end;
				_size = 0;
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