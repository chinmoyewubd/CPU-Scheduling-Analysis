# 🖥️ CPU Scheduling Algorithms Analysis  
### Operating Systems (CSE325) Project

## 📌 Project Overview

This project presents a comprehensive implementation and analysis of three fundamental CPU scheduling algorithms:

- First Come First Serve (FCFS)
- Preemptive Shortest Job First (SJF / SRTF)
- Round Robin (RR)

The project was developed as part of the Operating Systems (CSE325) academic course to demonstrate practical understanding of process scheduling techniques and performance evaluation.

---

## 🎯 Objectives

- Implement classical CPU scheduling algorithms in C.
- Compare algorithm performance based on standard metrics.
- Analyze advantages and limitations of each scheduling method.
- Strengthen understanding of process management concepts in Operating Systems.

---

## ⚙️ Algorithms Implemented

### 🔹 First Come First Serve (FCFS)
- Non-preemptive scheduling
- Executes processes in order of arrival
- Simple but may cause Convoy Effect

### 🔹 Preemptive Shortest Job First (SRTF)
- Preemptive scheduling
- Executes process with shortest remaining burst time
- Minimizes average waiting time
- May cause starvation

### 🔹 Round Robin (RR)
- Preemptive scheduling
- Each process gets a fixed time quantum
- Fair CPU allocation
- Suitable for time-sharing systems

---

## 📊 Performance Metrics

The program calculates:

- Waiting Time (WT)
- Turnaround Time (TAT)
- Response Time (RT)
- Average Waiting Time
- Average Turnaround Time

---

## 🛠️ Technologies Used

- Programming Language: C
- Compiler: GCC
- Concepts: Arrays, Structures, Scheduling Logic, Performance Calculation

---

## 📂 Project Structure
```
CPU-Scheduling-Analysis/
│
├── CSE325_project.c
├── PROJECT REPORT.pdf
└── README.md
```
---

## ▶️ How to Run the Project

1. Clone the repository:

git clone https://github.com/your-username/cpu-scheduling-analysis.git

2. Navigate to the project directory:

cd cpu-scheduling-analysis

3. Compile the program:

gcc CSE325_project.c -o scheduler

4. Run the program:

For Linux / Mac:
./scheduler

For Windows:
scheduler.exe

---

## 📚 Academic Information

- Course: Operating Systems (CSE325)
- Program: BSc in Computer Science & Engineering
- Project Type: Academic Project

This project was completed during academic coursework to apply theoretical knowledge of CPU scheduling algorithms in a practical implementation.




