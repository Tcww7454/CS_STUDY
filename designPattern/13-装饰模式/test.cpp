#include <iostream>
using namespace std;

//战士的基类    
//抽象接口类，以及一些十分基本的属性，这些不会很影响原则
class Solider
{
public:
    Solider(){}
    Solider(string name):m_name(name){}
    string getName(){return m_name;}
    virtual void fight()=0;
    virtual ~Solider(){};
protected:
    string m_name="";
};

//恶魔果实基类
class evil: public Solider
{
public:
    void setSolider(Solider* solider)
    {
        m_solider=solider;
    }

protected:
    Solider* m_solider=nullptr;
};

//黑胡子
class Teach : public Solider
{
    public:
        using Solider::Solider;

        void fight()
        {
            cout<<m_name<<" with great power."<<endl;
        }
};

//暗暗果实
class DarkFruit:public evil
{
public:
    using evil::Solider;

    void fight()override
    {
        m_solider->fight();
        cout<<m_solider->getName()<<"eat darkfruit,has dark ability."<<endl;
        warning();
    }
private:
    void warning()
    {
        cout<<m_solider->getName()<<" you ate dark fruit,and you can't move when you using ability.";
    }
};

void text()
{
    Teach* obj=new Teach("黑胡子");
    obj->fight();
    evil* dark=new DarkFruit;
    dark->setSolider(obj);
    cout<<"==========="<<endl;
    dark->fight();
    delete dark;
    cout<<endl<<"==========="<<endl;
    obj->fight();
    delete obj;
}


int main()
{
    text();
    return 0;
}