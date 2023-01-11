/**
  Name: Arduino final project
  Purpose: Realise path finding, recalculation, physical movment on the ground

  @author Mariia
  @author Hala
  @author Andreea

  Notes:
  BIG matrix - path_poundary matrix with 1 in boundariers , where after calculation we will have path inside square of 1
  Space from 0,0 to NUM_ROWS, NUM_COLUMNS
*/

//—--- Mari car
// Motor A
//int enA = 9;
//int in1 = 2;
//int in2 = 3;
//
//// Motor B
//int enB = 10;
//int in3 = 4;
//int in4 = 5;
//
////Ultrasonic
//int trigPin = 12; // Trigger
//int echoPin = 11; // Echo

//-----------Hala car
// Motor A
int enA = 9;
int in1 = 8;
int in2 = 7;

// Motor B
int enB = 3;
int in3 = 5;
int in4 = 4;

//Ultrasonic
int trigPin = 11; // Trigger
int echoPin = 10; // Echo
long duration, cm;

// 0 is up
// 1 is right
// 2 is down
// 3 is left
int direction = 2;

// The point in the grid where the robot is
int i = 1;
int j = 1;

//c part start
#define DIMENTION 4 //UP LEFT RIGHT DOWN
#define OBSTACLE 99
//#define beautiful_output 1 //not for progra, but for task, beautiful output

//Test 1 normal 8 8
#define NUM_ROWS 8
#define NUM_COLUMNS 8

#define size_map 64
int open_list[size_map][NUM_COLUMNS];
int wave = 1;
int wave_index = 0;

int ind[NUM_ROWS][NUM_COLUMNS] = {
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1},
  { -1, -1, -1, -1, -1, -1, -1, -1}
};

int path[NUM_ROWS][NUM_COLUMNS] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

