#include <iostream>
#include <pthread.h>
#include <memory>
#include <queue>

template<class T>
class SPSCQueue 
{
private:
    int cap;
    bool exit;
    int blocked_count;
    int counted;
    std::queue<std::unique_ptr<T>> line;
    pthread_mutex_t mtx   = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond_n = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cond_f = PTHREAD_COND_INITIALIZER;
    pthread_cond_t cond_b = PTHREAD_COND_INITIALIZER;

public:
    explicit SPSCQueue(size_t capacity)
        :cap(capacity),exit(false),blocked_count(0){}

    virtual bool Push(std::unique_ptr<T> item)
    {
        pthread_mutex_lock(&mtx); //加锁

        //若满，则阻塞等待
        while(line.size() == cap)
        {
            pthread_cond_wait(&cond_f,&mtx);
            if (exit){
                pthread_mutex_unlock(&mtx);
                return 0;
            }
        }

        //生产，若原来没有就提醒消费者可以消费了
        std::cout<< "pushing" << '\n';
        line.push(std::move(item));
        pthread_cond_signal(&cond_n);
        //cout << "produced item " << *line.back() << "  now have " << line.size() << '\n';

        //别忘记解锁
        pthread_mutex_unlock(&mtx);

        return 1;
    }
    virtual std::unique_ptr<T> pop()
    {
        pthread_mutex_lock(&mtx);
        bool add = false;

        //若空，则阻塞等待生产者生产
        while (line.size()==0)
        {
            blocked_count++;
            std::cout << "blocked_count" << blocked_count<< '\n';
            add = true;
            pthread_cond_signal(&cond_b);
            pthread_cond_wait(&cond_n,&mtx);
            if (exit){
                pthread_mutex_unlock(&mtx);
                return nullptr;
            }
        }

        //消费，若原来是满的就提醒生产者又可以生产了
        std::unique_ptr<T> ret = std::move(line.front());
        line.pop();
        pthread_cond_signal(&cond_f);
        //cout << "consumed item " << *ret << "  now have " << line.size() << '\n';

        if (add)
        {
            blocked_count--;
            add = false;
        }

        pthread_mutex_unlock(&mtx);

        return ret;
    }
    void liberate(void)
    {
        exit = true;
        pthread_cond_broadcast(&cond_n);
        pthread_cond_broadcast(&cond_f);
    }
    void wait_blocked(int ids)
    {
        pthread_mutex_lock(&mtx);
        while(blocked_count <= ids)
        {
            pthread_cond_wait(&cond_b,&mtx);
        }
        pthread_mutex_unlock(&mtx);
    }
    virtual ~SPSCQueue(){
        pthread_mutex_destroy(&mtx);
        pthread_cond_destroy(&cond_n);
        pthread_cond_destroy(&cond_f);
        pthread_cond_destroy(&cond_b);
    }
};
