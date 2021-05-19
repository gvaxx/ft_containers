
#ifndef FT_VECTOR
#define FT_VECTOR
#include <iostream>
#include <typeinfo>
#include <limits>
#include "helper.hpp"
#include <memory>
#include "random_access_iterator.hpp"
#include "helper.hpp"

namespace ft {
	template <class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T										value_type;
		typedef Alloc									allocator_type;
		typedef std::size_t								size_type;
		typedef std::ptrdiff_t							difference_type;
		typedef	value_type&								reference;
		typedef	const value_type&						const_reference;
		typedef	value_type*								pointer;
		typedef	const value_type*						const_pointer;
		typedef RandomAccessIterator<T>					iterator;
		typedef RandomAccessIterator<T const>			const_iterator;
		typedef RandomAccessReverseIterator<T>			reverse_iterator;
		typedef RandomAccessReverseIterator<T const>	const_reverse_iterator;

		private:
			value_type				*_array;
			size_type				_size;
			size_type				_capacity;
			allocator_type			_alloc;
			
		public:
			explicit vector(const allocator_type& alloc = allocator_type())
				: _array(NULL), _size(0), _capacity(0), _alloc(alloc)
			{}

			~vector()
			{
				clear();
				if (_array)
					_alloc.deallocate(_array, _capacity);
			}

			explicit vector(size_type n, const value_type& val = value_type(),
                 const allocator_type& alloc = allocator_type()): _array(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				assign(n, val);
			}

			template <class InputIterator>
			vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
				: _array(NULL), _size(0), _capacity(0), _alloc(alloc)
			{
				for (; first != last; ++first)
					push_back(*first);
			}

			vector(const vector& x): _array(NULL), _size(x.size()), _capacity(0)
			{
				if (x.size())
				{
					reserve(x.size());
					std::memcpy(_array, x._array, _size * sizeof(value_type));
				}
			}

			vector& operator=(const vector& x)
			{
				if (this != &x)
				{
					clear();
					_alloc = x._alloc;
					reserve(x.size());
					_size = x.size();
					std::memcpy(_array, x._array, _size * sizeof(value_type));
				}
				return *this;
			}

