#if 1

#include<iostream>
#include<mutex>
#include <atomic>
#include <queue>
#include <climits>
#include <thread>

using namespace std;

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

    //是否为空
    bool isempty()
    {
        //互斥锁挂载到了这个lock_guard的对象上
        lock_guard<mutex> locker(m_mutex);
        bool flag=m_date.empty();
        return flag;
    }
         
    //添加任务
    void addTask(int node)
    {
        lock_guard<mutex> locker(m_mutex);
        m_date.push(node);
    }
    //删除任务
    bool popTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if(isempty())
            return false;
        m_date.pop();
        return true;
    }
    //取出任务(不删除任务)
    int takeTask()
    {
        lock_guard<mutex> locker(m_mutex);
        if(isempty())
            return INT_MIN;
            return m_date.front();
    }

private:
    taskQueue()=default;
    static taskQueue* m_task;
    queue<int> m_date;
    mutex m_mutex;
};
taskQueue* taskQueue::m_task=new taskQueue;
#endif


int main()
{
    taskQueue* taskOnly=taskQueue::getPointer();
    
    //生产者
    thread t1 ([=]()
    {
        for(int i=0;i<10;i++)
        {
            taskOnly->addTask(i*100);
            cout<<"+++ push date: "<<i*100<<", threadID: "
                <<this_thread::get_id()<<endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });
    

    //消费者
    thread t2 ([=]()
    {
        this_thread::sleep_for(chrono::milliseconds(100));
        while(!taskOnly->isempty())
        {
            int num=taskOnly->takeTask();
            cout<<"+++ take date: "<<num<<", threadID: "
                <<this_thread::get_id()<<endl;
            taskOnly->popTask();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    });

    t1.join();
    t2.join();

    return 0;
}
#endif

#if 0

#include <iostream>
#include <mutex>
#include <queue>
#include <thread>
#include <condition_variable>

using namespace std;

class taskQueue {
public:
    // 单例获取方法
    static taskQueue* getPointer() {
        static taskQueue m_task;
        return &m_task;
    }

    // 添加任务
    void addTask(int node) {
        {
            lock_guard<mutex> locker(m_mutex);
            m_date.push(node);
        }
        m_cv.notify_one(); // 通知消费者
    }

    // 等待并取出任务
    int waitAndTakeTask() {
        unique_lock<mutex> locker(m_mutex);
        m_cv.wait(locker, [this] { return !m_date.empty(); }); // 阻塞直到队列非空
        int task = m_date.front();
        m_date.pop();
        return task;
    }

private:
    taskQueue() = default;
    queue<int> m_date;
    mutex m_mutex;
    condition_variable m_cv; // 条件变量
};

int main() {
    taskQueue* taskOnly = taskQueue::getPointer();

    // 生产者线程
    thread producer([=]() {
        for (int i = 0; i < 10; i++) {
            taskOnly->addTask(i * 100);
            cout << "+++ Produced task: " << i * 100
                 << ", ThreadID: " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(500));
        }
    });

    // 消费者线程
    thread consumer([=]() {
        for (int i = 0; i < 10; i++) {
            int task = taskOnly->waitAndTakeTask(); // 等待并取任务
            cout << "--- Consumed task: " << task
                 << ", ThreadID: " << this_thread::get_id() << endl;
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    });

    producer.join();
    consumer.join();

    return 0;
}


#endif