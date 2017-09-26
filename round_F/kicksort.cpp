#include <iostream>
#include <memory>
#include <vector>
#include <fstream>

using namespace std;
#define _min(a, b) a > b ? b : a


std::vector<int> kicksort(std::vector<int>& A, bool* Isempty) {
    if (A.size() <= 1) {
        return A;
    }
    else {
        vector<int> B, C;
        int E = A.size();
        int pivot = A[(E - 1) / 2];
        for (size_t i = 0; (i <= (E - 1)); ++i) {
            if (i == (E - 1) / 2) {
                continue;
            }
            else {
                if (A[i] <= pivot) {
                    B.push_back(A[i]);
                }
                else {
                    C.push_back(A[i]);
                }
            }
        }
        if (!((B.size() == (E - 1) && C.size() == 0) ||
            (B.size() == 0 && C.size() == (E - 1)))) {
            (*Isempty) = true;
            return A;
        }
        else {
            bool b = false, c = false;
            std::vector<int> B_sort = kicksort(B, &b);
            std::vector<int> C_sort = kicksort(C, &c);
            if (b) {
                (*Isempty) = true;
                return B_sort;
            }
            else if (c) {
                (*Isempty) = true;
                return C_sort;
            }
            else {
                B_sort.push_back(pivot);
                for (auto i : C_sort) {
                    B_sort.push_back(i);
                }
                return B_sort;
            }
        }
    }
}
int main() {

    std::ifstream in;
    in.open("A-large-practice.in", std::iostream::in);
    FILE* out = fopen("kickstart.txt", "w");
    int T;
    in >> T;
    for (size_t i = 0; i < T; ++i) {
        int N;
        in >> N;
        std::vector<int> A(N, 0);
        for (size_t j = 0; j < N; ++j) {
            in >> A[j];
        }
        bool emp = false;
        std::vector<int> sort = kicksort(A, &emp);

        fprintf(out, "Case #%d: %s\n", i + 1, emp ? "NO" : "YES");
    }
    in.close();
    fclose(out);
    return 0;
}