// void out(string s){
//     s = s + "!";
//     while (s.length()>1){
//         // string type = s.substr(0, s.find(' '));

//         // string func_name = s.substr(0, s.find(' ')-1);
//         // s = s.erase(0, s.find(' ')+1);

//         // s = s.erase(0, s.find(')')+1);

//         string str = s.substr(1, s.find(')')-1);
//         cout<<str<<"Dd"<<endl;
//         out_arguments(str);
//         s = s.erase(0, s.find(')'));
//         if (s.find(',')<30){
//             s = s.erase(0, s.find(',')+1);
//         }
//         else{
//             s = s.erase(0, s.find('!')+1);
//         }
//         s = delete_space(s);

//     }
// }

// int check_in(string s){
//     s = s + "!";

//     while (s.length()>1){

//         if (check_arguments(s)==0){
//             return 0;
//         }
//         s=s.erase(0, s.find('!'));

//         s = delete_space(s);

//     }
//     return 1;
// }

// void out_arguments(string s){
//     s = s + "!";
//     while (s.length()>3){
//         string arg;
//         string type;

//         if (s.find(':')<30){
//             arg = s.substr(0, s.find(':'));
//             s=s.erase(0, s.find(':')+1);
//             if (s.find(';')<30){
//                 type = s.substr(0, s.find(';'));
//                 s=s.erase(0, s.find(' '));
//             }
//             else {
//                 type = s.substr(0, s.find('!'));
//                 s=s.erase(0, s.find('!'));           
//             }
//             cout << arg << ", type: "<<type<<endl;
//         }
//         s = delete_space(s);
//         //cout << s << endl;
//     }

// }


#include "iostream"
#include "string.h"
#include "set"
#include "vector"
#include <algorithm>
#include <regex>

using namespace std;

set<string> res_words{"float", "int", "char", "unsigned char", "struct"};
set<char> alphabet{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
set<char> numbers{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
set<char> spec_syms{'[', ']', ',', ';'};
bool ok = 1;
int count(string str, char c)
{
int cnt = 0;
for (int i = 0; i < str.length(); i++)
{
if (str[i] == c)
{
cnt++;
}
}
return cnt;
}
void process(string words)
{

smatch m;

regex_search(words, m, regex("[;,\\[]"));
for (auto x : m)
cout << "Special symbol: *" << x << "*" << endl;

if (count(words, ']'))
{
cout << "Special symbol: *]*" << endl;
}
if (regex_search(words, regex("\\[")))
{
if (!regex_search(words, regex("\\[(([a-zA-Z][0-9]*[a-zA-Z]*+)|(\\s*)|([0-9]+))\\]")))
{
ok = 0;
cout << "Only numbers or identificators between brackets *[]*" << endl;
}
}

if (count(words, '[') > count(words, ']'))
{
ok = 0;
cout << "No closing bracket *]*" << endl;
}
else if (count(words, ']') > count(words, '['))
{
ok = 0;
cout << "No opening bracket *[* but got closing *]" << endl;
}
if (regex_search(words, m, regex("[a-zA-z]+[a-zA-z0-9]*")))
{
if (!res_words.count(m[0]))
cout << "Identificator: *" << m[m.size() - 1] << "*" << endl;
else
cout << "Type: *" << m[0] << "*" << endl;
}
else if (m.length() != 0)
{
cout << "Wrong identificator *" << m[0] << "*" << endl;
ok = 0;
}
}

void for_struct(string words)
{
bool correct_id = 1; // 1 = ок / 0 = неок(спец символы)
int c_bracket = 0; // 0 = не нашел скобку/ 1 = нашел
string id = "";
if (words.back() != ';')
{
if (words.back() != '}' && !res_words.count(words))
{
cout << "Expected a *;*" << words << endl;
ok = 0;
}
}
else
cout << "Special symbol: *;*" << endl;
if (count(words, '{') == count(words, '}') == 1)
{
if (words.find('{') > words.find('}'))
{
ok = 0;
cout << "Too much curl brackets *{}*" << endl;
}
else
{
cout << "Special symbol *{*" << endl;
cout << "Special symbol *}*" << endl;
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
string str = "int s[[2];"; // input
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
if (regex_search(words[0], m, regex("\\s*(struct|int|char|unsigned char|float)\\s*")))
{
cout << "Reserved word: *" << m[0] << "*" << endl;
if (!regex_search(words[0], regex("\\s*struct\\s*")))
{
if (count(input, ';') != 1 || count(input, '{') != 0 || count(input, '}') != 0)
{
cout << "Expected end of type definition" << endl;
ok = 0;

}
if (regex_search(input, regex(",\\s*;")))
{
cout << "Expected identificator got *;*" << endl;
ok = 0;
}
for (int i = 1; i < words.size(); i++)
{
if(regex_search(words[i], m, regex("\\s*(struct|int|char|unsigned char|float)\\s*")) && regex_search(words[i-1], regex("\\s*(int|char|unsigned char|float)\\s*"))){
cout<<"Expected identificator got type *"<<m[0]<<"*"<<endl;
ok = 0;
}
process(words[i]);
}
}
else
{
int index = 0;
for (int i = 0; i < words.size(); i++)
{
if (words[i] == "}")
index = i;
}
for (int i = index + 1; i < words.size() - 1; i++)
{
process(words[i]);
if (words[i].back() != ';' && !res_words.count(words[i]) && !regex_search(words[i], regex("[{};,]")))
{
cout << "Expected a *;*" << endl;
ok = 0;
}
}
}
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
