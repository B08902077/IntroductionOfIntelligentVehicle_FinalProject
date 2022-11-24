#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cmath>
#include <string>
#include <sstream>
#include <stack>
#include <deque>

using namespace std;

// number of cars in each lane
vector<int> carCnt;

// latency factor
double k;

class Car{
public:
    int arrivalTime;
    int drivingTime;
    Car(int s = -1, int c = -1): arrivalTime(s), drivingTime(c){}
    void change(int s, int c) { arrivalTime = s, drivingTime = c; }
};

class Cell{
public:
    int fromLane;
    int completionTime;
    Cell(int f = -1, int c = -1): fromLane(f), completionTime(c){}
    void change(int f, int c) { fromLane = f, completionTime = c; }
};

class CarResult{
public:
    int lane;
    int index;
    int startingTime;
    int completionTime;
    CarResult(int l, int i, int s, int c): lane(l), index(i), startingTime(s), completionTime(c){}
    void print() { cout << "lane: " << lane << " / index: " << index << " / startingTime: " << startingTime << " / completionTime: " << completionTime << '\n'; }
};

class IndexGenerator{
public:
    deque<int> carCumulativeCnts;
    IndexGenerator(vector<int> cnts, bool addOneNeeded = false){
        int curBase = 1;
        for(int i = cnts.size() - 1; i >= 0; i--){
            carCumulativeCnts.push_front(curBase);
            curBase *= (addOneNeeded)? cnts[i] + 1 : cnts[i];
        }
    }
    int index(vector<int> indices) {
        if (indices.size() != carCumulativeCnts.size())   return -1;
        int index = 0;
        for(int i = 0; i < indices.size(); i++){
            index += indices[i] * carCumulativeCnts[i];
        }
        return index;
    }

    vector<int> deindex(int idx){
        vector<int> indices;
        for(int i = 0; i < carCumulativeCnts.size(); i++){
            indices.emplace_back(idx / carCumulativeCnts[i]);
            idx %= carCumulativeCnts[i];
        }
        return indices;
    }

    int singleLane(int lane){
        return carCumulativeCnts[lane];
    }
};

int Sum(vector<int> vec){
    int res = 0;
    for(int i = 0; i < vec.size(); i++) res += vec[i];
    return res;
}

int AddOneMultiply(vector<int> vec){
    int res = 1;
    for(int i = 0; i < vec.size(); i++) res *= vec[i] + 1;
    return res;
}

void MultipleLaneMerge(vector<vector<Car>> &cars){
    vector<vector<Cell>> table; table.resize(cars.size());
    int totalNum = AddOneMultiply(carCnt);
    for(int lane = 0; lane < carCnt.size(); lane++)  table[lane].resize(totalNum);
    IndexGenerator g = IndexGenerator(carCnt, true);
    vector<vector<vector<int>>> indicesBySize; indicesBySize.resize(Sum(carCnt)+1);

    for(int i = 1; i < totalNum; i++){
        vector<int> indices = g.deindex(i);
        indicesBySize[Sum(indices)].emplace_back(indices);
    }
    
    // initialization
    for(int lane = 0; lane < carCnt.size(); lane++){
        if (carCnt[lane] == 0)    continue;
        table[lane][0].change(-1, cars[lane][0].arrivalTime + cars[lane][0].drivingTime);
    }

    // table construction
    for(int i = 1; i <= Sum(carCnt); i++){
        for(int j = 0; j < indicesBySize[i].size(); j++){
            int curIdx = g.index(indicesBySize[i][j]);
            for(int lane = 0; lane < carCnt.size(); lane++){
                if (carCnt[lane] == 0)  continue;
                int optLane = -1, optTime = INT32_MAX;
                for(int fromLane = 0; fromLane < carCnt.size(); fromLane++){
                    if(carCnt[fromLane] == 0 || indicesBySize[i][j][fromLane] == 0) continue;
                    int curTime = table[fromLane][curIdx - g.singleLane(fromLane)].completionTime + (int)ceil(abs(fromLane - lane) * k);
                    if (curTime < optTime){
                        optLane = fromLane; optTime = curTime;
                    }
                }
                table[lane][curIdx].change(optLane, max(optTime, cars[lane][indicesBySize[i][j][lane]].arrivalTime) + cars[lane][indicesBySize[i][j][lane]].drivingTime);
            }
        }
        // cout << "i = " << i << '\n';
        // for(int j = 0; j < indicesBySize[i].size(); j++){
        //     cout << indicesBySize[i][j][0] << ' ' << indicesBySize[i][j][1] << ' ' << indicesBySize[i][j][2] << '\n';
        // }
    }

    // show result
    stack<CarResult> results;
    int curIdx = totalNum-1, curLane = -1, optTime = INT32_MAX;
    vector<int> curIndices = g.deindex(curIdx);
    for(int lane = 0; lane < carCnt.size(); lane++){
        if (carCnt[lane] == 0)  continue;
        if (table[lane][curIdx - g.singleLane(lane)].completionTime < optTime){
            curLane = lane; optTime = table[lane][curIdx - g.singleLane(lane)].completionTime;
        }
    }
    curIdx -= g.singleLane(curLane);
    --curIndices[curLane];
    results.push(CarResult(curLane, curIndices[curLane], optTime - cars[curLane][curIndices[curLane]].drivingTime, optTime));
    curLane = table[curLane][curIdx].fromLane;
    curIdx -= g.singleLane(curLane);
    
    while(curLane >= 0 && curIdx >= 0){
        optTime = table[curLane][curIdx].completionTime;    --curIndices[curLane];
        results.push(CarResult(curLane, curIndices[curLane], optTime - cars[curLane][curIndices[curLane]].drivingTime, optTime));
        curLane = table[curLane][curIdx].fromLane;
        curIdx -= g.singleLane(curLane);
    }
    while(!results.empty()){
        results.top().print();
        results.pop();
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int N;  cin >> N;
    carCnt.resize(N);
    for(int i = 0; i < N; i++)  cin >> carCnt[i];
    cin >> k;

    // record the information of each car
    vector<vector<Car>> cars;
    int s, c;
    for(int lane = 0; lane < N; lane++){
        cars.emplace_back();
        if (carCnt[lane] > 0){
            for(int i = 0; i < carCnt[lane]; i++){
                cin >> s >> c; cars.back().emplace_back(Car(s,c));
            }
        }
    }

    MultipleLaneMerge(cars);
    return 0;
}