int path_poundary[NUM_ROWS + 2][NUM_ROWS + 2] = {
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
  {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

/**
  Add poundary to a matrix.
  @param the matrix without boundary and the poundary matrix.
  @return None.
*/
void add_poundary(int matrix1[NUM_ROWS + 2][NUM_COLUMNS + 2], int matrix2[NUM_ROWS][NUM_COLUMNS]) {
  for (int n = 0; n < NUM_ROWS; n++) { // loop for row of newMatrix
    for (int m = 0; m < NUM_COLUMNS; m++) { // loop for column of newMatrix
      // assign the value from matrix to newMatrix
      matrix1[n + 1][m + 1] = matrix2[n][m];
    }
  }
}

int start_x = 0; //vertical
int start_y = 0; //horisontal

int goal_target = -1;
int goal_x = NUM_ROWS - 1;
int goal_y = NUM_COLUMNS - 1;

int path_max_value = 0;
int calc_matrix_wave = 1; //bool

// CHANGE output for arduino
void pr(int value) {
  //    printf("%2d",value);
  Serial.print(" ");
  Serial.print(value);
}

void pr_s(char value[]) {
  //    printf(value);
  Serial.print(" ");
  Serial.print(value);
}

void ln(void) {
  //    printf("\n");
  Serial.println();
}

//arduino part start
unsigned long current_millis = millis();
unsigned long previous_millis = 0;
int goal = 0;

void setup() {
  //Serial Port begin
  Serial.begin(9600);

  //Define inputs and outputs pins for ultrasonic
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Set all the motor control pins to outputs
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
}

/**
  Turns on the motors to go forward.
  @param None.
  @return None.
*/
void forward() {
  current_millis = millis();

  // Turn on motor B and A to go forward
  analogWrite(enA, 170);
  analogWrite(enB, 200);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  if (current_millis - previous_millis >= 1560) {
    //Turn off the motors after the duration of forward is done.
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    //Change the indexs on the path matrix after the robot move
    if (direction == 0) j = j - 1;
    if (direction == 1) i = i + 1;
    if (direction == 2) j = j + 1;
    if (direction == 3) i = i - 1;

    previous_millis = current_millis;

    //print goal and stop the robot if we reach the goal
    if (goal) delay(100000);
  }
}

/**
  Turns on the motors to turn to the left.
  @param None.
  @return None.
*/
void left() {
  current_millis = millis();

  // Turn on motor B and A to turn to the left
  analogWrite(enB, 200);
  analogWrite(enA, 190);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  if (current_millis - previous_millis >= 505) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    // Change the direction of the robot after it turn left
    if (direction == 0) direction = 3;
    else if (direction == 1) direction = 0;
    else if (direction == 2) direction = 1;
    else if (direction == 3) direction = 2;

    previous_millis = current_millis;
  }
}

/**
  Turns on the motors to turn to the left after founding an obstacl.
  @param None.
  @return None.
*/
void left_obs() {
  current_millis = millis();

  // Turn on motor B and A to turn to the left
  analogWrite(enB, 200);
  analogWrite(enA, 190);

  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(500);

  if (direction == 0) direction = 3;
  else if (direction == 1) direction = 0;
  else if (direction == 2) direction = 1;
  else if (direction == 3) direction = 2;
}

/**
  Turns on the motors to turn to the right after founding an obstacl.
  @param None.
  @return None.
*/
void right_obs() {
  // Turn on motor B and A to turn to the right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  delay(500);

  if (direction == 0) direction = 1;
  else if (direction == 1) direction = 2;
  else if (direction == 2) direction = 3;
  else if (direction == 3) direction = 0;
}

/**
  Turns on the motors to turn to the right.
  @param None.
  @return None.
*/
void right() {
  current_millis = millis();

  // Turn on motor B and A to turn to the right
  analogWrite(enB, 200);
  analogWrite(enA, 190);

  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  if (current_millis - previous_millis >= 500) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    if (direction == 0) direction = 1;
    else if (direction == 1) direction = 2;
    else if (direction == 2) direction = 3;
    else if (direction == 3) direction = 0;

    previous_millis = current_millis;
  }
}
/**
  Turns on the motors to turn 180 degree.
  @param None.
  @return None.
*/
void turn_180() {
  current_millis = millis();

  analogWrite(enB, 200);
  analogWrite(enA, 190);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  if (current_millis - previous_millis >= 1000) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    if (direction == 0) direction = 2;
    else if (direction == 1) direction = 3;
    else if (direction == 2) direction = 0;
    else if (direction == 3) direction = 1;

    previous_millis = current_millis;
  }
}

void turn_180_obs() {
  current_millis = millis();

  analogWrite(enB, 200);
  analogWrite(enA, 190);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  delay(1000);

  if (direction == 0) direction = 2;
  else if (direction == 1) direction = 3;
  else if (direction == 2) direction = 0;
  else if (direction == 3) direction = 1;
}

/**
  Turns ofthe motors to stop.
  @param duration .
  @return None.
*/
void stop_robot(int duration) {
  //Stop the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);

  delay(duration);
}

/**
  Calculate the distance in the front of the robot.
  @param None.
  @return a the distance in cm.
*/
long calc_distance() {
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.

  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);

  // Convert the time into a distance
  cm = (duration / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
  return cm;
}

/**
  Test front of the robot due to the path matrix depending on the direction.
  @param None.
  @return the value of the matrix for the front.
*/
int test_front() {
  if (direction == 0) return path_poundary[j - 1][i];
  if (direction == 1) return path_poundary[j][i + 1];
  if (direction == 2) return path_poundary[j + 1][i];
  if (direction == 3) return path_poundary[j][i - 1];
}

/**
  Test right of the robot due to the path matrix depending on the direction.
  @param None.
  @return the value of the matrix for the right.
*/
int test_right() {
  if (direction == 0) return path_poundary[j][i + 1];
  if (direction == 1) return path_poundary[j + 1][i];
  if (direction == 2) return path_poundary[j][i - 1];
  if (direction == 3) return path_poundary[j - 1][i];
}

/**
  Test left of the robot due to the path matrix depending on the direction.
  @param None.
  @return the value of the matrix for the left.
*/
int test_left() {
  if (direction == 0) return path_poundary[j][i - 1];
  if (direction == 1) return path_poundary[j - 1][i];
  if (direction == 2) return path_poundary[j][i + 1];
  if (direction == 3) return path_poundary[j + 1][i];
}


