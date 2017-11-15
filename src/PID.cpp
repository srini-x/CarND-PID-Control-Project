#include "PID.h"
#include <cmath>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp_in, double Ki_in, double Kd_in) {
  Kp = Kp_in;
  Kd = Kd_in;
  Ki = Ki_in;

  total_abs_cte = 0;
  counter = 0;
  dKp = 0.4;
  dKd = 0.4;
  dKi = 0.4;
  twiddle_it = 0;
  tol = 0.2;
  max_count = 2000;
}

void PID::UpdateError(double cte) {
  // Update errors
  d_error = cte - p_error;
  p_error = cte;
  i_error += cte;

  // twiddle related
  if (counter == max_count) {
    if (twiddle_it == 0) {
      best_total_cte = total_abs_cte;
    }
    twiddle_it ++;
    total_abs_cte = 0;
    counter = 0;
  }
  counter ++;
  total_abs_cte += abs(cte);
}

double PID::TotalError() {
  double total_error = -Kp * p_error - Kd * d_error - Ki * i_error;
  return total_error;
}

void PID::Twiddle() {

  // while ((dKp + dKd + dKi) > tol) {
    // for (i in range(len(p))) {
      // p[i] += dp[i]
      // robot = make_robot()
      // x_trajectory, y_trajectory, err = run(robot, p)

      // if (total_abs_cte < best_total_cte) {
        // best_total_cte = total_abs_cte;
        // dp[i] *= 1.1;
      // } else {
        // p[i] -= 2 * dp[i];
        // robot = make_robot();
        // x_trajectory, y_trajectory, err = run(robot, p);

        // if (total_abs_cte < best_total_cte) {
          // best_total_cte = total_abs_cte;
          // dp[i] *= 1.1;
        // } else {
          // p[i] += dp[i];
          // dp[i] *= 0.9;
        // }
      // }
    // }
  // }
}
