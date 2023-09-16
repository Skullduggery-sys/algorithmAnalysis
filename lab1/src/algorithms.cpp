#include "../inc/algorithms.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <memory>
using namespace std;

size_t loeNonRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2) {
    if (!s1->size() && !s2->size())
        return 0;
    else if (!s1->size() && s2->size())
        return s2->size();
    else if (s1->size() && !s2->size())
        return s1->size();


    vector<vector<size_t>> matrix(2, vector<size_t>(s2->size() + 1, 0));
    for (size_t i = 0; i < matrix[0].size(); i++)
        matrix[0][i] = i;

//    for (size_t j = 0; j < matrix[0].size(); j++)
//        cout << matrix[0][j] << " ";
//    cout << endl;


    for (size_t i = 1; i < s1->size() + 1; i++) {
        matrix[1][0] = matrix[0][0] + 1;
        if (i == 6)
            size_t j;
        for (size_t j = 1; j < matrix[0].size(); j++) {
            matrix[1][j] = min(min(matrix[1][j - 1] + 1, matrix[0][j] + 1), matrix[0][j - 1] + ((*s1)[i - 1] != (*s2)[j -1] ? 1 : 0));
            if (i == 6 && j == 7) {
                for (size_t j = 0; j < matrix[0].size(); j++)
                    cout << matrix[0][j] << " ";
                cout << endl;
            }
        }
        swap(matrix[1], matrix[0]);
        if (i == 6) {

        }

    }
    return matrix[0][s2->size()];
}

size_t damerauLoeNonRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2) {
    if (!s1->size() && !s2->size())
        return 0;
    else if (!s1->size() && s2->size())
        return s2->size();
    else if (s1->size() && !s2->size())
        return s1->size();

    vector<vector<size_t>> matrix(3, vector<size_t>(s2->size() + 1, 0));
    for (size_t i = 0; i < s2->size() + 1; i++)
        matrix[0][i] = i;
    matrix[1][0] = matrix[0][0] + 1;
    for (size_t j = 1; j < matrix[0].size(); j++) {
        matrix[1][j] = min(min(matrix[1][j - 1] + 1, matrix[0][j] + 1), matrix[0][j - 1] + ((*s1)[1] != (*s2)[j - 1] ? 1 : 0));
    }

    for (size_t i = 2; i < s1->size() + 1; i++) {
        matrix[2][0] = matrix[1][0] + 1;
        for (size_t j = 1; j < matrix[0].size(); j++) {
            matrix[2][j] = min(min(matrix[2][j - 1] + 1, matrix[1][j] + 1), matrix[1][j - 1] + ((*s1)[i - 1] != (*s2)[j - 1] ? 1 : 0));
            if ((*s1)[i - 1] == (*s2)[j] && (*s1)[i] == (*s2)[j - 1])
                matrix[2][j] = min(matrix[2][j], matrix[0][j - 2] + 1);
        }
        for (size_t j = 0; j < matrix[0].size(); j++)
            cout << matrix[2][j] << " ";
        cout << endl;
        swap(matrix[0], matrix[1]);
        swap(matrix[2], matrix[1]);
    }

    return matrix[1][matrix[0].size() - 1];
}


size_t damerauLoeRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2) {
    return _damerauLoeRec(s1, s2, s1->size(), s2->size());
}


size_t _damerauLoeRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2, size_t index1, size_t index2) {
    if (!index1) {
        return index2;
    } else if (!index2) {
        return index1;
    }

    size_t res = min(min(_damerauLoeRec(s1, s2, index1 - 1, index2) + 1, _damerauLoeRec(s1, s2, index1, index2 - 1) + 1),
                     _damerauLoeRec(s1, s2, index1 - 1, index2 - 1) + ((*s1)[index1 - 1] != (*s2)[index2 - 1] ? 1 : 0));
    if (index1 > 1 && index2 > 1 && (*s1)[index1 - 2] == (*s2)[index2 - 1] && (*s1)[index1 - 1] == (*s2)[index2 - 2]) {
        res = min(res, _damerauLoeRec(s1, s2, index1 - 1, index2 - 1));
    }

    return res;
}

size_t damerauLoeRecMem(shared_ptr<wstring> s1, shared_ptr<wstring> s2) {
    vector<vector<size_t>> cache(s1->size() + 1, vector<size_t>(s2->size() + 1, -1));
    return _damerauLoeRecMem(s1, s2, cache, s1->size(), s2->size());
}

size_t _damerauLoeRecMem(shared_ptr<wstring> s1, shared_ptr<wstring> s2, vector<vector<size_t>> cache, size_t index1, size_t index2) {
    if (!index1) {
        return index2;
    } else if (!index2) {
        return index1;
    }

    if (cache[index1 - 1][index2] == -1) {
        cache[index1 - 1][index2] = _damerauLoeRecMem(s1, s2, cache, index1 - 1, index2) + 1;
    }
    size_t insert = cache[index1 - 1][index2];

    if (cache[index1][index2 - 1] == -1) {
        cache[index1][index2 - 1] = _damerauLoeRecMem(s1, s2, cache, index1, index2 - 1) + 1;
    }
    size_t del = cache[index1][index2 - 1];

    if (cache[index1 - 1][index2 - 1] == -1) {
        cache[index1 - 1][index2 - 1] = _damerauLoeRecMem(s1, s2, cache, index1 - 1, index2 - 1) + ((*s1)[index1 - 1] != (*s2)[index2 - 1] ? 1 : 0);
    }
    size_t change = cache[index1 - 1][index2 - 1];

    size_t res = min(min(del, change),
                     insert);

    if (index1 > 1 && index2 > 1 && (*s1)[index1 - 2] == (*s2)[index2 - 1] && (*s1)[index1 - 1] == (*s2)[index2 - 2]) {
        if (cache[index1 - 2][index2 - 2] == -1) {
            cache[index1 - 2][index2 - 2] = _damerauLoeRecMem(s1, s2, cache, index1 - 2, index2 - 2);
        }
        size_t exchange = cache[index1 - 2][index2 - 2] + 1;
        res = min(res, exchange);
    }
    return res;
}