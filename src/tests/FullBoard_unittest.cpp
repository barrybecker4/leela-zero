/*
    This file is part of Leela Zero.
    Copyright (C) 2018 Gian-Carlo Pascutto

    Leela Zero is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Leela Zero is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Leela Zero.  If not, see <http://www.gnu.org/licenses/>.
*/

#undef NDEBUG
#include <cassert>
#include <cstddef>
#include <gtest/gtest.h>

#include "FullBoard.h" 

FullBoard create_full_3x3() {
    FullBoard b;
    b.reset_board(3);
    b.update_board(FastBoard::BLACK, b.get_vertex(1, 1));
    b.update_board(FastBoard::BLACK, b.get_vertex(2, 1));
    b.update_board(FastBoard::WHITE, b.get_vertex(0, 1));
    b.update_board(FastBoard::WHITE, b.get_vertex(1, 0));
    b.update_board(FastBoard::BLACK, b.get_vertex(2, 2));
    return b;
  }

FullBoard create_full_5x5() {
    FullBoard b;
    b.reset_board(5);
    b.update_board(FastBoard::BLACK, b.get_vertex(1, 1));
    b.update_board(FastBoard::BLACK, b.get_vertex(2, 1));
    b.update_board(FastBoard::WHITE, b.get_vertex(3, 1));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 2));
    b.update_board(FastBoard::BLACK, b.get_vertex(3, 2));
    b.update_board(FastBoard::BLACK, b.get_vertex(0, 3));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 3));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 4));
    return b;
}

FullBoard create_full_9x9() {
    FullBoard b;
    b.reset_board(9);
    b.update_board(FastBoard::WHITE, b.get_vertex(5, 4));
    b.update_board(FastBoard::BLACK, b.get_vertex(5, 3));
    b.update_board(FastBoard::WHITE, b.get_vertex(4, 5));
    b.update_board(FastBoard::BLACK, b.get_vertex(2, 2));
    b.update_board(FastBoard::WHITE, b.get_vertex(4, 3));
    b.update_board(FastBoard::BLACK, b.get_vertex(1, 2));
    b.update_board(FastBoard::WHITE, b.get_vertex(6, 3));
    b.update_board(FastBoard::BLACK, b.get_vertex(2, 3));
    b.update_board(FastBoard::WHITE, b.get_vertex(5, 2));
    b.update_board(FastBoard::BLACK, b.get_vertex(0, 0));
    b.update_board(FastBoard::WHITE, b.get_vertex(6, 6));
    return b;
}

/*
      a b c d e
    5 . . O O .  5
    4 . . O . O  4
    3 O O O O .  3
    2 . . O . .  2
    1 . . O . .  1
      a b c d e
*/
FullBoard create_5x5_all_white() {
    FullBoard b;
    b.reset_board(5);
    b.update_board(FastBoard::WHITE, b.get_vertex(1, 2));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 1));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 2));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 3));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 4));
    b.update_board(FastBoard::WHITE, b.get_vertex(3, 2));
    b.update_board(FastBoard::WHITE, b.get_vertex(3, 4));
    b.update_board(FastBoard::WHITE, b.get_vertex(4, 3));
    b.update_board(FastBoard::WHITE, b.get_vertex(0, 2));
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 0));
    return b;
}


TEST(FullBoardTest, Board3x3) {
    FullBoard b;
    b.reset_board(3);
    const char *expected = "\n"
        "   a b c \n"
        " 3 . . .  3\n"
        " 2 . . .  2\n"
        " 1 . . .  1\n"
        "   a b c \n\n";
    
    EXPECT_EQ(expected, b.serialize_board());
    EXPECT_EQ(3, b.get_boardsize());
}

TEST(FullBoardTest, SemiFilled5x5Board) {
    FullBoard b = create_full_5x5();
    
    const char *expected = "\n"
        "   a b c d e \n"
        " 5 . . O . .  5\n"
        " 4 X . O . .  4\n"
        " 3 . . O X .  3\n"
        " 2 . X X O .  2\n"
        " 1 . . . . .  1\n"
        "   a b c d e \n\n";
    
    EXPECT_EQ(expected,  b.serialize_board());
}

