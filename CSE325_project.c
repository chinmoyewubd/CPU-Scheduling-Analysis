#include <stdio.h>

struct Process
{
    int id;
    int at;
    int bt;
    int wt;
    int tat;
    int rt;
    int ct;
    int remainingTime;

};


void FCFS(struct Process processes[], int n, int *cpuIdleTime)
{
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        if (currentTime < processes[i].at)
        {
            *cpuIdleTime += processes[i].at - currentTime;
            currentTime = processes[i].at;
        }

        processes[i].wt = currentTime - processes[i].at;

        processes[i].rt = processes[i].wt;
        processes[i].tat = processes[i].bt + processes[i].wt;
        processes[i].ct = processes[i].tat + processes[i].at;

        currentTime = processes[i].ct;
    }
}

void SJF(struct Process processes[], int n, int *cpuIdleTime)
{
    int currentTime = 0;
    int completed = 0;
    int shortest = -1;

    while (completed < n)
    {
        shortest = -1;
        int minBurst = 9999;

        for (int i = 0; i < n; i++)
        {
            if (processes[i].at <= currentTime && processes[i].remainingTime > 0)
            {
                if (processes[i].bt < minBurst)
                {
                    shortest = i;
                    minBurst = processes[i].bt;
                }
            }
        }

        if (shortest == -1)
        {
            currentTime++;
            (*cpuIdleTime)++;
            continue;
        }

        processes[shortest].remainingTime--;

        if (processes[shortest].remainingTime == 0)
        {
            completed++;

            processes[shortest].ct = currentTime + 1;
            processes[shortest].wt = processes[shortest].ct - processes[shortest].bt - processes[shortest].at;
            processes[shortest].tat = processes[shortest].wt + processes[shortest].bt;
            processes[shortest].rt = processes[shortest].wt;
        }

        currentTime++;
    }
}


void roundRobin(struct Process processes[], int n, int quantum, int *cpuIdleTime)
{
    int remainingTime[n];
    int currentTime = 0;

    for (int i = 0; i < n; i++)
    {
        remainingTime[i] = processes[i].bt;
    }

    while (1)
    {
        int done = 1;

        for (int i = 0; i < n; i++)
        {
            if (remainingTime[i] > 0)
            {
                done = 0;

                if (remainingTime[i] > quantum)
                {
                    currentTime += quantum;
                    remainingTime[i] -= quantum;
                }
                else
                {
                    currentTime += remainingTime[i];
                    processes[i].ct = currentTime;
                    remainingTime[i] = 0;
                }
            }
        }

        if (done == 1)
            break;
        else
            (*cpuIdleTime)++;
    }

    for (int i = 0; i < n; i++)
    {
        processes[i].tat = processes[i].ct - processes[i].at;
        processes[i].wt = processes[i].tat - processes[i].bt;
        processes[i].rt = processes[i].wt;
    }
}


float displayAverageTimes(struct Process processes[], int n, int totalCPUTime, int totalProcesses)
{
    float avgTurnaroundTime = 0, avgWaitingTime = 0, avgResponseTime = 0;
    float avgCompletionTime = 0, avgCpuIdleTime = 0;

    printf("\nProcess\t\tCompletion\tWaiting\t\tTurnaround\tResponse\n");
    for (int i = 0; i < n; i++)
    {
        printf("P%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].ct,processes[i].wt, processes[i].tat, processes[i].rt);

        avgTurnaroundTime += processes[i].tat;
        avgWaitingTime += processes[i].wt;
        avgResponseTime += processes[i].rt;
        avgCompletionTime += processes[i].ct;
    }

    avgTurnaroundTime /= n;
    avgWaitingTime /= n;
    avgResponseTime /= n;
    avgCompletionTime /= n;

    avgCpuIdleTime = ((float)totalCPUTime / totalProcesses) - avgCompletionTime;

    printf("\nAverage Completion Time: %.2f\n", avgCompletionTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);
    printf("Average Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Response Time: %.2f\n", avgResponseTime);
    printf("Average CPU Idle Time: %.2f\n", -avgCpuIdleTime);


    return avgResponseTime;
}

int main()
{
    printf("\nA Comprehensive Analysis of\n");
    printf("\t(1) FCFS\n");
    printf("\t(2) SJF Preemptive\n");
    printf("\t(3) Round-Robin Algorithms\n");
    int n, totalCPUTime = 0, totalProcesses = 0;
    printf("\nEnter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];
    printf("\n");
    for (int i = 0; i < n; i++)
    {

        printf("Enter Arrival Time and Burst Time for process P%d: ", i + 1);
        scanf("%d %d", &processes[i].at, &processes[i].bt);
       /* processes[i].bt = rand() % 10 + 2;
        processes[i].at = rand() % 6;*/

        processes[i].id = i + 1;

        totalCPUTime += processes[i].bt;
        totalProcesses++;
        processes[i].remainingTime = processes[i].bt;
    }
    printf("\n\n***Arrival Time and Bust Time for every Algorithm***\n");
    printf("\n\tArrival Time\t\tBust Time\n");
    for (int i = 0; i < n; i++)
    {
        printf("\t%d\t\t\t%d\n", processes[i].at, processes[i].bt);
    }


    int cpuIdleTime = 0;
    // Applying FCFS scheduling
    FCFS(processes, n, &cpuIdleTime);
    printf("\n\nFCFS Scheduling:\n");
    float FCFS_avgResTime = displayAverageTimes(processes, n, totalCPUTime, totalProcesses);

    // Reset remaining times for SJF and Round Robin
    for (int i = 0; i < n; i++)
    {
        processes[i].remainingTime = processes[i].bt;
    }

    // Applying SJF scheduling
    cpuIdleTime = 0;
    SJF(processes, n, &cpuIdleTime);
    printf("\n\nPreemptive SJF Scheduling:\n");
    float SJF_avgResTime = displayAverageTimes(processes, n, totalCPUTime, totalProcesses);

     // Applying Round Robin scheduling with quantum = 2
    int quantum = 2;
    cpuIdleTime = 0;
    roundRobin(processes,n,quantum, &cpuIdleTime);
    printf("\n\nRound Robin scheduling with quantum = 2:\n");
    float Round_robin_avgResTime = displayAverageTimes(processes, n, totalCPUTime, totalProcesses);


    if(FCFS_avgResTime>Round_robin_avgResTime && SJF_avgResTime>Round_robin_avgResTime)
    {
      printf("\nRound Robin Algorithm is superior among three because its Avg-ResponseTime is minimum and that is: %0.2f\n",Round_robin_avgResTime);
    }

    else if(SJF_avgResTime>FCFS_avgResTime && Round_robin_avgResTime>FCFS_avgResTime)
    {
      printf("\nFCFS Algorithm is superior among three because its Avg-ResponseTime is minimum and that is: %0.2f\n",FCFS_avgResTime);
    }

    else
    {
      printf("\nSJF Algorithm is superior among three because its Avg-ResponseTime is minimum and that is: %0.2f\n",SJF_avgResTime);
    }


    return 0;
}
