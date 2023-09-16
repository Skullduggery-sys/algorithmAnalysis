#ifndef ALGORITHMANALYSIS_ALGORITHMS_H
#define ALGORITHMANALYSIS_ALGORITHMS_H

#include <string>
using namespace std;
#include <memory>
#include <vector>

size_t loeNonRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2);

size_t damerauLoeNonRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2);

size_t damerauLoeRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2);

size_t _damerauLoeRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2, size_t index1, size_t index2);

size_t _damerauLoeRecMem(shared_ptr<wstring> s1, shared_ptr<wstring> s2, vector<vector<size_t>> cache, size_t index1, size_t index2);

size_t damerauLoeRecMem(shared_ptr<wstring> s1, shared_ptr<wstring> s2);

#endif //ALGORITHMANALYSIS_ALGORITHMS_H
