#ifndef _H_COMMON_UTIL_SEQUENCE_GENERATOR_H
#define _H_COMMON_UTIL_SEQUENCE_GENERATOR_H
#include <boost/thread.hpp>
namespace util{
	
class SequenceGenerator {
public:

    SequenceGenerator(unsigned int min = MIN_ID, unsigned int max = MAX_ID) : m_min(min), m_max(max) {
        if (m_min <= SELF_ID)
            m_min = SELF_ID + 1;
        m_idseq = m_min;
    }

    enum {
        INVALID_ID = 0x00000000
    };

    enum {
        SELF_ID = 0x00000001
    };

    enum {
        MIN_ID = 0x00001000
    };

    enum {
        MAX_ID = 0x8FFFFFFF
    };

    unsigned int next() {
       // boost::mutex::scoped_lock lock(the_mutex);
        if (++m_idseq >= m_max)
            m_idseq = m_min;
        return m_idseq;
    }

private:
    unsigned int m_min;
    unsigned int m_max;
    unsigned int m_idseq;
    //mutable boost::mutex the_mutex;
};
}
#endif