#include "../inc/algorithms.h"
#include <iostream>

int main() {
    shared_ptr<wstring> s1 = make_shared<wstring>(L"polynomial");
    shared_ptr<wstring> s2 = make_shared<wstring>(L"exponential");
    size_t res = loeNonRec(s1, s2);
    cout << res;

}