#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int compare(const void *a, const void *b) {
    return (*(double*)a > *(double*)b) - (*(double*)a < *(double*)b);
}

int main() {
    double a, b, c;
    double max_side = 0;
    double max_volume = 0;
    int count = 0;

    while (scanf("%lf %lf %lf", &a, &b, &c) == 3) {
        double dimensions[3] = {a, b, c};
        qsort(dimensions, 3, sizeof(double), compare);

        if (dimensions[0] < 0.01 || dimensions[2] > 10000000.00) {
            printf("Invalid input\n");
            return 1;
        }

        if ((a - (int)a) * 100 > 99 || (b - (int)b) * 100 > 99 || (c - (int)c) * 100 > 99) {
            printf("Invalid input\n");
            return 1;
        }

        if (dimensions[0] > max_side) {
            max_side = dimensions[0];
        }
        if (dimensions[1] > max_side) {
            max_side = dimensions[1];
        }
        if (dimensions[2] > max_side) {
            max_side = dimensions[2];
        }
        if (dimensions[0] * dimensions[1] * dimensions[2] > max_volume) {
            max_volume = dimensions[0] * dimensions[1] * dimensions[2];
        }

        count++;
    }

    if (count == 0) {
        printf("No products were entered\n");
        return 1;
    }

    double box_size = max_side > pow(max_volume, 1.0 / 3.0) ? max_side : pow(max_volume, 1.0 / 3.0);

    if (box_size > 10000000.00) {
        printf("Box too large\n");
    } else {
        printf("%.2f\n", box_size);
    }

    return 0;
}
