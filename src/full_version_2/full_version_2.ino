//#include "ArduinoSTL.h"

//—--- Mari car
// Motor A
int enA = 9;
int in1 = 2;
int in2 = 3;

// Motor B
int enB = 10;
int in3 = 4;
int in4 = 5;

//Ultrasonic
int trigPin = 12; // Trigger
int echoPin = 11; // Echo


//—--- Hala car
//int enA = 9;
//int in1 = 8;
//int in2 = 7;
//
//// Motor B
//
//int enB = 3;
//int in3 = 5;
//int in4 = 4;
//
////Ultrasonic
//int trigPin = 11;  // Trigger
//int echoPin = 10; // Echo

//---------------------HALA car-----------------------keep
long duration, cm;
int goal = 0;

// 0 is up
// 1 is right
// 2 is down
// 3 is left
int direction = 2;
//  the point in the grid where the robot is
//TODO: take variable from start_x, start_y
int i = 0;
int j = 0;
int obst_x = -1;
int obst_y = -1;

// path part start
#define D 4 //dimention
#define OBST 99
#define beautiful_output 1 //beautiful output
//
//Test 1 normal 8 8
#define map_size_rows 8
#define map_size_cols 8
//
#define size_map 64
int open_list[size_map][map_size_cols];
int wave = 1;
int wave_index = 0;

int start = 1; //start point
int start_x; //vertical
int start_y; //horisontal
int start_index = 0;
//start_y = i;
//start_x = j;
int goal_target = -1; //TODO: FINALLY REWRITE FOR PATH
int goal_x = map_size_rows - 1;
int goal_y = map_size_cols - 1;
int goal_index = 63;

int ind[map_size_rows][map_size_cols] = {
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1},
    {-1, -1, -1, -1, -1, -1, -1, -1}
};

