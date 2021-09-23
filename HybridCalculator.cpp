#include <iostream>
#include <cmath>

using namespace std;

struct maths_operates
{
    string simpleOperator[4] = {"sum", "substract", "multiply", "divide"};
    string scientificOPerator[6] = {"square", "sqrt", "sin", "cos", "tan", "log10"};
} operate;

class simpleCalculator // simple_calculator class
{
    string simple_oper;
    float num1, num2;

public:
    void setInput1(string, float, float);
    char setOperator1(void);
    float simple_Calc(void);
};

void simpleCalculator ::setInput1(string op, float inputNum1, float inputNum2) // set input function
{
    simple_oper = op;
    num1 = inputNum1;
    num2 = inputNum2;
    cout << "Result = " << simple_Calc() << endl;
}

char simpleCalculator::setOperator1(void) // set operator function
{
    int i;
    char op[4] = {1, 2, 3, 4};
    for (i = 0; i < 4; i++)
    {
        if (simple_oper == operate.simpleOperator[i])
        {
            return op[i];
            break;
        }
    }
    return 0;
}

float simpleCalculator::simple_Calc(void) // simple calculator function
{
    switch (setOperator1())
    {
    case 1:
        return num1 + num2;
        break;
    case 2:
        return num1 - num2;
        break;
    case 3:
        return num1 * num2;
        break;
    case 4:
        return num1 / num2;
        break;

    default:
        cout << "No such operation available" << endl;
        return 0;
        break;
    }
}

class scientificCalculator // scientific calculator
{
    string oper;
    float scinum;

public:
    void setInput2(string, float);
    char setOperator2();
    float sci_Calc();
};

void scientificCalculator::setInput2(string op, float num) // set input function
{
    oper = op;
    scinum = num;
    cout << "Result = " << sci_Calc() << endl;
}

char scientificCalculator::setOperator2() // set operator function
{
    int i;
    char op[6] = {'a', 'b', 'c', 'd', 'e', 'f'};
    for (i = 0; i < 6; i++)
    {
        if (oper == operate.scientificOPerator[i])
        {
            return op[i];
            break;
        }
    }
    return 0;
}

float scientificCalculator::sci_Calc() //scientific calculator function
{
    switch (setOperator2())
    {
    case 'a':
        return pow(scinum, 2);
        break;

    case 'b':
        return sqrt(scinum);
        break;

    case 'c':
        return sin(scinum);
        break;

    case 'd':
        return cos(scinum);
        break;

    case 'e':
        return tan(scinum);
        break;

    case 'f':
        return log10(scinum);
        break;

    default:
        cout << "No such operation available" << endl;
        return 0;
        break;
    }
}

class hybridCalc : simpleCalculator, scientificCalculator // hybrid calculator class by inheriting both the calculators
{
    int res;

public:
    void input_calc(void);
};

void hybridCalc::input_calc(void) // data input function
{
    float input1, input2;
    string inputOperator;
    bool flag1 = false, flag2 = false;
    cout << "Enter the operator and the numbers as (operator input1 input2)" << endl;
    cout<<"Operators available -> sum, substract, multiply, divide, square, sqrt, sin, cos, tan, log10"<<endl;
    cin >> inputOperator;
    for (int i = 0; i < 7; i++)
    {
        if (inputOperator == operate.scientificOPerator[i])
        {
            flag2 = true;
            break;
        }

        for (int j = 0; j < 5; j++)
        {
            if (inputOperator == operate.simpleOperator[j])
            {
                flag1 = true;
                break;
            }
        }
    }

    if (flag1 == true)
    {
        cin >> input1 >> input2;
        setInput1(inputOperator, input1, input2);
    }
    else if (flag2 == true)
    {
        cin >> input1;
        setInput2(inputOperator, input1);
    }
    else
    {
        cout << "No such operator available" << endl;
    }
}

int main()
{
    hybridCalc cal1;
    cal1.input_calc();

    return 0;
}


/*
Q. what type of inheritance are you using?
ans. - multiple inheritance

Q. which mode of inheritance are you using?
ans. private

Q. Create an object of hybridCalculator and display result of simple and scientific calculator
ans. object name - cal1
        the result of both simple and scientific is being displayed without any error

Q. How is code reusability implemented?
ans. Code reusability is implemeted using structure and loops and multiple inherited class.

*/