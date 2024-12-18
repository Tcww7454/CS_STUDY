#include <iostream>
#include <list>
#include <vector>
#include <string>
using namespace std;

class AbstractTeam
{
public:
    AbstractTeam(string name):m_name(name){}
    string getName(){return m_name;}
    void setFather(AbstractTeam* fa)
    {
        this->father=fa;
    }
    AbstractTeam* getFather(AbstractTeam* fa)
    {
        return this->father;
    } 
    //使用一个默认行为，子类可以覆写
    virtual bool hadChild()
    {
        return false;
    }
    //只在需要的子类中去进行重写即可
    virtual void addChild(AbstractTeam* node){}
    virtual void removeChild(AbstractTeam* node){}
    virtual void fight()=0;
    virtual void display()=0;
    virtual ~AbstractTeam(){}

protected:
    string m_name;
    AbstractTeam* father;
};

//叶子节点类
class LeafTeam:public AbstractTeam
{
public:
    using AbstractTeam::AbstractTeam;
    void fight()override
    {
        cout<<this->father->getName()+m_name+"fight with black."<<endl;
    }
    void display()override
    {
        cout<<"I am the subordinate of"<<this->father->getName()<<endl;
    }
    ~LeafTeam()
    {
        cout<<"I am the subordinate of"<<this->father->getName()
            <<". The fight end,bye."<<endl;
    }
};

//管理者节点类
class ManagerTeam:public AbstractTeam
{
public:
    using AbstractTeam::AbstractTeam;
    void fight()override
    {
        cout<<this->father->getName()+m_name+"fight with black ability."<<endl;
    }
    void display()override
    {
        string info;
        for(const auto& item :m_child)
        {
            if(item==m_child.back())
            {
                info+=item->getName();
            }
            else{
                info+=item->getName()+",";
            }
        }
        cout<<m_name<<" child are "<<info<<endl;
    }
    list<AbstractTeam*> getChild()
    {
        return m_child;
    }
    bool hadChild()override
    {
        return true;
    }
    void addChild(AbstractTeam* node)override
    {
        node->setFather(this);
        m_child.push_back(node);
    }
    void removeChild(AbstractTeam* node)override
    {
        node->setFather(nullptr);
        m_child.remove(node);
    }
    ~ManagerTeam()
    {
        cout<<"I am "<<this->getName()
            <<". The fight ended,bye."<<endl;
    }
private:
    list<AbstractTeam*>m_child;
};

void gameOver(AbstractTeam* root)
{
    if(root==nullptr)
        return ;
    if(root->hadChild())
    {
        ManagerTeam* team=dynamic_cast<ManagerTeam*>(root);
        list<AbstractTeam*> child=team->getChild();
        for(const auto& item:child)
        {
            gameOver(item);
        }
    }
    delete root;
}

void fighting()
{
    ManagerTeam* root=new ManagerTeam("cao mao");
    vector<string> nameList={
        "aaa","bbb","ccc","ddd","eee"
    };
    for(int i=0;i<nameList.size();i++)
    {
        ManagerTeam* child=new ManagerTeam(nameList[i]);
        root->addChild(child);
        if(i==nameList.size()-1)
        {
            for(int j=0;j<9;++j)
            {
                LeafTeam* leaf=new LeafTeam("the "+to_string(i+1)+" ship");
                child->addChild(leaf);
                leaf->fight();
                leaf->display();
            }
        }
        child->fight();
        child->display();
    }
    root->fight();
    root->display();
    cout<<"============="<<endl;
    gameOver(root);
}



int main()
{
    fighting();

    return 0;
}