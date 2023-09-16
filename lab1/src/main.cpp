#include "../inc/algorithms.h"
#include <iostream>

int main() {
    shared_ptr<wstring> s2 = make_shared<wstring>(L"");
    shared_ptr<wstring> s1 = make_shared<wstring>(L"FDBGBG");
    size_t res = loeNonRec(s1, s2);
    cout << "Нерекурсивный Левенштейн: " << res << endl;
    res = damerauLoeNonRec(s1, s2);
    cout << "Нерекурсивный Дамерау: " << res << endl;
    res = damerauLoeRec(s1, s2);
    cout << "Рекурсивный Дамерау: " << res << endl;
    res = damerauLoeRecMem(s1, s2);
    cout << "Рекурсивный Дамерау c кэшем: " << res << endl;

}