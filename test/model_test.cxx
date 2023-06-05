#include "model.hxx"
#include <catch.hxx>

TEST_CASE("Model::test_perform_gauss_elim")
{
    Model model(3, 4);

    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(7);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(2);
    model.save_number_next(3);
    model.save_number_next(2);
    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(9);

    // Perform Gaussian elimination
    model.perform_gauss_elim();

    // Check that the matrix is now in row-echelon form
    // 1  3  1
    // 0 -2 -2
    // 0  0  0

    CHECK(model.get_num_at_pos(Position{0, 0}) == 1);
    CHECK(model.get_num_at_pos(Position{1, 0}) == 0.5);
    CHECK(model.get_num_at_pos(Position{2, 0}) == 0.5);
    CHECK(model.get_num_at_pos(Position{3, 0}) == 4.5);
    CHECK(model.get_num_at_pos(Position{0, 1}) == -0);
    CHECK(model.get_num_at_pos(Position{1, 1}) == 1);
    CHECK(model.get_num_at_pos(Position{2, 1}) == -1);
    CHECK(model.get_num_at_pos(Position{3, 1}) == 1);
    CHECK(model.get_num_at_pos(Position{0, 2}) == -0);
    CHECK(model.get_num_at_pos(Position{1, 2}) == -0);
    CHECK(model.get_num_at_pos(Position{2, 2}) == 1);
    CHECK(model.get_num_at_pos(Position{3, 2}) == -2);
}

TEST_CASE("Model::test_perform_gauss_elim_then_rref")
{
    Model model(3, 4);

    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(7);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(2);
    model.save_number_next(3);
    model.save_number_next(2);
    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(9);

    // Perform Gaussian elimination
    model.perform_gauss_elim();
    model.perform_rref();

    CHECK(model.get_num_at_pos({0, 0}) == 1);
    CHECK(model.get_num_at_pos({1, 0}) == 0);
    CHECK(model.get_num_at_pos({2, 0}) == 0);
    CHECK(model.get_num_at_pos({3, 0}) == 6);
    CHECK(model.get_num_at_pos({0, 1}) == 0);
    CHECK(model.get_num_at_pos({1, 1}) == 1);
    CHECK(model.get_num_at_pos({2, 1}) == 0);
    CHECK(model.get_num_at_pos({3, 1}) == -1);
    CHECK(model.get_num_at_pos({0, 2}) == 0);
    CHECK(model.get_num_at_pos({1, 2}) == 0);
    CHECK(model.get_num_at_pos({2, 2}) == 1);
    CHECK(model.get_num_at_pos({3, 2}) == -2);
}
TEST_CASE("test_perform_rref_alone")
{
    Model model(3, 4);

    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(7);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(2);
    model.save_number_next(3);
    model.save_number_next(2);
    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(9);

    model.perform_rref();

    CHECK(model.get_num_at_pos({0, 0}) == 1);
    CHECK(model.get_num_at_pos({1, 0}) == 0);
    CHECK(model.get_num_at_pos({2, 0}) == 0);
    CHECK(model.get_num_at_pos({3, 0}) == 6);
    CHECK(model.get_num_at_pos({0, 1}) == 0);
    CHECK(model.get_num_at_pos({1, 1}) == 1);
    CHECK(model.get_num_at_pos({2, 1}) == 0);
    CHECK(model.get_num_at_pos({3, 1}) == -1);
    CHECK(model.get_num_at_pos({0, 2}) == 0);
    CHECK(model.get_num_at_pos({1, 2}) == 0);
    CHECK(model.get_num_at_pos({2, 2}) == 1);
    CHECK(model.get_num_at_pos({3, 2}) == -2);
}
TEST_CASE("test_update number of rows and columns")
{
    Model model(3, 4);
    CHECK(model.get_num_cols()==4);
    CHECK(model.get_num_rows()==3);
    model.update_num_cols(5);
    model.update_num_rows(6);
    CHECK(model.get_num_cols()==5);
    CHECK(model.get_num_rows()==6);

}

TEST_CASE("test_curr_pos")
{
    Model model(3, 4);

    model.save_number_next(1);
    model.save_number_next(1);
    model.save_number_next(-1);
    model.save_number_next(7);
    model.save_number_next(1);
    model.save_number_next(-1);

    CHECK(model.get_curr_pos().x == 2);
    CHECK(model.get_curr_pos().y == 1);

}