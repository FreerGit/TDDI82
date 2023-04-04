#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Argument {
    string flag;
    string parameter;
};


void apply_arg(string const& arg, vector<string>& text) {
    if(any_of(arg.begin(),arg.end(), [](char c) {return c == '=';})) {
        string flag = arg.substr(0, arg.find("="));
        string parameter = arg.substr(arg.find("=") + 1, -1);
        Argument splitted {flag, parameter};
        if (splitted.flag == "--remove") {
            remove(text.begin(), text.end(), splitted.parameter);
        }
    } else {
        Argument single {arg, ""};
        if(single.flag == "--print") {
            cout << text << endl;
        } 
    }

}


void run_arguments(vector<string>& args, vector<string>& text) {
    for_each(args.begin(), args.end(), [&text](string& arg) {apply_arg(arg,text);});
        
}   


int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2) {
            throw invalid_argument("Provide a file and arguments");
        } else {
            vector<string> arguments(argv + 1, argv + argc);
            string f_name = argv[1];
            ifstream in(f_name);
            string text((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());


            //gör till en vector av ord, inte löst splitting än
            run_arguments(arguments, text);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
