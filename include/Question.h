#ifndef QUESTION_H
#define QUESTION_H

#include <string>
#include <iostream>

using namespace std;

class BaseQuestion
{
    public:
        BaseQuestion() {};
        virtual ~BaseQuestion();
        virtual bool ask() = 0;
};

template <typename QUE, typename ANS>
class Question : public BaseQuestion
{
    public:
        Question(QUE question, ANS answer) {this->question=question; this->answer=answer;};
        virtual ~Question();

        bool ask() override;
        virtual ANS read_ans();
        virtual bool eval_ans(ANS ans);
        string resp;
        ANS answer;
        QUE question;


    protected:

    private:
};

template <typename QUE, typename ANS>
Question<QUE,ANS>::~Question()
{
    //dtor
}

template<typename QUE, typename ANS>
bool Question<QUE,ANS>::ask()
{
    cout << this->question << "\n";
    cout << ">" << endl;
    ANS ans = this->read_ans();
    bool res = eval_ans(ans);
    cout << this->resp << "\n";
    return res;
}

template<typename QUE, typename ANS>
ANS Question<QUE,ANS>::read_ans()
{
    ANS ans;
    cin >> ans;

    // to catch EoL for future inputs
    string s;
    getline(cin,s);
    return ans;
}

template<typename QUE, typename ANS>
bool Question<QUE,ANS>::eval_ans(ANS ans)
{
    bool res = (ans == this->answer);
    if(res) this->resp = "Accepted.";
    else this->resp = "Rejected.";

    return res;
}

class GuessNumberQuestion : public Question<string,long long>
{
    public:
        GuessNumberQuestion(string question,long long answer) : Question(question,answer) {};
        bool eval_ans(long long ans) override;
};


#endif // QUESTION_H
