
# PID Project

Using a PID controller to control the car and navigate it across the track.

## Content

Some of the important files and folders are listed below:

**/src**
   - The src folder consists of the following important .cpp files:
       - PID.cpp
           - implementation of PID controller and the Twiddle algorithm used to optimize the PID parameters
       - main.cpp
           - main procedure implementation

**/Debug**
   - This folder consists of executable file **PID.sh** which runs the main procedure of the project

**CMakeLists.txt**
   - Cmake file to build the project

**PID.xcodeproj**
   - Xcode IDE project file used to build the project files

**/output**
   - This folder consists of video outputs for the project

## Usage

1. In order to run the optimization for the controller change `optimization` variable of PID class value to `1` located at line 50 of main.cpp.
2. If you wish to test the PID controller, run the **PID.sh** executable and ensure value of `optimization` variable of PID class is `0` at line 50 of main.cpp.
3. Run the simulator and select 'Project 4: PID Controller'.
4. The car would drive across the track as per the steering angle specified by the PID controller.

## Reflections/ Observation

* The parameters of PID controller have been trained by Twiddle algorithm and have been fine tuned by some manual adjustments.
* In order to run the Twiddle across the entire track is a time and resource consuming process hence we ran the simulator for 1000 steps and fed the error recorded to Twiddle algorithm to optimize the parameters.


* With 0.2 as tolerance, we obtained (0.1, 0, 1.82898) as the parameters from the Twidle algorithm. We fine tuned these values to **(0.12, 0, 1.982898)** which provided a satisfactory result.
* The result of these parameters can be seen in the video [PID Controller](https://youtu.be/yW2sZmGIpMY).



### Effects of P, I and D components 
**P - component effect**
- To study the effect of Propotional component on the bearing of the car we will run the PID project by setting the value of propotional component parameter to 0 and retaining the other values.
- As seen in the video [PID Without P Component](https://youtu.be/QEu23lkjXe0), the absense of Propotional component reduces the sensitivity of the car to curves.

**I - component effect**
- As it is mentioned above that the value of I parameter in optimized values is 0, we can conclude that Integral component has the minimum effect on deciding the bearing of the car.

**D - component effect**
- To study the effect of Differential component on the bearing of the car we will run the PID controller by setting the value of differential component parameter to 0 and retaining the other values.
- As seen in the video [PID Without D Component](https://youtu.be/C_iVKEg9_Rk), tough our car is sensitive to curves, there is considerable loss in the stability of the car and car makes sharp turns from one side of the road to the other.


## Conclusion
- In conclusion we can say that the propotional component helps in providing sensitivity to the curvature of the road as it is directly linked with the cross track error.
- Similarily, differential component helps to ease the oscillations of the car by counter steering the car as the error reduces over time.
- Integral component is like the correctional component for the PID controller and hence it has the least value in the optimized values of PID parameters.
- A right combination of P, I and D provides a smooth control over the car.
- But, if we increase the speed of the car, it becomes difficult to control the car with the same parameters. Hence, along with the steering of the car, the throttle needs to be controlled in order to control the car in an orderly manner.
