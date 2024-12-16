#include <iostream>
using namespace std;

//父类
class GermaSolider
{
public:
    virtual GermaSolider* clone()=0;
    virtual string whoAmI()=0;
    virtual ~GermaSolider(){}
};

//子类
class solider66:public GermaSolider
{
public:
    virtual GermaSolider* clone()
    {
        return new solider66(*this);
    }
    virtual string whoAmI()
    {
        return "I am solider66.";
    }
    
    virtual ~solider66(){}
};

//子类
class solider77:public GermaSolider
{
public:
    virtual GermaSolider* clone()
    {
        return new solider77(*this);
    }
    virtual string whoAmI()
    {
        return "I am solider77.";
    }
    virtual ~solider77(){}
};

int main()
{
    GermaSolider* solider1=new solider66;
    GermaSolider* solider2=solider1->clone();
    cout<<solider2->whoAmI()<<endl;
    delete solider1;
    delete solider2;

    solider1=new solider77;
    solider2=solider1->clone();
    cout<<solider2->whoAmI();
    delete solider1;
    delete solider2;

    return 0;
}