#include <stdio.h>
#define D 4 //dimention
#define OBST 99
#define beautiful_output 1 //beautiful output
//
//Test 1 normal 8 8
#define map_size_rows 8
#define map_size_cols 8

#define size_map 64
int open_list[size_map][map_size_cols];
int wave = 1;
int wave_index = 0;


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

//Test 2 normal 4
//#define map_size_rows 4
//#define map_size_cols 4
////
//int ind[map_size_rows][map_size_cols] = {
//    {-1, -1, -1, -1},
//    {-1, -1, -1, -1},
//    {-1, -1, -1, -1},
//    {-1, -1,  -1, -1}
//};
//
//int path[map_size_rows][map_size_cols] = {
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0}
//};

//test 3
//#define map_size_rows 5
//#define map_size_cols 4
////
//
//int ind[map_size_rows][map_size_cols] = {
//    {-1, -1, -1, -1},
//    {-1, -1, -1, -1},
//    {-1, -1, -1, -1},
//    {-1, -1, -1, -1},
//    {-1, -1, -1, -1}
//};
//
//int path[map_size_rows][map_size_cols] = {
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0},
//    {0, 0, 0, 0}
//};

//this is to see data during testing process
int test = 0;

int start = 1; //start point
int start_x = 0; //vertical
int start_y = 0; //horisontal
int start_index = 0;

int goal_target = -1; //TODO: FINALLY REWRITE FOR PATH
int goal_x = map_size_rows - 1;
int goal_y = map_size_cols - 1;
int goal_index = 63;


int path_max_value = 0;
int calc_matrix_wave = 1; //bool

// CHANGE output for arduino
void pr(int value) {
    printf("%2d",value);
//   Serial.print(" ");
//   Serial.print(value);
}

void pr_s(char value[]) {
    printf(value);
//   Serial.print(" ");
//   Serial.print(value);
}

void ln(void) {
    printf("\n");
//    Serial.println();
}

int update_matrix_with(int matrix[map_size_rows][map_size_cols], int x, int y, int new_value) {
    //check if position exist
    if(x >= 0 && x <= map_size_rows && y >= 0 && y <= map_size_cols) {
        matrix[x][y] = new_value;
    } else {
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

void insert_obstcls(int ind[map_size_rows][map_size_cols], int obst){
    //without test no obstcls
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

void show_matrix(int matrix[map_size_rows][map_size_cols]) {
    if(beautiful_output) ind_first_line();
    for(int i = 0; i < map_size_rows; i++){
        if(beautiful_output) pr(i);
        for(int j = 0; j < map_size_cols; j++){
            pr(matrix[i][j]);
            pr_s(" ");
        } ln();
    } ln();
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

void show_matrix_revert(int matrix[map_size_rows][map_size_cols]) {
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

void show_variant_to_go(int store_indexes[5], int checked_values[5]) {
    int ind_up = 2; int ind_l = 0; int ind_r = 3; int ind_d = 1; int ind_center = 4;

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
            }
        }
    }
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
   
    int to_return = -5;
    int minimum_value_index = -1;
    int minimum_value = 100;
    for(int i = 0; i < D; i++) {
        int next_point = get_v_by_index(matrix, point_index) - 1;
        if(checked_values[i] > 0 && store_indexes[i] >= 0 && checked_values[i] <= next_point  && checked_values[i] != OBST){
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
  for(int i = 0; i < map_size_rows; i++){
        for(int j = 0; j < map_size_cols; j++){
            path[i][j] = 0;
        }
    }
}

void setup_func(void) {
    ind[start_x][start_y] = start;
    insert_obstcls(ind, OBST);
}

void calc_matrix_wave_func_2(void)  {
    setup_func();
    
    open_list[wave][wave_index] = 1; //1-open, 0 - closed/visited
    update_matrix_with_ind(ind, start_index, wave);
    
    //possible variants
    int possible_indexes[D];
    get_possible_indexes(possible_indexes, ind, start_index);
    
    for(int i = 0; i < D; i++) {
        if(possible_indexes[i] > 0) {
            open_list[wave + 1][wave_index++] = possible_indexes[i]; //add index to open_list
            update_matrix_with_ind(ind, possible_indexes[i], wave + 1);
        }
    }
    
    int exit_filling = 0;
    wave++;
    int start_for_j = 0;

    for(int i = wave; i < size_map; i++){
        int last_posible_index_position_in_open_list = wave_index;
        for(int j = start_for_j; j < last_posible_index_position_in_open_list; j++) {
            //add index to open_list
            if(open_list[i][j] == goal_index) {
                exit_filling = 1;
                break;
            }
            get_possible_indexes(possible_indexes, ind, open_list[i][j]);
          
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
    int index_tmp = goal_index; //get_index(point_down, point_right);
    int returned_index = get_possible_indexes_path(ind, index_tmp); //return one index to go
    int next_x = get_x(returned_index);
    int next_y = get_y(returned_index);

    int value = ind[next_x][next_y];
    
    int path_found = 1;
    int exit_path_not_found = map_size_rows * map_size_cols + 1;
    
    while(1){
        int ind_tmp = get_index(next_x, next_y);
        if (ind_tmp == start_index) break;
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
        //action
        pr_s("Path NOT found\n"); ln();
    }
    calc_matrix_wave = 0;
}

int main() {
    calc_matrix_wave_func_2();
    ln(); pr_s("SHOW IND"); ln();
    show_matrix(ind);
    
    path_finding();
    show_matrix(path);
    
}
