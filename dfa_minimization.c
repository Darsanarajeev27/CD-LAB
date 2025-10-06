#include <stdio.h>
#include <string.h>
#define N 10

int trans[N][2], final[N], mark[N][N];

int main() {
    int n, i, j, f;
    printf("States: "); scanf("%d", &n);

    int fcount; 
    printf("No. of final states: "); scanf("%d", &fcount);
    memset(final, 0, sizeof(final));
    printf("Final states: ");
    for (i = 0; i < fcount; ++i) { scanf("%d", &f); final[f] = 1; }

    printf("Transitions (a b) for each state:\n");
    for (i = 0; i < n; ++i) {
        printf("State %d: ", i);
        scanf("%d %d", &trans[i][0], &trans[i][1]);
    }
    memset(mark, 0, sizeof(mark));
    for (i = 0; i < n; ++i)
        for (j = 0; j < i; ++j)
            if (final[i] != final[j]) mark[i][j] = 1;

    int changed;
    do {
        changed = 0;
        for (i = 0; i < n; ++i)
            for (j = 0; j < i; ++j)
                if (!mark[i][j])
                    for (int s = 0; s < 2; ++s) {
                        int p = trans[i][s], q = trans[j][s];
                        if (p > q) { int t = p; p = q; q = t; }
                        if (mark[q][p]) { mark[i][j] = 1; changed = 1; break; }
                    }
    } while (changed);

    printf("\nEquivalent groups:\n");
    int done[N] = {0};
    for (i = 0; i < n; ++i) {
        if (done[i]) continue;
        printf("{ ");
        for (j = 0; j < n; ++j)
            if (i == j || (i > j && !mark[i][j]) || (j > i && !mark[j][i]))
                printf("%d ", j), done[j] = 1;
        printf("}\n");
    }
}
