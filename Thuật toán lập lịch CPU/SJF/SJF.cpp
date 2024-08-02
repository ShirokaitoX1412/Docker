#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

struct Process {
    int id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int waiting_time;
    int turnaround_time;
};

bool compareArrival(Process p1, Process p2) {
    return p1.arrival_time < p2.arrival_time;
}

int main() {
    int n;
    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    std::vector<Process> processes(n);

    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        std::cout << "Enter arrival time and burst time for process " << i + 1 << ": ";
        std::cin >> processes[i].arrival_time >> processes[i].burst_time;
    }

    std::sort(processes.begin(), processes.end(), compareArrival);

    int current_time = 0;
    float total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        int shortest_index = -1;
        int min_burst_time = INT_MAX;

        for (int j = 0; j < n; j++) {
            if (processes[j].arrival_time <= current_time && processes[j].completion_time == 0 && processes[j].burst_time < min_burst_time) {
                min_burst_time = processes[j].burst_time;
                shortest_index = j;
            }
        }

        if (shortest_index != -1) {
            current_time += processes[shortest_index].burst_time;
            processes[shortest_index].completion_time = current_time;
            processes[shortest_index].turnaround_time = processes[shortest_index].completion_time - processes[shortest_index].arrival_time;
            processes[shortest_index].waiting_time = processes[shortest_index].turnaround_time - processes[shortest_index].burst_time;

            total_waiting_time += processes[shortest_index].waiting_time;
            total_turnaround_time += processes[shortest_index].turnaround_time;
        } else {
            current_time++;
        }
    }

    std::cout << "\nProcess\tArrival Time\tBurst Time\tCompletion Time\tWaiting Time\tTurnaround Time\n";
    for (int i = 0; i < n; i++) {
        std::cout << "P" << processes[i].id << "\t\t" << processes[i].arrival_time << "\t\t" << processes[i].burst_time
                  << "\t\t" << processes[i].completion_time << "\t\t" << processes[i].waiting_time
                  << "\t\t" << processes[i].turnaround_time << "\n";
    }

    std::cout << "\nAverage Waiting Time: " << total_waiting_time / n << "\n";
    std::cout << "Average Turnaround Time: " << total_turnaround_time / n << "\n";

    return 0;
}

