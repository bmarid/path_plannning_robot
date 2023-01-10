////—------------ Mari car-----------------------
//// Motor A
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
//---------------------HALA car-----------------------
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
//  the point in the grid where the robot is

int i = 0;
int j = 0;

//c part start
//#include <stdio.h>
#define DIMENTION 4 //UP LEFT RIGHT DOWN
#define OBSTACLE 99
#define beautiful_output 1 //beautiful output

//Test 1 normal 8 8
#define NUM_ROWS 8
#define NUM_COLUMNS 8

#define size_map 64
int open_list[size_map][NUM_COLUMNS];
int wave = 1;
int wave_index = 0;

int ind[NUM_ROWS][NUM_COLUMNS] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
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

//this is to see data during testing process
int test = 0;

//int start = 1; //start point
int start_x = 0; //vertical
int start_y = 0; //horisontal
//int start_index = 0;

int goal_target = -1;
int goal_x = NUM_ROWS - 1;
int goal_y = NUM_COLUMNS - 1;
//int goal_index = 63;

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
unsigned long currentMillis = millis();
unsigned long previousMillis = 0;
int goal = 0;

void setup() {
  //Ulterasonic
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
  turns on the motors to go forward.

  @param None.
  @return None.
*/

void forward() {
  currentMillis = millis();
//  Serial.println(currentMillis);

  // Turn on motor B and A to go forward
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);

  analogWrite(enB, 200);
  analogWrite(enA, 175);

  if (currentMillis - previousMillis >= 1800) {

      Serial.println("Forward");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      //Change the indexs on the path matrix after the robot move
      if (direction == 0)
          j = j - 1;
      if (direction == 1)
          i = i + 1;
      if (direction == 2)
          j = j + 1;
      if (direction == 3)
          i = i - 1;
 previousMillis = currentMillis;
       if (goal) {

              delay(100000);
          }

  }
}

/**
  turns on the motors to turn to the left.

  @param None.
  @return None.
*/
void left() {
  currentMillis = millis();
//Serial.println(currentMillis);

  // Turn on motor B and A to turn to the left
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enB, 200);
  analogWrite(enA, 175);


  if (currentMillis - previousMillis >= 500) {

  Serial.println("Left");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      // Change the direction of the robot after it turn left
      if (direction == 0)
          direction = 3;
      else if (direction == 1)
          direction = 0;
      else if (direction == 2)
          direction = 1;
      else if (direction == 3)
          direction = 2;
      previousMillis = currentMillis;

  }
}
/**
  turns on the motors to turn to the right.

  @param None.
  @return None.
*/
void right() {
  currentMillis = millis();
//Serial.println(currentMillis);

    // Turn on motor B and A to turn to the right
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  analogWrite(enB, 200);
  analogWrite(enA, 175);


  if (currentMillis - previousMillis >= 500) {
    Serial.println("Right");
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);

      if (direction == 0)
          direction = 1;
      else if (direction == 1)
          direction = 2;
      else if (direction == 2)
          direction = 3;
      else if (direction == 3)
          direction = 0;
      previousMillis = currentMillis;
  }
}
/**
  turns on the motors to turn 180 degree.

  @param None.
  @return None.
*/
void turn180() {
  currentMillis = millis();
  Serial.println("Around");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  if (currentMillis - previousMillis >= 1000) {
      digitalWrite(in1, LOW);
      digitalWrite(in2, LOW);
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
  if (direction == 0)
      direction = 2;
  else if (direction == 1)
      direction = 3;
  else if (direction == 2)
      direction = 0;
  else if (direction == 3)
      direction = 1;
  previousMillis = currentMillis;
  }


}

/**
  turns ofthe motors to stop.

  @param None.
  @return None.
*/
void stopRobot() {
  //Stop the motors
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(2000);
}

/**
  Calculate the distance in the front of the robot.

  @param None.
  @return a the distance in cm.
*/
long calcDistance() {/////most change the comments---------------------------------

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

//  Serial.print(cm);
//  Serial.print("cm");
//  Serial.println();
  // delay(250);

  return cm;
}



/**
  test front of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix for the front.
*/
int testFront() {
  if (direction == 0) {
      return path[j - 1][i];
  }
  if (direction == 1) {
      return path[j][i + 1];
  }
  if (direction == 2) {
      return path[j + 1][i];
  }
  if (direction == 3) {
      return path[j][i - 1];
  }
}

/**
  test right of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix for the right.
*/
int testRight() {
  if (direction == 0) {
      return path[j][i + 1];
  }
  if (direction == 1) {
      return path[j + 1][i];
  }
  if (direction == 2) {
      return path[j][i - 1];
  }
  if (direction == 3) {
      return path[j - 1][i];
  }
}

