#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "queue.h"
#include "patient.h"
#include "exam.h"
#include "rx_machine.h"
#include "time_control.h"
#include "medical_check.h"
#define    MAX_EXECUTION 43.200
#define MAX_REPORT 7.200
#include <pthread.h>



typedef struct t { //Defining Struct  to Doctor's report thread
    Exam *current_exam;
    FILE *report_file;
    double *time_reports;
    double *tempo_total;
    int *reports_tempo_ok;
    int *report_finalizados;
    double *timer_conditions_array;
    int *report_counter_array;
    int *exam_priority_level;
} ReportThreadArgs;

typedef struct t2{//Defining Strcut to Patient's arrivals thread

    V_queue *patient_queue;
    FILE *patient_file;
    double *time_total;
    double *patient_freeze;
    int *total_patients;
}ReportThreadArgs2;

pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER; //Defining Mutex Thread Security

ReportThreadArgs *create_struct_report(Exam *exam,FILE *report_file,double *tempo_simulation, double *time_reports,int *reports_tempo_ok, int * reports_finalizados, double *report_timer_array, int *report_counter_array , int *exam_priority){
// Function to create and initialize a ReportThreadArgs structure
// This structure holds the necessary information for the report thread
        ReportThreadArgs *new_args  =(ReportThreadArgs*)malloc(sizeof(ReportThreadArgs));
        if(!new_args){
            printf("\nError Memory Allocation Failed!!(Args)");
            exit(1);
        }
    // Initialize the structure members with the provided arguments
    new_args->current_exam = exam;
    new_args->report_file = report_file;
    new_args->time_reports = time_reports;
    new_args->tempo_total = tempo_simulation;
    new_args->reports_tempo_ok = reports_tempo_ok;
    new_args->report_finalizados = reports_finalizados;
    new_args->timer_conditions_array = report_timer_array;
    new_args->report_counter_array = report_counter_array;
    new_args->exam_priority_level = exam_priority;

        return new_args;
}

ReportThreadArgs2 *create_struct_patient(V_queue *patient_queue,FILE *patient_file,double *time_total,double *patient_freeze ,int *pacientes_totais){
// Function to create and initialize a ReportThreadArgs2 structure
// This structure holds the necessary information for the patient arrival thread
    ReportThreadArgs2 *new_args2 = (ReportThreadArgs2*)malloc(sizeof(ReportThreadArgs2));
    if(!new_args2){
            printf("\nError Memory Allocation Failed!!(Args 2)");
            exit(1);

    }
    // Initialize the structure members with the provided arguments
    new_args2->patient_queue = patient_queue;
    new_args2->patient_file = patient_file;
    new_args2->time_total = time_total;
    new_args2->patient_freeze = patient_freeze;
    new_args2->total_patients = pacientes_totais;
    return new_args2;
}

