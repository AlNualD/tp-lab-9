//#include <iostream>
//#include <vector>
//#include <string>
//#include <thread>
//#include <mutex>
//
//
//using namespace std;
//
//bool sortIsFinished = false;
//bool stepChanged = false;
//bool isPrinted = true;
//
//mutex mut;
//condition_variable cv;
//
//
//void bubbleSort(vector<string>& strs, bool (*comparator) (const string&, const string&))
//{
//    size_t n = strs.size();
//    for (size_t i = 0; i < n; i++) {
//        unique_lock<mutex> lock(mut);
//        cv.wait(lock, []() { return isPrinted; });
//        for (size_t j = 0; j < n - 1; j++) {
//            if (!comparator(strs[j], strs[j + 1])) {
//                std::swap(strs[j], strs[j + 1]);
//            }
//        }
//        stepChanged = true;
//        isPrinted = false;
//        lock.unlock();
//        cv.notify_all();
//    }
//    sortIsFinished = true;
//}
//
//ostream& operator<<(ostream& out, vector<string>& strs)
//{
//    for (auto& i : strs) {
//        out << i << " ";
//    }
//    return out;
//}
//
//int main()
//{
//    vector<string> strs = { "abs", "ABS", "fruit", "smth", "math", "Dragon", "fox", "Gouse", "Box" };
//    cout << strs << endl;
//    bool (*cmp) (const string&, const string&) = [](const string& first, const string& second) -> bool {return first > second; };
//    thread w(bubbleSort, ref(strs), cmp);
//    cv.notify_all();
//    while (!sortIsFinished) {
//        unique_lock<mutex> lk(mut);
//        cv.wait(lk, []() { return stepChanged; });
//        cout << strs << endl;
//        stepChanged = false;
//        isPrinted = true;
//        lk.unlock();
//        cv.notify_all();
//    }
//    sortIsFinished = false;
//    w.join();
//}