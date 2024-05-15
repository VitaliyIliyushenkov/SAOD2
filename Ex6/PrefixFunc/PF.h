#include <string.h>
#include <stdexcept>

class PF {
public:
    PF() {
        pv = nullptr; 
        n = 0; 
        cmpCount = 0;
    }

    ~PF() {
        delete[] pv;
    }

    int intCmpCount() {
        return cmpCount;
    }

    void Init(const char* s) {
        cmpCount = 0;
        n = strlen(s);
        pv = new int[n];

        pv[0] = 0;
        for (int i = 1; i < n; i++) {
            int j = pv[i - 1];
            while (j > 0 && s[i] != s[j]) {
                j = pv[j - 1];
                cmpCount++;
            }
            if (s[i] == s[j]) {
                j++;
            }
            pv[i] = j;
        }
    }

    operator int() const {
        return n;
    }

    int operator[](int i) const {
        if (i < 0 || i >= n) {  
            throw std::out_of_range("Index out of range");
        }
        return pv[i];
    }

private:
    int cmpCount;
    int* pv;
    int n;
};