TEST(FullBoardTest, CountRealLibertiesOn5x5) {
    FullBoard b = create_full_5x5();
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(0, 0)));
    EXPECT_EQ(3, b.count_pliberties(b.get_vertex(1, 1)));
    EXPECT_EQ(1, b.count_pliberties(b.get_vertex(2, 1)));
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(3, 1)));
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(4, 1)));
    EXPECT_EQ(1, b.count_pliberties(b.get_vertex(2, 2)));
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(3, 2)));
    EXPECT_EQ(3, b.count_pliberties(b.get_vertex(0, 3)));
}

TEST(FullBoardTest, SemiFilled9x9Board) {
    FullBoard b = create_full_9x9();
    
    const char *expected = "\n"
        "   a b c d e f g h j \n"
        " 9 . . . . . . . . .  9\n"
        " 8 . . . . . . . . .  8\n"
        " 7 . . + . + . O . .  7\n"
        " 6 . . . . O . . . .  6\n"
        " 5 . . + . + O + . .  5\n"
        " 4 . . X . O . O . .  4\n"
        " 3 . X X . + O + . .  3\n"
        " 2 . . . . . . . . .  2\n"
        " 1 X . . . . . . . .  1\n"
        "   a b c d e f g h j \n\n";
    
    EXPECT_EQ(expected,  b.serialize_board());
}

TEST(FullBoardTest, CountRealLibertiesOn9x9) {
    FullBoard b = create_full_5x5();
    
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(0, 0)));
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(1, 2)));
    EXPECT_EQ(3, b.count_pliberties(b.get_vertex(4, 3)));
    EXPECT_EQ(2, b.count_pliberties(b.get_vertex(4, 4))); 
    EXPECT_EQ(0, b.count_pliberties(b.get_vertex(5, 4)));
}

TEST(FullBoardTest, IsSuicideWhenNotForBlack) {
    FullBoard b;
    b.reset_board(5);  
    b.update_board(FastBoard::WHITE, b.get_vertex(2, 2));
    EXPECT_EQ(false, b.is_suicide(b.get_vertex(1, 1), FastBoard::BLACK));
    EXPECT_EQ(false, b.is_suicide(b.get_vertex(2, 1), FastBoard::BLACK));
}

TEST(FullBoardTest, IsSuicideForBlackInAllWhiteField) {
    FullBoard b = create_5x5_all_white();

    EXPECT_EQ(false, b.is_suicide(b.get_vertex(1, 1), FastBoard::BLACK));
    EXPECT_EQ(true, b.is_suicide(b.get_vertex(3, 3), FastBoard::BLACK));
    EXPECT_EQ(true, b.is_suicide(b.get_vertex(4, 4), FastBoard::BLACK));
    EXPECT_EQ(false, b.is_suicide(b.get_vertex(4, 2), FastBoard::BLACK));
    EXPECT_EQ(false, b.is_suicide(b.get_vertex(3, 4), FastBoard::BLACK));
}

TEST(FullBoardTest, CalcAreaScore) {
    FullBoard b = create_full_5x5();
    EXPECT_EQ(-6.5, b.area_score(6.5F)); 
    EXPECT_EQ(-.5, b.area_score(0.5F));
    EXPECT_EQ(-9.0, b.area_score(9.0F)); 
}

TEST(FullBoardTest, CalcAreaScoreOnWhiteField) {
    FullBoard b = create_5x5_all_white();
    EXPECT_EQ(-31.5, b.area_score(6.5F)); 
    EXPECT_EQ(-25.5, b.area_score(0.5F));
    EXPECT_EQ(-34.0, b.area_score(9.0F)); 
}

TEST(FullBoardTest, CalcAreaScoreOnSemiFilled9x9) {
    FullBoard b = create_full_9x9();
    EXPECT_EQ(-9.5, b.area_score(6.5F)); 
    EXPECT_EQ(-3.5, b.area_score(0.5F));
    EXPECT_EQ(-12.0, b.area_score(9.0F)); 
}
