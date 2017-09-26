#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
#include <list>
using namespace std;
#define _min(a, b) a > b ? b : a


int main() {

    std::ifstream in;
    in.open("B-large-practice.in", std::iostream::in);
    FILE* out = fopen("kickstart.txt", "w");
    int T;
    in >> T;
    for (size_t i = 0; i < T; ++i) {
        int E, N;
        in >> E; in >> N;
        std::vector<int> S(N, 0);
        for (size_t j = 0; j < N; ++j) {
            in >> S[j];
        }
        std::sort(S.begin(), S.end());
        int H = 0; // honor
        size_t begin = 0, end = S.size() - 1;

        while (begin <= end) {
            if (E > S[begin]) {
                E -= S[begin];
                H++;
                begin++;
            }
            else if (H == 0 || begin == end) {
                break;
            }
            else {
                if (H > 0 ) {
                    E += S[end];
                    H--;
                    end--;
                }
                else {
                    
                    break;
                }
            }
        }
        fprintf(out, "Case #%d: %d\n", i + 1, H);
    }
    in.close();
    fclose(out);
    return 0;
}