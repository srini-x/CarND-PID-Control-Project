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
  double total_abs_cte;
  double best_total_cte;
  double counter;
  double tol;
  double dKp;
  double dKi;
  double dKd;
  int twiddle_it;
  int max_count;
  double *twiddle_p;
  double *twiddle_dp;
  bool Kp_stable;
  bool Kd_stable;
  bool Ki_stable;

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
  void Init(double Kp_in, double Ki_in, double Kd_in);

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
};

#endif /* PID_H */
