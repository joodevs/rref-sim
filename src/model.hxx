#pragma once


#include <ge211.hxx>
#include <unordered_map>
using namespace std;
using namespace ge211;
using Position= Posn<int>;
using Rectangle= Rect<int>;
using Dimensions= Dims<int>;


class Model
{
    /// the number of rows
    int num_rows_;

    /// the number of columns
    int num_cols_;

    /// map containing all positions of the board (key) with respective numbers (value) at each position
    unordered_map <ge211::Posn<int>, double> board_map_;

    /// the current position the user is at while inputting numbers
    Position curr_pos_ = {0,0};

    /// the current entry number, starts from 1, ends at rows*columns +2
    int curr_entry_ = 1;

public:

    /// constructor, makes model given the number of rows and columns of the matrix
    Model (int num_rows, int num_cols);

    ///helper for save_number_next, advances the current position curr_pos_
    /// and current entry curr_entry_ to the next)
    void advance_curr ();

    ///helper for save_number_next and perform_gauss_elim, saves the number given
    /// at the current position curr_pos_ in the board_map_
    void save_number (double);

    ///saves number at current position curr_pos_ in board_map_ using save_number,
    /// calls advance_curr after saving
    void save_number_next (double);

    ///returns a rectangle which contains all positions of the board, used in Draw_XX functions in View
    Rectangle all_positions ();

    ///performs gaussian elimination on the rows in the matrix, uses all_positions, save_number
    void perform_gauss_elim ();

    ///changes the matrix to reduced row-echelon form, uses all_positions, save_number
    void perform_rref ();

    ///solves for the values of the variables in the matrix
    void solve();

    ///returns the number at the position in the board_map_
    double get_num_at_pos (Position pos);

    ///returns the number of rows
    int  get_num_rows ();

    ///returns the number of columns
    int get_num_cols ();

    ///returns the current entry number
    int get_current_entry ();

    ///returns the current position curr_pos_
    Position get_curr_pos();

    ///updates the number of rows to given input
    void update_num_rows (int);

    ///updates the number of columns to given input
    void update_num_cols (int);

    ///updates the board_map_ to the new rows and columns number
    void update_board_map ();

};