/**
  Return the value of the matrix so we can now if we can go oe not.
  @param None.
  @return 1 if the front of the robot is closed due to the grid and the value of the grid if the front is open(0 or -1)
*/
int front_open() {
  int next = test_front();

  if (next == 0) return next;
  else if (next == -1) {
    goal = 1;
    return next;
  } else {
    return 1;
  }
}

/**
  Test if the right is open to turn to it or not
  @param None.
  @return return True or False.
*/
boolean right_open() {
  int next = test_right();

  if (next == 0 || next == -1) {
    return true;
  } else {
    return false;
  }
}
/**
  Test if the left if is open to turn to it or not
  @param None.
  @return return True or False.
*/
boolean left_open() {
  int next = test_left();

  if (next == 0 || next == -1) {
    return true;
  } else {
    return false;
  }
}

/**
  Calulate the J index of the Robot.
  @param None.
  @return the value of J index .
*/
int get_robot_x() {
  return j;
}

/**
    Calulate the I index of the Robot.
    @param None.
    @return the value of J index .
*/
int get_robot_y() {
  return i;
}

/**
    Calulate the J index of the obstecal.
    @param None.
    @return the value of J index .
*/
int get_obstacl_x() {
  if (direction == 0) return j - 2;
  if (direction == 1 || direction == 3) return j - 1;
  if (direction == 2) return j + 0;
}

/**
    Calulate the i index of the obstecal.
    @param None.
    @return the value of I index .
*/
int get_obstecal_y() {
  if (direction == 0 || direction == 2) return i - 1;
  if (direction == 1) return i + 0;
  if (direction == 3) return i - 2;
}

void set_obstecal() {
  ind[get_obstacl_x()][get_obstecal_y()] = OBSTACLE;
}

/**
    Update matrix with new value

    @param matrix - in which we want update element
    @param x,y - position of the element which we want update
    @param new_value - with which we want update value in mmatrix
    @return None.
*/
void update_matrix_with(int matrix[NUM_ROWS][NUM_COLUMNS], int x, int y, int new_value) {
  if (x >= 0 && x <= NUM_ROWS && y >= 0 && y <= NUM_COLUMNS) {
    matrix[x][y] = new_value;
  } else {
    pr_s("Can't update, position doesn't exist");
  }
}

/**
  Check if this point position exist in out space

  @param point_x, point_y - posiotion in our space

  @return
  1 if position found
  0 if position is not found
*/
int check_point_boundaries(int point_x, int point_y) {
  int result;
  if (point_x < NUM_ROWS && point_x >= 0 && point_y < NUM_COLUMNS && point_y >= 0) {
    result = 1; //true
  } else result = 0; //false
  return result;
}

/**
  Calculate x position from index
  @param index - from our matrix space
  @return x position from matrix in our space
*/
int get_x(int index) {
  return (index - (index % NUM_COLUMNS)) / NUM_COLUMNS;
}

/**
  Calculate y position from index
  @param index - from our matrix space
  @return y position from matrix in our space
*/
int get_y(int index) {
  return index % NUM_COLUMNS;
}

/**
  Calculate index from x,y
  @param x,y - position of point
  @return index
*/
int get_index(int x, int y) {
  return x * NUM_COLUMNS + y;
}

/**
  Calculate the value from given index
  @param index - position in matrix
  @param matrix -  from which we will take value in the specific index
  @return value
*/
int get_v_by_index(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
  int x = get_x(index);
  int y = get_y(index); int value = -1;
  if (check_point_boundaries(x, y)) value = matrix[x][y];
  return value;
}

