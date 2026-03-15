Software Department – Recruitment Tasks

Below are the descriptions of two recruitment tasks for the Software Department.



Website: www.racing-pwr.pl

Email: racing.pwr@gmail.com

Task 1

Your task is to:

1. Create a project

Create a project in STM32CubeIDE configured to work with the STM32F205RGT6 microcontroller, using an external clock source with a frequency of 16 MHz.

2. LED blinking program

Write a program that makes an LED blink (turn on and off) with a frequency of 5 Hz.

The LED is connected to pin PA5

Use a timer to implement this functionality

3. Watchdog

Implement a watchdog in the program.

4. CAN communication

Implement data transmission via the CAN1 interface using the following pins:

PA11

PA12

CAN interface parameters:

Baud Rate: 1,000,000 bit/s

Frame ID: 0x738

Frame length: 2 bytes

Transmission period: 1 s

The entire frame payload should contain the program uptime in seconds, with 1-second precision.

Documentation requirements

The code should be documented, meaning:

the functions' behavior should be explained

important code fragments should be described

Additionally, attach a file describing your solution, explaining:

how it works

the implementation decisions

Place the code and documentation in a Git repository, and send the repository link as the solution.

Task 2

Write a C++ program that takes a set of points in two-dimensional space and performs the following tasks.

1. Convex hull

Find the smallest (least numerous) subset of points that encloses all other points.

(This describes the convex hull of the point set.)

2. Closest parallel lines

Find the two closest parallel lines such that all points in the set lie exactly on them or between them.

3. Closest pair of points

Find the two closest points in the set.

Focus on achieving the lowest possible computational complexity.

Input format

The program should take the name of an input file containing the points in the following format:

<n> — the first line contains the number of points

<x> <y> — the next n lines contain the coordinates of the points

Notes:

x and y are separated by a space

coordinates do not have to be integers

points will not overlap

Program output

A program implementing all subtasks should print to the terminal:

1. Convex hull

Points forming the convex hull
(order does not matter)

2. Parallel lines

The distance between the two parallel lines that bound all points
(the value may be rounded)

3. Closest points

The two closest points in the set and the distance between them

the distance may be rounded

if multiple pairs have the same minimal distance, the program may output any one of them

Example input
10
-4 2
2.5 1.5
4 3
0 -2
-2 4
4 -1.5
2 2
-2 1
-1 2.5
1 0
Example output
Convex hull: (-2.0, 4.0), (-4.0, 2.0), (0.0, -2.0), (4.0, -1.5), (4.0, 3.0)

Lines: d = 5.5896

Closest points: [(2.0, 2.0), (2.5, 1.5)] d = 0.707
Documentation requirements

The code should be documented, explaining:

how the functions work

the important code fragments

Additionally, attach a document describing your solution, including for example:

how the program works

algorithms used

technologies used

encountered edge cases

other problems and their solutions

Place the code and the document in a Git repository and send the repository link as the solution.

Your understanding of your own solution will be verified.

Good luck!
