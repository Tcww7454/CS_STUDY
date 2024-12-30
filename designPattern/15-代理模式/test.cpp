#include <iostream>
using namespace std;

//代理模式中存在三个角色：抽象主题角色、真实主题角色和代理主题角色。

//抽象主题角色：声明真实主题和代理主题的共同接口。
class Communication {
public:
    virtual void commuication() = 0;
    virtual ~Communication() {}
};

//幕后人：定义了代理角色所代理的事物
class Speaker : public Communication { 
public:
    void commuication() {
        cout << "Speaker is speaking." << endl;
    }
};

//代理主题角色：保存一个引用使得代理可以访问实体，并提供一个与真实主题角色相同的接口，这样代理就可以用来代替真实主题。
class Proxy : public Communication {
public:
    Proxy() {
        is_Start = true;//只要创建了就是开启代理
        speaker = new Speaker();
    }
    bool isStart() {
        return is_Start;
    }
    void setStart(bool isStart) {
        is_Start = isStart;
    }
    void commuication() {
        if (is_Start) {
            cout<<"开始代理"<<endl;
            speaker->commuication();
        }
        else{
            cout<<"没有代理权限"<<endl;
        }
    }
    ~Proxy() {
        delete speaker;
    }
private:
    bool is_Start;
    Speaker* speaker;
};

int main() {
    //直接绕过代理
    Speaker* speaker = new Speaker();
    speaker->commuication();
    delete speaker;
    cout << "----------------" << endl;

    //通过代理
    Proxy* proxy = new Proxy();
    proxy->setStart(false);
    proxy->commuication();
    cout << "----------------" << endl;
    proxy->setStart(true);
    proxy->commuication();
    return 0;
}