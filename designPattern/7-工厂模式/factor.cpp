#include <iostream>
using namespace std;

//强类型枚举(枚举类)，加上class来限定作用域
//使用:数据类型来指定底层储存数据的模式
//这里储存是一种映射，需要注意char本质上其实就是一个字节的数
//也就是说这里的表示方式其实就是对应数据类型的一个状态(01串)
enum class smileType:char
{
    sheepSmile,
    lionSmile,
    batSmile
};

class Product
{
    public:
        Product()=default;
        virtual void transform()=0;
        virtual void ability()=0;
        virtual ~Product(){} 
};

class sheepSmile :public Product
{
    public:
        sheepSmile()=default;
        void transform()override
        {
            cout<<"变成山羊形态..."<<endl;
        }
        void ability()override
        {
            cout<<"拥有弹跳能力..."<<endl;
        }
        ~sheepSmile(){} 
};

class lionSmile :public Product
{
    public:
        lionSmile()=default;
        void transform()override
        {
            cout<<"变成狮子形态..."<<endl;
        }
        void ability()override
        {
            cout<<"拥有喷火能力..."<<endl;
        }
        ~lionSmile(){} 
};

class batSmile :public Product
{
    public:
        batSmile()=default;
        void transform()override
        {
            cout<<"变成蝙蝠形态..."<<endl;
        }
        void ability()override
        {
            cout<<"拥有飞行能力..."<<endl;
        }
        ~batSmile(){} 
};

#if 0
//定义工厂类
class smileFactor
{
public:
    Product* generateSmile(smileType type)
    {
        Product* product=nullptr;
        switch(type)
        {
            case smileType::batSmile :
            {
                product=new batSmile;
                break;
            }
            case smileType::lionSmile :
            {
                product=new lionSmile;
                break;
            }
            case smileType::sheepSmile :
            {
                product=new sheepSmile;
                break;
            }
            default:
                break;
        }
        return product;
    }
    smileFactor()=default;
};
#endif

class AbstractFactor
{
public:
    virtual Product* creatSmile()=0;
    virtual ~AbstractFactor(){};
};

class sheepFactor:public AbstractFactor
{
public:
    Product* creatSmile()
    {
        Product* obj=new sheepSmile;
        return obj;
    }
    ~sheepFactor()
    {
        cout<<"delete the sheepFactor"<<endl;
    }
};

class lionFactor:public AbstractFactor
{
public:
    Product* creatSmile()
    {
        Product* obj=new lionSmile;
        return obj;
    }
    ~lionFactor()
    {
        cout<<"delete the lionFactor"<<endl;
    }
};

class batFactor:public AbstractFactor
{
public:
    Product* creatSmile()
    {
        Product* obj=new batSmile;
        return obj;
    }
    ~batFactor()
    {
        cout<<"delete the batFactor"<<endl;
    }
};


int main()
{

    // smileFactor* factor=new smileFactor;
    // Product* obj=factor->generateSmile(smileType::batSmile);
    // obj->ability();
    // obj->transform();

    AbstractFactor * Batfactor=new batFactor;
    Product* bat=Batfactor->creatSmile();
    bat->ability();
    bat->transform();

    delete Batfactor;
    delete bat;

    return 0;
}