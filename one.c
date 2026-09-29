#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct {
int id;
int at;
int bt1;
int bt2;
int io_wait;
int io_done;
int ready_time;
int rem_bt1;
int rem_bt2;
int ct;
int tat;
int wt;
int completed;
} Process;
int main() {
int n, tq, i;
srand(time(NULL));
printf("Enter number of processes: ");
if(scanf("%d", &n) != 1) return 0;
Process p[20];
for(i = 0; i < n; i++) {
p[i].id = i + 1;
printf("Process P%d - Arrival Time: ", i + 1);
scanf("%d", &p[i].at);
printf("Process P%d - First CPU Burst: ", i + 1);
scanf("%d", &p[i].bt1);
p[i].bt2 = (rand() % 10) + 1;
p[i].io_wait = 2;
p[i].io_done = 0;
p[i].ready_time = p[i].at;
p[i].rem_bt1 = p[i].bt1;
p[i].rem_bt2 = p[i].bt2;
p[i].completed = 0;
printf("Process P%d - Fixed I/O Wait: 2 units, Next CPU Burst (random): %d\n", i + 1, p[i].bt2);
}
printf("Enter Time Quantum: ");
scanf("%d", &tq);
int current_time = 0, completed_cnt = 0;
int gantt_p[300], gantt_t[300], g_cnt = 0;
gantt_t[0] = 0;
while(completed_cnt < n) {
int acted = 0;
for(i = 0; i < n; i++) {
if(!p[i].completed && p[i].ready_time <= current_time) {
if(p[i].rem_bt1 > 0) {
acted = 1;
int run = (p[i].rem_bt1 > tq) ? tq : p[i].rem_bt1;
p[i].rem_bt1 -= run;
current_time += run;
gantt_p[g_cnt] = p[i].id;
gantt_t[g_cnt + 1] = current_time;
g_cnt++;
if(p[i].rem_bt1 == 0) {
p[i].io_done = 1;
p[i].ready_time = current_time + p[i].io_wait;
}
} else if(p[i].rem_bt2 > 0) {
acted = 1;
int run = (p[i].rem_bt2 > tq) ? tq : p[i].rem_bt2;
p[i].rem_bt2 -= run;
current_time += run;
gantt_p[g_cnt] = p[i].id;
gantt_t[g_cnt + 1] = current_time;
g_cnt++;
if(p[i].rem_bt2 == 0) {
p[i].completed = 1;
p[i].ct = current_time;
p[i].tat = p[i].ct - p[i].at;
p[i].wt = p[i].tat - (p[i].bt1 + p[i].bt2 + p[i].io_wait);
completed_cnt++;
}
}
}
}
if(!acted) {
current_time++;
}
}
printf("\nGantt Chart:\n|");
for(i = 0; i < g_cnt; i++) printf(" P%d |", gantt_p[i]);
printf("\n%d", gantt_t[0]);
for(i = 0; i < g_cnt; i++) printf("    %d", gantt_t[i + 1]);
printf("\n\nProcess\tAT\tBT1\tIO\tBT2\tCT\tTAT\tWT\n");
float total_tat = 0, total_wt = 0;
for(i = 0; i < n; i++) {
total_tat += p[i].tat;
total_wt += p[i].wt;
printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt1, p[i].io_wait, p[i].bt2, p[i].ct, p[i].tat, p[i].wt);
}
printf("\nAverage Turnaround Time = %.2f\n", total_tat / n);
printf("Average Waiting Time = %.2f\n", total_wt / n);
return 0;
}
