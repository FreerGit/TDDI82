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

template<typename T>  
void print_container(std::ostream& os, const T& container, const std::string& delimiter)  
{  
    std::copy(std::begin(container),   
              std::end(container),   
              std::ostream_iterator<typename T::value_type>(os, delimiter.c_str())); 
}  

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
    auto item =  max_element(begin, end, [](const auto &x, const auto &y) {
        return x.first.length() < y.first.length();
    });
    return item->first.length();
}

map<string, int> build_occurances(vector<string>& text) {
    map<string, int> occurances;

    for_each(text.begin(), text.end(), [&occurances](string str) {
        occurances[str]++;
    });
    return occurances;
}

template<typename Iter>
void print_occ(Iter M, bool left_shifted = false) {
    int length = get_length(M.begin(), M.end());

    for_each(M.begin(), M.end(), [&length, left_shifted](auto i) {
        if(i.first != "") {
            cout << setw(length);
            if (left_shifted) {
                cout << left;
            }
            cout << i.first << " " << i.second << endl;
        }
    });
}

void sort_print(map<string, int>& M) {
    vector<pair<string, int>> occ;

    copy(M.begin(), M.end(), back_inserter(occ));

    auto cmp = [](std::pair<string,int> const & a, std::pair<string,int> const & b) 
    { 
        return  a.second > b.second;
    };

    std::sort(occ.begin(), occ.end(), cmp);

    print_occ(occ);
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

void substitute(vector<string>& text, string parameter) {
    string old = parameter.substr(0, parameter.find("+"));
    string change = parameter.substr(parameter.find("+") + 1, -1);
    replace(text.begin(), text.end(), old, change); 
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
        vector<string> before_change{text};
        substitute(text, parameter);
        had_an_effect(splitted, before_change, text);     
    } else {
        throw invalid_argument(man_page());
    }
}

void apply_single_by_arg(string const& arg, vector<string>& text) {
    Argument single {arg, ""};

    if(single.flag == "--print") {
        auto print = [](const string& n) { std::cout << n << ' '; };

        print_container(cout, text, " ");
    }
    else if (single.flag == "--frequency" || single.flag == "--table") {
        map<string,int> occurances{build_occurances(text)};
        if (single.flag == "--frequency") {
            sort_print(occurances);
        } 
        else if (single.flag == "--table") {
            print_occ(occurances, true);
        }
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
    if(file.rdstate() != 0) {
        throw invalid_argument("Please provide a file!");
    }
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
            
            run_arguments(arguments, words);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << endl;
    }
    
    return 0;
}
