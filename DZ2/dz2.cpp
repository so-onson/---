#include "iostream"
#include "string.h"
#include "set"
#include "vector"
#include <algorithm>
#include <regex>

using namespace std;

set<string> res_types{"integer", "real", "boolean", "char", "string" };
set<string> res_words{"Procedure", "Function" };
set<char> alphabet{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', '_'};
set<char> numbers{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
set<char> spec_syms{'(', ')', ',', ';'};
bool ok = 1;

int count(string str, char c)
{
    int count = 0;
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == c)
        {
            count++;
        }
    }
    return count;
}


void process(string words)
{

    smatch m;

    regex_search(words, m, regex("();,"));
    for (auto x : m)
        cout << "Special symbol: *" << x << "*" << endl;

    // if (count(words, '['))
    // {
    //     cout << "Special symbol: *[*" << endl;
    // }
    // if (regex_search(words, regex("\\]")))
    // {
    //     if (!regex_search(words, regex("\\((([a-zA-Z][0-9]*[a-zA-Z]*+)|(\\s*)|([0-9]+))\\)")))
    //     {
    //         ok = 0;
    //         cout << "Only numbers or identificators between brackets *()*" << endl;
    //     }
    // }

    // if (count(words, '[') > count(words, ']'))
    // {
    //     ok = 0;
    //     cout << "No closing bracket *)*" << endl;
    // }
    // else if (count(words, ')') > count(words, '('))
    // {
    //     ok = 0;
    //     cout << "No opening bracket *(* but got closing *)" << endl;
    // }
    // if (regex_search(words, m, regex("[a-zA-z]+[a-zA-z0-9]*")))
    // {
    //     if (!res_types.count(m[0]))
    //         cout << "Identificator: *" << m[m.size() - 1] << "*" << endl;
    //     else
    //         cout << "Type: *" << m[0] << "*" << endl;
    // }
    // else if (m.length() != 0)
    // {
    //     cout << "Wrong identificator *" << m[0] << "*" << endl;
    //     ok = 0;
    // }
    }

void for_struct(string words)
{
    bool correct_id = 1; // 1 = ок / 0 = неок(спец символы)
    int c_bracket = 0; // 0 = не нашел скобку/ 1 = нашел
    string id = "";
    if (words.back() != ';')
    {
        if (words.back() != ')' && !res_types.count(words))
        {
            cout << "Expected *;*" << words << endl;
            ok = 0;
        }
    }
    else
        cout << "Special symbol: *;*" << endl;
    if (count(words, '(') == count(words, ')') == 1)
    {
        if (words.find('(') > words.find(')'))
        {
            ok = 0;
            cout << "Too much curl brackets *()*" << endl;
        }
        else
        {
            cout << "Special symbol *(*" << endl;
            cout << "Special symbol *)*" << endl;
        }
    }
    else
    {
        cout << "Wrong number curl brackets *{}*" << endl;
        ok = 0;
    }
    
    process(words);
}



int main()
{
    string str = "Procedure as3(Var a_34,bjt:real; car:integer; const ddd:byte);"; // input
    string input = str;
    vector<string> words;
    bool correct_input = 1;
    int pos = str.find(" ");
    smatch m;
    cout << str << endl;
    // split

    while (str.length() > 0 && pos < str.length())
    {
        string el = str.substr(0, pos);
        if (el != "")
        {
            words.push_back(el);
        }
        str = str.erase(0, pos + 1);
        pos = str.find(" ");
    }
    
    if (str != "")
        words.push_back(str);


    if (regex_match(words[0], m, regex("\\s*(Procedure)\\s*")))
    {
        cout << "Reserved word: *" << m[0] << "*" << endl;

        // if (!regex_match(words[0], regex("\\s*Procedure\\s*")))
        // {
        //     if (count(input, ';') != 0 || count(input, '(') != 0 || count(input, ')') != 0)
        //     {
        //         cout << "Expected end of type definition" << endl;
        //         ok = 0;
        //     }


        //     if (regex_search(input, regex(",\\s*;")))
        //     {
        //         cout << "Expected identificator got *;*" << endl;
        //         ok = 0;
        //     }
        //     for (int i = 1; i < words.size(); i++)
        //     {
        //         if(regex_search(words[i], m, regex("\\s*(struct|int|char|unsigned char|float)\\s*")) && regex_search(words[i-1], regex("\\s*(int|char|unsigned char|float)\\s*")))
        //         {
        //         cout<<"Expected identificator got type *"<<m[0]<<"*"<<endl;
        //         ok = 0;
        //         }
        //         process(words[i]);
        //     }
        // }
        // else
        // {
            int index = 0;
            for (int i = 0; i < words.size(); i++)
            {
                if (words[i] == ")")
                index = i;
            }
            for (int i = index + 1; i < words.size() - 1; i++)
            {
                process(words[i]);
                if (words[i].back() != ';' && !res_types.count(words[i]) && !regex_search(words[i], regex("(;,)")))
                {
                    cout << "Expected a *;*" << endl;
                    ok = 0;
                }
            }
        // }
        if (input.back() != ';')
            {
                cout << "Expected a *;*" << endl;
                ok = 0;
            }
    }

    else
    {
        cout << "Undefined type: *" << words[0] << "*" << endl;
        ok = 0;
    }


    if (ok)
        cout << "yes" << endl;
    else
        cout << "no" << endl;
    return 0;
}
