# IntroductionOfIntelligentVehicle_FinalProject
## ManyToOne.cpp
### input
First input an integer $L$, where $L$ is the number of lanes.  
Next input $L$ integers representing the number of vehicles on each lane and a real number $k$ as the latency factor.  
Then for each vehicle, input two integers $s$ and $c$, where $s$ means its arrival time and $c$ means its passing time.
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
```
lane: 2 / index: 0 / startingTime: 0 / completionTime: 1
lane: 2 / index: 1 / startingTime: 2 / completionTime: 3
lane: 1 / index: 0 / startingTime: 5 / completionTime: 6
lane: 1 / index: 1 / startingTime: 6 / completionTime: 7
lane: 0 / index: 0 / startingTime: 9 / completionTime: 10
lane: 0 / index: 1 / startingTime: 10 / completionTime: 11
```
