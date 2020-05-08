#ifndef CONDITION_H
#define CONDITION_H

#include <string>
#include <set>
#include <iostream>

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

class RoomHasItemCondition : public BaseCondition
{
    public:
        RoomHasItemCondition(Level* level, string name, string room_name, string item_name, bool permanent = false) : BaseCondition(level, name, permanent) {this->item_name = item_name; this->room_name = room_name;};
        bool evaluate_inner() override;
        string item_name;
        string room_name;
};

template <typename T>
class PasswordCondition : public BaseCondition
{
    public:
        PasswordCondition(Level* level, string name, T password, bool permanent = false, string request_msg = "Enter password:") : BaseCondition(level, name, permanent) {this->password = password; this->request_msg=request_msg;};
        T password;
        string request_msg;
        bool evaluate_inner() override;
};

template <typename T>
bool PasswordCondition<T>::evaluate_inner()
{
    cout << this->request_msg << "\n";
    cout << ">" << endl;
    T guess;
    cin >> guess;
    string s;
    //eat until EoL so main loop doesn't catch it
    getline(cin,s);
    if(guess == this->password)
    {
        cout << "Accepted\n";
        return true;
    }
    cout << "Rejected\n";
    return false;
}


class Condition : public BaseCondition
{
    public:
        Condition(Level* level, string name) : BaseCondition(level, name) {};
        bool evaluate_inner() override;
        set<BaseCondition*,CondPtrCmp> subconditions;
        void add_condition(BaseCondition* cond) {this->subconditions.insert(cond);};
};

#endif // CONDITION_H
