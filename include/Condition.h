#ifndef CONDITION_H
#define CONDITION_H

#include<string>
#include<set>

using namespace std;

class Level;

class BaseCondition
{
    public:
        BaseCondition(Level* level, string name, bool permanent = false);
        virtual ~BaseCondition();
        Level* level;

        bool evaluate();
        virtual bool evaluate_inner() {return true;};
        string name;
        bool permanent;
        bool satisfied = false; //permanently
        struct CondPtrCmp
        {
            bool operator()(const BaseCondition* lhs, const BaseCondition* rhs) const  { return lhs->name < rhs->name; };
        };

    protected:

    private:
};

class PlayerHasItemCondition : public BaseCondition
{
    public:
        PlayerHasItemCondition(Level* level, string name, string item_name, bool permanent = false) : BaseCondition(level, name, permanent) {this->item_name = item_name;};
        bool evaluate_inner() override;
        string item_name;
};

class Condition : public BaseCondition
{
    public:
        Condition(Level* level, string name) : BaseCondition(level, name) {};
        bool evaluate_inner() override;
        set<BaseCondition*,CondPtrCmp> subconditions;
        void add_condition(BaseCondition* cond) {this->subconditions.insert(cond);};
};

#endif // CONDITION_H
