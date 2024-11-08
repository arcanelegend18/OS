#include <stdio.h>

#define MAX_PROC 10
#define MAX_RES 10

void calculateNeed(int n, int m, int max[MAX_PROC][MAX_RES], int alloc[MAX_PROC][MAX_RES], int need[MAX_PROC][MAX_RES]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }
}

int isSafe(int n, int m, int available[], int need[MAX_PROC][MAX_RES], int alloc[MAX_PROC][MAX_RES]) {
    int work[MAX_RES];
    int count = 0;
    int finish[MAX_PROC] = {0};
    int safeSeq[MAX_PROC];
    
    for(int i = 0; i < m; i++) {
        work[i] = available[i];
    }
    
    while(count < n) {
        int found = 0;
        for(int i = 0; i < n; i++) {
            if(!finish[i]) {
                int j;
                for(j = 0; j < m; j++) {
                    if(need[i][j] > work[j]) {
                        break;
                    }
                }
                
                if(j == m) {
                    for(int k = 0; k < m; k++) {
                        work[k] += alloc[i][k];
                    }
                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        
        if(!found) {
            printf("Deadlock detected. Process involved in deadlock: \n");
            for(int i = 0; i < n; i++) {
                if(!finish[i]) {
                    printf("P%d", i);
                }
            }
            printf("\n");
            return 0;
        }
    }
    
    printf("System is in safestate.\nSafe sequence: ");
    for(int i = 0; i < n; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");
    return 1;
}

int main() {
    int n, m;
    int max[MAX_PROC][MAX_RES], alloc[MAX_PROC][MAX_RES], need[MAX_PROC][MAX_RES], available[MAX_RES];
    
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the number of resources: ");
    scanf("%d", &m);
    
    printf("Enter the max matrix: \n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }
    
    printf("Enter the allocation matrix: \n");
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }
    
    printf("Enter the available matrix: \n");
    for(int i = 0; i < m; i++) {
        scanf("%d", &available[i]);
    }
    
    calculateNeed(n, m, max, alloc, need);
    
    isSafe(n, m, available, need, alloc);
    
    return 0;
}



