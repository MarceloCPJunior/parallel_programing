/* Baseline 08 — Contagem de k-mers em sequencia (frequencia de subcadeias)
 * IESB 2026/2 — CCO085 — Prof. Rodrigo Goncalves Pinto
 * Aspecto interessante: reducao sobre estrutura associativa; particionamento
 * de dados e combinacao dos histogramas parciais em MPI.
 *
 * Compilar: g++ -O2 -o 08_kmers 08_kmers.cpp
 * Executar: ./08_kmers 40000000 6   (tamanho da sequencia; k)
 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <cstdint>
#include <ctime>
using namespace std;

static double agora() {
    timespec t; clock_gettime(CLOCK_MONOTONIC, &t);
    return t.tv_sec + t.tv_nsec * 1e-9;
}

int main(int argc, char** argv) {
    long n = (argc > 1) ? atol(argv[1]) : 40000000L;
    int k = (argc > 2) ? atoi(argv[2]) : 6;   // alfabeto {A,C,G,T} => 4^k buckets
    if (k > 12) { printf("use k <= 12\n"); return 1; }

    // sequencia sintetica deterministica sobre {0,1,2,3}
    vector<uint8_t> seq(n);
    uint64_t s = 987654321ULL;
    for (long i = 0; i < n; i++) { s = s*6364136223846793005ULL + 1; seq[i] = (s >> 62) & 3; }

    long buckets = 1L << (2*k);
    vector<long> hist(buckets, 0);

    double t0 = agora();
    long mask = buckets - 1;
    long code = 0;
    for (int i = 0; i < k-1 && i < n; i++) code = ((code << 2) | seq[i]) & mask;
    for (long i = k-1; i < n; i++) {
        code = ((code << 2) | seq[i]) & mask;
        hist[code]++;
    }
    double t1 = agora();

    long total = 0, maxc = 0;
    for (long i = 0; i < buckets; i++) { total += hist[i]; if (hist[i] > maxc) maxc = hist[i]; }
    printf("n=%ld k=%d  total_kmers=%ld  max_freq=%ld  tempo=%.6f s\n", n, k, total, maxc, t1 - t0);
    return 0;
}
