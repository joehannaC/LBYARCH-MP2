#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Assembly function declaration
// change the compute_acceleration to compute_acceleration_mac if you're using macos
extern void compute_acceleration(double *matrix, int *results, int rows);

// Generate random values
void generate_random_matrix(double *matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        double vi = (rand() % 20001) / 100.0;               // vi = 0.00 to 200.00 km/h
        double vf = vi + (rand() % 20001) / 100.0;          // vf = vi + 200.00 km/h
        double t = ((rand() % 6000) + 1) / 100.0;           // t = 0.01 to 60.00 seconds
        matrix[i * 3 + 0] = vi;
        matrix[i * 3 + 1] = vf;
        matrix[i * 3 + 2] = t;
    }
}

// USer data if rows < 10
void manual_input_test(int rows) {
    double *matrix = malloc(sizeof(double) * rows * 3);
    int *results = malloc(sizeof(int) * rows);

    printf("Enter Vi, Vf, and T for each row:\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d:\n", i + 1);
        printf("  Vi (km/h): ");
        scanf("%lf", &matrix[i * 3 + 0]);
        printf("  Vf (km/h): ");
        scanf("%lf", &matrix[i * 3 + 1]);
        printf("  T (s): ");
        scanf("%lf", &matrix[i * 3 + 2]);
    }

    compute_acceleration(matrix, results, rows);

    printf("\nResults: Acceleration values (in m/s^2):\n");
    for (int i = 0; i < rows; i++) {
        printf("Row %d: %d m/s^2\n", i + 1, results[i]);
    }

    free(matrix);
    free(results);
}

// Random data if rows >= 10
void performance_test(int rows) {
    double *matrix = malloc(sizeof(double) * rows * 3);
    int *results = malloc(sizeof(int) * rows);

    srand((unsigned int)time(NULL));
    generate_random_matrix(matrix, rows);

    compute_acceleration(matrix, results, rows);

    for (int i = 0; i < rows; i++) {
        printf("Row %d: vi = %.2f, vf = %.2f, t = %.2f; a = %d m/s²\n",
                i + 1,
                matrix[i * 3 + 0],
                matrix[i * 3 + 1],
                matrix[i * 3 + 2],
                results[i]);
    }

    free(matrix);
    free(results);
}

int main() {
    int rows;
    printf("\nEnter number of rows: ");
    scanf("%d", &rows);

    if (rows < 10) {
        printf("\n---- Manual Inputted Data and Result/s ----\n\n");
        manual_input_test(rows);
    } else {
        printf("\n---- Random Generated Data and Result/s ----\n\n");
        performance_test(rows);
    }

    return 0;
}