/**
  Update point in matrix with new value
  @param matrix - in which we will update value
  @param point_index - which element we want update
  @param new_value - with which value we want update
  @return None
*/
void update_matrix_with_ind(int matrix[NUM_ROWS][NUM_COLUMNS], int point_index, int new_value) {
  int x = get_x(point_index);
  int y = get_y(point_index);

  //check if position exist
  if (x >= 0 && x <= NUM_ROWS && y >= 0 && y <= NUM_COLUMNS) {
    matrix[x][y] = new_value;
  } else {
    pr_s("Can't update, position doesn't exist");
    pr(x); pr_s(","); pr(y); ln();
  }
}

/**
  Insert all obstacles in matrix here
  @param matrix - place where we put obstacles
  @param obst - value which we will avoid
  @return None
*/
void insert_obstcls(int ind[NUM_ROWS][NUM_COLUMNS], int obst) {
  //without test no obstcls
  update_matrix_with(ind, 0, 3, OBSTACLE);
  update_matrix_with(ind, 0, 4, OBSTACLE);

  update_matrix_with(ind, 2, 3, OBSTACLE);
  update_matrix_with(ind, 2, 4, OBSTACLE);
  update_matrix_with(ind, 2, 6, OBSTACLE);

  update_matrix_with(ind, 3, 1, OBSTACLE);
  update_matrix_with(ind, 4, 0, OBSTACLE);
  update_matrix_with(ind, 4, 4, OBSTACLE);
  update_matrix_with(ind, 4, 6, OBSTACLE);

  update_matrix_with(ind, 5, 2, OBSTACLE);

  update_matrix_with(ind, 6, 5, OBSTACLE);
  update_matrix_with(ind, 7, 0, OBSTACLE);
  update_matrix_with(ind, 7, 3, OBSTACLE);
}

/**
  Change value in all matrix
  @param matrix - in which we change value
  @param replace_what - one value which we want replace in all matrix with new value (replace_with)
  @param replace_with - new value
  @return None
*/
void replace_all(int matrix[NUM_ROWS][NUM_COLUMNS], int replace_what, int replace_with) {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLUMNS; j++) {
      if (matrix[i][j] == replace_what) matrix[i][j] = replace_with;
    }
  }
}

/**
  Calculate index for 4 directions (movement) up, left, right, down.

  Calculate x,y of next movement, check if we can get value from next movement (including boundaries check )
  @param matrix - matrix in which we want get index
  @param index - number of point (like center) from which we get points up/left/right/down
  @return index
*/
int get_index_up(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
  int x = get_x(index);
  int y = get_y(index) - 1;
  int to_return = -1;
  if (check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE) to_return = get_index(x, y);
  return to_return;
}

int get_index_left(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
  int x = get_x(index) + 1;
  int y = get_y(index);
  int to_return = -1;
  if (check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE) to_return = get_index(x, y);
  return to_return;
}

int get_index_right(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
  int x = get_x(index) - 1;
  int y = get_y(index);
  int to_return = -1;
  if (check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE) to_return = get_index(x, y);
  return to_return;
}

int get_index_down(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
  int x = get_x(index); int y = get_y(index) + 1;
  int to_return = -1;
  if (check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE) to_return = get_index(x, y);
  return to_return;
}

/**
  Calculate ALL possible variants from cur point where to go

  @param possible indexes - to store indexes
  @param matrix - original filled matrix with values from 1...to Max,
  @param point_index - from which point we check where can we go
  @return index
*/
int get_possible_indexes(int possible_indexes[DIMENTION], int matrix[NUM_ROWS][NUM_COLUMNS], int point_index) {
  int not_checked_value = -4;
  int size_v = DIMENTION + 1;
  static int checked_values[5]; //5 = DIMENTION+1 to stor center point
  static int store_indexes[5];

  for (int i = 0; i < size_v; i++) {
    checked_values[i] = not_checked_value;
    store_indexes[i] = not_checked_value + 1;
  }

  store_indexes[0] = get_index_up(matrix, point_index);
  store_indexes[1] = get_index_left(matrix, point_index);
  store_indexes[2] = get_index_right(matrix, point_index);
  store_indexes[3] = get_index_down(matrix, point_index);
  store_indexes[4] = point_index;

  for (int i = 0; i < size_v; i++) checked_values[i] = get_v_by_index(matrix, store_indexes[i]);

  int to_return = -5;
  int minimum_value_index = -1;
  int minimum_value = 100;
  for (int i = 0; i < DIMENTION; i++) {
    possible_indexes[i] = -1;
    if (checked_values[i] != OBSTACLE) {
      if (store_indexes[i] >= point_index && checked_values[i] == -1) {
        possible_indexes[i] = store_indexes[i];
      } else if (store_indexes[i] < point_index && checked_values[i] == -1) {
        possible_indexes[i] = store_indexes[i];
      }

      if (checked_values[i] > 0) {
        if (checked_values[i] < minimum_value) {
          minimum_value = checked_values[i];
          minimum_value_index = store_indexes[i];
        }
      }
    }
    to_return = minimum_value_index;
  }
  return to_return;
}

