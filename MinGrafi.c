#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int aggiungiGrafo(int d);
void maxHeapify (int topPath[], int topIndex[], int i, int k);

int main() {
    int d = 0, k = 0, l, i, n, nGrafo = 0, pathValue;
    char string[25];

    //printf("Inserisci i valori di d e k\n");
    if (fgets(string, 25, stdin) != NULL) {
        l = (int) strlen(string) - 2;
        n = 1;
        while (string[l] != ' ') {
            k = k + (string[l] - '0') * n;
            n = n * 10;
            l--;
        }
        l--;
        n = 1;
        while (l >= 0) {
            d = d + (string[l] - '0') * n;
            n = n * 10;
            l--;
        }

		
        //creo i due array per tenere in memoria l'indice del grafo e la corrispondente somma dei cammini minimi
        int topIndex[k], topPath[k];
        for (int i = 0; i < k; ++i) {
            topIndex[i] = -1;
            topPath[i] = -1;
        }
        //printf("Che azione vuoi fare?\n");
        while (fgets(string, 25, stdin) != NULL) {
            if (string[0] == 'A') {
                pathValue = aggiungiGrafo(d);
                //printf("topPath[%d] e' %d\n", nGrafo, pathValue);
                if (nGrafo == k){
                    for (int j = (k / 2) - 1; j >= 0; j--) {
                        maxHeapify(topPath, topIndex,j, k);
                    }
                }
                if (nGrafo < k){
                    //printf("\ni %d\n", i);
                    topPath[nGrafo] = pathValue;
                    topIndex[nGrafo] = nGrafo;
                } else {
                    if (pathValue < topPath[0]){
                        topPath[0] = pathValue;
                        topIndex[0] = nGrafo;
                        maxHeapify(topPath, topIndex,0, k);
                    }
                }
                nGrafo++;
            } else if (string[0] == 'T') {
                i = 0;
                while (i < k && i<nGrafo) {
                    printf("%d", topIndex[i]);
                    i++;
                    if (i < k && topIndex[i] != -1) { printf(" "); }

                }
                printf("\n");
            }
        }
    }
    return 0;
}

int aggiungiGrafo(int d) {
    int pathValue = 0, k, n, minCurr = 0, next = 0, t[d - 1], found = 0, minNext = 0, M[d][d], m, a, b, c, e,i, value=0;
    char string[d * 11 + 1];
    bool sameValue = true;

    for (int l = 0; l < d; l++) {
        //printf("Inserisci la riga della matrice\n");
        if (fgets(string, d * 11 + 1, stdin) != NULL) {
            m = (int) strlen(string) - 2;
            k = d-1;
            while (k > 0) {
                a = 0;
                n = 1;
                if (l != k) {
                    while (string[m] != ',') {
                        a = a + (string[m] - 48) * n;
                        n = n * 10;
                        m--;
                    }
                    M[l][k] = a;
                    if (k==d-1 && l == 0){
                        value = a;
                    } else if (value != a){
                        sameValue = false;
                    }
                    //printf(" M[%d][%d] %d\n", l, k, M[l][k]);
                } else {
                    M[l][k] = 0;
                    while (string[m] != ',') {
                        m--;
                    }
                }
                if (l == 0) {
                    if (M[l][k] != 0) {
                        b = M[0][k];
                        t[k-1] = b;
                        //printf("t[%d] %d\n", k,t[k]);
                        if (minCurr > b || minCurr == 0) {
                            minCurr = b;
                            next = k;
                            //printf("next %d\n", next);
                        }
                    } else {
                        t[k-1] = -1;
                        //printf("t[%d] %d\n", k,t[k]);
                        found++;
                    }
                }
                k--;
                m--;
            }
        }
    }
    if (found == d - 1) {
        return pathValue;
    }
    if (sameValue){
        pathValue = value*(d-1);
        return pathValue;
    }
    found = 0;
    i = next-1;
    //printf("i %d\n", i);
    while (minCurr != 0) {
        pathValue = pathValue + minCurr;
        //printf("pathValue %d\n", pathValue);
        t[i] = -2;
        found++;
        if (found < (d - 1)) {
            // minNext = 0;
            for (int j = 0; j < d; j++) {
                c = t[j];
                //printf("\nt[%d] e' %d\n", j, t[j]);
                //printf("M[%d][%d] e' %d\n", i+1, j+1,M[i+1][j+1]);
                //printf("minNext %d\n", minNext);
                if (c != -2 && j != i && M[i+1][j+1] != 0) {
                    e = M[i+1][j+1];
                    if (e != 0 && (c == -1 || c > (minCurr + e))) {
                        c = minCurr + e;
                        t[j] = c;
                    }
                }
                if (c > 0 && (minNext == 0 || minNext > c)) {
                    minNext = c;
                    next = j;
                }
            }
        }
        i = next;
        minCurr = minNext;
        minNext = 0;
    }
    return pathValue;
}


void maxHeapify (int topPath[], int topIndex[], int i, int k){
    int l, r, max, temp;
    l = 2 * i + 1;
    r = 2 * i + 2;
    if (l < k && topPath[l] > topPath[i]){
        max = l;
    } else {
        max = i;
    }
    if (r < k &&  topPath[r] > topPath[max]){
        max = r;
    }
    if (max != i){
        temp = topPath[max];
        topPath[max] = topPath[i];
        topPath[i] = temp;
        temp = topIndex[max];
        topIndex[max] = topIndex[i];
        topIndex[i] = temp;
        maxHeapify(topPath, topIndex, max, k);
    }
}
