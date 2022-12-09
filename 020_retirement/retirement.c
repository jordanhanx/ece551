#include <stdio.h>
#include <stdlib.h>

struct _retire_info {
  int months;
  double contribution;
  double rate_of_return;
};

typedef struct _retire_info retire_info;

void retirement(int startAge,           //in months
                double initial,         //innitial savings in dollars
                retire_info working,    //info about working
                retire_info retired) {  //info about being retired

  double balance = initial;
  int maxAge = startAge + working.months + retired.months;
  int retiredAge = startAge + working.months;

  for (int Age = startAge; Age < maxAge; Age++) {
    printf("Age %3d month %2d you have $%.2f\n", Age / 12, Age % 12, balance);
    if (Age < retiredAge) {
      balance = balance + (balance * working.rate_of_return / 12 + working.contribution);
    }
    else {
      balance = balance + (balance * retired.rate_of_return / 12 + retired.contribution);
    }
  }
}

int main(void) {
  int startAge = 327;
  double initial = 21345;

  retire_info working;
  working.months = 489;
  working.contribution = 1000;
  working.rate_of_return = 0.045;

  retire_info retired;
  retired.months = 384;
  retired.contribution = -4000;
  retired.rate_of_return = 0.01;

  retirement(startAge, initial, working, retired);

  return EXIT_SUCCESS;
}
