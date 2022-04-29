#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <list>
#include <cstdio>
#include <exception>
#include <pthread.h>
#include "locker.h"

template<typename T>
class threadpool {
    public:
        threadpool(int thread_number = 0, int max_requests = 10000);
        ~threadpool();
        bool append(T* request);

    private:
        static void* worker(void* arg);
        void run();    

    private:
        int m_thread_number;
        pthread_t* m_threads;

        int m_max_requests;
        std::list<T*> m_workqueue;

        locker m_queuelocker;
        sem m_queuestat;

        bool m_stop;
};


#endif