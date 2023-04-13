#include <fstream>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <map>
#include <iomanip>

using namespace std;

string man_page() {
    return 
    "Usage: ./your_executable_name textfile.txt OPTIONS.... \n"
    "available options are: \n\n"
    "--print \n--frequency \n--table \n--substitute=old+new \n--remove=word \n";
}

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

void had_an_effect(Argument& splt, vector<string>& before, vector<string>& text) {
    if(equal(before.begin(), before.end(), text.begin(), text.end())) {
        cout << endl << splt.flag << "=" 
            << splt.parameter << " had no effect. " << endl;
    } 
}

void apply_input_by_arg(string const& arg, vector<string>& text) {
    string flag = arg.substr(0, arg.find("="));
    string parameter = arg.substr(arg.find("=") + 1, -1);
    Argument splitted {flag, parameter};

    if (splitted.flag == "--remove") {
        auto discard = remove(text.begin(), text.end(), splitted.parameter);
        vector<string> before_change{text};
        text.erase(discard, text.end());
        had_an_effect(splitted, before_change, text);     
    }

    else if (splitted.flag == "--substitute") {
        string old = parameter.substr(0, parameter.find("+"));
        string change = parameter.substr(parameter.find("+") + 1, -1);
        vector<string> before_change{text};
        replace(text.begin(), text.end(), old, change); 
        had_an_effect(splitted, before_change, text);     
    } else {
        throw invalid_argument(man_page());
    }
}

void apply_single_by_arg(string const& arg, vector<string>& text) {
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
        
    } else {
        throw invalid_argument(man_page());
    }
    cout << endl;
    
}

void apply_arg(string const& arg, vector<string>& text) {
    if(any_of(arg.begin(),arg.end(), [](char c) {return c == '=';})) {
        apply_input_by_arg(arg, text);

    } else {
        apply_single_by_arg(arg, text);
    }
}

void run_arguments(vector<string>& args, vector<string>& text) {
    for_each(args.begin(), args.end(), [&text](string& arg) {apply_arg(arg,text);});
}   

vector<string> read_file(string const& file_name) {
    vector<string> words;
    fstream file;
    file.open(file_name);

    copy(istream_iterator<string>{file}, istream_iterator<string>{}, back_inserter(words));

    return words;
}

int main(int argc, char* argv[])
{
    try
    {
        if (argc < 2) {
            throw invalid_argument(man_page());
        } else {
            vector<string> arguments(argv + 2, argv + argc);
            string f_name = argv[1];
            vector<string> words{read_file(f_name)};

            if(words.empty()) {
                throw invalid_argument("Please provide a file!");
            }
            
            run_arguments(arguments, words);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    
    return 0;
}
