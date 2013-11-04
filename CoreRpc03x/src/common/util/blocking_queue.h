/* 
 * File:   BlockingQueue.h
 * Author: ZhangJing
 *
 * Created on 2012年12月4日, 下午5:16
 */

#ifndef COMMON_UTILS_BLOCKINGQUEUE_H
#define	COMMON_UTILS_BLOCKINGQUEUE_H

#include <boost/thread/condition.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <boost/circular_buffer.hpp>
#include <assert.h>
namespace util {
    typedef boost::unique_lock<boost::mutex> UniqueLock;
	typedef boost::mutex::scoped_lock ScopedLock;
    template<typename T>
    class BlockingQueue : boost::noncopyable {
    public:

        BlockingQueue(size_t queueSize = 50) : m_queueSize(queueSize), m_buffer(queueSize) {
        }

        void put(const T& t) {
            ScopedLock lg(m_mutex);
            if (m_buffer.full()) {
                m_notFull.wait(lg);
            }
            assert(!m_buffer.full());
            m_buffer.push_back(t);
            m_notEmpty.notify_one();
        }

        bool put(const T& t, int timeout) {
            ScopedLock lg(m_mutex);
            if (m_buffer.full()) {
                if (!m_notFull.timed_wait(lg, boost::posix_time::milliseconds(timeout))) {
                    return false;
                }
            }
            assert(!m_buffer.full());
            m_buffer.push_back(t);
            m_notEmpty.notify_one();
            return true;
        }

        bool take(T& t, int timeout) {
            ScopedLock lg(m_mutex);
            if (m_buffer.empty()) {
                if (!m_notEmpty.timed_wait(lg, boost::posix_time::milliseconds(timeout))) {
                    return false;
                }
            }
            assert(!m_buffer.empty());
            t = m_buffer.front();
            m_buffer.pop_front();
            m_notFull.notify_one();
            return true;
        }
        // bool put(const T& t)

        void take(T& t) {
            ScopedLock lg(m_mutex);
            if (m_buffer.empty()) {
                m_notEmpty.wait(lg);
            }
            assert(!m_buffer.empty());
            t = m_buffer.front();
            m_buffer.pop_front();
            m_notFull.notify_one();
            // return t;
        }
    private:
        boost::mutex m_mutex;
        boost::condition_variable m_notFull;
        boost::condition_variable m_notEmpty;
        boost::circular_buffer<T> m_buffer;
        size_t m_queueSize;
    };
}

#endif	/* COMMON_UTILS_BLOCKINGQUEUE_H */