int path[map_size_rows][map_size_cols] = {
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
int test_main = 0;
int test_main_path = 0;
int test_main_display = 0;
int test_arduino = 0; //for arduino functions to show
//int test_main_path_arduino = 1;

//int goal_x = 7; int goal_y = 1; //test left goal
int path_max_value = 0;
int calc_matrix_wave = 1; // 1 - calculated?

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

void ln(void){
//    printf("\n");
    Serial.println();
}


//arduino part starts here

unsigned long currentMillis = millis();
unsigned long previousMillis = 0;

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
  turns on the motors to go forward and calculate the current indexes after moving.

  @param None.
  @return None.
*/

void forward() {
 currentMillis = millis();
 Serial.println(currentMillis);
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

//
///**
//  turns on the motors to turn to the left and change the current direction after moving.
//
//  @param None.
//  @return None.
//*/
//
void left() {
 currentMillis = millis();
Serial.println(currentMillis);
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
//
///**
//  turns on the motors to turn to the right and change the current direction after moving.
//
//  @param None.
//  @return None.
//*/
//
void right() {
    currentMillis = millis();
   Serial.println(currentMillis);
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
  turns off the motors for 2 secondes.

  @param None.
  @return None.
*/
void stopRobot() {
    if (test_arduino) pr_s("stop_robot"); ln();
    //Stop the motors
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(2000);
}
//
///**
//  turns on the motors to turn 180 degree and change the current direction after moving.
//
//  @param None.
//  @return None.
//*/
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
///**
//  Calculate the distance in the front of the robot.
//
//  @param None.
//  @return a the distance in cm.
//*/
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

 Serial.print(cm);
 Serial.print("cm");
 Serial.println();
 // delay(250);

 return cm;
}
/**
  calulate the J index of the obstecal.

  @param None.
  @return the value of J index .
*/
//int returnIndexJ() {
//    if (direction == 0) {
//        return j - 1;
//    }
//    if (direction == 1 || direction == 3) {
//        return j;
//    }
//    if (direction == 2) {
//        return j + 1;
//    }
//}

/**
  calulate the i index of the obstecal.
//
  @param None.
  @return the value of i index .
*/
//int returnIndexI() {
//    if (direction == 0 || direction == 2) {
//        return i;
//    }
//    if (direction == 1) {
//        return i + 1;
//    }
//
//    if (direction == 3) {
//        return i - 1;
//    }
//}
//
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
  test the right of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix to the right.
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
  test the left of the robot due to the path matrix depending on the direction.

  @param None.
  @return the value of the matrix to the left.
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
  @return 1 if the front of the robot is closed due to the grid and the value of the grid if the front is open(0 or -1).
*/
int frontOpen() {
    if (test_arduino) pr_s("frontOpen"); ln();

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
  test if the right is open to turn to it or not.

  @param None.
  @return True or False.
*/
boolean rightOpen() {
    if (test_arduino) pr_s("rightOpen"); ln();
    int next = testRight();
    if (next == 0 || next == -1) {
        return true;
    }
    else {
        return false;
    }
}

/**
  test if the left is open to turn to it or not.

  @param None.
  @return True or False.
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


//change on update_matrix_with?
void setObstecal() {
    obst_x = getObstecalX();
    obst_y = getObstecalY();
    ind[obst_x][obst_y] = OBST;
    ln();
    pr(ind[obst_x][obst_y]);
    pr_s("[");pr(obst_x); pr_s("]");
    pr_s("[");pr(obst_y); pr_s("]"); ln();
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

////arduino part finish

int update_matrix_with(int matrix[map_size_rows][map_size_cols], int x, int y, int new_value){
    //check if position exist
    if(x >= 0 && x <= map_size_rows && y >= 0 && y <= map_size_cols) {
        matrix[x][y] = new_value;
    }
    else {
        pr_s("Can't update, position doesn't exist");
        pr(x); pr_s(","); pr(y); ln();
    }
    return matrix[x][y];
}

int check_point_boundaries(int point_x, int point_y) {
   int result;
   if (point_x < map_size_rows && point_x >= 0 && point_y < map_size_cols && point_y >= 0) {
       result = 1; //true
   } else result = 0; //false
   return result;
}

void insert_obstcls(int ind[map_size_rows][map_size_cols], int obst){
    update_matrix_with(ind, 0, 3, OBST);
    update_matrix_with(ind, 0, 4, OBST);
    
    update_matrix_with(ind, 2, 3, OBST);
    update_matrix_with(ind, 2, 4, OBST);
    update_matrix_with(ind, 2, 6, OBST);
    
    update_matrix_with(ind, 3, 1, OBST);
    update_matrix_with(ind, 4, 0, OBST);
    update_matrix_with(ind, 4, 4, OBST);
    update_matrix_with(ind, 4, 6, OBST);
    
    update_matrix_with(ind, 5, 2, OBST);
    
    update_matrix_with(ind, 6, 5, OBST);
    update_matrix_with(ind, 7, 0, OBST);
    update_matrix_with(ind, 7, 3, OBST);
}

void ind_first_line(void) {
    pr_s("..");
    for(int i = 0; i < map_size_cols; i++) {
        pr(i);
        pr_s(" ");
    }
    ln();
}

void show_matrix(int matrix[map_size_rows][map_size_cols]){
    if(beautiful_output) ind_first_line();
    for(int i = 0; i < map_size_rows; i++){
        if(beautiful_output) pr(i);
        for(int j = 0; j < map_size_cols; j++){
            pr(matrix[i][j]);
            pr_s(" ");
        } ln();
    } ln();
}

int get_x(int index) {
    return (index - (index % map_size_cols)) / map_size_cols;
}
int get_y(int index) {
    return index % map_size_cols;
}

int get_index(int x, int y) {
    int index = x * map_size_cols + y;
    return index;
}


//get_value_by_index
int get_v_by_index(int matrix[map_size_rows][map_size_cols], int index) {
    int x = get_x(index); int y = get_y(index); int value = -1;
    if(check_point_boundaries(x, y)) value = matrix[x][y];
    return value;
}

void show_matrix_ind(int matrix[map_size_rows][map_size_cols]) {
    if(beautiful_output) ind_first_line();
    for(int i = 0; i < map_size_rows; i++){
        if(beautiful_output) pr(i);
        for(int j = 0; j < map_size_cols; j++){
            pr(matrix[i][j]);
            pr_s("["); pr(get_index(i, j));pr_s("] ");
        } ln();
    } ln();
}

void show_matrix_revert(int matrix[map_size_rows][map_size_cols]){
    if(beautiful_output) {
        pr_s(".. ");
        for(int i = map_size_rows - 1; i >= 0; i--)
            pr(i);
        ln();
    }
    for(int i = map_size_rows - 1; i >= 0; i--) {
        if(beautiful_output) {
            pr(i);
            pr_s(":");
         }
        for(int j = map_size_rows - 1; j >= 0; j--) {
          pr(matrix[i][j]);
        }
        ln();
    } ln();
}

void replace_all(int matrix[map_size_rows][map_size_cols], int replace_what, int replace_with) {
    for(int i=0; i < map_size_rows; i++){
        for(int j=0; j < map_size_cols; j++){
            if(matrix[i][j] == replace_what) matrix[i][j] = replace_with;
        }
    }
}

int get_index_up(int matrix[map_size_rows][map_size_cols], int index) {
    int x = get_x(index); int y = get_y(index) - 1;
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBST)
        to_return = get_index(x, y);
    return to_return;
}

int get_index_left(int matrix[map_size_rows][map_size_cols], int index) {
    int x = get_x(index) + 1; int y = get_y(index);
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBST)
        to_return = get_index(x, y);
    return to_return;
}

int get_index_right(int matrix[map_size_rows][map_size_cols], int index) {
    int x = get_x(index) - 1; int y = get_y(index);
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBST)
        to_return = get_index(x, y);
    return to_return;
}

int get_index_down(int matrix[map_size_rows][map_size_cols], int index) {
    int x = get_x(index); int y = get_y(index) + 1;
    int to_return = -1;
    if(check_point_boundaries(x, y) && matrix[x][y] != OBST)
        to_return = get_index(x, y);
    return to_return;
}


int update_matrix_with_ind(int matrix[map_size_rows][map_size_cols], int point_index, int new_value) {
    int x = get_x(point_index); int y = get_y(point_index);
    //check if position exist
    if(x >= 0 && x <= map_size_rows && y >= 0 && y <= map_size_cols) {
        matrix[x][y] = new_value;
    } else {
        pr_s("Can't update, position doesn't exist");
        pr(x); pr_s(","); pr(y); ln();
    }
    return matrix[x][y];
}


void show_variant_to_go(int store_indexes[5], int checked_values[5]) {
//    show_matrix_ind(ind);
    ln();
    int ind_up = 2; int ind_l = 0; int ind_r = 3; int ind_d = 1; int ind_center = 4;
    //for testing - show up left right down variants
    if(test) {
        int value_show = 3;
        for(int i = 0; i < value_show; i++){
            for(int j = 0; j < value_show; j++){
                int to_print = 0;
                int to_print_index = -1;
                if(i == 0 && j == 1) {
                    to_print = checked_values[ind_up]; //up
                    to_print_index = store_indexes[ind_up];
                }
                if(i == 1 && j == 0) {
                    to_print = checked_values[ind_l]; //l
                    to_print_index = store_indexes[ind_l];
                }
                if(i == 1 && j == 1) {
                    to_print =  checked_values[ind_center];
                    to_print_index = store_indexes[ind_center];
                }
                if(i == 1 && j == 2) {
                    to_print = checked_values[ind_r]; //r
                    to_print_index = store_indexes[ind_r];
                }
                if(i == 2 && j == 1) {
                    to_print = checked_values[ind_d]; //d
                    to_print_index = store_indexes[ind_d]; //d
                }
                if(to_print) {
                    pr(to_print);
//                    pr_s("   ");
                    pr_s("[");  pr(to_print_index); pr_s("] ");
                } else {
                    pr_s("   "); pr_s(" "); pr_s("--"); pr_s("  ");
                }
            } ln();
        }
    }ln();
}

int get_possible_indexes(int possible_indexes[D], int matrix[map_size_rows][map_size_cols], int point_index) {
    int not_checked_value = -4;
    int size_v = D + 1;
    static int checked_values[5]; //5 = D+1 to stor center point
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
    if(test) {
        ln();
        for(int i = 0; i < D; i++){
            pr(checked_values[i]); pr_s(" ");
        }  pr_s(" Point_checked_values \n");
        for(int i = 0; i < D; i++){
            pr(store_indexes[i]);  pr_s(" ");
        } pr_s(" : [Indexes]\n ");
    }

    if(test) pr_s("possible variant(s):\n");
    int to_return = -5;
    int minimum_value_index = -1;
    int minimum_value = 100;
    for(int i = 0; i < D; i++) {
        possible_indexes[i] = -1;
        if(checked_values[i] != OBST){
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

int get_possible_indexes_path(int matrix[map_size_rows][map_size_cols], int point_index) {
    int not_checked_value = -4;
    int size_v = D + 1;
    static int checked_values[5]; //5 = D+1 to stor center point
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
    if(test) {
        ln();
        for(int i = 0; i < D; i++){
            pr(checked_values[i]); pr_s(" ");
        }  pr_s(" Point_checked_values \n");
        for(int i = 0; i < D; i++){
            pr(store_indexes[i]);  pr_s(" ");
        } pr_s(" : [Indexes]\n ");
    }

    if(test) pr_s("possible variant(s):\n");
    int to_return = -5;
    int minimum_value_index = -1;
    int minimum_value = 100;
    for(int i = 0; i < D; i++) {
        int next_point = get_v_by_index(matrix, point_index) - 1;
        if(checked_values[i] > 0 && store_indexes[i] >= 0 && checked_values[i] <= next_point  && checked_values[i] != OBST){

            int test_ind = store_indexes[i];
            int test_x = get_x(test_ind);
            int test_y = get_y(test_ind);

            if(checked_values[i] > 0 ) {
                if(checked_values[i] < minimum_value) {
                    minimum_value = checked_values[i];
                    minimum_value_index = store_indexes[i];
                }
            }

            if(test) {
                pr(checked_values[i]); pr_s("["); pr(store_indexes[i]);  pr_s("] =");  //pr(i);
                pr(ind[test_x][test_y]);  pr_s("["); pr(test_x); pr_s(","); pr(test_y); pr_s("]");
                pr_s(",\n");
            }
        }
        to_return = minimum_value_index;
    }

    return to_return;
}

void clean_path(void){
  for(int i = 0; i < map_size_rows; i++){
        for(int j = 0; j < map_size_cols; j++){
            path[i][j] = 0;

        }
    }
}

void revert_matrix(int matrix[map_size_rows][map_size_cols]) {
    pr_s("revert matrix"); ln();
//    if(beautiful_output) {
//        pr_s(".. ");
//        for(int i = map_size_rows - 1; i >= 0; i--)
//            pr(i);
//        ln();
//    }
    for(int i = 0; i < map_size_rows; i++){
          for(int j = i; j < map_size_cols; j++){
            int tmp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = tmp;
        }
//        ln();
    } //ln();
}

void show_massiv(int matrix[D]) { //show possible variants
    for(int i = 0; i < D; i++){
        pr(matrix[i]); pr_s(" ");
    }
}

void setup_func(void) {
//    ind[start_x][start_y] = start; //set up goal?
    insert_obstcls(ind, OBST);
}

void calc_matrix_wave_func_2(void)  {
    setup_func();
    //open  list store all nodes where to go
    //wave - from 1.2.3 to last maximum, where last maximum is goal
    open_list[wave][wave_index] = 1; //1-open, 0 - closed/visited
    // update_matrix_with_ind(ind, start_index, wave);
    ind[start_x][start_y] = wave;
    start_index =  get_index(start_x, start_y);
    //show all possible variants for each point
    //show possible variants from this point
    int possible_indexes[D];
    get_possible_indexes(possible_indexes, ind, start_index); //where to go
    if(test) {pr_s("pos ind var:"); show_massiv(possible_indexes);}

    for(int i = 0; i < D; i++) {
        if(possible_indexes[i] > 0) {
            open_list[wave + 1][wave_index++] = possible_indexes[i]; //add index to open_list
            update_matrix_with_ind(ind, possible_indexes[i], wave + 1);
        }
    }

    int exit_filling = 0;
    wave++; 
    int start_for_j = 0;
    //before we setup the start nodes in open list
    //now we will do it in a loop
    for(int i = wave; i < size_map; i++){
        if(test) {
            pr_s("FROM Wave = "); pr(wave-1); pr_s(" for wave = "); pr(wave); pr_s(" open list ind: "); //    show open list
        }
        int last_posible_index_position_in_open_list = wave_index;

//        for(int j = start_for_j; j < last_posible_index_position_in_open_list; j++) {
//            if(open_list[i][j] > 0) pr(open_list[i][j]); //recurcia? //show open list
//        }

        for(int j = start_for_j; j < last_posible_index_position_in_open_list; j++) {
            //add index to open_list
            if(test) ln();
            if(test) {if(open_list[i][j] > 0) {pr(open_list[i][j]); pr_s(":");}} //recurcia? //show open list
            if(open_list[i][j] == goal_index) {
                exit_filling = 1;
                break;
            }
            get_possible_indexes(possible_indexes, ind, open_list[i][j]);
            if(test) {pr_s(" pos ind var:"); show_massiv(possible_indexes);}
            for(int l = 0; l < D; l++) {
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
    if(test_main_path) {
      pr_s(" FROM {|x = "); pr(point_down);
      pr_s(",  -y ="); pr(point_right);
      pr_s("}");  ln();
    }
    int index_tmp = goal_index; //get_index(point_down, point_right);
    //search for path from goal to start
    
    //get next node where to go
    int returned_index = get_possible_indexes_path(ind, index_tmp); //return one index to go
    
    int next_x = get_x(returned_index);
    int next_y = get_y(returned_index);

    if(test_main_path) {
        pr_s("point "); pr(ind[point_down][point_right]);
    }
    if(test_main_path) {
        pr_s(" next |x:"); pr(next_x); pr_s(", -y:");pr(next_y);
    }

    int value = ind[next_x][next_y];
    if(test_main_path) {
        pr_s(" "); pr(value); pr_s("["); pr(returned_index);  pr_s("] !="); pr(start); ln();
    }
    int path_found = 1;
    int exit_path_not_found = map_size_rows * map_size_cols + 1;

    while(1){
        int ind_tmp = get_index(next_x, next_y);
        //if we reach start x y - we found path, exit from while
        if (next_x == start_x && next_y == start_y) break;

        //get new position
        point_down = next_x; point_right = next_y;
        //encoding path
        update_matrix_with(path, point_down, point_right, filling_path_with); 

        if(test) show_matrix(path);
        if(test_main) {
          pr_s("poit__down  = "); pr(point_down);
          pr_s(", point__right ="); pr(point_right); ln();
        }
        int index_tmp = get_index(point_down, point_right);
         //return one index to go
        returned_index = get_possible_indexes_path(ind, index_tmp);
         next_x = get_x(returned_index);
         next_y = get_y(returned_index);
        if(test_main_path) {
          pr_s(" point ");   pr(ind[point_down][point_right]);
        }
        if(test_main_path) {
            pr_s(" next x:");  pr(next_x);
          pr_s(", next y:"); pr(next_y);
        }
        value = ind[next_x][next_y]; //print value for testing
        if(test_main_path) {
          pr_s(" "); pr(value);
          pr_s("["); pr(returned_index); pr_s("] !=");
          pr(start);
          ln();
        }
        
        exit_path_not_found--;
        if(exit_path_not_found == 0) {
            path_found = 0; //path not found
            break;
        }
//        if (next_y == start_y && next_x == start_x) break;
    }
    update_matrix_with(path, start_x, start_y, start);
    update_matrix_with(path, goal_x, goal_y, goal_target); //for -1

    if(path_found) {
        //final encoding
        replace_all(path, 1, 2);
        replace_all(path, 0, 1);
        replace_all(path, 2, 0); //path 0
        pr_s("Path found\n");
//        show_matrix(ind);
    } else {
        //TODO: path not found what todo? go around??)) dance
        //go back? to history of steps
        pr_s("Path NOT found\n"); ln();
    }
    calc_matrix_wave = 0;
}

//keep for C testing
//int main() {
//    calc_matrix_wave_func_2(); //first calc matrix
//    ln(); pr_s("SHOW IND"); ln();
//    show_matrix_ind(ind);
////    show_matrix(ind);
//
//    path_finding();
//    show_matrix(path);
//}

void loop() {
    pr_s("HELLO");
    
    if(calc_matrix_wave) {
        pr_s("calc_matrix_wave inside = "); pr(calc_matrix_wave); ln();
      calc_matrix_wave_func_2();
      ln(); pr_s("SHOW IND"); ln();
      show_matrix_ind(ind);
//      show_matrix(ind);

      path_finding(); //update/return path
      show_matrix(path);
  }

  if (calcDistance() < 35) {
      pr_s("calcDistance() < 35"); ln();
      calc_matrix_wave = 1; // we can recalc path
      stopRobot();
      clean_path();
      setObstecal();

      //save current position which will be next position for start
      start_y = j;
      start_x = i;

      pr_s("We stopped at ");
      //ind[i][j];
      // path[i][j];
      pr_s("x =");pr(start_x);
      pr_s("y =");pr(start_y); ln();

      calc_matrix_wave_func_2();
      ln(); pr_s("SHOW new IND"); ln();
      show_matrix_ind(ind);
//      show_matrix(ind);

      path_finding(); //update/return path
      show_matrix(path);
      
      //start going from last position
      j = start_y;
      i = start_x;

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
  }
  else {
      pr_s("ELSE calc_matrix_wave inside = "); pr(calc_matrix_wave);ln();
      if (frontOpen() == 0 || frontOpen() == -1) {
           pr_s("FWD position: ");
          pr_s("x: ");pr(getRobotX());
          pr_s("y: ");pr(getRobotY());ln();

          forward();

      }
      else if (rightOpen() == true) {
           pr_s("RIGHT position: ");
          pr_s("x: ");pr(getRobotX());
          pr_s("y: ");pr(getRobotY());ln();
          right();
      }
      else if (leftOpen() == true) {
          pr_s("LEFT position: ");
          pr_s("x: ");pr(getRobotX());
          pr_s("y: ");pr(getRobotY());ln();
          left();
      }
      else {
          turn180();
      }
  }
 }
