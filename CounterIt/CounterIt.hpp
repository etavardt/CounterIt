// CounterIt.hpp
//
// Author: Thomas C. Etavard (https://github.com/etavardt)
// Date: 02/07/2023
// 
// GitHub link: https://github.com/etavardt/CounterIt
//
// An iterator that counts instead of iterating over objects.
//
// Usage:
//     // One Example:
//     #include <execution>
//     #include "CounterIt.hpp"
//     ...
//     Kewl::Counter count( startValue, endValue );
//     std::for_each(std::execution::par, count.begin(), count.end(), []( const int& i ) { std::cout << " " << i; });
// 
// This could return an out of order count since it is a for_each loop where the tasks are ran in parrallel asynchronous
// but each task needs to know the value(i in this case) it will work with. Do not use this for_each if you need the 
// order to be synchronous.
//

#pragma once

#include <iterator>
#include <cassert>

namespace Kewl {

    class Counter {
    private:
        class iterator {
            long m_start = 0;
            long m_end = 0;
            long m_num = 0;
            bool m_rev = false;
        public:
            using iterator_category = std::forward_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = long;
            using pointer           = const long*;
            using reference         = long;

            iterator() = default;
            explicit iterator( value_type _num, value_type _start, value_type _end, bool _rev = 0 ) : m_num( _num ), m_start( _start ), m_end( _end ), m_rev( _rev ) {}

            iterator& operator++() {
                assert( m_num >= std::min( m_start, m_end ) && "Out of range: less than the min bound!" );
                assert( m_num <= std::max( m_start, m_end ) && "Out of range: greater than the max bound!" );
                m_num = m_rev ? m_num - 1 : m_num + 1;
                return *this;
            }
            iterator operator++( int ) { iterator retval = *this; ++(*this); return retval; }
            bool operator==( iterator other ) const { return m_num == other.m_num; }
            bool operator!=( iterator other ) const { return !(*this == other); }
            reference operator*() const { return m_num; }
        };

        bool m_rev = false;
        long m_start = 0;
        long m_end = 0;
    public:
        using Iterator = iterator;
        Iterator begin()  { return Iterator( m_start, m_start, m_end, m_rev ); }
        Iterator first()  { return Iterator( m_start, m_start, m_end, m_rev ); }
        Iterator last()   { return Iterator( m_end, m_start, m_end, m_rev ); }
        Iterator end()    { return Iterator( (m_rev ? m_end - 1 : m_end + 1), m_start, m_end, m_rev ); }
        Iterator rbegin() { return Iterator( m_end, m_end, m_start, !m_rev ); }
        Iterator rfirst() { return Iterator( m_end, m_end, m_start, !m_rev ); }
        Iterator rlast()  { return Iterator( m_start, m_start, m_end, !m_rev ); }
        Iterator rend()   { return Iterator( (!m_rev ? m_start - 1 : m_start + 1), m_start, m_end, !m_rev ); }

        Counter() = delete;
        Counter( long _end ) :
            m_start( 0 ),
            m_end( _end ),
            m_rev( 0 > _end ) {}
        Counter( long _start, long _end ) :
            m_start( _start ),
            m_end( _end ),
            m_rev( _start > _end ) {}
        ~Counter() {};
        Counter( const Counter& ) = delete;
        Counter( const Counter&& ) = delete;
        const Counter& operator=( const Counter& ) = delete;
        const Counter& operator=( const Counter&& ) = delete;
    };
} // namespace Kewl
