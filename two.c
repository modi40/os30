#include <stdio.h>
#include <stdlib.h>
int main() {
int ref[] = {2, 5, 2, 8, 5, 4, 1, 2, 3, 2, 6, 1, 2, 5, 9, 8};
int n_pages = sizeof(ref) / sizeof(ref[0]);
int n_frames, i, j, k, faults = 0;
printf("Reference String: ");
for(i = 0; i < n_pages; i++) printf("%d ", ref[i]);
printf("\nEnter number of frames: ");
if(scanf("%d", &n_frames) != 1) return 0;
int frames[20], freq[20], load_time[20];
for(i = 0; i < n_frames; i++) {
frames[i] = -1;
freq[i] = 0;
load_time[i] = 0;
}
printf("\nPage\tFrames\t\t\tPage Fault\n");
for(i = 0; i < n_pages; i++) {
int page = ref[i];
int found = 0;
for(j = 0; j < n_frames; j++) {
if(frames[j] == page) {
found = 1;
freq[j]++;
break;
}
}
char status[4] = "No";
if(!found) {
faults++;
status[0] = 'Y'; status[1] = 'e'; status[2] = 's'; status[3] = '\0';
int empty_slot = -1;
for(j = 0; j < n_frames; j++) {
if(frames[j] == -1) {
empty_slot = j;
break;
}
}
if(empty_slot != -1) {
frames[empty_slot] = page;
freq[empty_slot] = 1;
load_time[empty_slot] = i;
} else {
int max_freq = -1, mfu_idx = 0;
for(j = 0; j < n_frames; j++) {
if(freq[j] > max_freq) {
max_freq = freq[j];
mfu_idx = j;
} else if(freq[j] == max_freq && load_time[j] < load_time[mfu_idx]) {
mfu_idx = j;
}
}
frames[mfu_idx] = page;
freq[mfu_idx] = 1;
load_time[mfu_idx] = i;
}
}
printf("%d\t", page);
for(k = 0; k < n_frames; k++) {
if(frames[k] != -1) printf("%d ", frames[k]);
else printf("- ");
}
printf("\t\t%s\n", status);
}
printf("\nTotal Page Faults: %d\n", faults);
return 0;
}
