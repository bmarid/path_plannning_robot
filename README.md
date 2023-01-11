
# Project Name: Robot MHA

## Team: 
Mariia Bai, Andreea Stroia, Hala Albahloul
## Objective:
Programming path planning algorithm for robot. Go from start point to the goal point in 8*8 grid.

# Algorithm
## Path finding and A*

#### A* is a graph traversal and path search algorithm. Starting from a specific starting node of a graph, it aims to find apath to the given goal point having the smallest cost

We are going to take this grid as an example:

![image](https://user-images.githubusercontent.com/113441374/210691268-29917a55-1359-42c9-96c4-0a360b14ac95.png)


The grid has a start point, an end point and obstacles

- First, it checks for neighbours. Because our robot can move up,
down, right or left, it checks for the neighbour that has
smallest cost.

- The smallest cost, f is the sum of g and h, where:
    - g = the movement cost to move from the starting point to a given
square on the grid, following the path generated to get there
    - h = the estimated movement cost to move from that given square on the grid to
the final destination

In our modification of A*, we are using only g with cost = 1
- At each iteration, the f value is calculated (wave)

- It keeps track of the paths originating from the start point

- The algorithm is extending the paths one grid cell at a time until its termination criterion is satisfied, which is meeting the end point

## The steps involved in implementation of A*

- Specifying the start and end ponts

- Creating an open list to store all the point that can be taken into account when calculating the path

- Creating a closed list that stores all the nodes that have been visited. In original A* we would do this, but in our modification we don't need it, because we will always have one best path.

- We start with the start point and check its children (up, down, left and right)

- We check if the children are in the maze boundaries, if the identify as an obstacle, or if they were already visited. If they meet any of these requirements, then we skip to the next child and do not calculate the f value, nor assign it to the open list. Otherwise, we calculate the g and h cost that form the final f.

- We then check for the child with the lowest f and make this child the current point. We also append it to the closed list to form the path later (dont append in our modification)

- The iteration continues until the current point will have the same x and y positions as the end point.

- The path will be returned taken into account the parents of the points. The path is calculated backwards, starting with the end point and tracing back the parents accordingly.

## Flowchart of A* algorithm

 ![image](https://user-images.githubusercontent.com/113441374/210694023-ff1081c1-a971-48b0-8659-01b11a468859.png)


### Movment

## Test the front 

![WhatsApp Image 2023-01-05 at 09 25 47](https://user-images.githubusercontent.com/113441374/210738497-08524a0e-cebb-4d09-93bc-6667d08010e6.jpg)

## frontOpen

![WhatsApp Image 2023-01-05 at 09 25 48](https://user-images.githubusercontent.com/113441374/210738582-f55d6433-0d8e-457a-8c01-411f206d52bc.jpg)

## Go Forward

![WhatsApp Image 2023-01-05 at 09 25 48](https://user-images.githubusercontent.com/113441374/210738674-e10dde17-e0c5-458c-9e5b-c02088b8faa9.jpg)

## Turn left

![WhatsApp Image 2023-01-05 at 09 25 47](https://user-images.githubusercontent.com/113441374/210738742-470fb530-3c18-4797-bcde-74f7c72a3066.jpg)


## Calculate matrix wave func

![1_calc_matrix_wave_func.png](https://github.com/bmarid/robotics_course_2022/blob/mari/lib/algorithm_pics/1_calc_matrix_wave_func.png)

## Path finding

![2_path_finding.png](https://github.com/bmarid/robotics_course_2022/blob/mari/lib/algorithm_pics/2_path_finding.png)

## Test example

![test_obstcale.png](https://github.com/bmarid/robotics_course_2022/blob/mari/lib/algorithm_pics/test_obstcale.png)

### General Algorithm of movment

![WhatsApp Image 2023-01-05 at 02 10 02](https://user-images.githubusercontent.com/113441374/210738268-da515aec-b926-45a1-8071-9e2a88f34c6f.jpg)

## Video with obstacle

![v3_test_obstacle.MOV](https://github.com/bmarid/robotics_course_2022/blob/mari/lib/videos/v3_test_obstacle.MOV)

## Video without obstacle

![v3_test_without_obstacle.MOV](https://github.com/bmarid/robotics_course_2022/blob/mari/lib/videos/v3_test_without_obstacle.MOV)
