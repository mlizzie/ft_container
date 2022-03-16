#ifndef REV_ITERATOR_VECTOR_HPP
#define REV_ITERATOR_VECTOR_HPP

#include "iterator_vector.hpp"


namespace ft
{
    template <class T, bool B>
    class rev_iterator_vector
    {

        public:

        typedef T*                                              iterator;
        typedef typename chooseConst<B, T*, const T*> :: type   pointer;
        typedef typename chooseConst<B, T&, const T&> :: type   reference;

        private:

        iterator itr;

        public:

        rev_iterator_vector(iterator itr = 0)
        {
            this->itr = itr;
        }
        rev_iterator_vector(const rev_iterator_vector<T, false> &copy)
        {
             this->itr = copy.getItr();
        }

        rev_iterator_vector(const iterator_vector<T, false>& copy) 
        {
            this->itr = copy.getItr();
        }

        ~rev_iterator_vector()
        {}

        rev_iterator_vector & operator=(const rev_iterator_vector & copy)
        {
            if (copy != *this)
                this->itr = copy.getItr();
            return(*this);
        }

        iterator getItr()const{return (this->itr);};

        reference operator*()const {return(*itr);}
    
        
        pointer operator->() {return(itr);}

        
        rev_iterator_vector & operator++() 
        { 
            itr--;
            return (*this);
        }
        rev_iterator_vector & operator--() 
        { 
            itr++;
            return (*this);
        }
        rev_iterator_vector  operator++(int) 
        { 
            rev_iterator_vector res(itr);
             ++(*this);
            return (res);
        }
        rev_iterator_vector  operator--(int) 
        { 
            rev_iterator_vector res(itr);
            --(*this);
            return (res);
        }

        bool operator==(const rev_iterator_vector & it)const {return(it.itr == this->itr);}
        bool operator!=(const rev_iterator_vector & it)const{return(it.itr != this->itr);}
        bool operator>(const rev_iterator_vector & it)const{return(it.itr > this->itr);}
        bool operator>=(const rev_iterator_vector & it)const {return(it.itr >= this->itr);}
        bool operator<(const rev_iterator_vector & it)const{return(it.itr < this->itr);}
        bool operator<=(const rev_iterator_vector & it)const {return(it.itr <= this->itr);}

        rev_iterator_vector & operator+=(int num)
        {
           this->itr -= num;
            return(*this);
        }
        rev_iterator_vector & operator-=(int num)
        {
            if (num > 0)
                this->itr += num;
            else
                this->itr -= num; 
            return(*this);
        }

        rev_iterator_vector operator+(int num) const
        {
            rev_iterator_vector it(*this);
            it.itr = it.itr - num;
            return (it);
        }
        rev_iterator_vector operator-(int num) const
        {
            rev_iterator_vector it(*this);
             if (num > 0)
                it.itr = it.itr + num;
            else
                it.itr = it.itr - num;
            return (it);
        }

        reference operator[](int num) const
        {
            T* tmp = this->itr;
            tmp = tmp - num;
            return(*tmp);
        }
        long int operator-(rev_iterator_vector it) const
        {
            return(this->itr - it.itr);
        }

        friend rev_iterator_vector operator+(int nb, const rev_iterator_vector& it)
        {
            rev_iterator_vector newIt(it);
            return (newIt += nb);
        }

        friend rev_iterator_vector operator-(int nb, const rev_iterator_vector& it)
        {
            rev_iterator_vector newIt(it);
            return (newIt -= nb);
        }

    };
}
#endif