// Function representing the arrival of patients, running in a separate thread
void *arrival_of_patients(void *args){

    // Cast the argument to the appropriate structure type
    ReportThreadArgs2 *arrival_args = (ReportThreadArgs2*)args;

    // Loop to continuously check for patient arrivals until the maximum execution time is reached
    while(*arrival_args->time_total < MAX_EXECUTION){

        // Check if the patient queue is available
        if (arrival_args->patient_queue == NULL) {
            printf("\nError: No queue available\n");
            exit(1);
        }

        // Check if the patient file is available for writing
        if (arrival_args->patient_file == NULL) {
            printf("\nError: Patient file is NULL\n");
            exit(1);
        }

        // If simulation time exceeds 1 second, print a waiting message
        if(*arrival_args->time_total > 1.00){
            printf("\nWaiting Patients... %lf secs...\n", *arrival_args->time_total);
        }


        Patient *new_patient = patient_arrival(); // Simulate the arrival of a new patient based on the probability already set in patient_arrival() function


        if (new_patient) { // If a new patient arrives, lock the queue and add the patient to the queue
            pthread_mutex_lock(&queue_mutex);  // Lock the mutex to protect shared resources
            (*arrival_args->total_patients)++; // Increment the total number of patients


            print_patient_db(new_patient, arrival_args->patient_file);// Print the patient data to the database


            enqueue(arrival_args->patient_queue, new_patient);// Add the new patient to the patient queue
        }


        pthread_mutex_unlock(&queue_mutex); // Unlock the mutex after modifying the queue


        my_sleep(*arrival_args->patient_freeze); // Sleep for the duration specified by patient_freeze before the next possible patient arrival
    }
    return NULL;
}
void *report(void *args) {

// Function that represents the report generation process in a separate thread


    ReportThreadArgs *report_args = (ReportThreadArgs *)args; // Cast the argument to the appropriate structure type


        if(*report_args->tempo_total <= MAX_EXECUTION){// Check if the total simulation time is within the allowed execution time

        double report_duration = pre_random_time() * 2 + 2.150; // Calculate the duration of the report generation using a random value --> pre_random_time returns a double between (2 , 3]
                                                                // Get a random value between 6.150 and 8.150 to the report



        if (report_args->current_exam == NULL) {
            return NULL;
        }

        if (report_args->report_file == NULL) {
            printf("\nError: Report file is NULL\n");
            return NULL;
        }

        my_sleep(report_duration); // Simulate the time taken by the patient while waiting in priority queue till get the final report

        pthread_mutex_lock(&queue_mutex);// Lock the mutex to protect shared resources

        *report_args->time_reports += report_duration;
        (*report_args->report_finalizados)++;

        if (report_duration > 7.200) { // Check if the report duration exceeds the defined max time for finishing a report
            (*report_args->reports_tempo_ok)++;
        }



        printf("\nDOCTOR REPORT DONE FOR EXAM ID: %d\n", get_exam_id(report_args->current_exam)); // Print a message indicating that the report has been completed
        Report *report = do_medical_report(report_args->current_exam);


        if(strcmp(get_report_condition(report), get_exam_condition(report_args->current_exam)) == 0){  // Compare the report condition with the exam condition
        int exam_condition = get_ai_priority(report_args->current_exam); // If conditions match, update the timing and count for this exam's condition
        report_args->timer_conditions_array[ exam_condition- 1] += report_duration;

        report_args->report_counter_array[exam_condition-1]++;

        }else{  // If a new diagnostic is given by the doctor, update the timing and count based on the report's condition
        int report_priority = get_report_priority_condition(report);
        report_args->timer_conditions_array[report_priority - 1] += report_duration;

        report_args->report_counter_array[report_priority - 1] ++;


        }
        pthread_mutex_unlock(&queue_mutex); // Unlock the mutex after updating shared resources
        print_report_db(report, report_args->report_file);// Save the report to the "database"

        print_report(report); // and print it

        free(report);// Free the memory allocated for the report
        }else{

        // If the total simulation execution time has been exceeded, terminate the thread

            return NULL;

        }


    return NULL;
}