/**
  test left of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix for the left.
*/
int testLeft() {
  if (direction == 0) {
      return path[j][i - 1];
  }
  if (direction == 1) {
      return path[j - 1][i];
  }
  if (direction == 2) {
      return path[j][i + 1];
  }
  if (direction == 3) {
      return path[j + 1][i];
  }
}


/**
  return the value of the matrix so we can now if we can go oe not.

  @param None.
  @return 1 if the front of the robot is closed due to the grid and the value of the grid if the front is open(0 or -1)
*/
int frontOpen() {
  int next = testFront();
  if (next == 0) {
      return next;
  }
  else if (next == -1) {
      goal = 1;
      return next;
  }

  else {
      return 1;
  }
}

/**
  test if the right is open to turn to it or not

  @param None.
  @return return True or False.
*/
boolean rightOpen() {
  int next = testRight();
  if (next == 0 || next == -1) {
      return true;
  }
  else {
      return false;
  }
}
/**
  test if the left if is open to turn to it or not

  @param None.
  @return return True or False.
*/
boolean leftOpen() {
  int next = testLeft();
  if (next == 0 || next == -1) {
      return true;
  }
  else {
      return false;
  }
}

/**
  calulate the J index of the Robot.
  @param None.
  @return the value of J index .
*/
int getRobotX(){
  return j;
  }

/**
  calulate the I index of the Robot.
  @param None.
  @return the value of J index .
*/
int getRobotY(){
  return i;
  }

/**
  calulate the J index of the obstecal.
  @param None.
  @return the value of J index .
*/
int getObstecalX() {
    if (direction == 0) {
        return j - 1;
    }
    if (direction == 1 || direction == 3) {
        return j;
    }
    if (direction == 2) {
        return j + 1;
    }
}

/**
  calulate the i index of the obstecal.
  @param None.
  @return the value of i index .
*/
int getObstecalY(){
   if (direction == 0 || direction == 2) {
        return i;
    }
    if (direction == 1) {
        return i + 1;
    }

    if (direction == 3) {
        return i - 1;
    }
  }


void setObstecal() {
  ind[getObstecalX()][getObstecalY()] = OBSTACLE;
}
//arduino part finish


int update_matrix_with(int matrix[NUM_ROWS][NUM_COLUMNS], int x, int y, int new_value) {
    //check if position exist
    if(x >= 0 && x <= NUM_ROWS && y >= 0 && y <= NUM_COLUMNS) {
        matrix[x][y] = new_value;
    } else {
        pr_s("Can't update, position doesn't exist");
        pr(x); pr_s(","); pr(y); ln();
    }
    return matrix[x][y];
}

int check_point_boundaries(int point_x, int point_y) {
    int result;
    if (point_x < NUM_ROWS && point_x >= 0 && point_y < NUM_COLUMNS && point_y >= 0) {
        result = 1; //true
    } else result = 0; //false
    return result;
}

int get_x(int index) {
    return (index - (index % NUM_COLUMNS)) / NUM_COLUMNS;
}

int get_y(int index) {
    return index % NUM_COLUMNS;
}

int get_index(int x, int y) {
    int index = x * NUM_COLUMNS + y;
    return index;
}

//get_value_by_index
int get_v_by_index(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
    int x = get_x(index); int y = get_y(index); int value = -1;
    if(check_point_boundaries(x, y)) value = matrix[x][y];
    return value;
}

int update_matrix_with_ind(int matrix[NUM_ROWS][NUM_COLUMNS], int point_index, int new_value) {
    int x = get_x(point_index); int y = get_y(point_index);
    //check if position exist
    if(x >= 0 && x <= NUM_ROWS && y >= 0 && y <= NUM_COLUMNS) {
        matrix[x][y] = new_value;
    } else {
        pr_s("Can't update, position doesn't exist");
        pr(x); pr_s(","); pr(y); ln();
    }
    return matrix[x][y];
}

void insert_obstcls(int ind[NUM_ROWS][NUM_COLUMNS], int obst){
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

void ind_first_line(void) {
    pr_s("..");
    for(int i = 0; i < NUM_COLUMNS; i++) {
        pr(i);
        pr_s(" ");
    }
    ln();
}

void show_matrix(int matrix[NUM_ROWS][NUM_COLUMNS]) {
    if(beautiful_output) ind_first_line();
    for(int i = 0; i < NUM_ROWS; i++){
        if(beautiful_output) pr(i);
        for(int j = 0; j < NUM_COLUMNS; j++){
            pr(matrix[i][j]);
            pr_s(" ");
        } ln();
    } ln();
}

void show_matrix_ind(int matrix[NUM_ROWS][NUM_COLUMNS]) {
    if(beautiful_output) ind_first_line();
    for(int i = 0; i < NUM_ROWS; i++){
        if(beautiful_output) pr(i);
        for(int j = 0; j < NUM_COLUMNS; j++){
            pr(matrix[i][j]);
            pr_s("["); pr(get_index(i, j));pr_s("] ");
        } ln();
    } ln();
}

void replace_all(int matrix[NUM_ROWS][NUM_COLUMNS], int replace_what, int replace_with) {
    for(int i=0; i < NUM_ROWS; i++){
        for(int j=0; j < NUM_COLUMNS; j++){
            if(matrix[i][j] == replace_what) matrix[i][j] = replace_with;
        }
    }
}

int get_index_up(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
    int x = get_x(index); int y = get_y(index) - 1;
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE)
        to_return = get_index(x, y);
    return to_return;
}

