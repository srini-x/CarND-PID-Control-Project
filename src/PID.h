#ifndef PID_H
#define PID_H

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  /*
  * Twiddle
  */
  bool tune;

  double total_abs_cte;
  double best_total_cte;

  double counter;
  int max_count;
  int loop_num;

  double tol;
  double dKp;
  double dKi;
  double dKd;

  double *twiddle_p;
  double *twiddle_dp;

  int state;
  int next_p;

  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp_in, double Ki_in, double Kd_in, double dKp_in, double dKi_in, double dKd_in, int max_count_in);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();

  /*
  * Tune the Coefficients using the twiddle algorithm
  */
  void Twiddle();

  /*
  * Tune the Coefficients using the twiddle algorithm
  */
  void SelectNextParam();
};

#endif /* PID_H */
