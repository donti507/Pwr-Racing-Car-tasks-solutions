# Task 2 – Solution Description

## How to compile and run

```bash
g++ -std=c++17 -o geometry main.cpp
./geometry points.txt
```

The program takes a filename as argument. If no argument is given it looks for points.txt in the current directory.

---

## What the program does

Reads a set of 2D points from a file and solves 3 geometry problems:
1. Convex hull
2. Minimum width enclosing strip
3. Closest pair of points

---

## Sub-task 1 – Convex Hull

I used the Graham Scan algorithm because it's O(n log n) and not too hard to implement.

The idea is:
- First find the lowest point (bottom-left) and use it as a starting pivot
- Sort all other points by polar angle relative to that pivot
- Go through the sorted points and keep only left turns (counter-clockwise)
- If a right turn is detected, the middle point gets removed from the stack – it's not on the hull

The key operation is the 2D cross product:
```
cross(O, A, B) = (A.x-O.x)*(B.y-O.y) - (A.y-O.y)*(B.x-O.x)
```
If this is positive we have a left turn (keep), if zero or negative we pop.

One edge case I had to handle: collinear points with the same polar angle. I sort them by distance (closer first) and the scan naturally removes them since cross product = 0 triggers a pop.

---

## Sub-task 2 – Minimum width strip

The minimum width strip is defined by two parallel lines that contain all points between them, with the smallest possible distance between the lines.

The key insight is that the optimal strip direction is always parallel to one of the convex hull edges. So I just check every hull edge and for each one find the farthest point from it – that distance is the strip width for that direction. The answer is the minimum across all edges.

To find the farthest point efficiently I used the rotating calipers technique – instead of restarting from scratch for each edge, I keep a pointer j that only moves forward around the hull. This makes the whole thing O(n) after the hull is built.

Perpendicular distance from point P to line AB:
```
distance = |cross(A, B, P)| / length(AB)
```

---

## Sub-task 3 – Closest pair

Brute force would be O(n²) which is too slow for large inputs. I used the classic divide and conquer approach which runs in O(n log n).

How it works:
- Sort points by x coordinate
- Split the set in half and recursively find the closest pair in each half
- Let delta = the best distance found so far
- Look at points within delta of the dividing line (the "strip")
- For each strip point only check points within delta in the y direction – at most 7 comparisons per point due to geometry

The "at most 7 comparisons" part was interesting – basically in a delta x 2*delta rectangle you can fit at most 8 points (4 from each half) because all points within the same half are at least delta apart. So the strip check is O(n) per recursion level.

Base case is 2 or 3 points where I just brute force all pairs.

---

## Example output

Input from the task PDF (10 points):
```
Otoczka: (0.0, -2.0), (4.0, -1.5), (4.0, 3.0), (-2.0, 4.0), (-4.0, 2.0)
Proste: d=5.5896
Najblizsze Punkty: [(2.5, 1.5), (2.0, 2.0)] d=0.707
```
Matches the expected output exactly.