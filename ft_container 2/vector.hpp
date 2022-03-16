#ifndef VECTOR_HPP
# define VECTOR_HPP

# include <iostream>
# include "iterator_vector.hpp"
# include "rev_iterator_vector.hpp"
# include "other.hpp"

namespace ft
{
    template<class T, class Allocate = std :: allocator<T> >
    class vector
    {


        public:

        typedef T*                              pointer;
        typedef size_t                          size_type;
        typedef Allocate                        allocator_type;
        typedef T                               value_type;
        typedef T&                              reference;
        typedef const T&                        const_reference;
        typedef iterator_vector<T, false>       iterator;
        typedef iterator_vector<T, true>        const_iterator;
        typedef rev_iterator_vector<T, false>   reverse_iterator;
        typedef rev_iterator_vector<T, true>    const_reverse_iterator;
        typedef long int                        difference_type;

        private:
        
        allocator_type	_alloc;
        pointer			_array;
		size_type		_size;
		size_type		_capacity;

        public:

        vector(const allocator_type& alloc = allocator_type())
        {
            this->_alloc = alloc;
            this->_size = 0;
            this->_capacity = 0; 
        }

        vector(size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
        {
            this->_alloc = alloc;
            this->_size = n;
            this->_capacity = n;
            if (_capacity > 0)
                _array = _alloc.allocate(_capacity);
            for (size_type i = 0; i < _size; i++)
                _alloc.construct(&_array[i], val);
        }
                            
        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
            typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0) : _alloc(alloc), _size(0)
        {
            InputIterator tmp(first);
            while (tmp++ != last)
                _size++;    
            _capacity = _size;
            if (_capacity > 0)
                _array = _alloc.allocate(_capacity);
            for (int i = 0; first != last; ++first, ++i)
                _alloc.construct(&_array[i], *first);
        }
                    
            
        vector(const vector& x) : _size(x._size), _capacity(x._capacity)
        {
            _alloc = allocator_type();
            if (_capacity > 0)
            {
                this->_array = _alloc.allocate(_capacity);
                for (size_type i = 0; i < x.size(); i++)
                    _alloc.construct(&_array[i], x[i]);
            }
        }
        

        vector& operator= (const vector& x)
        {
            if ( this != &x ) 
            {
                if (this->_capacity)
                    _alloc.deallocate(this->_array, this->_capacity);
                this->_capacity = x._capacity;
                this->_size = x._size;
                if (x._capacity)
                    this->_array = _alloc.allocate(x._capacity);
                for (size_type i = 0; i < this->_size; i++)
                    _alloc.construct(&_array[i], x._array[i]);
            }
            return (*this);
        }

        ~vector()
        {
            for (size_type i = 0; i < _size; i++)
                _alloc.destroy(&(_array[i]));
            if (_capacity)
                _alloc.deallocate(_array, _capacity);
        }
        // - Iterators:

        iterator begin()const{return(iterator(_array));}
        iterator end() const {return(iterator(_array + _size));}
        reverse_iterator rbegin(){return(reverse_iterator(_array + _size - 1 ));}
        reverse_iterator rend()  {return(reverse_iterator(_array - 1));}
        const_reverse_iterator rbegin() const   { return const_reverse_iterator(_array + _size - 1); }
        const_reverse_iterator rend() const   { return const_reverse_iterator(_array - 1); }
        const_iterator cbegin()const{return(const_iterator(_array));}
        const_iterator cend()const  {return(const_iterator(_array + _size));}
        allocator_type  get_allocator() const{ return (_alloc);}
        
        //size capacity
        size_type size() const {return (this->_size);}
        size_type capacity() const {return (this->_capacity);}
        size_type max_size()const {return(_alloc.max_size());}
        bool empty() const {return(_size == 0);}
        
        void reserve(size_type n)
        {
            if (n > max_size())
                throw std::out_of_range("exception");
            if (n > _capacity)
                reallocateVec(n);
        }

        void resize (size_type n, const value_type & val = value_type())
        {
            while (n < _size)
                pop_back();
            // while (n > _size)
            //     push_back(val);
            insert(this->end(), n - _size, val);
        }

        // Element access
        reference at(size_type n)
        {
            if (n >= _size || n < 0)
                throw std::out_of_range("vector");
            return _array[n];
        }

        reference operator[](size_type const  n){return *(_array + n);}
        const_reference operator[](size_type const  n) const {return *(_array + n);}
        pointer data() const {return(_array);}
        reference front() const {return(*_array);}
        reference back() const {return(_array[_size ? _size - 1 : 0]);}
       
       // --- 
        void pop_back()
        {
            if (_size)
                _alloc.destroy(&(_array[--_size]));
        }
        
        void push_back(const value_type &value)
        {
            if (_size + 1 > _capacity)
                reallocateVec(!_capacity ? 1 : _capacity * 2);
            _alloc.construct(&_array[_size++], value);
        }

       void clear()
       {
            iterator begin = this->begin();
            iterator end = this->end();
            while(begin != end)
            {
                _alloc.destroy(&(*begin));
                begin++;
            }
            _size = 0;
       }