int get_index_left(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
    int x = get_x(index) + 1; int y = get_y(index);
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE)
        to_return = get_index(x, y);
    return to_return;
}

int get_index_right(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
    int x = get_x(index) - 1; int y = get_y(index);
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE)
        to_return = get_index(x, y);
    return to_return;
}

int get_index_down(int matrix[NUM_ROWS][NUM_COLUMNS], int index) {
    int x = get_x(index); int y = get_y(index) + 1;
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBSTACLE)
        to_return = get_index(x, y);
    return to_return;
}

int get_possible_indexes(int possible_indexes[DIMENTION], int matrix[NUM_ROWS][NUM_COLUMNS], int point_index) {
    int not_checked_value = -4;
    int size_v = DIMENTION + 1;
    static int checked_values[5]; //5 = DIMENTION+1 to stor center point
    static int store_indexes[5];

    for(int i = 0; i < size_v; i++) {
        checked_values[i] =  not_checked_value;
        store_indexes[i] = not_checked_value + 1;
    }

    store_indexes[0] = get_index_up(matrix, point_index);
    store_indexes[1] = get_index_left(matrix, point_index);
    store_indexes[2] = get_index_right(matrix, point_index);
    store_indexes[3] = get_index_down(matrix, point_index);
    store_indexes[4] = point_index;

    for(int i = 0; i < size_v; i++){
        checked_values[i] = get_v_by_index(matrix, store_indexes[i]);
    }

    int to_return = -5;
    int minimum_value_index = -1;
    int minimum_value = 100;
    for(int i = 0; i < DIMENTION; i++) {
        possible_indexes[i] = -1;
        if(checked_values[i] != OBSTACLE){
            if(store_indexes[i] >= point_index && checked_values[i] == -1) {
                possible_indexes[i] = store_indexes[i];
            } else if (store_indexes[i] < point_index && checked_values[i] == -1) {
                possible_indexes[i] = store_indexes[i];
            }

            if(checked_values[i] > 0 ) {
                if(checked_values[i] < minimum_value) {
                    minimum_value = checked_values[i];
                    minimum_value_index = store_indexes[i];
                }
            }
        }
        to_return = minimum_value_index;
    }
    return to_return;
}

int get_possible_indexes_path(int matrix[NUM_ROWS][NUM_COLUMNS], int point_index) {
    int not_checked_value = -4;
    int size_v = DIMENTION + 1;
    static int checked_values[5]; //5 = DIMENTION+1 to stor center point
    static int store_indexes[5];

    for(int i = 0; i < size_v; i++) {
        checked_values[i] =  not_checked_value;
        store_indexes[i] = not_checked_value + 1;
    }

    store_indexes[0] = get_index_up(matrix, point_index);
    store_indexes[1] = get_index_left(matrix, point_index);
    store_indexes[2] = get_index_right(matrix, point_index);
    store_indexes[3] = get_index_down(matrix, point_index);
    store_indexes[4] = point_index;

    for(int i = 0; i < size_v; i++){
        checked_values[i] = get_v_by_index(matrix, store_indexes[i]);
    }

    int to_return = -5;
    int minimum_value_index = -1;
    int minimum_value = 100;
    for(int i = 0; i < DIMENTION; i++) {
        int next_point = get_v_by_index(matrix, point_index) - 1;
        if(checked_values[i] > 0 && store_indexes[i] >= 0 && checked_values[i] <= next_point  && checked_values[i] != OBSTACLE){
            if(checked_values[i] > 0 ) {
                if(checked_values[i] < minimum_value) {
                    minimum_value = checked_values[i];
                    minimum_value_index = store_indexes[i];
                }
            }
        }
        to_return = minimum_value_index;
    }
    return to_return;
}

void clean_path(void) {
  for(int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLUMNS; j++){
            path[i][j] = 0;
        }
    }
}
void clean_ind(void) {
  for(int i = 0; i < NUM_ROWS; i++){
        for(int j = 0; j < NUM_COLUMNS; j++){
            ind[i][j] = -1;
        }
    }
}

