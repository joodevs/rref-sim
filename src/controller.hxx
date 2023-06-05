#pragma once

#include "model.hxx"
#include "view.hxx"
#include <vector>
#include <variant>
#include "string"

#include <ge211.hxx>

class Controller : public ge211::Abstract_game
{
public:
    Controller();

    //Controller(int num_rows, int num_cols);

    void draw(ge211::Sprite_set& set) override;

    int get_controller_count ();

protected:
    Dimensions initial_window_dimensions () const override;

private:
    string on_key_helper(ge211::Key);
    void on_key_down(ge211::Key) override;

    Model model_;
    View view_;
    int controller_count_=1;
    std::vector<string> controller_vector;

};
