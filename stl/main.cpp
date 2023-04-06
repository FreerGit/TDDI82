#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ostream>
#include <map>
#include <iomanip>


using namespace std;

bool cmp(pair<string, int>& a, pair<string, int>& b) {
    return a.second > b.second;
}

template<typename Iter>
int get_length(Iter begin, Iter end) {
    int length{0};
    for_each(begin, end, [&length](auto i) {
        if(i.first.length() > length) {
            length = i.first.size();
        }
    });
    return length;
}

map<string, int> build_occurances(vector<string>& text) {
    map<string, int> occurances;
    for_each(text.begin(), text.end(), [&occurances](string str) {
        occurances[str]++;
    });
    return occurances;
}

void sort_print(map<string, int>& M) {
    vector<pair<string, int>> occ;
    for_each(M.begin(), M.end(), [&occ](auto &it){occ.push_back(it);});
    sort(occ.begin(), occ.end(), cmp);
    int length = get_length(occ.begin(), occ.end());

    for_each(occ.begin(), occ.end(), [&occ,&length](auto i) {
        if(i.first != "") {
            cout << setw(length) << i.first << " " << i.second << endl;
        }
    });
}

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
            auto discard = remove(text.begin(), text.end(), splitted.parameter);
            text.erase(discard, text.end());
        }

        else if (splitted.flag == "--substitute") {
            string old = parameter.substr(0, parameter.find("+"));
            string change = parameter.substr(parameter.find("+") + 1, -1);
            replace(text.begin(), text.end(), old, change);            
        }

    } else {
        Argument single {arg, ""};

        if(single.flag == "--print") {
            auto print = [](const string& n) { std::cout << n << ' '; };
            for_each(text.begin(), text.end(), print);
        }

        else if (single.flag == "--frequency") {
            map<string,int> occurances{build_occurances(text)};

            sort_print(occurances);
        } 
        
        else if (single.flag == "--table") {
            map<string,int> occurances{build_occurances(text)};

            int length = get_length(occurances.begin(), occurances.end());

            for_each(occurances.begin(), occurances.end(), [&length](auto i) {
                if(i.first != "") {
                    cout << setw(length) << left << i.first << " " << i.second << endl;
                }
            });
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
            cout << argc << endl;
            cout << "ddddd" << endl;
            throw invalid_argument("Provide a file and arguments");
        } else {
            vector<string> arguments(argv + 1, argv + argc);
            vector<string> words{""};
            string word;
            string f_name = argv[1];
            fstream file;
            file.open(f_name);

            //ska inte vara while loop
            while(file >> word) {
                words.push_back(word);
            }
            // std::ifstream t(f_name);
            // std::string file_text((std::istreambuf_iterator<char>(t)),
            //                 std::istreambuf_iterator<char>());


            // auto of_words = [&words](char arg) {
            //     if
            //     if(arg != ' ') {
            //         words.back().push_back(arg);
            //     } else {
            //         words.push_back("");
            //     }
            // };

            // for_each(file_text.begin(), file_text.end(), of_words);

            // for (size_t i = 0; i < words.size(); i++)
            // {
            //     cout << words[i] << endl;
            // }
            
            run_arguments(arguments, words);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}
