#include "model.hxx"

Model::Model(int num_rows, int num_cols)
        : num_rows_ (num_rows),
          num_cols_ (num_cols)
{
    for (int i=0; i< num_cols_; i++) {
        for (int j=0; j<num_rows_; j++) {
            board_map_[{i, j}] = 0.0;
            // initialize all values in matrix entries to zero
        }
    }
}


void Model::advance_curr()
{
    if (curr_pos_.x +1 >= num_cols_) {
        curr_pos_.y++;
        curr_pos_.x = 0;
    } else {
        curr_pos_.x ++;
    }

    curr_entry_++;
}


void Model::save_number(double num)
{
    board_map_[curr_pos_] = num;
}


void Model::save_number_next (double num)
{
    save_number(num);
    advance_curr();
}


Rectangle Model::all_positions ()
{
    Rectangle matrix_rec;
    matrix_rec.x=0;
    matrix_rec.y=0;
    matrix_rec.width = num_cols_;
    matrix_rec.height = num_rows_;

    return matrix_rec;
}


void Model::perform_gauss_elim ()
{
    Rectangle matrix_dim = all_positions();

    for (int pivot = 0; pivot < matrix_dim.width; pivot++) {

        int maxRow = pivot;
        for (int r = pivot+1; r < matrix_dim.height; r++) {
            if (abs(board_map_[Position{pivot, r}]) > abs(board_map_[Position{pivot, maxRow}])) {
                maxRow = r;
            }
        }

        if (pivot != maxRow) {
            for (int c = 0; c < matrix_dim.width; c++) {
                std::swap(board_map_[Position{c, pivot}], board_map_[Position{c, maxRow}]);
            }
        }

        if (board_map_[Position{pivot, pivot}] == 0) {
            continue;
        }

        double pivotValue = board_map_[Position{pivot, pivot}];
        for (int c = 0; c < matrix_dim.width; c++) {
            curr_pos_ = Position{c, pivot};
            save_number(board_map_[Position{c, pivot}] / pivotValue);
            advance_curr();
        }

        for (int r = pivot+1; r < matrix_dim.height; r++) {
            double factor = board_map_[Position{pivot, r}];
            for (int c = 0; c < matrix_dim.width; c++) {
                curr_pos_ = Position{c, r};
                save_number(board_map_[Position{c, r}] - factor * board_map_[Position{c, pivot}]);
                advance_curr();
            }
        }
    }
}



void Model::perform_rref ()
{
    Rectangle matrix_dim = all_positions();

    for (int pivot = 0; pivot < matrix_dim.width; pivot++) {

        int maxRow = pivot;
        for (int r = pivot+1; r < matrix_dim.height; r++) {
            if (abs(board_map_[Position{pivot, r}]) > abs(board_map_[Position{pivot, maxRow}])) {
                maxRow = r;
            }
        }

        if (pivot != maxRow) {
            for (int c = 0; c < matrix_dim.width; c++) {
                std::swap(board_map_[Position{c, pivot}], board_map_[Position{c, maxRow}]);
            }
        }

        if (board_map_[Position{pivot, pivot}] == 0) {
            continue;
        }

        double pivotValue = board_map_[Position{pivot, pivot}];
        for (int c = 0; c < matrix_dim.width; c++) {
            curr_pos_ = Position{c, pivot};
            save_number(board_map_[Position{c, pivot}] / pivotValue);
            advance_curr();
        }

        for (int r = 0; r < matrix_dim.height; r++) {
            if (r != pivot) {
                double factor = board_map_[Position{pivot, r}];
                for (int c = 0; c < matrix_dim.width; c++) {
                    curr_pos_ = Position{c, r};
                    save_number(board_map_[Position{c, r}] - factor * board_map_[Position{c, pivot}]);
                    advance_curr();
                }
            }
        }
    }
}

double Model::get_num_at_pos (Position pos)
{
    return board_map_[pos];
}

int Model::get_num_rows()
{
    return num_rows_;
}

int Model::get_num_cols()
{
    return num_cols_;
}

int Model::get_current_entry()
{
    return curr_entry_;
}

Position Model::get_curr_pos()
{
    return curr_pos_;
}

void Model::update_num_rows(int num_rows)
{
    num_rows_= num_rows;
}

void Model::update_num_cols(int num_cols)
{
    num_cols_= num_cols;
}

void Model::update_board_map()
{
    for (int i=0; i< num_cols_; i++) {
        for (int j=0; j<num_rows_; j++) {
            board_map_[Position {i,j}] = 0;
            // initialize all values in matrix entries to zero
        }
    }
}