/**
  Calculate possible variants where to go

  @param possible indexes - to store indexes
  @param matrix - original filled matrix with values from 1...to Max,
  @param point_index - from which point we check where can we go
  @return index,
*/
int get_possible_indexes_path(int matrix[NUM_ROWS][NUM_COLUMNS], int point_index) {
  int not_checked_value = -4;
  int size_v = DIMENTION + 1;
  static int checked_values[5]; //5 = DIMENTION+1 to store center point
  static int store_indexes[5];

  for (int i = 0; i < size_v; i++) {
    checked_values[i] = not_checked_value;
    store_indexes[i] = not_checked_value + 1;
  }

  store_indexes[0] = get_index_up(matrix, point_index);
  store_indexes[1] = get_index_left(matrix, point_index);
  store_indexes[2] = get_index_right(matrix, point_index);
  store_indexes[3] = get_index_down(matrix, point_index);
  store_indexes[4] = point_index;

  for (int i = 0; i < size_v; i++) {
    checked_values[i] = get_v_by_index(matrix, store_indexes[i]);
  }

  int to_return = -5;
  int minimum_value_index = -1;
  int minimum_value = 100;
  for (int i = 0; i < DIMENTION; i++) {
    int next_point = get_v_by_index(matrix, point_index) - 1;
    if (checked_values[i] > 0 && store_indexes[i] >= 0 && checked_values[i] <= next_point && checked_values[i] != OBSTACLE) {
      if (checked_values[i] > 0) {
        if (checked_values[i] < minimum_value) {
          minimum_value = checked_values[i];
          minimum_value_index = store_indexes[i];
        }
      }
    }
    to_return = minimum_value_index;
  }
  return to_return;
}

/**
  Clean data in path and ind matrix for good usage

  @param None
  @return None
*/
void clean_path(void) {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLUMNS; j++) {
      path[i][j] = 0;
    }
  }
}

void clean_ind(void) {
  for (int i = 0; i < NUM_ROWS; i++) {
    for (int j = 0; j < NUM_COLUMNS; j++) {
      ind[i][j] = -1;
    }
  }
}

