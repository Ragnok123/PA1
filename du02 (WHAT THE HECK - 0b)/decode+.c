#include <stdio.h>
#include <string.h>
 
#define MAX_MESSAGES 100
 
int pulse_length(char c) {
    if (c < 'a' || c > 'z') return -1; // Invalid character
    return 1 << (c - 'a');
}
 
int get_total_length(char *msg) {
    int total = 0;
    int found_pipe = 0;
    for (int i = 0; msg[i] != '\0'; ++i) {
        if (msg[i] == '|') {
            found_pipe = 1;
            continue;
        }
        if (!found_pipe) continue;
        int length = pulse_length(msg[i]);
        if (length == -1) return -1; // Invalid character
        total += length;
    }
    return total;
}
 
int get_remaining_length(char *msg) {
    int total = 0;
    for (int i = 0; msg[i] != '|'; ++i) {
        int length = pulse_length(msg[i]);
        if (length == -1) return -1; // Invalid character
        total += length;
    }
    return total;
}
 
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
 
int lcm(int a, int b) {
    return a * b / gcd(a, b);
}
 
int main() {
    char messages[MAX_MESSAGES][101];
    int num_msgs = 0;
 
    while (scanf("%100s", messages[num_msgs]) == 1) {
        ++num_msgs;
        if (num_msgs == MAX_MESSAGES) break;
    }
 
    if (num_msgs < 2) {
        printf("Error: Less than two messages.\n");
        return 1;
    }
 
    int total_lengths[MAX_MESSAGES];
    int remaining_lengths[MAX_MESSAGES];
 
    for (int i = 0; i < num_msgs; ++i) {
        int total_length = get_total_length(messages[i]);
        int remaining_length = get_remaining_length(messages[i]);

        printf("Delka: %i\n", total_length);
        printf("Zbytek: %i\n", remaining_length);
 
        if (total_length == -1 || remaining_length == -1) {
            printf("Error: Invalid message format.\n");
            return 1;
        }
 
        total_lengths[i] = total_length;
        remaining_lengths[i] = remaining_length;
    }
 
    int sync_time = -1;
    int lcm_value = total_lengths[0];
    for (int i = 1; i < num_msgs; ++i) {
        lcm_value = lcm(lcm_value, total_lengths[i]);
    }
 
    for (int i = 0; i < lcm_value; ++i) {
        int all_aligned = 1;
        for (int j = 0; j < num_msgs; ++j) {
            if ((i - remaining_lengths[j] + total_lengths[j]) % total_lengths[j] != 0) {
                all_aligned = 0;
                break;
            }
        }
        if (all_aligned) {
            sync_time = i;
            break;
        }
    }
 
    if (sync_time == -1) {
        printf("The messages will never synchronize.\n");
    } else {
        printf("Synchronization will occur in %d time units.\n", sync_time);
    }
 
    return 0;
}