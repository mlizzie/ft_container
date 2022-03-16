#ifndef ITERATOR_VECTOR_HPP
#define ITERATOR_VECTOR_HPP



#include "other.hpp"

namespace ft
{
    template <class T, bool B>
    class iterator_vector
    {

        public:

        typedef T*                                              iterator;
        typedef typename chooseConst<B, T*, const T*> :: type   pointer;
        typedef typename chooseConst<B, T&, const T&> :: type   reference;

        private:

        iterator itr;

        public:

        iterator_vector(iterator itr = 0)
        {
            this->itr = itr;
        }
        iterator_vector(const iterator_vector<T, false> &copy)
        {
             this->itr = copy.getItr();
        }
        ~iterator_vector()
        {}

        iterator_vector & operator=(const iterator_vector & copy)
        {
            if (copy != *this)
                this->itr = copy.getItr();
            return(*this);
        }

        iterator getItr()const{return (this->itr);};

        reference operator*()const {return(*itr);}
    
        
        pointer operator->() {return(itr);}

        
        iterator_vector & operator++() 
        { 
            itr++;
            return (*this);
        }
        iterator_vector & operator--() 
        { 
            itr--;
            return (*this);
        }
        iterator_vector  operator++(int) 
        { 
            iterator_vector res(itr);
             ++(*this);
            return (res);
        }
        iterator_vector  operator--(int) 
        { 
            iterator_vector res(itr);
            --(*this);
            return (res);
        }

        bool operator==(const iterator_vector & it)const {return(it.itr == this->itr);}
        bool operator!=(const iterator_vector & it)const{return(it.itr != this->itr);}
        bool operator>(const iterator_vector & it)const{return(it.itr < this->itr);}
        bool operator>=(const iterator_vector & it)const {return(it.itr <= this->itr);}
        bool operator<(const iterator_vector & it)const{return(it.itr > this->itr);}
        bool operator<=(const iterator_vector & it)const {return(it.itr >= this->itr);}

        iterator_vector & operator+=(int num)
        {
           this->itr += num;
            return(*this);
        }
        iterator_vector & operator-=(int num)
        {
            if (num > 0)
                this->itr -= num;
            else
                this->itr += num; 
            return(*this);
        }

        iterator_vector operator+(int num) const
        {
            iterator_vector it(*this);
            it.itr = it.itr + num;
            return (it);
        }
        iterator_vector operator-(int num) const
        {
            iterator_vector it(*this);
             if (num > 0)
                it.itr = it.itr - num;
            else
                it.itr = it.itr + num;
            return (it);
        }

        reference operator[](int num) const
        {
            T* tmp = this->itr;
            tmp = tmp + num;
            return(*tmp);
        }
        long int operator-(iterator_vector it) const
        {
            return(this->itr - it.itr);
        }

        friend iterator_vector operator+(int nb, const iterator_vector& it)
        {
            iterator_vector newIt(it);
            return (newIt += nb);
        }

        friend iterator_vector operator-(int nb, const iterator_vector& it)
        {
            iterator_vector newIt(it);
            return (newIt -= nb);
        }

    };
}
#endif