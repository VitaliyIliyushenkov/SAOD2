#include <iostream>
#include <string>
using namespace std;

class WF {
public:
    int* pm;
    int M;
    int N;

    WF() : pm(nullptr), M(0), N(0) {}
    WF(int m, int n) : pm(new int[m * n]), M(m), N(n) {}

    ~WF() { delete[] pm; }

    void Init(const char* sc, const char* tc) {
        string s(sc), t(tc);
        M = s.length()+1;
        N = t.length()+1;
        pm = new int[M * N];

        for (int i = 0; i < M; i++) {
            for (int j = 0; j < N; j++) {
                if (i == 0 || j == 0) {
                    pm[i * N + j] = max(i, j);
                }
                else {
                    int cost = (s[i - 1] == t[j - 1]) ? 0 : 1;
                    pm[i * N + j] = min({ pm[(i - 1) * N + j] + 1,
                                        pm[i * N + (j - 1)] + 1,
                                        pm[(i - 1) * N + (j - 1)] + cost });
                }
            }
        }
    }

    int intRows() const { return M; }
    int intColumns() const { return N; }

    int intGet(int i, int j) const {
        if (i < 0 || i >= M || j < 0 || j >= N)
            throw out_of_range("WF::intGet: Index out of range");
        return pm[i * N + j];
    } 

    void voidSet(int i, int j, int val) {
        if (i < 0 || i >= M || j < 0 || j >= N)
            throw out_of_range("WF::voidSet: Index out of range");
        pm[i * N + j] = val;
    }

    int intDistance() const {
        return pm[M * N - 1];
    }
private:
    WF(const WF& other) = delete;
    WF& operator=(const WF& other) = delete; 
};