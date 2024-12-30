#include <iostream>
#include <map>
#include <vector>
using namespace std;

//享元模式的基类
class FlyweightBody {
public:
    FlyweightBody(string sprite):m_sprite(sprite) {}
    virtual ~FlyweightBody() {}

    virtual void move(int x,int y ,int speed) = 0;
    virtual void draw(int x,int y) = 0;//重绘精灵图

protected:
    string m_sprite;    //精灵图
    //string color;    //颜色
};

//享元类的子类-共享的
class SharedBombBody : public FlyweightBody {
public:
    using FlyweightBody::FlyweightBody;
    ~SharedBombBody() {}

    void move(int x,int y ,int speed) {
        cout <<m_sprite<<"以每小时" <<speed<<"的速度飞到了("<<x<<","<<y<<")处"<< endl;
    }

    void draw(int x,int y) {
        cout << "当前在("<<x<<","<<y<<")的位置处重绘了"<<m_sprite<<"弹体..." << endl;
    }
};

//享元类的子类-不共享的
class UniqueBombBody : public FlyweightBody {
public:
    using FlyweightBody::FlyweightBody;
    ~UniqueBombBody() {}

    void move(int x,int y ,int speed) {
        cout << m_sprite<<"以每小时" <<speed<<"的速度飞到了("<<x<<","<<y<<")处"<< endl;
    }

    void draw(int x,int y) {
        cout << "当前在("<<x<<","<<y<<")的位置处重绘了"<<m_sprite<<"弹体..." << endl;
    }
};

//发射炮弹，享元类挂载的大类，复杂的实际对象
class LaunchBomb {
public:
    LaunchBomb(FlyweightBody* body):m_body(body) {}
    ~LaunchBomb() {}

    void setSpeed(int speed) {
        m_speed = speed;
    }

    void move(int x,int y) {
        m_x = x;
        m_y = y;
        m_body->move(m_x,m_y,m_speed);  //调用享元类的方法,统一接口的思想
        draw();  //调用享元类的方法,统一接口的思想
    }

    void draw() {
        m_body->draw(m_x,m_y);  //调用享元类的方法,统一接口的思想
    }
private:
    FlyweightBody *m_body;
    int m_speed=100;
    int m_x=0;
    int m_y=0;
};

//享元简单工厂类
class BombBodyFactory {
public:
    BombBodyFactory() {}
    //工厂类的析构函数  由工厂类来对享元类的对象进行管理释放
    ~BombBodyFactory() {
        for(auto it = m_map.begin();it != m_map.end();it++) {
            delete it->second;
        }
        m_map.clear();
    }

    FlyweightBody* getFlyweightBody(string key) {
        if(m_map.find(key) == m_map.end()) {
            FlyweightBody* body = nullptr;
            cout<<"创建新的"<<key<<"对象"<<endl;
            body = new SharedBombBody(key);
            m_map[key] = body;
            return body;
        }
        else{
            cout<<"正在复用"<<key<<endl;
            return m_map[key];
        }
    }

protected:
    map<string,FlyweightBody*> m_map;
};

//创建三种型号炮弹，每种有若干个对象对该类对象进行复用
void test() {
    BombBodyFactory factory;
    string key1 ="毒气弹";
    string key2 ="炸弹";
    string key3 ="彩蛋";

    //需要动态数据，即那些具体发射炮弹的类，就是上面的LaunchBomb类
    vector<LaunchBomb*> bombs;
    
    //创建三种型号炮弹，每种有3对象,2个会对该类对象进行复用
    vector<string> keys = {key1+"1",key2+"2",key3+"3",key1+"1",key2+"2",key3+"3",key1+"1",key2+"2",key3+"3"};

    //通过工厂类创建炮弹对象
    for(auto key:keys) {
        FlyweightBody* body = factory.getFlyweightBody(key);
        LaunchBomb* bomb = new LaunchBomb(body);
        //使用随机轨迹
        int x=0,y=0;
        for(int i=0;i<3;i++) {
            x = rand()%1000;
            y = rand()%1000;
            bomb->move(x,y);
        }
        bombs.push_back(bomb);
    }

    //移动炮弹
    for(auto bomb:bombs) {
        bomb->move(100,200);
    }

    for(auto bomb:bombs) {
        delete bomb;
    }

    //创建彩蛋
    //可以采取一个工厂类来创建，也可以直接new
    FlyweightBody* body = new UniqueBombBody("大彩蛋");
    LaunchBomb* bomb = new LaunchBomb(body);
    bomb->move(100,200);
    delete bomb;

    //享元类是与业务类聚合的，业务类的生命周期结束，享元类不一定也就结束了，所以需要手动释放
    delete body;
}

int main() {
    test();
    return 0;
}