#include <stdio.h>
#include <stdlib.h>

#define MAX 20

int numStates, numSymbols;
char symbols[MAX]; // Input symbols (excluding epsilon)
int transition[MAX][MAX][MAX]; // state -> input -> list of next states
int epsilon[MAX][MAX];        // state -> list of epsilon transitions 
int epsilonClosure[MAX][MAX];  // epsilon closure for each state
int closureSize[MAX];

int newTrans[MAX][MAX][MAX];
int newTransSize[MAX][MAX];

int visited[MAX];

// Add transition
void addTransition(int from, char symbol, int to) {
    int idx = -1;
    for (int i = 0; i < numSymbols; i++) {
        if (symbols[i] == symbol) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        int k = 0;
        while (transition[from][idx][k] != -1) k++;
        transition[from][idx][k] = to;
    }
}

// Add epsilon transition
void addEpsilon(int from, int to) {
    int k = 0;
    while (epsilon[from][k] != -1) k++;
    epsilon[from][k] = to;
}

// DFS for epsilon closure
void dfsClosure(int state, int closure[], int* size) {
    if (visited[state]) return;
    visited[state] = 1;
    closure[(*size)++] = state;
    for (int i = 0; epsilon[state][i] != -1; i++) {
        dfsClosure(epsilon[state][i], closure, size);
    }
}

// Compute epsilon closures
void computeClosures() {
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numStates; j++) visited[j] = 0;
        closureSize[i] = 0;
        dfsClosure(i, epsilonClosure[i], &closureSize[i]);
    }
}

// Build new transitions (no epsilon)
void buildNewTransitions() {
    for (int s = 0; s < numStates; s++) {
        for (int a = 0; a < numSymbols; a++) {
            int reached[MAX] = {0};
            for (int i = 0; i < closureSize[s]; i++) {
                int eState = epsilonClosure[s][i];
                for (int j = 0; transition[eState][a][j] != -1; j++) {
                    int t = transition[eState][a][j];
                    for (int k = 0; k < closureSize[t]; k++) {
                        int r = epsilonClosure[t][k];
                        reached[r] = 1;
                    }
                }
            }

            int count = 0;
            for (int i = 0; i < numStates; i++) {
                if (reached[i]) {
                    newTrans[s][a][count++] = i;
                }
            }
            newTransSize[s][a] = count;
        }
    }
}

void printNewTransitions() {
    printf("\nTransitions of NFA without epsilon transitions:\n");
    for (int s = 0; s < numStates; s++) {
        for (int a = 0; a < numSymbols; a++) {
            printf("δ(%d, %c) = { ", s, symbols[a]);
            for (int i = 0; i < newTransSize[s][a]; i++) {
                printf("%d ", newTrans[s][a][i]);
            }
            printf("}\n");
        }
    }
}

int main() {
    int numEps;
    printf("Enter number of states: ");
    scanf("%d", &numStates);

    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &numSymbols);
    printf("Enter symbols: ");
    for (int i = 0; i < numSymbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    // Initialize all
    for (int i = 0; i < numStates; i++) {
        for (int j = 0; j < numSymbols; j++) {
            for (int k = 0; k < MAX; k++) {
                transition[i][j][k] = -1;
                newTrans[i][j][k] = -1;
            }
            newTransSize[i][j] = 0;
        }
        for (int j = 0; j < MAX; j++) {
            epsilon[i][j] = -1;
            epsilonClosure[i][j] = -1;
        }
    }

    int numTrans;
    printf("Enter number of transitions (excluding epsilon): ");
    scanf("%d", &numTrans);
    printf("Enter transitions in form <from> <symbol> <to>:\n");
    for (int i = 0; i < numTrans; i++) {
        int u, v;
        char c;
        scanf("%d %c %d", &u, &c, &v);
        addTransition(u, c, v);
    }

    printf("Enter number of epsilon transitions: ");
    scanf("%d", &numEps);
    printf("Enter epsilon transitions in form <from> <to>:\n");
    for (int i = 0; i < numEps; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEpsilon(u, v);
    }

    computeClosures();
    buildNewTransitions();
    printNewTransitions();

    return 0;
}
