#include "controller.hxx"

Controller::Controller()
        : model_ (0,0),
          view_(model_)
{}
/*
Controller::Controller(int num_rows, int num_cols)
        : model_(num_rows, num_cols),
          view_(model_)
{}*/

void Controller::on_key_down(ge211::Key key)
{
    if (controller_count_ ==1){
        if (key!= Key::code(' ')) {
            controller_vector.push_back(on_key_helper(key));
            return;
        }
        else{
            int num =0;
            for (unsigned int i=0; i<controller_vector.size(); i++){
                int num_help = stof (controller_vector[i]);
                for (unsigned int j=0; j<controller_vector.size()-i-1; j++){
                    num_help *= 10;
                }
                num += num_help;
            }
            controller_vector.clear();
            controller_count_++;
            model_.update_num_rows(num);
            view_.update_matrix_line();
            return;
        }
    }
    else if (controller_count_ ==2) {
        if (key!= Key::code(' ')) {
            controller_vector.push_back(on_key_helper(key));
            return;
        }
        else{
            int num =0;
            for (unsigned int i=0; i<controller_vector.size(); i++){
                int num_help = stof (controller_vector[i]);
                for (unsigned int j=0; j<controller_vector.size()-i-1; j++){
                    num_help *= 10;
                }
                num += num_help;
            }
            controller_vector.clear();
            controller_count_++;
            model_.update_num_cols(num);
            model_.update_board_map();
            return;
        }
    }
    else {
        if (key == ge211::Key::code('g')) {
            if (controller_count_ > model_.get_num_rows() * model_.get_num_cols()  +2) {
                model_.perform_gauss_elim();
                return;
            }else {
                return;
            }
        }else if (key == ge211::Key::code('r')) {
            if (controller_count_ > model_.get_num_rows() * model_.get_num_cols()  +2) {
                model_.perform_rref();
                return;
            }else {
                return;
            }
        }else if (key == ge211::Key::code('s')) {
            if (controller_count_ > model_.get_num_rows() * model_.get_num_cols() + 2) {
                //the function that does the solving for the variables
                controller_count_++;
                return;
            }
        }else {
            if (controller_count_ == model_.get_num_rows() * model_.get_num_cols() + 3) {
                return;
            }
            else {
                if (key != Key::code(' ') && key != Key::code('\r')) {
                    controller_vector.push_back(on_key_helper(key));
                    return;
                } else {
                    if (key == Key::code('\r') && model_.get_curr_pos().x < model_.get_num_cols() - 1) {
                        throw Client_logic_error("Controller: can't hit enter before last column");
                    }
                    int num = 0;
                    if (controller_vector[0] == "-") {
                        for (unsigned int i = 1; i < controller_vector.size(); i++) {
                            int num_help = stof(controller_vector[i]);
                            for (unsigned int j = 1; j < controller_vector.size() - i; j++) {
                                num_help *= 10;
                            }
                            num += num_help;
                        }
                        num *= -1;
                    } else {
                        for (unsigned int i = 0; i < controller_vector.size(); i++) {
                            int num_help = stof(controller_vector[i]);
                            for (unsigned int j = 1; j < controller_vector.size() - i; j++) {
                                num_help *= 10;
                            }
                            num += num_help;
                        }
                    }
                    controller_vector.clear();
                    controller_count_++;
                    model_.save_number_next(num);
                    return;
                }
                //                else {
                //                    throw Client_logic_error("Controller: can't hit enter before last column");
                //                }
            }
        }
    }
}

string Controller::on_key_helper (Key key)
{
    if (key == ge211::Key::code('0')) {
        return "0";
    }
    else if (key == ge211::Key::code('1')) {
        return "1";
    }
    else if (key == ge211::Key::code('2')) {
        return "2";
    }
    else if (key == ge211::Key::code('3')) {
        return "3";
    }
    else if (key == ge211::Key::code('4')) {
        return "4";
    }
    else if (key == ge211::Key::code('5')) {
        return "5";
    }
    else if (key == ge211::Key::code('6')) {
        return "6";
    }
    else if (key == ge211::Key::code('7')) {
        return "7";
    }
    else if (key == ge211::Key::code('8')) {
        return "8";
    }
    else if (key == ge211::Key::code('9')) {
        return "9";
    }
    else if (key == ge211::Key::code('-')) {
        return "-";
    }
    else {
        return "0";
    }
}
void
Controller::draw(ge211::Sprite_set& set)
{
    if (controller_count_<=2) {
        view_.draw_initial_questions(set);
    }
    else if (controller_count_<= model_.get_num_rows()*model_.get_num_cols()+3 && controller_count_>2) {
        view_.draw_matrix(set);
    }
    else {
        view_.draw_solve(set);
    }

}

int Controller::get_controller_count()
{
    return controller_count_;
}

Dimensions Controller::initial_window_dimensions() const {
    return {1000, 1000};
}