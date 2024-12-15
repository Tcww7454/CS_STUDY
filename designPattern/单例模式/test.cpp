#include<iostream>
#include<mutex>
#include <atomic>

using namespace std;

#if 0
class taskQueue
{
public:
    taskQueue(const taskQueue& t)=delete;
    taskQueue& operator=(const taskQueue& t)=delete;

    void print(){cout<<"单例模式，启动！！！！！";}
    static taskQueue* getPointer()
    {
        taskQueue* task=m_task.load();
        if(m_task==nullptr)
        {
            m_mutex.lock();
            task=m_task.load();
            if(m_task==nullptr)
            {
                task=new taskQueue;
                m_task.store(task);
            }
            m_mutex.unlock();
        }
        return task;
    }

private:
    taskQueue()=default;
    //static taskQueue* m_task;
    static atomic <taskQueue*> m_task;
    static mutex m_mutex;
};
//taskQueue* taskQueue::m_task=new taskQueue;
atomic<taskQueue*>taskQueue::m_task;
mutex taskQueue::m_mutex;

#endif

#if 1
class taskQueue
{
public:
    taskQueue(const taskQueue& t)=delete;
    taskQueue& operator=(const taskQueue& t)=delete;

    void print(){cout<<"单例模式，启动！！！！！";}
    static taskQueue* getPointer()
    {
        static taskQueue m_task;
        return &m_task;
    }

private:
    taskQueue()=default;
    static taskQueue* m_task;
};
#endif


int main()
{
    taskQueue* taskOnly=taskQueue::getPointer();
    taskOnly->print();

    return 0;
}