       //INSERT
       void insert(iterator position, size_type n, const value_type &val)
       {
            size_type index;

            if ( n < 0 || position < this->begin() || position > this->end())
                return ;
            index = position - this->begin();
            if ((_size + n) > _capacity)
            {
                if (_capacity * 2 > _size + n )
                    reallocateVec((!_capacity ? 1 : _capacity * 2));
                else 
                    reallocateVec(_capacity + n);
            }
            iterator newPosition(&_array[index]);
            if (newPosition != this->end())
                moveElementsToTheRight(newPosition, n);
            try
            {
                for (size_type i = 0; i < n; i++)
                {
                    _alloc.construct(&_array[index++], val);
                    _size++;
                }
                
            }
            catch(...)
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(&(_array[i]));
                _size = 0;
                _alloc.deallocate(_array, _capacity);
                _capacity = 0;
                throw std :: exception();
            }
       }


       iterator insert(iterator position, const value_type &val)
       {
           difference_type index;

           index = position - this->begin();
           insert(position, 1, val);
           return(&_array[index]);
       }

       template <class InputIterator>
        void insert (iterator position, InputIterator first, InputIterator last, typename  enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
        {
            size_type index;
            size_type n = 0;
            InputIterator copy(first);

            if (position < this->begin() || position > this->end())
                return ;
            while (copy != last)
            {
                n++;
                copy++;
            }
            index = position - this->begin();
            if ((_size + n) > _capacity)
            {
                if (_capacity * 2 > _size + n )
                    reallocateVec((!_capacity ? 1 : _capacity * 2));
                else 
                    reallocateVec(_capacity + n);
            }
            iterator newPosition(&_array[index]);
            
            if (newPosition != this->end())
                moveElementsToTheRight(newPosition, n);
            try
            {
                for (size_type i = 0; i < n; i++)
                {
                    _alloc.construct(&_array[index++], *(first++));
                    _size++;
                }
            }
            catch(...)
            {
                for (size_type i = 0; i < _size; i++)
                    _alloc.destroy(&(_array[i]));
                _size = 0;
                _alloc.deallocate(_array, _capacity);
                _capacity = 0;
                throw std :: exception();
            
            }
            
        }

        //asign
        template <class InputIterator>
        void assign (InputIterator first, InputIterator last,
                    typename ft::enable_if<!ft::is_integral<InputIterator>::value >::type* = 0)
        {
            size_type n = 0;
            InputIterator itr(first);
            while (itr++ != last)
                n++;
            this->clear();
            if (n > _capacity)
                reallocateVec((n));
            insert(this->begin(), first, last);
        }

        void assign (size_type n, const value_type& val)
        {
            this->clear();
            if (n > _capacity)
                reallocateVec((n));
            _size = n;
            for (size_type i = 0; i < n; i++)
                _array[i] = val;
        }

        //erase
        iterator erase (iterator first)
        {
            size_type index = first - this->begin();

            if (first == this->end())
                return (first);
            _alloc.destroy(&(_array[index]));
            for(; index  != this->size(); index++)
                _array[index] = _array[index + 1];
            _size -= 1;
            return(first);
        }

        iterator erase (iterator first, iterator last)
        {
            size_type   index;
            size_type   end;
            size_type   size = this->size() ;

          if (first == last || first == this->end() || last > this->end())
                return (first);
            
            index =  first - this->begin()  ;
            end =   last -  this->begin();
            for(size_type i = 0; i  + index < end;i++)   
                 _alloc.destroy(&(_array[index + i]));
            _size -= end - index;
            while (end < size)
            {
                _array[index++] = _array[end];
                _alloc.destroy(&(_array[end]));
                end++;
            }
            return (first);
        }

        void swap(vector& x)
        {
            std :: swap (this->_array, x._array);
            std :: swap (this->_size, x._size);
            std :: swap (this->_capacity, x._capacity);
            std :: swap (this->_alloc, x._alloc);
        }

        //operator
         
         bool operator==(const vector & another) const
         {
            if (this->size() != another.size())
                return(false);
            for (size_type i = 0; i < this->size(); i++)
            {
               if ((*this)[i] != another[i])
                    return (false);
            }
            return (true);
         }
         bool operator!=(const vector & another) const
         {
            return(!(*this == another));
         }
        
        private:

        void moveElementsToTheRight(iterator position, size_type n)
        {
            size_type index = position - this->begin();
            size_type end = this->size() - 1;
            size_type size = this->size();
            
            for (size_type i = 0; index < end - i; i++)
            {
                _array[size  + n - i - 1]= _array[end - i];
                _alloc.destroy(&(_array[end - i]));
            }
        }

        void reallocateVec(size_type newCapacity)
        {
            if (newCapacity > max_size())
                throw std::out_of_range("exception");
            pointer newVector = _alloc.allocate(newCapacity);
            for (size_type i = 0; i < _size; i++)
                _alloc.construct(&newVector[i], _array[i]);
            this->~vector();
            _capacity = newCapacity;
            _array = newVector;
        }

    };

    template < class T, class Alloc>
 	bool operator<  (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) 
    {
        return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end())); 
    }
    template < class T, class Alloc>
 		bool operator>  (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) { return (operator<(rhs, lhs)); }
	template < class T, class Alloc>
 		bool operator<=  (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) { return (!operator<(rhs, lhs)); }
	template < class T, class Alloc>
 		bool operator>=  (vector<T,Alloc>& lhs, vector<T,Alloc>& rhs) { return (!operator<(lhs, rhs)); }
}
#endif