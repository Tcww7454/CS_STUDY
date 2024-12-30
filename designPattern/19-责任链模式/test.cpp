#include <iostream>
#include <string>
#include <memory>

// 请求类型
enum RequestType {
    Leave,       // 请假
    Raise,       // 加薪
    Resignation  // 辞职
};

// 请求对象
struct Request {
    RequestType type;
    std::string description;

    Request(RequestType t, const std::string& desc) : type(t), description(desc) {}
};

// 抽象处理者
class Handler {
protected:
    std::shared_ptr<Handler> next; // 下一个处理者

public:
    virtual ~Handler() = default;

    void setNext(std::shared_ptr<Handler> nextHandler) {
        next = nextHandler;
    }

    void handleRequest(const Request& request) {
        if (canHandle(request)) {
            processRequest(request);
        } else if (next) {
            next->handleRequest(request);
        } else {
            std::cout << "请求未被处理：" << request.description << std::endl;
        }
    }

    virtual bool canHandle(const Request& request) = 0;
    virtual void processRequest(const Request& request) = 0;
};

// 具体处理者：部门主管
class Supervisor : public Handler {
public:
    bool canHandle(const Request& request) override {
        return request.type == Leave;
    }

    void processRequest(const Request& request) override {
        std::cout << "主管批准请求：" << request.description << std::endl;
    }
};

// 具体处理者：部门经理
class Manager : public Handler {
public:
    bool canHandle(const Request& request) override {
        return request.type == Raise;
    }

    void processRequest(const Request& request) override {
        std::cout << "经理批准请求：" << request.description << std::endl;
    }
};

// 具体处理者：CEO
class CEO : public Handler {
public:
    bool canHandle(const Request& request) override {
        return true; // CEO可以处理所有请求
    }

    void processRequest(const Request& request) override {
        std::cout << "CEO批准请求：" << request.description << std::endl;
    }
};

// 主函数
int main() {
    // 创建责任链
    auto supervisor = std::make_shared<Supervisor>();
    auto manager = std::make_shared<Manager>();
    auto ceo = std::make_shared<CEO>();

    supervisor->setNext(manager);
    manager->setNext(ceo);

    // 创建请求
    Request leaveRequest(Leave, "请假一天");
    Request raiseRequest(Raise, "加薪申请");
    Request resignationRequest(Resignation, "辞职申请");

    // 测试责任链
    supervisor->handleRequest(leaveRequest);
    supervisor->handleRequest(raiseRequest);
    supervisor->handleRequest(resignationRequest);

    return 0;
}
