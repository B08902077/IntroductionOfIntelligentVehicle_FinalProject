# IntroductionOfIntelligentVehicle_FinalProject
## ManyToOne.cpp
### input
Input a positive integer $L$, where $L$ is the number of lanes.  
  
Next, input $L$ integers representing the number of vehicles on each lane and a positive real number $k$ as the latency factor.  
  
Then for each vehicle, input two integers $a$ and $p$, where $a$ means its arrival time and $p$ means its passing time. We suppose that any vehicle arrives at time $t\ge0$.  
  
Note that we assume all numbers the user inputs can represent a reasonalbe situation (ex. the arrival time of any vehicle is no smaller than the summation of the arrival time and passing time of the previous one, if it exists), so the program doesn't check whether the input data is invalid.
```
3
2 2 2 1.5
0 1
2 1
1 1
3 1
0 1
2 1
```
### output
After inputting the above data, the program prints as follows.
```
lane: 2 / index: 0 / startingTime: 0 / completionTime: 1
lane: 2 / index: 1 / startingTime: 2 / completionTime: 3
lane: 1 / index: 0 / startingTime: 5 / completionTime: 6
lane: 1 / index: 1 / startingTime: 6 / completionTime: 7
lane: 0 / index: 0 / startingTime: 9 / completionTime: 10
lane: 0 / index: 1 / startingTime: 10 / completionTime: 11
```
## ManyToOneWithAmbulances.cpp
### input
Input a positive integer $L$, where $L$ is the number of lanes.  
  
Next, input $L$ integers representing the number of vehicles on each lane and a positive real number $k$ as the latency factor.  
  
Then for each vehicle, input three integers $a$, $p$, and $b$, where $a$ means its arrival time, $p$ means its passing time, and $b$ is 1/0 if it is/isn't an ambulance. We suppose that any vehicle arrives at time $t\ge0$.  
  
Note that we assume all numbers the user inputs can represent a reasonalbe situation (ex. the arrival time of any vehicle is no smaller than the summation of the arrival time and passing time of the previous one, if it exists), so the program doesn't check whether the input data is invalid.
```
3
4 4 4 0

0 1 1
1 1 0
2 3 0
8 1 1

2 1 1
3 1 0
4 2 0
13 1 1

1 1 0
4 1 1
5 1 0
6 1 0
```
### output
After inputting the above data, the program prints as follows.
```
lane: 0 / index: 0 / startingTime: 0 / completionTime: 1
lane: 2 / index: 0 / startingTime: 1 / completionTime: 2
lane: 1 / index: 0 / startingTime: 2 / completionTime: 3
lane: 0 / index: 1 / startingTime: 3 / completionTime: 4
lane: 2 / index: 1 / startingTime: 4 / completionTime: 5
lane: 0 / index: 2 / startingTime: 5 / completionTime: 8
lane: 0 / index: 3 / startingTime: 8 / completionTime: 9
lane: 2 / index: 2 / startingTime: 9 / completionTime: 10
lane: 1 / index: 1 / startingTime: 10 / completionTime: 11
lane: 1 / index: 2 / startingTime: 11 / completionTime: 13
lane: 1 / index: 3 / startingTime: 13 / completionTime: 14
lane: 2 / index: 3 / startingTime: 14 / completionTime: 15
```
By the way, if there are no valid schedule for the input data, the program only prints a line `infeasible!`