void calc_matrix_wave_func_2(void)  {
    insert_obstcls(ind, OBSTACLE);

    open_list[wave][wave_index] = 1; //1-open, 0 - closed/visited
    ind[start_x][start_y] = wave;

    int tmp_start_index = get_index(start_x, start_y);

    //possible variants
    int possible_indexes[DIMENTION];
    get_possible_indexes(possible_indexes, ind, tmp_start_index);

    for(int i = 0; i < DIMENTION; i++) {
        if(possible_indexes[i] > 0) {
            open_list[wave + 1][wave_index++] = possible_indexes[i]; //add index to open_list
            update_matrix_with_ind(ind, possible_indexes[i], wave + 1);
        }
    }

    int exit_filling = 0;
    int start_for_j = 0;
    wave++;

    for(int i = wave; i < size_map; i++){
        int last_posible_index_position_in_open_list = wave_index;
        for(int j = start_for_j; j < last_posible_index_position_in_open_list; j++) {
            //add index to open_list
            int tmp_goal_index = get_index(goal_x, goal_y);
            if(open_list[i][j] == tmp_goal_index) {
                exit_filling = 1;
                break;
            }
            get_possible_indexes(possible_indexes, ind, open_list[i][j]);

            for(int l = 0; l < DIMENTION; l++) {
                if(possible_indexes[l] > 0) {
                    open_list[wave+1][wave_index++] = possible_indexes[l]; //add index to open_list
                    update_matrix_with_ind(ind, possible_indexes[l], wave+1);
                } possible_indexes[l] = -1;
            }
        }
        wave++;
        start_for_j = last_posible_index_position_in_open_list;
        if(exit_filling) break;
    }
}

void path_finding(void) {
    //get path //path finding
    int filling_path_with = 1;
    int point_down = goal_x; int point_right = goal_y; //    int point_down = 7; int point_right = 3;
    int index_tmp = get_index(goal_x, goal_y); //get_index(point_down, point_right);
    int returned_index = get_possible_indexes_path(ind, index_tmp); //return one index to go
    int next_x = get_x(returned_index);
    int next_y = get_y(returned_index);

    int value = ind[next_x][next_y];

    int path_found = 1;
    int exit_path_not_found = NUM_ROWS * NUM_COLUMNS + 1;

    while(1){
        if (next_x == start_x && next_y == start_y) break;
        point_down = next_x; point_right = next_y; //get new position

        update_matrix_with(path, point_down, point_right, filling_path_with); //encoding path

        int index_tmp = get_index(point_down, point_right);
        returned_index = get_possible_indexes_path(ind, index_tmp); //return one index to go
        next_x = get_x(returned_index);
        next_y = get_y(returned_index);

        value = ind[next_x][next_y];
        exit_path_not_found--;
        if(exit_path_not_found == 0) {
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
    if(path_found) {
        pr_s("Path found\n");
    } else {
        //action
        pr_s("Path NOT found\n"); ln();
    }
    calc_matrix_wave = 0;
    wave = 1;
    wave_index = 0;
}


//c part finish


void loop() {
    if(calc_matrix_wave) {
//    pr_s("calc_matrix_wave inside = "); pr(calc_matrix_wave); ln();
      calc_matrix_wave_func_2();
      ln(); pr_s("SHOW IND"); ln();
      show_matrix_ind(ind);
//      show_matrix(ind);

      path_finding(); //update/return path
      show_matrix(path);
  }

  if (calcDistance() < 35) {
      stopRobot();

      start_y = i;
      start_x = j;

      pr_s("We stopped at ");
      pr_s("x =");pr(start_x);
      pr_s("y =");pr(start_y); ln();

      clean_path();
      clean_ind();
      setObstecal();

      calc_matrix_wave_func_2();
      ln(); pr_s("SHOW new IND"); ln();
      show_matrix_ind(ind);
//      show_matrix(ind);
      path_finding(); //update/return path
      show_matrix(path);
      i = start_y;
      j = start_x;
       pr_s("We start from ");
      pr_s("x =");pr(i);
      pr_s("y =");pr(j); ln();
      if (rightOpen() == true) {
          right();
      }
      else if (leftOpen() == true) {
          left();
      }
      else {
             turn180();}
  //recalc path----------------------------------------------
  }
  else {
      // pr_s("ELSE calc_matrix_wave inside = "); pr(calc_matrix_wave);ln();
      if (frontOpen() == 0 || frontOpen() == -1) {
          forward();

      }
      else if (rightOpen() == true) {
          right();
      }
      else if (leftOpen() == true) {
          left();
      }
      else {
          turn180();
      }
  }
}
