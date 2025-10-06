#include <stdio.h>
#include <string.h>

#define MAX 20  // max NFA states
#define MAX_STATES (1<<MAX)  // max possible DFA states (bitmask)
#define MAX_SYM 10            // max input symbols

int nfa[MAX][MAX];            // NFA transitions as bitmask
int dfa[MAX_STATES][MAX_SYM]; // DFA transitions (sparse)
int vis[MAX_STATES];          // visited DFA states
int states[MAX_STATES];       // list of discovered DFA states
int ns, ni;                   // number of NFA states, symbols
char syms[MAX_SYM];

// Compute next DFA state from a given set and input symbol
int nextState(int set, int sym) {
    int nxt = 0;
    for (int i = 0; i < ns; i++)
        if (set & (1<<i))
            nxt |= nfa[i][sym];
    return nxt;
}

// Print a bitmask set as {0 2 3}
void printSet(int set) {
    printf("{ ");
    for (int i = 0; i < ns; i++)
        if (set & (1<<i)) printf("%d ", i);
    printf("}");
}

// Convert NFA to DFA
void nfaToDfa() {
    int q[MAX_STATES], f=0, r=0, cnt=0;

    int start = 1; // start state = {0} bitmask
    states[cnt++] = start;
    vis[start] = 1;
    q[r++] = start;

    while (f < r) {
        int cur = q[f++];
        for (int s = 0; s < ni; s++) {
            int nxt = nextState(cur, s);
            dfa[cur][s] = nxt;
            if (nxt && !vis[nxt]) {
                vis[nxt] = 1;
                states[cnt++] = nxt;
                q[r++] = nxt;
            }
        }
    }

    printf("\nDFA transitions:\n");
    for (int i=0; i<cnt; i++) {
        printSet(states[i]); printf(":\n");
        for (int s=0; s<ni; s++) {
            printf("  '%c' -> ", syms[s]);
            printSet(dfa[states[i]][s]);
            printf("\n");
        }
    }
}

int main() {
    printf("States: "); scanf("%d",&ns);
    if (ns > MAX) { printf("Max %d states supported\n", MAX); return 1; }

    printf("Symbols: "); scanf("%d",&ni);
    for (int i=0;i<ni;i++) scanf(" %c",&syms[i]);

    // initialize NFA transitions
    for (int i=0;i<MAX;i++)
        for (int j=0;j<MAX;j++)
            nfa[i][j] = 0;

    int nt; 
    printf("Transitions: "); scanf("%d",&nt);
    printf("<from> <symbol> <to>:\n");
    for (int i=0;i<nt;i++) {
        int f,t; char c;
        scanf("%d %c %d",&f,&c,&t);
        int idx = -1;
        for (int j=0;j<ni;j++) if(syms[j]==c) idx=j;
        if(idx==-1) { printf("Invalid symbol!\n"); return 1; }
        nfa[f][idx] |= 1<<t;
    }

    nfaToDfa();
    return 0;
}
