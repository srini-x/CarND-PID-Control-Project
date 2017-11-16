#include "PID.h"
#include <cmath>
#include <iostream>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_in, double Ki_in, double Kd_in,
               double dKp_in, double dKi_in, double dKd_in, int max_count_in) {
  Kp = Kp_in;
  Ki = Ki_in;
  Kd = Kd_in;

  dKp = dKp_in;  // 0.1;
  dKi = dKi_in;  // 0.00005;
  dKd = dKd_in;  // 1.0;

  tol = 0.2;
  p_error = 0;

  total_abs_cte = 0;

  counter = 0;
  loop_num = 0;
  max_count = max_count_in;  // 2100;

  next_p = 0;
  state = 0;

  tune = true;
  std::cout << "Kp: " << Kp << " Kd: " << Kd << " Ki: " << Ki << std::endl;
  std::cout << "dKp: " << dKp << " dKd: " << dKd << " dKi: " << dKi << std::endl;
}

void PID::UpdateError(double cte) {
  // Update errors
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;
}

double PID::TotalError() {
  double total_error = -Kp * p_error - Kd * d_error - Ki * i_error;

  if (tune) {
    // twiddle related
    counter++;
    total_abs_cte += fabs(p_error);

    // std::cout << counter << endl;

    if (counter == max_count) {
      if (loop_num == 0) {
        best_total_cte = total_abs_cte;
        if (max_count == 2100) {
          max_count = 1900;
        }
      }
      std::cout << loop_num << " - " << counter;
      std::cout << " Total CTE: " << total_abs_cte << " Best CTE: " << best_total_cte << std::endl;
      loop_num++;
      Twiddle();
      std::cout << endl;
      std::cout << "Kp: " << Kp << " Kd: " << Kd << " Ki: " << Ki << std::endl;
      std::cout << "dKp: " << dKp << " dKd: " << dKd << " dKi: " << dKi << std::endl;
      total_abs_cte = 0;
      counter = 0;
    }
  }

  return total_error;
}

void PID::Twiddle() {
  double dp_sum = dKp + dKd + dKi;
  if ((dp_sum > tol) || (next_p != 0)) {
    std::cout << "In Twiddle -> ";
    switch (state) {
      case 0:
        std::cout << "Select Next Param -> Increase Param -> Next run" << std::endl;
        SelectNextParam();
        *twiddle_p = *twiddle_p + *twiddle_dp;
        state = 1;
        break;
      case 1:
        if (total_abs_cte < best_total_cte) {
          std::cout << "Going up is good -> Select Next Param -> Increase Param -> Next run" << std::endl;
          best_total_cte = total_abs_cte;
          *twiddle_dp = *twiddle_dp * 1.1;
          SelectNextParam();
          *twiddle_p = *twiddle_p + *twiddle_dp;
          state = 1;
        } else {
          std::cout << "Going up is bad -> Go down -> Next run" << std::endl;
          *twiddle_p = *twiddle_p - 2 * *twiddle_dp;
          state = 2;
        }
        break;
      case 2:
        if (total_abs_cte < best_total_cte) {
          std::cout << "Going down is good -> Select Next Param -> Increase Param -> Next run" << std::endl;
          best_total_cte = total_abs_cte;
          *twiddle_dp = *twiddle_dp * 1.1;
        } else {
          std::cout << "Going up/down is bad -> Select Next Param -> Increase Param -> Next run" << std::endl;
          *twiddle_p = *twiddle_p + *twiddle_dp;
          *twiddle_dp = *twiddle_dp * 0.9;
        }
        SelectNextParam();
        *twiddle_p = *twiddle_p + *twiddle_dp;
        state = 1;
        break;
    }
  } else {
    tune = false;
  }
}

void PID::SelectNextParam() {
  switch (next_p) {
    case 0:
      twiddle_p = &Kp;
      twiddle_dp = &dKp;
      next_p++;
      break;
    case 1:
      twiddle_p = &Kd;
      twiddle_dp = &dKd;
      next_p++;
      break;
    case 2:
      twiddle_p = &Ki;
      twiddle_dp = &dKi;
      next_p = 0;
      break;
  }
}
