#include "WFOpt.h"
#include <string>
#include <iostream>
using namespace std;

int Distance(const char* s, const char* t) {
    int M = strlen(s)+1;
    int N = strlen(t)+1;
    /*int* p1 = new int[N];
    int* p2 = new int[N];

    for (int i = 0; i < N; i++) {
        p1[i] = i;
    }

    for (int i = 1; i < M; i++) {
        p2[0] = i;
        for (int j = 1; j < N; j++) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            p2[j] = min({ p2[j - 1] + 1,
                           p1[j] + 1,
                           p1[j - 1] + cost });
        }
        
        swap(p1, p2);
    }

    int result = p2[M-1];

    delete[] p1;
    delete[] p2;*/

    int* p = new int[N];
    for (int i = 0; i < N; i++) {
        p[i] = i;
    }

    for (int i = 1; i < M; i++) {
        int prev = p[0];
        p[0] = i;

        for (int j = 1; j < N; j++) {
            int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
            int temp = p[j];
            p[j] = min({ prev + cost,
                           p[j] + 1,
                           p[j - 1] + 1 });
            prev = temp;
        }
    }

    int result = p[N-1];

    delete[] p;

    return result;
}