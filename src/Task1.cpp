#include <iostream>
#include <vector>
#include <string>

using namespace std;

template<class F>
void bubbleSort(vector<string>& strs, F comparator) 
{
    size_t n = strs.size();
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n - 1; j++) {
            if (!comparator(strs[j], strs[j + 1])) {
                std::swap(strs[j], strs[j + 1]);
            }
        }
    }
}

ostream& operator<<(ostream& out, vector<string>& strs) 
{
    for (auto& i : strs) {
        out << i << " ";
    }
    return out;
}

int main() 
{
    vector<string> strs = { "abs", "ABS", "fruit", "smth", "math", "Dragon", "fox", "Gouse", "Box" };
    cout << strs << endl;
    bubbleSort(strs, [](const string& first, const string& second) {return first > second; });
    cout << strs << endl;
    bubbleSort(strs, [](const string& first, const string& second) {return first < second; });
    cout << strs << endl;
    bubbleSort(strs, [](const string& first, const string& second) {return first.size() > second.size(); });
    cout << strs << endl;
    bubbleSort(strs, [](const string& first, const string& second) {return first.size() < second.size(); });
    cout << strs << endl;
    bubbleSort(strs, [](const string& first, const string& second) {return first[0] > second[0]; });
    cout << strs << endl;
}