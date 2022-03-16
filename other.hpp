#ifndef OTHER_HPP
#define OTHER_HPP

namespace ft
{
    
    template <bool isConst, typename isFalse, typename isTrue>
    struct chooseConst {};

   
    template <typename isFalse, typename isTrue>
    struct chooseConst<false, isFalse, isTrue>
    {
        typedef isFalse type;
    };

   
    template <typename isFalse, typename isTrue>
    struct chooseConst<true, isFalse, isTrue>
    {
        typedef isTrue type;
    };

    template <bool B>
    struct enable_if {};

    template <>
    struct enable_if<true> { typedef int type; };


    template <typename T>
    struct is_integral{ static const bool value = false;};

    template <>
    struct is_integral<short> { static const bool value = true; };

    template <>
    struct is_integral<unsigned char> { static const bool value = true; };

    template <>
    struct is_integral<unsigned short> { static const bool value = true; };

    template <>
    struct is_integral<unsigned int> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long> { static const bool value = true; };

    template <>
    struct is_integral<unsigned long long> { static const bool value = true; };

    template <>
    struct is_integral<int> { static const bool value = true; };
    
    template <>
    struct is_integral<bool> { static const bool value = true; };
        
    template <>
    struct is_integral<char> { static const bool value = true; };

    template <>
    struct is_integral<long> { static const bool value = true; };

    template <>
    struct is_integral<long long> { static const bool value = true; };

    template <class InputIterator1, class InputIterator2>
    bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
    InputIterator2 first2, InputIterator2 last2) 
    {
        while (first1 != last1) 
        {
            if (first2 == last2 || *first2 < *first1) 
                return false;
        else if (*first1 < *first2) 
            return true;
        ++first1;
        ++first2;
        }
        return (first2 != last2);
    }
    
    template <typename T1, typename T2>
    class pair
    {
        public:

        pair() : first(), second() {};
        
        pair(const T1& a, const T2& b) : first(a), second(b) {};
        
        pair(const pair<T1, T2>& copy) : first(copy.first), second(copy.second) {};
        
        template <typename U, typename V>
        pair(const pair<U, V>& copy) : first(copy.first), second(copy.second) {};

        ~pair() {};
        pair& operator=(const pair& assign)
        {
            if (this != &assign)
            {
                first = assign.first;
                second = assign.second;
            }
            return (*this);
        }
        T1 first;
        T2 second;
            
    }; 
}
#endif