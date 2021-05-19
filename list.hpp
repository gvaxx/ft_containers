#ifndef FT_LIST
#define FT_LIST
#include <iostream>
#include <typeinfo>
#include <limits>
#include <memory>
#include "helper.hpp"
#include "bidirectional_iterator.hpp"

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class list {
	public:
		typedef T										value_type;
		typedef std::size_t								size_type;
		typedef Alloc									allocator_type;
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
		allocator_type									__alloc;
		public:
			explicit list(const allocator_type& alloc = allocator_type()): __alloc(alloc)
			{
				__base_construct();
			}

			~list()
			{
				clear();
				__destroy_node(__end);
			}

			explicit list(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) : __alloc(alloc)
			{
				__base_construct();
				for (size_type i = 0 ; i < n; i++)
					push_back(val);
			}

			template <class InputIterator>
			list(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: __alloc(alloc)
			{
				__base_construct();
				while (first != last) {
					push_back(*first);
					__size++;
					first++;
				}
			}

			list(const list& x): __alloc(alloc)
			{
				__base_construct();
				if (!x.empty()) {
					__alloc = x.__alloc;
					iterator first = x.begin();
					iterator last = x.end();
					for (; first != last; first++)
						push_back(*first);
				}
				__size = x.__size;
			}

			size_type size() const
			{
				return __size;
			}

			size_type size()
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

			size_type max_size() const
			{
				return std::min((size_type) std::numeric_limits<difference_type>::max(), std::numeric_limits<size_type>::max() / (sizeof(__node)));
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

			void resize(size_type n, value_type val = value_type())
			{
				if (n < __size)
					erase(__iterator(n), end());
				else if (n > __size)
					insert(end(), n - __size, val);
			}

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

			void insert(iterator position, size_type n, const value_type& val)
			{
				if (n) {
					__node_pointer first_node, last_node;
					first_node = last_node = __create_node(val) ;
					for (size_type i = 1; i < n; i++) {
						last_node->next = __create_node(val);
						last_node->next->prev = last_node;
						last_node = last_node->next;
					}
					__size += n;
					__link_nodes(position.getNode(), first_node, last_node);
				}
			}
			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				if (first != last) {
					__node_pointer first_node, last_node;
					first_node = last_node = __create_node(*first) ;
					__size++;
					for (++first; first != last; first++) {
						last_node->next = __create_node(*first);
						last_node->next->prev = last_node;
						last_node = last_node->next;
						__size++;
					}
					__link_nodes(position.getNode(), first_node, last_node);
				}
			}
			

			template <class InputIterator>
			void assign(InputIterator first, InputIterator last)
			{
				iterator index = begin();
				iterator finish = end();
				for (; first != last && index != finish; ++first, ++index)
					*index = *first;
				if (index == finish)
					insert(finish, first, last);
				else
					erase(index, finish);
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

			void swap (list& x)
			{
				swap_value(x.__end, __end);
				swap_value(x.__size, __size);
			}

			void unique()
			{
				unique(&equal<value_type>);
			}

			template <class BinaryPredicate>
			void unique(BinaryPredicate binary_pred)
			{
				iterator start = begin();
				iterator next = start;
				for (iterator back = end(); start != back;)
				{
					next++;
					for (; next != back && binary_pred(*start, *next); next++);
					if (++start != next) {
						erase(start, next);
						start = next;
					}
				}
			}
			void merge (list& x)
			{
				merge(x, &less<value_type>);
			}
			
			template <class Comp>
			void merge(list& x, Comp comp)
			{
				if (&x != this)
				{
					iterator start_1 = begin();
					iterator end_1 = end();
					iterator start_2 = x.begin();
					iterator end_2 = x.end();
					while (start_1 != end_1 && start_2 != end_2)
					{
						if (comp(*start_2, *start_1))
						{
							size_type insert_size = 1;
							iterator insert_elements = __next_iterator(start_2);
							for (; insert_elements != end_2 && comp(*insert_elements, *start_1); ++insert_elements, ++insert_size)
							;
							__size += insert_size;
							x.__size -= insert_size;
							__node_pointer first = start_2.getNode();
							__node_pointer last = (insert_elements.getNode())->prev;
							start_2 = insert_elements;
							__unlink_nodes(first, last);
							__link_nodes(start_1.getNode(), first, last);
							++start_1;
						}
						else
							++start_1;
					}
					splice(end_1, x);
				}
			}

			void reverse()
			{
				if (__size > 1)
				{
					for (__node_pointer start = begin().getNode(); start != __end;)
					{
						swap_value(start->prev, start->next);
						start = start->prev;
					}
					swap_value(__end->prev, __end->next);
				}
			}
			void sort()
			{
				sort(&less<value_type>);
			}
			template <class Compare>
			void sort(Compare comp)
			{
				
				if (__size > 1)
				{
					bool had_sorted_value = true;
					while (had_sorted_value)
					{
						had_sorted_value = false;
						__node_pointer start = (begin().getNode())->next;
						for (; start != __end;)
						{
							if (comp(start->value, start->prev->value)) {
								had_sorted_value = true;
								__swap_nodes(start->prev, start);
								start = start->next;
							}
							start = start->next;
						}
					}
				}
			}
		private:
			void __swap_nodes(__node_pointer first, __node_pointer second)
			{
				swap_value(first->prev->next, second->next->prev);
				first->next = second->next;
				second->prev = first->prev;
				second->next = first;
				first->prev = second;
			}
			iterator __next_iterator(iterator i)
			{
				return ++i;
			}

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
				__node_pointer node = new __node();
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
				delete node;
			}

			iterator	__iterator(size_type n)
			{
				iterator start = begin();
				for (size_type i = 0; i < n; i++)
					start++;
				return start;
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
		return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T>
	bool operator!=(const list<T>& lhs, const list<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T>
	bool operator<(const list<T>& lhs, const list<T>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
	}

	template <class T>
	bool operator<=(const list<T>& lhs, const list<T>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T>
	bool operator>(const list<T>& lhs, const list<T>& rhs)
	{
		return rhs < lhs;
	}

	template <class T>
	bool operator>=(const list<T>& lhs, const list<T>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif