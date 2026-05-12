#include "CityMap.hpp"
#include <cmath>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <queue>

#include <iostream> // TODO remove this later

CityMap::CityMap() {
    locations.resize(8);

    locations[0].name = "Downtown";
    locations[0].x = 4; locations[0].y = 4;
    locations[0].neighbors = {{1, 8}, {3, 15}, {6, 12}};

    locations[1].name = "Harbor";
    locations[1].x = 4; locations[1].y = 0;
    locations[1].neighbors = {{0, 8}, {2, 20}, {4, 10}};

    locations[2].name = "Airport";
    locations[2].x = 10; locations[2].y = 0;
    locations[2].neighbors = {{1, 20}, {4, 5}, {7, 18}};

    locations[3].name = "University";
    locations[3].x = 0; locations[3].y = 6;
    locations[3].neighbors = {{0, 15}, {5, 9}, {6, 7}};

    locations[4].name = "Industrial";
    locations[4].x = 9; locations[4].y = 1;
    locations[4].neighbors = {{1, 10}, {2, 5}, {7, 8}};

    locations[5].name = "Medical Center";
    locations[5].x = 2; locations[5].y = 9;
    locations[5].neighbors = {{3, 9}, {6, 11}, {7, 14}};

    locations[6].name = "Suburb North";
    locations[6].x = 1; locations[6].y = 5;
    locations[6].neighbors = {{0, 12}, {3, 7}, {5, 11}};

    locations[7].name = "Suburb South";
    locations[7].x = 8; locations[7].y = 8;
    locations[7].neighbors = {{2, 18}, {4, 8}, {5, 14}};
}

void CityMap::printCity() const {
    std::cout << "City Locations:\n";
    for (int i = 0; i < (int)locations.size(); i++) {
        std::cout << "  [" << i << "] " << locations[i].name << "\n";
        std::cout << "       neighbors: ";
        for (int j = 0; j < (int)locations[i].neighbors.size(); j++) {
            auto [idx, time] = locations[i].neighbors[j];
            std::cout << locations[idx].name << "(" << time << ")";
            if (j < (int)locations[i].neighbors.size() - 1) std::cout << ", ";
        }
        std::cout << "\n";
    }
}

int CityMap::heuristic(int from, int to) const {
    // Might return one less then expected for pythagorian tripples due to floating point errors
    return int(std::sqrt(std::pow(locations[from].x-locations[to].x, 2)+std::pow(locations[from].y-locations[to].y, 2)));
    // TODO make sure this actually works
}

std::pair<std::vector<std::string>, int> CityMap::greedyPath(int start, int end) {
    std::vector<int> prev(locations.size(), -1);
    

    if(start >= locations.size() || end >=locations.size()) {
        return {{}, -1};
    }
    if (start == end) {
        return {{{locations[start].name}}, 0};
    }

    std::vector<bool> visitedNodes(locations.size(), false);
    visitedNodes[start] = true;
    int currentLocation = start;
    bool unvisitedNeighbor = true;
    int travelTime = 0;

    while(unvisitedNeighbor) {
        unvisitedNeighbor = false;
        int closestNeighbor;
        int distance = std::numeric_limits<int>::max();

        // Loops until there is no unvisitedNeighbors in the current node
        for(std::pair<int, int> neighbor : locations[currentLocation].neighbors) {
            if(!visitedNodes[neighbor.first]) {
                unvisitedNeighbor = true;
                if(distance > neighbor.second) {
                    closestNeighbor = neighbor.first;
                    distance = neighbor.second;
                }
            }
        }

        if(unvisitedNeighbor) {
            visitedNodes[closestNeighbor] = true;
            prev[closestNeighbor] = currentLocation;
            travelTime += distance;
            if(closestNeighbor == end) {
                return {reconstructPath(prev, start, end), travelTime};
            }
            currentLocation = closestNeighbor;
        }
    }
    return {{}, -1};
}

std::pair<std::vector<std::string>, int> CityMap::dijkstraPath(int start, int end) {
    if(start >= locations.size() || end >=locations.size()) {
        return {{}, -1};
    }
    if (start == end) {
        return {{{locations[start].name}}, 0};
    }
    
    std::vector<bool> visitedNodes(locations.size(), false);
    std::vector<int> prev(locations.size(), -1);
    std::vector<int> shortestDistance(locations.size(), std::numeric_limits<int>::max());
    shortestDistance[start] = 0;
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
    pq.push({0, start});

    while(!pq.empty()) {
        if(!visitedNodes[pq.top().second]) {
            for(std::pair<int, int> neighbor : locations[pq.top().second].neighbors) {
                if(pq.top().first+neighbor.second < shortestDistance[neighbor.first]) {
                    shortestDistance[neighbor.first] = pq.top().first+neighbor.second;
                    prev[neighbor.first] = pq.top().second;
                    pq.push({shortestDistance[neighbor.first], neighbor.first});
                }
            }
            visitedNodes[pq.top().second] = true;
        }
        pq.pop();
    }
    return {reconstructPath(prev, start, end), shortestDistance[end]};
}

std::pair<std::vector<std::string>, int> CityMap::aStarPath(int start, int end) {
    if(start >= locations.size() || end >=locations.size()) {
        return {{}, -1};
    }
    if (start == end) {
        return {{{locations[start].name}}, 0};
    }
    std::vector<int> fScore(locations.size(), std::numeric_limits<int>::max());
    std::vector<int> gScore(locations.size(), std::numeric_limits<int>::max());
    gScore[start] = 0;
    std::vector<int> hScore;
    std::vector<int> prev(locations.size(), -1);
    std::vector<bool> visitedNodes(locations.size(), false);
    for(int i = 0; i < locations.size(); i++) {
        hScore.push_back(heuristic(i, end));
    }


    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> pq;
    pq.push({hScore[start], start});

    while(pq.top().second != end) {
        if(!visitedNodes[pq.top().second]) {
            for(std::pair<int, int> neighbor : locations[pq.top().second].neighbors) {
                if(gScore[neighbor.first] > gScore[pq.top().second] + neighbor.second) {
                    gScore[neighbor.first] = gScore[pq.top().second] + neighbor.second;
                    fScore[neighbor.first] = gScore[neighbor.first] + hScore[neighbor.first];
                    prev[neighbor.first] = pq.top().second;
                    pq.push({fScore[neighbor.first], neighbor.first});
                }
            }
            visitedNodes[pq.top().second] = true;
        }
        pq.pop();
    }
    return {reconstructPath(prev, start, end), gScore[end]};
}

std::vector<std::string> CityMap::reconstructPath(const std::vector<int>& prev, int start, int end) const {
    std::vector<std::string> returnVec;
    int currentNode = end;

    
    while (currentNode != start) {
        returnVec.push_back(locations[currentNode].name);
        if(prev[currentNode] == -1) {
            return {};
        }
        currentNode = prev[currentNode];
    }
    returnVec.push_back(locations[start].name);
    std::reverse(returnVec.begin(), returnVec.end());
    return returnVec;
}