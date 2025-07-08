
#include <stdio.h>

typedef struct {
    int pid;
    int bt;
    int wt;
    int tat;
    int remaining_bt;
} Process;

void fcfs(Process p[], int n) {
    int total_wt = 0, total_tat = 0;
    p[0].wt = 0;

    for (int i = 1; i < n; i++) {
        p[i].wt = p[i-1].wt + p[i-1].bt;
    }

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nFCFS Scheduling:\n");
    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("Average WT: %.2f\n", total_wt / (float)n);
    printf("Average TAT: %.2f\n", total_tat / (float)n);
}

void round_robin(Process p[], int n, int quantum) {
    int time = 0, done;
    int total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) {
        p[i].remaining_bt = p[i].bt;
        p[i].wt = 0;
    }

    do {
        done = 1;
        for (int i = 0; i < n; i++) {
            if (p[i].remaining_bt > 0) {
                done = 0;
                if (p[i].remaining_bt > quantum) {
                    time += quantum;
                    p[i].remaining_bt -= quantum;
                } else {
                    time += p[i].remaining_bt;
                    p[i].wt = time - p[i].bt;
                    p[i].remaining_bt = 0;
                }
            }
        }
    } while (!done);

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].bt + p[i].wt;
        total_wt += p[i].wt;
        total_tat += p[i].tat;
    }

    printf("\nRound Robin (q=%d):\n", quantum);
    printf("PID\tBT\tWT\tTAT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tat);
    }
    printf("Average WT: %.2f\n", total_wt / (float)n);
    printf("Average TAT: %.2f\n", total_tat / (float)n);
}

int main() {
    int n, choice, quantum;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    Process p[n];
    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("Enter Burst Time for P%d: ", p[i].pid);
        scanf("%d", &p[i].bt);
    }

    printf("\nChoose Scheduling Algorithm:\n1. FCFS\n2. Round Robin\nChoice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        fcfs(p, n);
    } else if (choice == 2) {
        printf("Enter Time Quantum: ");
        scanf("%d", &quantum);
        round_robin(p, n, quantum);
    } else {
        printf("Invalid choice.\n");
    }

    return 0;
}
