#include <iostream>
#include <vector>
#include <climits>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        std::cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        std::cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].remaining_time = processes[i].burst_time;
    }

    int completed = 0, current_time = 0;
    
    while (completed != n) {
        int shortest = -1;
        int min_remaining_time = INT_MAX;

        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0 && processes[i].remaining_time < min_remaining_time) {
                min_remaining_time = processes[i].remaining_time;
                shortest = i;
            }
        }

        if (shortest == -1) {
            current_time++;
            continue;
        }

        processes[shortest].remaining_time--;
        current_time++;

        if (processes[shortest].remaining_time == 0) {
            completed++;
            processes[shortest].completion_time = current_time;
            processes[shortest].turnaround_time = processes[shortest].completion_time - processes[shortest].arrival_time;
            processes[shortest].waiting_time = processes[shortest].turnaround_time - processes[shortest].burst_time;
        }
    }

    float total_waiting_time = 0, total_turnaround_time = 0;

    std::cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        std::cout << "P" << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time
                  << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].waiting_time
                  << "\t\t" << processes[i].turnaround_time << "\n";
    }

    std::cout << "\nAverage Waiting Time: " << total_waiting_time / n << "\n";
    std::cout << "Average Turnaround Time: " << total_turnaround_time / n << "\n";

    return 0;
}

