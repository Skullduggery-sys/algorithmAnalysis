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

    for (size_t j = 0; j < matrix[0].size(); j++)
        cout << matrix[0][j] << " ";
    cout << endl;


    for (size_t i = 1; i < s1->size() + 1; i++) {
        matrix[1][0] = matrix[0][0] + 1;
        for (size_t j = 1; j < matrix[0].size(); j++) {
            matrix[1][j] = min(min(matrix[1][j - 1], matrix[0][j]), matrix[0][j - 1]);
            if ((*s1)[i] != (*s2)[j])
                ++matrix[1][j];
        }
        swap(matrix[1], matrix[0]);
        for (size_t j = 0; j < matrix[0].size(); j++)
            cout << matrix[0][j] << " ";
        cout << endl;
    }
    return matrix[0][s2->size() - 1];
}

size_t damerauLoeNonRec(shared_ptr<wstring> s1, shared_ptr<wstring> s2) {
    if (!s1->size() && !s2->size())
        return 0;
    else if (!s1->size() && s2->size())
        return s2->size();
    else if (s1->size() && !s2->size())
        return s1->size();

    vector<vector<size_t>> matrix(3, vector<size_t>(s2->size(), 0));
    for (size_t i = 0; i < s2->size(); i++)
        matrix[0][i] = i;
    matrix[1][0] = matrix[0][0] + 1;
    for (size_t j = 1; j < matrix[0].size(); j++) {
        matrix[1][j] = min(min(matrix[1][j - 1], matrix[0][j]), matrix[0][j - 1]);
        if ((*s1)[1] != (*s2)[j])
            ++matrix[1][j];
    }

    for (size_t i = 2; i < s1->size(); i++) {
        matrix[2][0] = matrix[1][0] + 1;
        for (size_t j = 1; j < matrix[0].size(); j++) {
            matrix[2][j] = min(min(matrix[2][j - 1], matrix[1][j]), matrix[1][j - 1]) + (*s1)[i] == (*s2)[j] ? 0 : 1;
            if ((*s1)[i - 1] == (*s2)[j] && (*s1)[i] == (*s2)[j - 1])
                matrix[2][j] = min(matrix[2][j], matrix[0][j - 2] + 1);
        }

        swap(matrix[0], matrix[1]);
        swap(matrix[2], matrix[1]);
    }

    return matrix[1][matrix[0].size() - 1];
}