int main() {
    printf("\n Simulation started...\n");
    pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER; // Initialize the mutex to handle concurrency in the queue
     srand((unsigned int)time(NULL)); // Seed the random number generator for generating random times

     // Declare threads for handling patients and doctor's report
     pthread_t thread_patient;
     pthread_t thread_doctor;



     FILE *patient_file = fopen("db_patient.txt", "w"); // Open the patient file for writing
    if (!patient_file) {
        perror("Failed to open db_patient.txt");
        return 1;
    }

    FILE *exam_file = fopen("db_exam.txt", "w"); // Open the exam file for writing
    if (!exam_file) {
        perror("Failed to open db_exam.txt");
        fclose(patient_file);
        return 1;
    }

    FILE *report_file = fopen("db_report.txt", "w"); // Open the report file for writing
    if (!report_file) {
        perror("Failed to open db_report.txt");
        fclose(patient_file);
        fclose(exam_file);
        return 1;
    }

    // Initialize various counters and variables to track the simulation progress
    int status_delay = 0;
    double tempo_total = 0;//
    double time_reports = 0;//
    int pacientes_totais = 0;//
    int reports_finalizados = 0; //
    int reports_tempo_ok = 0;//
    int ia_exames_realizados = 0;
    int pacientes_fila_prioridade;
    int last_print_time = 0;
    double sum_conditions_time[6] = {0.00};
    int condiotions_count[6] = {0};

    // Create machines (e.g., X-Ray machines) and patient queue
    Rx **machines_list = create_machines();
    V_queue *patient_queue = create_queue();

    ExamPriorityQueue *exam_priority_queue = new_priority_queue();// Create a priority queue for exams

    double freezing = pre_random_time();  // Generate a random freezing time for patients arrivals


     // Create the arguments structure for the patient thread and start the thread
    ReportThreadArgs2 *args_patiente = create_struct_patient(patient_queue,patient_file,&tempo_total,&freezing,&pacientes_totais);
    pthread_create(&thread_patient,NULL,arrival_of_patients,(void *)args_patiente);

    while (tempo_total < MAX_EXECUTION) { // Main simulation loop

    freezing =  pre_random_time();
    my_sleep(freezing); // This one is just for the main interations, doesn't affects the patients arrival delay and doctor's report, because they both are other threads
    tempo_total+= freezing;



    pthread_mutex_lock(&queue_mutex);  // Lock the mutex to safely access the patient queue
    if(!is_queue_empty(patient_queue)){


    Patient *current_patient = P_denqueue(patient_queue);

    pthread_mutex_unlock(&queue_mutex); //Unlock the mutex
    print_patient(current_patient);

    Exam *current_exam = verify_and_ocupate(machines_list, current_patient);
    ia_exames_realizados++;

    print_exam_db(current_exam,exam_file);  // Print exam details to the database file



    insert_in_priority_queue(exam_priority_queue, current_exam);// Add the exam to the priority queue

    }else{

    pthread_mutex_unlock(&queue_mutex); //Unlock the mutex




    }
if (!is_priority_queue_empty(exam_priority_queue)) {  // Check if there are exams in the priority queue and gets the first in priority queue and starts report thread


            Exam *check_exam = get_priority_exams(exam_priority_queue);
            pacientes_fila_prioridade = priority_queue_waiting(exam_priority_queue);
            int exam_condition = get_ai_priority(check_exam);

            print_exam(check_exam);

            // Create the arguments structure for the doctor thread and start the thread
            ReportThreadArgs *new_args = create_struct_report(check_exam, report_file,&tempo_total, &time_reports, &reports_tempo_ok, &reports_finalizados,sum_conditions_time,condiotions_count,&exam_condition);
            pthread_create(&thread_doctor, NULL,report, (void *)new_args);


   }




    // Update the status display every 11 seconds after at least one report is completed
    if (tempo_total >= last_print_time + 11 && reports_finalizados>1) {
    system("clear");
    print_status(tempo_total, time_reports, pacientes_totais,
    pacientes_fila_prioridade,
    reports_finalizados, reports_tempo_ok, ia_exames_realizados, sum_conditions_time, condiotions_count);

    last_print_time = tempo_total;
}



    }
    // Wait for both patient and doctor threads to finish
    pthread_join(thread_patient, NULL);
    pthread_join(thread_doctor, NULL);

     // Final status display at the end of the simulation
    if(pacientes_totais>1 && reports_finalizados>1){
    print_status(tempo_total, time_reports, pacientes_totais,
    pacientes_fila_prioridade,
    reports_finalizados, reports_tempo_ok, ia_exames_realizados,sum_conditions_time,condiotions_count);
    }else{

    print_status(tempo_total, 0 , pacientes_totais,
    0,
    reports_finalizados, reports_tempo_ok, 0 ,sum_conditions_time,condiotions_count);


    }

    // Clean up resources, free memory, and close files
    P_free_queue(patient_queue);
    destroy_machines(machines_list);
    free_priority_queue(exam_priority_queue);

    free(args_patiente);


    fclose(patient_file);
    fclose(exam_file);
    fclose(report_file);

    printf("\nSimulation Finished\n");
    printf("\n\nCheck out these files: db_patient.txt,db_exam.txt and db_report.txt!!!\n");
    return 0;
}



