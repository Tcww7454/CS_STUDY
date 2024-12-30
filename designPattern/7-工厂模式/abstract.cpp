#include <iostream>
using namespace std;

//船体
class shipBody
{
public:
    virtual string getBody()=0;
    virtual ~shipBody(){}
};

//木头船体
class wodenBody:public shipBody
{
public:
    string getBody()override
    {
        return string("used wooden body");
    }
};

//钢铁船体
class ironBody:public shipBody
{
public:
    string getBody()override
    {
        return string("used iron body");
    }
};

//金属船体
class metalBody:public shipBody
{
public:
    string getBody()override
    {
        return string("used mental body");
    }
};

//引擎类基类
class Engine
{
public:
    virtual string getEngine()=0;
    virtual ~Engine(){}
};

class human:public Engine
{
public:
    string getEngine()override
    {
        return string("used human engine");
    }
};

class diesel:public Engine
{
public:
    string getEngine()override
    {
        return string("used diesel engine");
    }
};

class nuclear:public Engine
{
public:
    string getEngine()override
    {
        return string("used nuclear engine");
    }
};

//武器系统
class Weapon
{
public:
    virtual string getWeapon()=0;
    virtual ~Weapon(){}
};

class gun:public Weapon
{
   public:
   string getWeapon()override
   {
    return "used gun weapon";
   } 
};

class cannon:public Weapon
{
   public:
   string getWeapon()override
   {
    return "used cannon weapon";
   } 
};

class laser:public Weapon
{
   public:
   string getWeapon()override
   {
    return "used laser weapon";
   } 
};

//船
class ship
{
public:
    ship(shipBody* body,Engine* engine,Weapon* weapon)
    :m_body(body),m_engine(engine),m_weapon(weapon){};
    //这里通过析构函数能够确定这个类与子类之间是组合还是聚合关系
    //这里直接在析构中删除意味着就是生命周期绑定，是组合关系
    string getProperty()
    {
        string temp=m_body->getBody()+" "+
                    m_engine->getEngine()+" "+
                    m_weapon->getWeapon();
        return temp;
    }
    ~ship()
    {
        delete m_body;
        delete m_engine;
        delete m_weapon;
    }

protected:
    shipBody* m_body;
    Engine* m_engine;
    Weapon* m_weapon;
};

class factor
{
public:
    virtual ship* createShip()=0;
    virtual ~factor(){}
};

class BasicShip:public factor
{
public:
    ship* createShip()override
    {
        shipBody* body=new wodenBody;
        Engine* engine=new human;
        Weapon* weapon=new gun;
        ship* m_ship=new ship(body,engine,weapon);
        cout<<"Basic ship had been made."<<endl;
        return m_ship;
    }
};

class StandardShip:public factor
{
public:
    ship* createShip()override
    {
        shipBody* body=new ironBody;
        Engine* engine=new diesel;
        Weapon* weapon=new cannon;
        ship* m_ship=new ship(body,engine,weapon);
        cout<<"Standard ship had been made."<<endl;
        return m_ship;
    }
};

class UltimateShip:public factor
{
public:
    ship* createShip()override
    {
        shipBody* body=new metalBody;
        Engine* engine=new nuclear;
        Weapon* weapon=new laser;
        ship* m_ship=new ship(body,engine,weapon);
        cout<<"Ultimate ship had been made."<<endl;
        return m_ship;
    }
};

int main()
{
    factor* m_factory=new UltimateShip;
    ship* m_ship=m_factory->createShip();
    cout<<m_ship->getProperty();

    delete m_ship;
    delete m_factory;

    return 0;
}