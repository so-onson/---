#include <iostream>

using namespace std;

string Types[6] {"integer", "real", "boolean", "char", "byte", "string"};

string Rez_words[2] {"var", "const"};


string delete_space(string s){
    int i = 0;
    while (s[i]==' '){
        s = s.substr(1);
    }
    return s;
}

int check_type(string s){
    if (s.length()<1){
        cout << "Type cant be blank! " << s << endl;
        return 0;
    }
    for (int i=0;i<6;i++){
        if (s==Types[i]){
            cout <<"Reserved word: "<< Types[i] << endl;
            return 1;
        }
    }
    cout << "Incorrect type: " << s << endl;
    return 0;
}

int check_word(string s){
    if (s.length()<1){
        cout << "Word cant be blank! " << s << endl;
        return 0;
    }
    for (int i=0;i<2;i++){
        if (s==Rez_words[i]){
            cout <<"Reserved word: "<< Rez_words[i] << endl;
            return 1;
        }
    }
    cout << "Incorrect word: " << s << endl;
    return 0;
}

int check_symbols(string s){
    if (!(char(s[0]) > 64 and char(s[0]) < 91 or char(s[0]) > 96 and char(s[0]) < 123 or char(s[0]) == 95)){
        cout<<"Wrong symbol: "<<s[0]<<endl;
        return 0;
    }
    for (int i =1; i < s.length(); i++){
        if (!((char(s[i]) > 64 and char(s[i]) < 91) or (char(s[i]) == 95) or (char(s[i]) > 96 and char(s[i]) < 123) or (char(s[i]) > 47 and char(s[i]) < 58))){
            cout<<"Wrong symbol: "<<s[i]<<endl;
            return 0;
        }
    }
    return 1;
}

int check_name_func(string s){

    s = delete_space(s);
    if(check_symbols(s)==0){
        return 0;
    }
    if (s.length()==0){
        cout << "Name of func argument cant be blank" << endl;
        return 0;
    }
    return 1;
}

int check_name(string stroka){
    // здесь можно добавить проверку на имя внутренней функции
    // if (s[0]!='*'){
    //     return 0;
    // }
    // cout<<s<<endl;
    string name;
    if (stroka.find(' ')!=string::npos){
        string word = stroka.substr(0, stroka.find(' '));
        if (check_word(word)==0){
            return 0;
        }

        stroka = stroka.erase(0, stroka.find(' '));
    }
    stroka = delete_space(stroka);
    while (stroka.length()!=0){
    // cout<<stroka<<"do"<<endl;
        if (stroka.find(',') != string::npos){
            name = stroka.substr(0, stroka.find(','));
            //
            // cout<<", "<<name<<endl
            if(check_symbols(name)==0){
                return 0;
            }
            cout<<"Identifier: "<<name<<endl;
            stroka = stroka.erase(0, stroka.find(',')+1);

        }
        else {
            name = stroka.substr(0, stroka.find(':'));
            if(check_symbols(name)==0){
                return 0;
            }
            cout<<"Identifier: "<<name<<endl;
            stroka = stroka.erase(0, stroka.find(':')+1);
        }
        // cout<<stroka<<endl;
        if (name.length()==0){

            cout << "Name of parametr argument cant be blank" << endl;
            return 0;
        }
    }
    return 1;
}



int check_arguments(string s){
    s = s + "!";
    // cout<<s<<endl;
    while (s.length()>3){
        string arg;
        string type;

        if (s.find(':')!=string::npos){
            
            arg = s.substr(0, s.find(':')+1);
            if(check_name(arg)==0){
                return 0;
            }
            s=s.erase(0, s.find(':')+1);
            if (s.find(';')!=string::npos){
                type = s.substr(0, s.find(';'));
                if(check_type(type)==0){
                    return 0;
                }
                s=s.erase(0, s.find(' '));
            }
            else {
                type = s.substr(0, s.find('!'));
                if(check_type(type)==0){
                    return 0;
                }
                s=s.erase(0, s.find('!'));           
            }
        }
        s = delete_space(s);

    }
    return 1;
}


int check_brackets(string str){                             ////ok
    int br1 = 0, br2 = 0;
    for (int i = 0; i < str.length(); i++){
        if (str[i] == '(')
            br1++;
        if (str[i] == ')')
            br2++;
    }
    if (br1 == br2)
        return 1;
    cout << "Incorrect brackets" << endl;
    return 0;
}



int check_after_proc(string s){
    s = s.substr(s.rfind(')')+1, s.length());
    // cout << s;
    int k=0;
    for (int i =0; i< s.length(); i++){
        if (s[i]!=' ' && s[i]!=';'){
            cout << "Incorrect symbols after string: " << s[i] << endl;
            return 0;
        }
        if (s[i]==';')
            k++;
    }
    if (k!=1){
        cout << "Incorrect count of ; after string " << endl;
        return 0;
    }
    return 1;
}

int check_after_func(string s){
    if (s.find(':')==string::npos){
        cout << "Type of function cant be blank" << endl;
        return 0;
    }
    s=s.substr(1,s.find(';')-1);
    // cout<<s<<endl;
    if (check_type(s)==0){
        return 0;
    }
    return 1;
}

int check_proc(string s){


    string vd = s.substr(0, 9);

    cout << "Procedure with name: ";

    vd = s.substr(10, s.length()-6);

    string func_name = vd.substr(0, vd.find('('));

    cout <<func_name<< " and params: " <<endl;
    check_name_func(func_name);
    if (check_brackets(s)==0){
        return 0;
    }
    vd=vd.erase(0,vd.find('('));
    // cout<<vd<<endl;
    string str = vd.substr(vd.find('(')+1, vd.find(')')-1);

    if (check_arguments(str)==0){
        return 0;
    }



    if (check_after_proc(s)==0){
        return 0;
    }

    return 1;
}

int check_func(string s){

    cout << "Function with name: ";

    string vd = s.substr(9, s.length()-6);

    string func_name = vd.substr(0, vd.find('('));

    cout <<func_name<< " and params: " <<endl;
    check_name_func(func_name);
    if (check_brackets(s)==0){
        return 0;
    }
    vd=vd.erase(0,vd.find('('));
    cout<<vd<<endl;
    string str = vd.substr(vd.find('(')+1, vd.find(')')-1);
    if (check_arguments(str)==0){
        return 0;
    }
    cout << "Returns: ";

    if (check_after_func(vd.substr(vd.find(')')+1, vd.find(';')))){
        return 0;
    }


    if (check_after_proc(s)==0){
        return 0;
    }

    cout << str << endl;
    return 1;
}

int check(string s){
    s = delete_space(s);

    if (s.substr(0, 9) == "Procedure") {
        check_proc(s);
    }
    else if (s.substr(0, 8) == "Function") {
        check_func(s);
    }
    else {
        cout << "Inccorect symbols";
        return 0;
    }
    return 1;
}


int main()
{
    string inp = "Function hjkh(var k:integer):char;";

    cout << inp << endl;

    check(inp);
    return 0;
}
