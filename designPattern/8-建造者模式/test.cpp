#include <iostream>
#include <vector>
#include <map>
using namespace std;

/*
    定义与船相关的类
    定义与生产器相关的类
    添加管理者类->根据提出需求的不同产出不同的产品
    编写代码
*/

//定义船相关的类,这里我使用不同类别储存，不使用多态

//这里其实就是一些具体的工厂，就是一些组装厂，不考虑生产零件
class SunnyShip
{
public:
    void addParts(string name)
    {
        m_parts.push_back(name);
    }
    void showParts()
    {
        for(auto item:m_parts)
        {
            cout<<item<<" ";
        }
        cout<<endl;
    }
private:
    vector<string>m_parts;
};

class MerryShip
{
public:
    //keys为parts
    void assemble(string name,string parts)
    {
        m_parts.insert(make_pair(parts,name));
    }
    void showParts()
    {
        for(auto item:m_parts)
        {
            cout<<item.first<<":"<<item.second<<" ";
        }
        cout<<endl;
    }
private:
    map<string,string>m_parts;
};

//定义相关生成器类
class ShipBuilder
{
public:
    virtual void reset()=0;
    virtual void buildBody()=0;
    virtual void buildEngine()=0;
    virtual void buildWeapon()=0;
    virtual void buildInterior()=0;
    virtual ~ShipBuilder(){}
};

class SunnyBuilder:public ShipBuilder
{
public:
    SunnyBuilder(){
        reset();
    }
    //我们需要考虑的是一个建造者类可以多次复用
    //当一个产品交付后，一个工厂是不需要再对其负责的
    //所以我们考虑情况成员即可，不必删除对象
    //那么我们需要一个方法将现有对象传给需求发出者
    SunnyShip* getShip()
    {
        SunnyShip* ship=m_sunny;
        m_sunny=nullptr;
        return ship;
    }
    //这个reset方法必须在上面那个方法调用后再调用，不然你建造它干嘛
    void reset()override
    {
        m_sunny=new SunnyShip;
    }
    void buildBody()override
    {
        m_sunny->addParts("body is tree");
    }
    void buildEngine()override
    {
        m_sunny->addParts("engine is cola");
    }
    void buildWeapon()override
    {
        m_sunny->addParts("weapon is gun");
    }
    void buildInterior()override
    {
        m_sunny->addParts("interior is rare");
    }
    ~SunnyBuilder()
    {
        if(m_sunny)
        {
            delete m_sunny;
        }
    }

private:
    SunnyShip* m_sunny;
};

class MerryBuilder:public ShipBuilder
{
public:
    MerryBuilder(){
        reset();
    }
    //我们需要考虑的是一个建造者类可以多次复用
    //当一个产品交付后，一个工厂是不需要再对其负责的
    //所以我们考虑情况成员即可，不必删除对象
    //那么我们需要一个方法将现有对象传给需求发出者
    MerryShip* getShip()
    {
        MerryShip* ship=m_merry;
        m_merry=nullptr;
        return ship;
    }
    //这个reset方法必须在上面那个方法调用后再调用，不然你建造它干嘛
    void reset()override
    {
        m_merry=new MerryShip;
    }
    void buildBody()override
    {
        m_merry->assemble("body is tree","Body");
    }
    void buildEngine()override
    {
        m_merry->assemble("engine is cola","Engine");
    }
    void buildWeapon()override
    {
        m_merry->assemble("weapon is gun","Weapon");
    }
    void buildInterior()override
    {
        m_merry->assemble("interior is rare","Interior");
    }
    ~MerryBuilder()
    {
        if(m_merry)
        {
            delete m_merry;
        }
    }

private:
    MerryShip* m_merry;
};

//管理者类
class Direator
{
public:
    void setBuilder(ShipBuilder* builder)
    {
        m_builder=builder;
    }
    //简约型
    void buildSimpleShip()
    {
        m_builder->buildBody();
        m_builder->buildEngine();
    }
    //标准型
    void buildStandardShip()
    {
        buildSimpleShip();
        m_builder->buildWeapon();
    }
    //豪华型
    void buildRegalShip()
    {
        buildStandardShip();
        m_builder->buildInterior();
    }

protected:
    ShipBuilder* m_builder=nullptr;
};

//测试代码
//sunny号
void buildSunnyShip()
{
    Direator* direator=new Direator;
    SunnyBuilder* builder=new SunnyBuilder;

    //简约型
    direator->setBuilder(builder);
    direator->buildSimpleShip();
    SunnyShip* ship=builder->getShip();
    ship->showParts();
    delete ship;

    //标准型
    builder->reset();
    direator->buildStandardShip();
    ship=builder->getShip();
    ship->showParts();
    delete ship;

    //豪华型
    builder->reset();
    direator->buildRegalShip();
    ship=builder->getShip();
    ship->showParts();
    delete ship;

    delete direator;
    delete builder;
}

//merry
void buildMerryShip()
{
    Direator* direator=new Direator;
    MerryBuilder* builder=new MerryBuilder;

    //简约型
    direator->setBuilder(builder);
    direator->buildSimpleShip();
    MerryShip* ship=builder->getShip();
    ship->showParts();
    delete ship;

    //标准型
    builder->reset();
    direator->buildStandardShip();
    ship=builder->getShip();
    ship->showParts();
    delete ship;

    //豪华型
    builder->reset();
    direator->buildRegalShip();
    ship=builder->getShip();
    ship->showParts();
    delete ship;

    delete direator;
    delete builder;
}

int main()
{
    buildMerryShip();
    cout<<"=================="<<endl;
    buildSunnyShip();

    return 0;
}