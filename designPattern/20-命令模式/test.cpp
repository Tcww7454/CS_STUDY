#include <iostream>
#include <string>
#include <memory>
#include <vector>

// Receiver: 后厨
class Kitchen {
public:
    void prepareDish(const std::string& dish) {
        std::cout << "Kitchen is preparing: " << dish << std::endl;
    }
};

// Command: 命令接口
class Command {
public:
    virtual ~Command() = default;
    virtual void execute() = 0;
};

// ConcreteCommand: 具体命令类
class PrepareDishCommand : public Command {
private:
    Kitchen* kitchen;
    std::string dish;
public:
    PrepareDishCommand(Kitchen* k, const std::string& d) : kitchen(k), dish(d) {}
    void execute() override {
        kitchen->prepareDish(dish);
    }
};

// Invoker: 服务员
class Waiter {
private:
    std::vector<std::shared_ptr<Command>> orders;
public:
    void takeOrder(std::shared_ptr<Command> command) {
        orders.push_back(command);
    }
    void sendOrders() {
        for (const auto& order : orders) {
            order->execute();
        }
        orders.clear();
    }
};

// Client: 客户端
int main() {
    // 创建接收者
    Kitchen kitchen;

    // 创建具体命令
    auto steakCommand = std::make_shared<PrepareDishCommand>(&kitchen, "Steak");
    auto pastaCommand = std::make_shared<PrepareDishCommand>(&kitchen, "Pasta");

    // 创建调用者
    Waiter waiter;
    waiter.takeOrder(steakCommand);
    waiter.takeOrder(pastaCommand);

    // 服务员发送订单
    waiter.sendOrders();

    return 0;
}
