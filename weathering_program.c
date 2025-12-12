#include <stdio.h>
#include <math.h>

void quadratic_solver(double a, double b, double c, double *root1, double *root2, int *hasRealRoots) {
    double discriminant = b*b - 4*a*c;

    if (discriminant > 0) {
        *root1 = (-b + sqrt(discriminant)) / (2*a);
        *root2 = (-b - sqrt(discriminant)) / (2*a);
        *hasRealRoots = 1;
    } else if (discriminant == 0) {
        *root1 = *root2 = -b / (2*a);
        *hasRealRoots = 1;
    } else {
        *hasRealRoots = 0;
    }
}

void solve_weather_equation(double a, double b, double c) {
    double r1, r2;
    int hasReal;

    quadratic_solver(a, b, c, &r1, &r2, &hasReal);

    if (hasReal) {
        printf("Solutions: %.5f , %.5f\n", r1, r2);
    } else {
        printf("No real solutions.\n");
    }
}

void plot_weather_model(double a, double b, double c) {
    double discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        printf("No real roots. Cannot plot values.\n");
        return;
    }

    printf("\nPlot data (x , y = ax^2 + bx + c):\n");

    for (int x = -4; x <= 4; x++) {
        double y = a*x*x + b*x + c;
        printf("x = %d , y = %.3f\n", x, y);
    }
    printf("\n");
}

int main() {
    int choice;
    printf("Choose an option:\n1. Hard-coded variables\n2. Keyboard input\n3. Read from a file\n");
    scanf("%d", &choice);

    if (choice == 1) {
        double a = 2, b = -7, c = 3;
        printf("Using hard-coded coefficients: a=2, b=-7, c=3\n");
        solve_weather_equation(a, b, c);
        plot_weather_model(a, b, c);

    } else if (choice == 2) {
        double a, b, c;
        printf("Enter coefficient a: ");
        scanf("%lf", &a);
        printf("Enter coefficient b: ");
        scanf("%lf", &b);
        printf("Enter coefficient c: ");
        scanf("%lf", &c);

        solve_weather_equation(a, b, c);
        plot_weather_model(a, b, c);

    } else if (choice == 3) {
        char filename[100];
        FILE *file;

        printf("Enter file name (e.g., coefficients.txt): ");
        scanf("%s", filename);

        file = fopen(filename, "r");

        if (!file) {
            printf("File not found. Please provide a valid file name.\n");
            return 1;
        }

        double a, b, c;
        while (fscanf(file, "%lf %lf %lf", &a, &b, &c) == 3) {
            printf("\nCoefficients: %.2f %.2f %.2f\n", a, b, c);
            solve_weather_equation(a, b, c);
            plot_weather_model(a, b, c);
        }

        fclose(file);

    } else {
        printf("Invalid choice. Please select 1, 2, or 3.\n");
    }

    return 0;
}
