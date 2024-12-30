#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

// 抽象观察者（订阅者）
class Observer {
public:
    virtual ~Observer() = default;
    virtual void update(const std::string &message) = 0;
};

// 具体观察者（订阅者）
class Subscriber : public Observer {
private:
    std::string name;
public:
    explicit Subscriber(const std::string &name) : name(name) {}

    void update(const std::string &message) override {
        std::cout << "Subscriber " << name << " received message: " << message << std::endl;
    }

    std::string getName() const { return name; } // 用于识别订阅者
};

// 抽象发布者
class Publisher {
public:
    virtual ~Publisher() = default;
    virtual void subscribe(std::shared_ptr<Observer> observer) = 0;
    virtual void unsubscribe(const std::string &observerName) = 0; // 通过标识符移除
    virtual void notify(const std::string &message) = 0;
};

// 具体发布者
class NewsPublisher : public Publisher {
private:
    std::vector<std::shared_ptr<Observer>> subscribers; // 订阅者列表
public:
    void subscribe(std::shared_ptr<Observer> observer) override {
        subscribers.push_back(observer);
    }

    void unsubscribe(const std::string &observerName) override {
        subscribers.erase(
            std::remove_if(subscribers.begin(), subscribers.end(),
                           [&observerName](const std::shared_ptr<Observer> &subscriber) {
                               auto concreteSubscriber = std::dynamic_pointer_cast<Subscriber>(subscriber);
                               return concreteSubscriber && concreteSubscriber->getName() == observerName;
                           }),
            subscribers.end()
        );
    }

    void notify(const std::string &message) override {
        for (const auto &subscriber : subscribers) {
            subscriber->update(message);
        }
    }
};

int main() {
    // 创建发布者
    auto publisher = std::make_shared<NewsPublisher>();

    // 创建订阅者
    auto subscriber1 = std::make_shared<Subscriber>("Alice");
    auto subscriber2 = std::make_shared<Subscriber>("Bob");

    // 订阅新闻
    publisher->subscribe(subscriber1);
    publisher->subscribe(subscriber2);

    // 发布新闻
    std::cout << "Publishing news..." << std::endl;
    publisher->notify("Breaking News: Observer Pattern in Action!");

    // 取消订阅
    publisher->unsubscribe("Alice");

    // 再次发布新闻
    std::cout << "\nPublishing more news..." << std::endl;
    publisher->notify("Update: Observer Pattern Still Relevant!");

    return 0;
}

