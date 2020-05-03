#include "Condition.h"
#include "Item.h"
#include "Player.h"
#include "Level.h"

BaseCondition::~BaseCondition()
{
    //dtor
}

bool BaseCondition::evaluate()
{
    if(this->satisfied) return true;
    bool sat = this->evaluate_inner();
    if(permanent) this->satisfied = true;
    return sat;
}

bool PlayerHasItemCondition::evaluate_inner()
{
    Item* it = new Item(this->item_name);
    bool sat = (this->level->player->inventory.find(it)) != (this->level->player->inventory.end());
    delete it;
    return sat;
}

bool Condition::evaluate_inner()
{
    bool sat = true;
    for(BaseCondition* cond : this->subconditions)
        sat &= cond->evaluate();
    return sat;
}
