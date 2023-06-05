#pragma once

#include "model.hxx"
#include <unordered_map>

class View
{
public:
    explicit View(Model& model);

    ///draws the rows and columns question in the first window
    void draw_initial_questions (ge211::Sprite_set&);

    /// draws the matrix in the second window
    void draw_matrix (ge211::Sprite_set& set);

    /// draws the matrix for the variables in the third window
    void draw_solve (ge211::Sprite_set& set);

    /// multiplies the position by adequate number to expand to screen-viewing size
    Position board_to_screen (Position board_pos);

    /// divides the position by adequate number to reduce to board size
    Position screen_to_board (Position screen_pos);

    ///draws “Number of Rows: ” on initial window
    void draw_num_row_q_sprite(ge211::Sprite_set&);

    ///draws “Number of Columns: ” on initial window
    void draw_num_col_q_sprite(ge211::Sprite_set&);

    ///draws the numbers for the rows/columns numbers
    void draw_initial_q_num (ge211::Sprite_set&);

    ///if inputted number == #, draw # sprite at adequate position
    void draw_matrix_num_sprite (ge211::Sprite_set&);

    ///updates matrix_line to the correct height
    void update_matrix_line ();

    ///helper for draw_empty_matrix_sprite, draws the squares for each entry
    void draw_entry_square_sprite (ge211::Sprite_set& set);

    ///helper for draw_empty_matrix_sprite, draws the line of the matrix)
    void draw_matrix_line_sprite  (ge211::Sprite_set& set);

    ///helper for draw_solve, draws the variables needed
    void draw_variables_sprite (ge211::Sprite_set& set);

    ///dimensions for the first window that displays rows and columns questions
    Dimensions initial_window_dimensions ();

    ///dimensions for the second window displaying the matrix
    Dimensions matrix_window_dimensions ();

    int const grid_size = 150;

private:
    Model& model_;
    // changed Model const& to Model, revisit if problems arise
    ge211::Font sans28_{"sans.ttf", 28};
    ge211::Text_sprite num_sprite_ {"0", sans28_};
    ge211::Text_sprite row_q_sprite_ {"Number of Rows: ", sans28_};
    ge211::Text_sprite col_q_sprite_ {"Number of Columns: ", sans28_};
    ge211::Text_sprite row_num_sprite_ {"0", sans28_};
    ge211::Text_sprite col_num_sprite_ {"0", sans28_};
    ge211::Rectangle_sprite entry_square_sprite_;
    ge211::Rectangle_sprite matrix_line_sprite_;

    unordered_map<ge211::Posn<int>, ge211::Text_sprite> cells_text;
};
