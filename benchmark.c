#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_SIZE 1000
#define NUM_THREADS 10

// Structure to pass data to threads
struct thread_data
{
    int thread_id;
    int num_threads;
    int **matrix1;
    int **matrix2;
    int **result_matrix;
    int rows;
    int cols;
};

// Function to generate random values for a matrix
void initializeMatrix(int **matrix, int rows, int cols)
{
    int i, j;
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            matrix[i][j] = rand() % 10; // Adjust the range as needed
        }
    }
}

// Function to perform matrix multiplication for a specific range of rows
void *multiplyMatrix(void *arg)
{
    struct thread_data *data = (struct thread_data *)arg;
    int start_row = data->thread_id * (data->rows / data->num_threads);
    int end_row = (data->thread_id + 1) * (data->rows / data->num_threads);
    int i, j, k;
    for (i = start_row; i < end_row; ++i)
    {
        for (j = 0; j < data->cols; ++j)
        {
            data->result_matrix[i][j] = 0;
            for (k = 0; k < data->cols; ++k)
            {
                data->result_matrix[i][j] += data->matrix1[i][k] * data->matrix2[k][j];
            }
        }
    }

    pthread_exit(NULL);
}

int main()
{
    pid_t p = getpid();
    syscall(548, p);
    int rows = MAX_SIZE;
    int cols = MAX_SIZE;

    int i;

    // Get matrix size from user
    // printf("Enter the number of rows: ");
    // scanf("%d", &rows);
    // printf("Enter the number of columns: ");
    // scanf("%d", &cols);

    // if (rows <= 0 || cols <= 0 || rows > MAX_SIZE || cols > MAX_SIZE)
    // {
    //     printf("Invalid matrix size. Please enter valid dimensions.\n");
    //     return 1;
    // }

    // Dynamically allocate memory for matrices
    int **matrix1 = (int **)malloc(rows * sizeof(int *));
    int **matrix2 = (int **)malloc(rows * sizeof(int *));
    int **result_matrix = (int **)malloc(rows * sizeof(int *));

    for (i = 0; i < rows; ++i)
    {
        matrix1[i] = (int *)malloc(cols * sizeof(int));
        matrix2[i] = (int *)malloc(cols * sizeof(int));
        result_matrix[i] = (int *)malloc(cols * sizeof(int));
    }

    // Initialize matrices with random values
    initializeMatrix(matrix1, rows, cols);
    initializeMatrix(matrix2, rows, cols);

    // Number of threads to use
    int num_threads = NUM_THREADS;
    // printf("Enter the number of threads: ");
    // scanf("%d", &num_threads);

    // if (num_threads <= 0)
    // {
    //     printf("Invalid number of threads. Please enter a positive value.\n");
    //     return 1;
    // }

    // Create thread data and array of thread IDs
    pthread_t threads[num_threads];
    struct thread_data thread_data_array[num_threads];

    // Create threads
    for (i = 0; i < num_threads; ++i)
    {
        thread_data_array[i].thread_id = i;
        thread_data_array[i].num_threads = num_threads;
        thread_data_array[i].matrix1 = matrix1;
        thread_data_array[i].matrix2 = matrix2;
        thread_data_array[i].result_matrix = result_matrix;
        thread_data_array[i].rows = rows;
        thread_data_array[i].cols = cols;

        pthread_create(&threads[i], NULL, multiplyMatrix, (void *)&thread_data_array[i]);
    }

    // Join threads
    for (i = 0; i < num_threads; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Print result matrix
    // printf("Result Matrix:\n");
    // for (int i = 0; i < rows; ++i)
    // {
    //     for (int j = 0; j < cols; ++j)
    //     {
    //         printf("%d\t", result_matrix[i][j]);
    //     }
    //     printf("\n");
    // }

    printf("No of extents created:%ld\n", syscall(549));

    // Free dynamically allocated memory
    for (i = 0; i < rows; ++i)
    {
        free(matrix1[i]);
        free(matrix2[i]);
        free(result_matrix[i]);
    }
    free(matrix1);
    free(matrix2);
    free(result_matrix);

    return 0;
}
