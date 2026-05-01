[![Open in Codespaces](https://classroom.github.com/assets/launch-codespace-2972f46106e565e64193e422d61a12cf1da4916b45550586e14ef0a7c637dd04.svg)](https://classroom.github.com/open-in-codespaces?assignment_repo_id=23789357)
# 🤖 CE11 — Robot City Navigator
**CS 2420 · Path Badge · 20 Points**

---

## 🍕 The Mission

George is a delivery robot assigned to the great and fictional **Crescent City** — a city with 8 locations connected by roads with different travel times. Crescent City boasts having the fastest delivery in the Quad-State Area, and people are incredibly angered when their pizza is delivered in 11 minutes instead of 10. Your job is to train George to find the quickest and most efficient paths through the city. Make customers happy (not mad). Good luck!

---

## 📍 City Locations (Indices)

| Index | Location        |
|-------|----------------|
| 0     | Downtown       |
| 1     | Harbor         |
| 2     | Airport        |
| 3     | University     |
| 4     | Industrial     |
| 5     | Medical Center |
| 6     | Suburb North   |
| 7     | Suburb South   |

---

## 📁 File Structure

```
CE11/
├── Location.hpp     ← Provided struct (with coordinates) — DO NOT MODIFY
├── CityMap.hpp      ← Class declaration (provided)
├── CityMap.cpp      ← YOUR implementations go here
├── main.cpp         ← Starter provided — connect your algorithms
└── analysis.txt     ← YOUR written comparison (create this file!)
```

---

## ✅ What You Need to Implement

### In `CityMap.cpp`:

**`heuristic(int from, int to)`** *(private)*
- Returns Euclidean distance between the two locations' `x`/`y` coordinates, truncated to `int`
- Formula: `sqrt((x2-x1)² + (y2-y1)²)` — use `#include <cmath>`
- Admissible: straight-line distance never exceeds actual travel time in this graph

**`reconstructPath(prev, start, end)`** *(private)*
- Traces back through the `prev[]` array from `end` to `start`
- Builds and returns a `vector<string>` of location names in order
- Returns empty vector if no path exists
- Called by all three path algorithms — implement it once, use it three times

**`greedyPath(int start, int end)`**
- At each step, move to the unvisited neighbor with the smallest edge weight
- NOT guaranteed to find the shortest total path
- **Validate input:** if `start` or `end` is out of range, return `{{}, -1}` immediately
- Return `{{}, -1}` if the destination cannot be reached

**`dijkstraPath(int start, int end)`**
- Use a min-priority queue to always expand the globally cheapest known node
- Guaranteed to find the shortest path
- **Validate input:** if `start` or `end` is out of range, return `{{}, -1}` immediately
- Call `reconstructPath()` to build the return value

**`aStarPath(int start, int end)`**
- Like Dijkstra's, but uses `heuristic(neighbor, end)` to compute `fScore = gScore + h`
- Also guaranteed to find the shortest path
- **Validate input:** if `start` or `end` is out of range, return `{{}, -1}` immediately
- Call `reconstructPath()` to build the return value

> 🛡️ **Defensive coding note:** "Out of range" means any index that isn't a valid location in the graph — negative numbers, or values ≥ `locations.size()`. Check this *before* you index into any vector. Crashing on bad input is never acceptable.

### In `main.cpp`:
- Connect the three algorithm calls to the provided `printResult()` helper
- Test at least **two different routes** (starter routes are provided as a guide)
- Pick a third route of your own choosing

### `analysis.txt`:
Write 1–2 paragraphs addressing:
1. Did Greedy find the optimal path? If not, why not?
2. Did Dijkstra's and A* always agree on the best path?
3. Did A* explore fewer locations than Dijkstra's? Why?
4. When would you choose each algorithm in a real system?

---

## 🔧 Compile & Run

```bash
g++ -std=c++17 -o autonav main.cpp CityMap.cpp
./autonav
```

---

## 📊 Grading (20 pts)

| Category | Points |
|----------|--------|
| `heuristic()` returns correct Euclidean distance | 1 |
| `reconstructPath()` returns correct named path | 1 |
| Greedy correct path & cost | 2 |
| Greedy handles no-path / invalid input | 1 |
| Dijkstra's optimal — single route | 2 |
| Dijkstra's optimal — multiple routes | 2 |
| A* optimal — single route | 2 |
| A* optimal — multiple routes | 2 |
| Edge cases (same start/end, invalid input) | 2 |
| `analysis.txt` quality | 3 |
| Code style & documentation | 2 |
| **Total** | **20** |

---

## ⚠️ Rules

- Do **not** modify `Location.hpp`
- No `std::cout` inside `CityMap` class methods — all output in `main.cpp`
- `reconstructPath()` must be called by all three path algorithms — no duplicated logic
- All three path algorithms must validate their inputs and return `{{}, -1}` for out-of-range indices — no crashes allowed
- `analysis.txt` must be in your repo before submitting
- Commit as you go — no all-at-once uploads
