#include <stdio.h>

#define MAX_PROCESSES 10
#define QUANTUM 2

typedef struct {
    int process_id;
    int burst_time;
    int remaining_time;
    int waiting_time;
    int turn_around_time;
} Process;

void get_waiting_time(Process processes[], int n) {
    int i;
    processes[0].waiting_time = 0;
    for (i = 1; i < n; i++) {
        processes[i].waiting_time = processes[i - 1].waiting_time + processes[i - 1].burst_time;
    }
}

void get_turn_around_time(Process processes[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        processes[i].turn_around_time = processes[i].burst_time + processes[i].waiting_time;
    }
}

void print_table(Process processes[], int n) {
    int i;
    printf("Process ID\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].burst_time, processes[i].waiting_time, processes[i].turn_around_time);
    }
}

int main() {
    int i, n;
    Process processes[MAX_PROCESSES];

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        processes[i].process_id = i + 1;
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

    int time = 0;
    int done = 0;
    while (done < n) {
        for (i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > QUANTUM) {
                    time += QUANTUM;
                    processes[i].remaining_time -= QUANTUM;
                } else {
                    time += processes[i].remaining_time;
                    processes[i].remaining_time = 0;
                    done++;
                }
            }
        }
    }

    get_waiting_time(processes, n);
    get_turn_around_time(processes, n);
    print_table(processes, n);

    return 0;
}
