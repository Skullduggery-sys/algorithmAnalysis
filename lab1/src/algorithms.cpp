#include "../inc/algorithms.h"
#include <string>
#include <vector>
#include <algorithm>
#include <memory>
using namespace std;

size_t loeNonRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2) {
    if (!s1->size() && !s2->size())
        return 0;
    else if (!s1->size() && s2->size())
        return s2->size();
    else if (s1->size() && !s2->size())
        return s1->size();


    vector<vector<size_t>> matrix(2, vector<size_t>(s2->size(), 0));
    for (size_t i = 0; i < matrix[0].size(); i++)
        matrix[0][i] = i;


    for (size_t i = 1; i < s1->size(); i++) {
        for (size_t j = 0; j < matrix[0].size(); j++) {
            if (!j) {
                matrix[1][j] = matrix[0][j] + 1;
                continue;
            }
            matrix[1][j] = min(min(matrix[1][j - 1], matrix[0][j]), matrix[0][j - 1]);
            if ((*s1)[i] != (*s2)[j])
                ++matrix[1][j];
        }
        swap(matrix[1], matrix[0]);
    }
    return matrix[0][s2->size() - 1];
}