			void push_back(const value_type& val)
			{
				reserve(_size + 1);
				_array[_size++] = val;
			}

			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_array[i].value_type::~value_type();
				_size = 0;
			}

			size_type max_size() const
			{
				return std::min((size_type) std::numeric_limits<difference_type>::max(), std::numeric_limits<size_type>::max() / sizeof(value_type));
			}

			size_type size() const
			{
				return _size;
			}

			void reserve(size_type n)
			{
				if (n > _capacity) {
					size_t new_capacity = (n > _capacity * 2) ? n : _capacity * 2;
					value_type *tmp = _alloc.allocate(new_capacity);
					if (_array) {
						std::memcpy(tmp, _array, _size * sizeof(value_type));
						_alloc.deallocate(_array, _capacity);
					}
					_array = tmp;
					_capacity = new_capacity;
				}
			}

			iterator begin()
			{
				return iterator(&_array[0]);
			}

			const_iterator begin() const
			{
				return const_iterator(&_array[0]);
			}

			iterator end()
			{
				return iterator(&_array[_size]);
			}

			const_iterator end() const
			{
				return const_iterator(&_array[_size]);
			}

			reverse_iterator rbegin()
			{
				return reverse_iterator(&_array[_size - 1]);
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(&_array[_size - 1]);
			}

			reverse_iterator rend()
			{
				return reverse_iterator(&_array[-1]);
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(&_array[-1]);
			}

			size_type capacity()
			{
				return _capacity;
			}

			size_type capacity() const
			{
				return _capacity;
			}

			void resize(size_type n, value_type val = value_type())
			{
				while (n > _size)
					push_back(val);
				if (n < _size) {
					erase(begin() + n, end());
				}
				return ;
			}

			bool empty() const
			{
				return !_size;
			}

			reference operator[] (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("Vector index out of range");
				return _array[n];
			}

			const_reference operator[] (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("Vector index out of range");
				return _array[n];
			}
			
			reference at (size_type n)
			{
				if (n >= _size)
					throw std::out_of_range("Vector index out of range");
				return _array[n];
			}

			const_reference at (size_type n) const
			{
				if (n >= _size)
					throw std::out_of_range("Vector index out of range");
				return _array[n];
			}

			reference front()
			{
				return _array[0];
			}

			const_reference front() const
			{
				return _array[0];
			}

			reference back()
			{
				return _array[_size - 1];
			}

			const_reference back() const
			{
				return _array[_size - 1];
			}

			void pop_back()
			{
				if (_size) {
					_array[--_size].value_type::~value_type();
				}
			}

			iterator insert(iterator position, const value_type& val)
			{
				size_type index = position - begin();
				__move_elems(position, 1);
				new(&_array[index]) value_type(val);
				return iterator(&_array[index]);
			}

			void insert (iterator position, size_type n, const value_type& val)
			{
				size_type index = position - begin();
				__move_elems(position, n);
				for (size_type i = 0; i < n; i++) {
					new(&_array[index + i]) value_type(val);
				}
			}

			template <class InputIterator>
			void insert (iterator position, InputIterator first, InputIterator last)
			{
				size_type index = position - begin();
				size_type quantity = __distance(first, last);
				__move_elems(position, quantity);
				while (first != last) {
					new(&_array[index++]) value_type(*first);
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

			void swap (vector& x)
			{
				swap_value(x._array, _array);
				swap_value(x._size, _size);
				swap_value(x._capacity, _capacity);
			}
		private:
			value_type *__reserve(size_type n)
			{
				return static_cast<value_type*>(::operator new(sizeof(value_type) * n));
			}

			void __move_elems(iterator start, long offset)
			{
				size_type new_size = offset + _size;

				if (new_size > _capacity) {
					size_t new_capacity = (new_size > _capacity * 2) ? new_size : _capacity * 2;
					value_type *tmp = __reserve(new_capacity);

					if (_array) {
						size_t tmp_offset = 0;
						for (size_t i = 0; i < _size; i++) {
							if (start.getPtr() == &_array[i]) {
								tmp_offset = offset;
							}
							new(&tmp[i + tmp_offset]) value_type(_array[i]);
						}
					}
					::operator delete(_array);
					_array = tmp;
					_capacity = new_capacity;
				} else {
					size_type index = start - begin();
					size_type number_of_move_elements = end() - start;
					std::memmove(reinterpret_cast<void *>(&_array[index + offset]), reinterpret_cast<void *>(&_array[index]), number_of_move_elements * sizeof(value_type));
				}
				_size = new_size;
			}

			template <class InputIterator>
			size_type __distance(InputIterator first, InputIterator last)
			{
				size_type distance = 0;
				while (first++ != last)
					distance++;
				return distance;
			}
	};
	template <class T>
  	void swap (vector<T>& x, vector<T>& y)
	{
		x.swap(y);
	}

	template <class T>
	bool operator==(const vector<T>& lhs, const vector<T>& rhs)
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
	bool operator!=(const vector<T>& lhs, const vector<T>& rhs)
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
	bool operator<(const vector<T>& lhs, const vector<T>& rhs)
	{
		unsigned long size = lhs.size();
		if (size > rhs.size()) size = rhs.size();
		for (unsigned long i = 0; i < size; i++)
			if (lhs[i] != rhs[i])
				return (lhs[i] < rhs[i]);
		return lhs.size() < rhs.size();
	
	}

	template <class T>
	bool operator<=(const vector<T>& lhs, const vector<T>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}

	template <class T>
	bool operator>(const vector<T>& lhs, const vector<T>& rhs)
	{
		unsigned long size = lhs.size();
		if (size > rhs.size()) size = rhs.size();
		for (unsigned long i = 0; i < size; i++)
			if (lhs[i] != rhs[i])
				return (lhs[i] > rhs[i]);
		return lhs.size() > rhs.size();
	}

	template <class T>
	bool operator>=(const vector<T>& lhs, const vector<T>& rhs)
	{
		return (lhs > rhs || lhs == rhs);
	}
}

#endif