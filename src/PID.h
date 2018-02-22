#ifndef PID_H
#define PID_H
#include <vector>

using namespace std;

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
   * Variables for Twiddle Optimization
  */
  double best_err = 999;                                                    // To record best error
  int counter = 0;                                                          // To keep track of the parameter to be optimized
  int twidle_flag = 0;                                                      // Flag to keep track of twiddle optimization step
  int optimization = 1;                                                     // Flag to decide whether to run optimization or not
    
  vector<double> p;                                                         // To store PID parameters
  vector<double> dp;                                                        // To store increments to made to parameters during optimization
    
  int steps = 0;                                                            // To record number of steps executed by the car
  double tot_error = 0;                                                     // Total error for an iteration
  int twiddle_iter = 0;                                                     // To record number of iterations of Twiddle Algorithm
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
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
   
  /*
   * Calculate sum of dp
   */
  double sum_dp();
  
  /*
   * Twiddle Optimization Algorithm
  */
  void Twiddle(double error);
};

#endif /* PID_H */
