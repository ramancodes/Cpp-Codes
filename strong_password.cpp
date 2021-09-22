#include <iostream>
#include <string>

using namespace std;

class password
{
    string pass;
    int specialChars[6] = {33, 35, 36, 38, 63, 64};
    bool haslower = false, hasupper = false;
    bool hasdigit = false, hasspecialChar = false;
    void lengthcheck(void);
    void passCheck(void);

public:
    password() {}
    password(string enteredPass);
};

password::password(string eneteredPass)
{
    pass = eneteredPass;
    lengthcheck();
}

void password::lengthcheck(void)
{
    if (pass.length() < 8 && pass.length() > 6)
    {
        cout << "20% Less than 8 characters" << endl;
    }
    else if (pass.length() < 6)
    {
        cout << "0% Less than 8 characters" << endl;
    }
    else
    {
        passCheck();
    }
}

void password ::passCheck(void)
{
    for (int i = 0; i < pass.length(); i++)
    {
        if (islower(pass.at(i)))
        {
            haslower = true;
        }
        else if (isupper(pass.at(i)))
        {
            hasupper = true;
        }
        else if (isdigit(pass.at(i)))
        {
            hasdigit = true;
        }
        else
        {
            for (int j = 0; j < 6; j++)
            {
                if (pass.at(i) == specialChars[j])
                {
                    hasspecialChar = true;
                }
            }
        }
    }

    if (haslower && hasupper && hasdigit && hasspecialChar)
    {
        cout << "100% Strong" << endl;
    }
    else if ((haslower && hasupper && hasdigit) || (haslower && hasupper && hasspecialChar) || (hasspecialChar && hasupper && hasdigit) || (haslower && hasspecialChar && hasdigit))
    {
        cout << "75% Moderate" << endl;
    }
    else if ((haslower && hasupper) || (hasupper && hasdigit) || (hasdigit && hasupper) || (haslower && hasspecialChar) || (hasupper && hasspecialChar) || (hasdigit && hasspecialChar))
    {
        cout << "50% Moderate" << endl;
    }
    else if (haslower || hasupper || hasdigit || hasspecialChar)
    {
        cout << "25% Weak" << endl;
    }
}

int main()
{
    password pass1;
    string EnterPass;
    cout << "Enter your password" << endl;
    cin >> EnterPass;
    pass1 = password(EnterPass);
    return 0;
}