/**
  Calculate matrix for best path finding

  1. Insert obstacles
  2. In open list we record on certan wave(like level) and wave_index(we need this to start and finish in this frame of index)
  3. Get index where we start filling the matrix. Note: When we update matrix after inserting new obstacle, we update strart_index with current position where we stopped, that here we will start not from the beginning, but from last point where we stopped
  4. Calculate all possible variants to go
  5. Store  possible variants where to go (from which point we will fill matrix. Insert wave in ind matrix.index
  6. When we fill initial elements, we update from which point we start looking into open wave, that on next wave we insert next value
  7. Fill all matrix, take values from open list. If we reach the gol - do exit
  8. Update last index in open_list

  @param None
  @return None
*/
void calc_matrix_wave_func(void) {
  insert_obstcls(ind, OBSTACLE);

  open_list[wave][wave_index] = 1;
  ind[start_x][start_y] = wave;

  int tmp_start_index = get_index(start_x, start_y);

  //get possible variants
  int possible_indexes[DIMENTION];
  get_possible_indexes(possible_indexes, ind, tmp_start_index);

  for (int i = 0; i < DIMENTION; i++) {
    if (possible_indexes[i] > 0) {
      open_list[wave + 1][wave_index++] = possible_indexes[i]; //add index to open_list
      update_matrix_with_ind(ind, possible_indexes[i], wave + 1);
    }
  }

  int exit_filling = 0;
  int start_for_j = 0;
  wave++;

  for (int i = wave; i < size_map; i++) {
    int last_posible_index_position_in_open_list = wave_index;
    for (int j = start_for_j; j < last_posible_index_position_in_open_list; j++) {

      //add index to open_list
      int tmp_goal_index = get_index(goal_x, goal_y);
      if (open_list[i][j] == tmp_goal_index) {
        exit_filling = 1;
        break;
      }

      get_possible_indexes(possible_indexes, ind, open_list[i][j]);

      for (int l = 0; l < DIMENTION; l++) {
        if (possible_indexes[l] > 0) {
          open_list[wave + 1][wave_index++] = possible_indexes[l]; //add index to open_list
          update_matrix_with_ind(ind, possible_indexes[l], wave + 1);
        }
        possible_indexes[l] = -1;
      }
    }
    wave++;
    start_for_j = last_posible_index_position_in_open_list;
    if (exit_filling) break;
  }
}

/**
  Path finding

  Now, when we have filled matrix ind, we start going from goal_index, and we are looking for smallest value, thats our next point to move. We dont need to store it on clsoe_list, because we always have best path (Note: be careful with obstacle, make sure there is at least one way to reach the goal). If we reach start x,y, we stop. In parallel we encode path.

  @param None
  @return None
*/
void path_finding(void) {
  //get path
  int filling_path_with = 1;
  int point_down = goal_x;
  int point_right = goal_y;
  int index_tmp = get_index(goal_x, goal_y);
  int returned_index = get_possible_indexes_path(ind, index_tmp); //return one index to go
  int next_x = get_x(returned_index);
  int next_y = get_y(returned_index);

  int value = ind[next_x][next_y];

  int path_found = 1;
  int exit_path_not_found = NUM_ROWS * NUM_COLUMNS + 1;

  while (1) {
    if (next_x == start_x && next_y == start_y) break;
    point_down = next_x; point_right = next_y; //get new position

    update_matrix_with(path, point_down, point_right, filling_path_with); //encoding path

    int index_tmp = get_index(point_down, point_right);
    returned_index = get_possible_indexes_path(ind, index_tmp); //return one index to go
    next_x = get_x(returned_index);
    next_y = get_y(returned_index);

    value = ind[next_x][next_y];
    exit_path_not_found--;
    if (exit_path_not_found == 0) {
      path_found = 0; //path not found
      break;
    }
  }
  update_matrix_with(path, start_x, start_y, filling_path_with);
  update_matrix_with(path, goal_x, goal_y, goal_target); //for -1

  //final encoding
  replace_all(path, 1, 2);
  replace_all(path, 0, 1);
  replace_all(path, 2, 0); //path 0
  if (path_found) {
    pr_s("Path found\n");
  } else {
    //action
    pr_s("Path NOT found\n"); ln();
  }
  calc_matrix_wave = 0;
  wave = 1;
  wave_index = 0;
}

void loop() {
  if (calc_matrix_wave) {
    calc_matrix_wave_func();
    path_finding(); //update-return path
    add_poundary(path_poundary, path);
  }

  if (calc_distance() < 25) {
    stop_robot(100);

    start_y = i - 1;
    start_x = j - 1;

    clean_path();
    clean_ind();
    set_obstecal();

    calc_matrix_wave_func();

    path_finding(); //update-return path
    add_poundary(path_poundary, path);

    if (right_open() == true) {
      right_obs();
      stop_robot(10);
    } else if (left_open() == true) {
      left_obs();
      stop_robot(10);
    } else {
      turn_180_obs();
      stop_robot(10);
    }
  } else {
    if (front_open() == 0 || front_open() == -1) forward();
    else if (right_open() == true) right();
    else if (left_open() == true) left();
    else turn_180();
  }
}
