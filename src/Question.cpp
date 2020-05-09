#include "Question.h"

BaseQuestion::~BaseQuestion()
{

}

bool GuessNumberQuestion::eval_ans(long long ans)
{
    if(ans > this->answer)
    {
        this->resp = "No, my number is smaller!";
        return false;
    }
    else if (ans < this->answer)
    {
        this->resp = "No, my number is greater!";
        return false;
    }

    this->resp = "Yes! You guessed it! The man steps aside. You obviously made his day.";
    return true;
}
