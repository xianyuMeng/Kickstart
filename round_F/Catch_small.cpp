#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

void Markov(std::vector<float>& state, float* time, int P, std::vector<float>& row_map) {

    int N = state.size();
    int extra = P >= N ? P % N : P;

    for (size_t i = 0; i < P; ++i) {
        std::vector<float> cur(N, 0);
        float total = 1.0f;
        for (size_t j = 0; j < N; ++j) {
            cur[j] = (total - state[j]) / float(N - 1);
        }
        for (size_t j = 0; j < N; ++j) {
            (*time) += float(row_map[j]) * state[j];
        }
        state = cur;
    }
}

int main() {
    std::ifstream in;
    in.open("C-small-practice.in", std::iostream::in);
    FILE* out = fopen("catch_new.in", "w");

    int T;
    in >> T;
    for (size_t i = 0; i < T; ++i) {
        int N, M, P;
        in >> N >> M >> P;
        __int64** map = new __int64*[N];
        for (size_t j = 0; j < N; ++j) {
            map[j] = new __int64[N];
        }
        for (size_t j = 0; j < N; ++j) {
            for (size_t k = 0; k < N; ++k) {
                if (j == k) {
                    map[j][k] = 0;
                }
                else {
                    map[j][k] = std::numeric_limits<int>::max();
                }
            }
        }
        for (size_t j = 0; j < M; ++j) {
            int U, V, D;
            in >> U >> V >> D;
            map[U - 1][V - 1] = __int64(D);
            map[V - 1][U - 1] = __int64(D);
        }

        //Floyd-Warshall
        //O(N^3) time complexity, O(N^2) space complexity
        for (size_t kk = 0; kk < N; ++kk) {
            for (size_t ii = 0; ii < N; ++ii) {
                for (size_t jj = 0; jj < N; ++jj) {
                    if (((map[ii][jj])) > ((map[ii][kk] + map[kk][jj]))) {
                        map[ii][jj] = map[ii][kk] + map[kk][jj];
                    }
                }
            }
        }

        std::vector<float> row_map(N, 0);
        for (size_t ii = 0; ii < N; ++ii) {
            for (size_t jj = 0; jj < N; ++jj) {
                row_map[ii] += map[ii][jj];
            }
            row_map[ii] /= float(N - 1);
        }
        float time = 0;
        // Initial state of markov chain
        std::vector<float> State(N, 0);
        State[0] = 1;
        Markov(State, &time, P, row_map);
        fprintf(out, "Case #%d: %f\n", i + 1, time);

        for (size_t j = 0; j < N; ++j) {
            delete[] map[j];
            map[j] = nullptr;
        }
        delete[] map;
        map = nullptr;
    }

    in.close();
    fclose(out);
    return 0;
}
