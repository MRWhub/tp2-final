# X-Ray Examination Simulator

# Overview
This project simulates a hospital scenario where patients undergo X-ray examinations managed by AI. After the examination, patients are placed in a priority queue and eventually pass through a doctor's report. The simulation involves multiple threads handling patient arrivals, exam processing, and medical report generation, focusing on implementing TADs (Abstract Data Types), concurrency, synchronization, and real-time processing.

# MakeFile
1° Clone the Repository: Download the repository and unzip it.

2° Compile the Program: Navigate to the project directory in the terminal, and execute:
    --> On linux : make
    --> On windows: migw32-make

# Principal TADs (Types Abstract Data)
- Queue TAD: A void queue with void nodes that handle data from patients and from exams.
- Patient TAD: Has patient Struct(ID, NAME, ARRIVAL TIME) and it's functions and procedures to deal with it's data  and prints patient to .txt file.
- Exam TAD:  Has exam Struct(ID, PATIENT ID, CONDITION(by AI) , EXAM TIME) and it's functions and procedures to deal with it's data  and prints exam to .txt file.
- RX Machines TAD: Has Machines List of structs of machine type(ID, BOOLEAN AVAIBLE, PATIENT ID), it's functions and procedures. In this TAD, the "AI" Exam is done on function verify_and_ocupate(), using do_exam_with_AI() and diagnostic_by_ai() functions.
- Medical Check TAD: Has report Struct(ID,EXAM_ID,CONDITION(by Doctor), REPORT TIME) and ExamPriorityQueue Struct( SIX QUEUE, one per priority) and they functions and procedures. In this TAD are the procedure that prints the simulation status and prints report to .txt file.
-  Time Control File:  Has functions and procedures to control time during program execution. In this TAD, the function pre_random_time() returns a random double number between (2 and 3].

# Main Implementation Decisions
Concurrency with Threads:

- Arrival of Patients: A dedicated thread handles patient arrivals, simulating real-time patient flow.
- Report Generation: Another thread manages the generation of medical reports after exams are completed.

Mutex for Synchronization:

- Used to ensure safe access to shared resources (e.g., patient queue, file writing) across multiple threads.

Priority Queue for Exam Handling:

- Exams are prioritized based on patient condition, ensuring that critical cases are handled first.

File Operations:

- Patient, exam, and report data are written to separate files for post-simulation analysis.

Dynamic Memory Management:

- Structures like ReportThreadArgs, ReportThreadArgs2, priorit queues and queues are dynamically allocated to manage thread arguments efficiently.


# Key Considerations

- Real-Time Simulation: The program uses random delays (my_sleep) to simulate real-time events like patient arrivals and report generation.
- Error Handling: Basic error handling is implemented, such as checking for NULL pointers and file I/O errors.
- Comments: For more details about any function and TADS, verify on the source code comments.

 #Conclusion
- This simulation demonstrates the use of threads, synchronization, queues and priority queues to manage a hospital's X-ray examination process. The approach focuses on concurrency and real-time event handling, making it a practical model for similar real-world applications.
