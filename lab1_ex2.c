#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>


typedef enum statuses {
    OK,
    INCORRECT_ARGUMENTS
} statuses;


int getArgs(char ** argv, int argc, double * eps);
double e_lim(double eps);
double e_summ(double eps);
double e_equation(double eps);
double pi_lim(double eps);
double pi_summ(double eps);
double pi_equation(double eps);
double ln2_lim(double eps);
double ln2_summ(double eps);
double ln2_equation(double eps);
double sqrt2_lim(double eps);
double sqrt2_comp(double eps);
double sqrt2_equation(double eps);


int getArgs(char ** argv, int argc, double * eps) {
    if (argc != 2) {
        return INCORRECT_ARGUMENTS;
    }
    char *s = argv[1];
    int fl = 0;
    for (int i = 0; i < strlen(s); i++) {
        if (isdigit(s[i])) {
            continue;
        }
        else if (s[i] == '.' && i != 0 && i != strlen(s)) {
            fl++;
        }
        else return INCORRECT_ARGUMENTS;
    }
    if (fl <= 1) {
        *eps = atof(s);
        return OK;
    }
    return INCORRECT_ARGUMENTS;
}


double e_lim(double eps) {
    double prev = -10;
    double current = 0;
    double n = 1;
    while (fabs(current - prev) > eps) {
        prev = current;
        current = powl((1.0 + 1.0 / n), n);
        n *= 2;
    }
    return current;
}

double e_summ(double eps) {
    double n = 0;
    double current = 1;
    double ans = current;
    while (current > eps) {
        n++;
        current = current / n;
        ans += current;
    }
    return ans;
}

double e_equation(double eps) {
    double left = 1;
    double right = 10;
    double centr = (left + right) / 2;
    while ((right - left) > eps) {
        centr = (left + right) / 2;
        if ((1 - log(centr)) * (1 - log(right)) < 0) {
            left = centr;
        }
        else if ((1 - log(centr)) * (1 - log(left)) < 0) {
            right = centr;
        }
    }
    return (left + right) / 2;
}

double pi_lim(double eps) {
    double prev = 0;
    double current = 4;
    double n = 1;
    while (fabs(current - prev) > eps * n) {
        n++;
        prev = current;
        current *= (2 * 2 * 2 * 2 * n * n * n * n ) / (2 * n * (2 * n - 1) * 2 * n * (2 * n - 1));
    }
    return current / n;
    
}

double pi_summ(double eps) {
    double n = 1;
    double current = 4;
    double ans = current;
    while (fabs(current) > eps) {
        n++;
        current *= (-1) * (2 * (n - 1) - 1) / (2 * n - 1);
        ans += current;
    }
    return ans;
}

double pi_equation(double eps) {
    double left = 1.5;
    double right = 6;
    double centr = (left + right) / 2;
    while ((right - left) > eps) {
        centr = (left + right) / 2;
        if ((cos(right) + 1) - (cos(left) + 1) > 0) {
            right = centr;
        }
        else {
            left = centr;
        }
    }
    return (left + right) / 2;
}

double ln2_lim(double eps) {
    double prev = -10;
    double current = 0;
    double n = 1;
    while (current - prev > eps) {
        prev = current;
        current = n * (pow(2, 1 / n) - 1);
        n *= 1 / eps;
    }
    return current;
}

double ln2_summ(double eps) {
    double n = 1;
    double current = 1;
    double ans = current;
    while (fabs(current) > eps) {
        n++;
        current *= (-1) * (n - 1) / n;
        ans += current;
    }
    return ans;
}

double ln2_equation(double eps) {
    double left = 0;
    double right = 1;
    double centr = (right + left) / 2;
    while ((right - left) > eps) {
        centr = (right + left) / 2;
        if ((exp(centr) - 2) * (exp(right) - 2) < 0) {
                left = centr;
        }
        else if ((exp(centr) - 2) * (exp(left) - 2) < 0) {
                right = centr;
        }
    }
    return (left + right) / 2;
}

double sqrt2_lim(double eps) {
    double prev = -0.5;
    double current = 0.375;
    while (fabs(current - prev) > eps) {
        prev = current;
        current = prev - prev * prev / 2 + 1;
    }
    return current;
}

double sqrt2_comp(double eps) {
    double k = 2;
    double ans = pow(2, pow(2, -k));
    double prev_ans = 0;
    while (fabs(ans - prev_ans) > eps) {
        k++;
        prev_ans = ans;
        ans *= pow(2, pow(2, -k));
    }
    return ans;
}

double sqrt2_equation(double eps) {
    double left = 1;
    double right = 2;
    double centr = (right + left) / 2;
    while ((right - left) > eps) {
        centr = (right + left) / 2;
        if ((left * left - 2) * (centr * centr - 2) < 0) {
            right = centr;
        }
        else {
            left = centr;
        } 
    }
    return (left + right) / 2;
}


int main(int argc, char ** argv) {
    double eps;
    if (getArgs(argv, argc, &eps)) {
        printf("incorrect arguments");
        return INCORRECT_ARGUMENTS;
    }
    printf("e_lim = %.15f\n", e_lim(eps));
    printf("e_summ = %.15f\n", e_summ(eps));
    printf("e_equation = %.15f\n", e_equation(eps));
    printf("Pi_lim = %.15f\n", pi_lim(eps));
    printf("Pi_summ = %.15f\n", pi_summ(eps));
    printf("Pi_equation = %.15f\n", pi_equation(eps));
    printf("Ln2_lim = %.15f\n", ln2_lim(eps));
    printf("Ln2_summ = %.15f\n", ln2_summ(eps));
    printf("Ln2_equation = %.15f\n", ln2_equation(eps));
    printf("sqrt(2)_lim = %.15f\n", sqrt2_lim(eps));
    printf("sqrt(2)_summ = %.15f\n", sqrt2_comp(eps));
    printf("sqrt(2)_equation = %.15f\n", sqrt2_equation(eps));
    return OK;

}