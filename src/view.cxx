#include "view.hxx"
#include <iostream>
#include <string>

static Color const num_color {255, 0, 0};
static Color const rec_color {255, 255, 255};
static Color const line_color {0,255,0};

View::View(Model& model)
        : model_(model),
          entry_square_sprite_(Dimensions (grid_size -3, grid_size -3)),
          matrix_line_sprite_(Dimensions (1, grid_size))
{}
void View::draw_initial_questions (ge211::Sprite_set& set)
{
    draw_num_row_q_sprite(set);
    draw_num_col_q_sprite(set);
    draw_initial_q_num(set);
}

void View::draw_matrix (ge211::Sprite_set& set)
{
    draw_matrix_num_sprite(set);
    draw_entry_square_sprite(set);
    draw_matrix_line_sprite(set);

}

void View::draw_solve (ge211::Sprite_set& set)
{
    draw_variables_sprite(set);
    draw_entry_square_sprite(set);
    draw_matrix_line_sprite(set);
}

void View::draw_num_row_q_sprite (ge211::Sprite_set& set)
{
    set.add_sprite(row_q_sprite_, Position {0,0});
}

void View::draw_num_col_q_sprite(ge211::Sprite_set & set)
{
    set.add_sprite(col_q_sprite_,Position {0,36});
}

void View::draw_initial_q_num (ge211::Sprite_set& set)
{
    ge211::Text_sprite::Builder num_builder_r(sans28_);
    num_builder_r << model_.get_num_rows();
    row_num_sprite_.reconfigure(num_builder_r);
    set.add_sprite(row_num_sprite_, Position{250,0});

    ge211::Text_sprite::Builder num_builder_c(sans28_);
    num_builder_c << model_.get_num_cols();
    col_num_sprite_.reconfigure(num_builder_c);
    set.add_sprite(col_num_sprite_, Position{300,40});

}

void View::draw_matrix_num_sprite(ge211::Sprite_set& set)
{
    cells_text.clear();
    for (auto pos : model_.all_positions()) {
        cells_text[pos] = ge211::Text_sprite();
    }


    for (auto pos : model_.all_positions()) {
        ge211::Text_sprite::Builder num_builder(sans28_);
        num_builder.color(num_color);
        num_builder << model_.get_num_at_pos(pos);
        cells_text[pos].reconfigure(num_builder);
        set.add_sprite(cells_text[pos], Position {board_to_screen(pos).x +2, board_to_screen(pos).y +2 }, 1);
    }
}

void View::draw_entry_square_sprite (ge211::Sprite_set& set)
{
    for (auto pos : model_.all_positions()) {
        set.add_sprite(entry_square_sprite_, board_to_screen(pos));
    }
}

void View::draw_matrix_line_sprite (ge211::Sprite_set& set)
{
    Position square_at_line_pos = board_to_screen(Position {model_.get_num_cols() -1, 0});
    set.add_sprite (matrix_line_sprite_, Position {square_at_line_pos.x -2, square_at_line_pos.y});
}

