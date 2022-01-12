#include <complex.h>
#include <stdio.h>
#include <string.h>

#define ISR2 0.7071067811865476

void X(_Complex double *qubit) {
  _Complex double tmp = qubit[0];
  qubit[0] = qubit[1];
  qubit[1] = tmp;
}
void Y(_Complex double *qubit) {
  _Complex double tmp = qubit[0];
  qubit[0] = -qubit[1] * _Complex_I;
  qubit[1] = tmp * _Complex_I;
}
void Z(_Complex double *qubit) { qubit[1] = -qubit[1]; }
void H(_Complex double *qubit) {
  _Complex double tmp = qubit[0];
  qubit[0] = (qubit[0] + qubit[1]) * ISR2;
  qubit[1] = (tmp - qubit[1]) * ISR2;
}

void help(void) {
  puts(
      "Applies four quantum logic gates (X, Y, Z, H) in a user-defined order.");
  puts("Arguments:");
  puts("\t--help:\t\tPrints this message");
  puts("\t--interactive:\tStarts an interactive session");
  puts(
      "\t--operands:\tApplies the operations given through the next argument.");
}
void apply(_Complex double *qubit, char operand) {
  switch (operand) {
  case 'X':
  case 'x':
    X(qubit);
    break;
  case 'Y':
  case 'y':
    Y(qubit);
    break;
  case 'Z':
  case 'z':
    Z(qubit);
    break;
  case 'H':
  case 'h':
    H(qubit);
    break;
  }
}

int main(int argc, char **argv) {
  _Complex double qubit[2] = {1, 0};
  if (argc == 2 && strcmp(argv[1], "--help") == 0) {
    help();
  } else if (argc == 2 && strcmp(argv[1], "--interactive") == 0) {
    char input[50] = "";
    while (strcmp(input, ".q") != 0) {
      printf("Enter operand: ");
      scanf("%s", input);
      apply(qubit, input[0]);
      printf("( %lf + %lfi , %lf + %lfi )\n", creal(qubit[0]), cimag(qubit[0]),
             creal(qubit[1]), cimag(qubit[1]));
    }
  } else if (argc == 3 && strcmp(argv[1], "--operands") == 0) {
    for (size_t i = 0; argv[2][i] != '\0'; i++)
      apply(qubit, argv[2][i]);
    printf("( %lf + %lfi , %lf + %lfi )\n", creal(qubit[0]), cimag(qubit[0]),
           creal(qubit[1]), cimag(qubit[1]));
  } else {
    puts("Invalid arguments.");
    help();
  }
  return 0;
}
