#include "PID.h"
#include <iostream>
#include <math.h>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    
    // Initialzing various variables
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    
    p_error = 0;
    i_error = 0;
    d_error = 0;
    
    if (optimization == 1)
    {
        // Initialzing p and dp for twiddle optimization
        p = {Kp, Ki, Kd};
        dp = {0.1, 0.1, 0.1};
        
        best_err = 999;
        steps = 0;
        tot_error = 0;
    }
   
}

void PID::UpdateError(double cte)
{
    // Updating errors
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
    // Calculating total error which provides steering angle
    return -(Kp * p_error + Ki * i_error + Kd * d_error);
}

// Twiddle Optimization
void PID::Twiddle(double error)
{
    if(counter == 0 && twidle_flag == 0)
    {
        cout<<"\nIteration "<<twiddle_iter<<": "<<endl;
        twiddle_iter++;
    }
    cout << "\ndp Sum: "<<sum_dp()<<endl;
    
    // Sum of dp greater than threshold
    if (sum_dp() > 0.2)
    {
        cout<<"Error: "<<error<<endl;
        cout<<"Twiddle flag: "<<twidle_flag<<endl;
        cout<<"Counter: "<<counter<<endl;
        if(twidle_flag == 0)
        {
            // 1st step of Twiddle
            p[counter] += dp[counter];
            
            // Go to step 2
            twidle_flag = 1;
        }
        else if (twidle_flag == 1)
        {
            // 2nd step of Twiddle
            
            // Checking for improvement
            if (error < best_err)
            {
                // If improvement
                best_err = error;
                dp[counter] *= 1.1;
                
                // Go to step 1
                twidle_flag = 0;
                
                // Icrement counter to access next parameter
                counter = (counter + 1)%3;
            }
            else
            {
                // If no improvement, go in other direction
                p[counter] -= 2*dp[counter];
                
                // Go to step 3
                twidle_flag = 2;
            }
        }
        else if (twidle_flag == 2)
        {
            // 3rd step of Twiddle
            
            if (error < best_err)
            {
                // If improvement after moving in other direction
                best_err = error;
                dp[counter] *= 1.1;
            }
            else
            {
                // If no improvement after moving in other direction
                p[counter] += dp[counter];
                dp[counter] *= 0.9;
            }
            
            // Go to step 1
            twidle_flag = 0;
            
            // Icrement counter to access next parameter
            counter = (counter + 1)%3;
        }
        
        // Update PID parameters
        Kp = p[0];
        Ki = p[1];
        Kd = p[2];
        
       
        cout<<"Best Err: "<<best_err<<endl;
        cout<<"K: "<<Kp << ","<<Ki<<","<<Kd<<endl;
        
    }
    else
    {
        // If threshold breached, stop optimization
        optimization = 0;
    }
    
}


double PID::sum_dp()
{
    double sum = 0;
    
    for(int i = 0; i < 3; i++)
    {
        sum+= dp[i];
    }
    
    return sum;
}