void View::draw_variables_sprite(ge211::Sprite_set &set)
{
    cells_text.clear();
    for (auto pos : model_.all_positions()) {
        if (model_.get_num_at_pos(pos) !=0 || pos.x ==model_.get_num_cols()-1) {
            cells_text[pos] = ge211::Text_sprite();
        }
    }
    // int i=1;
    // int j=1;
    //    bool is_first_1 = true;

    int col = 0;
    for (int row = 0; row < model_.get_num_rows(); row++) {
        if (model_.get_num_at_pos({col, row}) == 1 && col != model_.get_num_cols() - 1) {
            ge211::Text_sprite::Builder x_builder(sans28_);
            x_builder.color(num_color);
            string x = "x" + std::to_string(row + 1);
            x_builder << x;
            cells_text[{col, row}].reconfigure(x_builder);
            set.add_sprite(cells_text[{col, row}], Position {board_to_screen({col, row}).x +2, board_to_screen({col, row}).y +2 }, 1);
            col ++;
        }
        else if (col == model_.get_num_cols()-1) {
            ge211::Text_sprite::Builder num_builder(sans28_);
            num_builder.color(num_color);
            num_builder << model_.get_num_at_pos({col, row});
            cells_text[{col, row}].reconfigure(num_builder);
            set.add_sprite(cells_text[{col, row}], Position {board_to_screen({col, row}).x +2, board_to_screen({col, row}).y +2 }, 1);
            //            is_first_1 = true;
        }
        else {
            ge211::Text_sprite::Builder s_builder(sans28_);
            s_builder.color(num_color);
            string s = "s" + std::to_string(col + 1);
            s_builder << s;
            cells_text[{col, row}].reconfigure(s_builder);
            set.add_sprite(cells_text[{col, row}], Position {board_to_screen({col, row}).x +2, board_to_screen({col, row}).y +2 }, 1);
            col++;
            row--;
        }
    }

    for (int row = 0; row < model_.get_num_rows(); row++) {
        ge211::Text_sprite::Builder num_builder(sans28_);
        num_builder.color(num_color);
        num_builder << model_.get_num_at_pos({col, row});
        cells_text[{model_.get_num_cols() - 1, row}].reconfigure(num_builder);
        set.add_sprite(cells_text[{model_.get_num_cols() - 1, row}], Position {board_to_screen({model_.get_num_cols() - 1, row}).x +2, board_to_screen({model_.get_num_cols() - 1, row}).y +2 }, 1);
    }


    //    for (auto pair : cells_text) {
    //        if (model_.get_num_at_pos(pair.first)==1 && is_first_1 && pair.first.x!=model_.get_num_cols()-1) {
    //            ge211::Text_sprite::Builder x_builder(sans28_);
    //            x_builder.color(num_color);
    //            string x = "x" + std::to_string(i);
    //            x_builder << x;
    //            cells_text[pair.first].reconfigure(x_builder);
    //            set.add_sprite(cells_text[pair.first], Position {board_to_screen(pair.first).x +2, board_to_screen(pair.first).y +2 }, 1);
    //            is_first_1 = false;
    //            i++;
    //        }
    //        else if (pair.first.x ==model_.get_num_cols()-1) {
    //            ge211::Text_sprite::Builder num_builder(sans28_);
    //            num_builder.color(num_color);
    //            num_builder << model_.get_num_at_pos(pair.first);
    //            cells_text[pair.first].reconfigure(num_builder);
    //            set.add_sprite(cells_text[pair.first], Position {board_to_screen(pair.first).x +2, board_to_screen(pair.first).y +2 }, 1);
    //            is_first_1 = true;
    //        }
    //        else {
    //            ge211::Text_sprite::Builder s_builder(sans28_);
    //            s_builder.color(num_color);
    //            string s = "s" + std::to_string(j);
    //            s_builder << s;
    //            cells_text[pair.first].reconfigure(s_builder);
    //            set.add_sprite(cells_text[pair.first], Position {board_to_screen(pair.first).x +2, board_to_screen(pair.first).y +2 }, 1);
    //            j++;
    //        }
    //    }
}

void View::update_matrix_line()
{
    matrix_line_sprite_= Rectangle_sprite(Dimensions (1, grid_size * model_.get_num_rows()), line_color);
}

Dimensions View::initial_window_dimensions()
{
    return grid_size * Dimensions (4, 4);
}

Dimensions View::matrix_window_dimensions()
{
    return grid_size * model_.all_positions().dimensions();
}

Position View::board_to_screen(Position board_pos)
{
    return Position {board_pos.x * grid_size, board_pos.y * grid_size};
}

Position View::screen_to_board (Position screen_pos)
{
    return Position {screen_pos.x/grid_size, screen_pos.y/grid_size};
}