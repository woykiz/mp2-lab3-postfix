#include "postfix.cpp"
#include <gtest.h>
TEST(TPostfix, can_create_postfix) 
{
	ASSERT_NO_THROW(TPostfix p);
}
TEST(TPostfix, can_add_infix) 
{
	TPostfix p;
	p.Set("3 + 4");
	EXPECT_EQ("3 + 4", p.GetInfix());
}
TEST(TPostfix, can_get_postfix) 
{
	TPostfix p("1 + 5");
	EXPECT_EQ("1_5_+", p.GetPostfix());
}
TEST(TPostfix, can_get_postfix_from_expression_with_two_characters_of_the_same_order) 
{
	TPostfix p("1 + 2 * 3 / 4 - 5");
	EXPECT_EQ("1_2_3_*_4_/_+_5_-", p.GetPostfix());
}
TEST(TPostfix, can_create_postfix_from_postfix) 
{
	TPostfix p1("1 + 5");
	p1.GetPostfix();
	TPostfix p2(p1);
	EXPECT_EQ("1 + 5", p2.GetInfix());
	EXPECT_EQ("1_5_+", p2.GetPostfix());
}
TEST(TPostfix, can_assign_postfix) 
{
	TPostfix p1("1 + 5");
	TPostfix p2;
	p1.GetPostfix();
	p2 = p1;
	EXPECT_EQ("1 + 5", p2.GetInfix());
	EXPECT_EQ("1_5_+", p2.GetPostfix());
}
TEST(TPostfix, can_calculate_simple_expression) 
{
	TPostfix p("11 - 5");
	EXPECT_EQ(6, p.Calculate());
}
TEST(TPostfix, can_calculate_expression_with_brackets) 
{
	TPostfix p("20 / (6 + 4)");
	EXPECT_EQ(2, p.Calculate());
}
TEST(TPostfix, can_calculate_expression_with_two_characters_of_the_same_order) 
{
	TPostfix p("1 + 2 * 3 / 4 - 5");
	EXPECT_EQ(-2.5, p.Calculate());
}
TEST(TPostfix, can_not_divide_by_zero) 
{
	TPostfix p("20 / 0");
	ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, can_reset_expression) 
{
	TPostfix p("4 - 5");
	p.Calculate();
	p.Set("1 - 3");
	EXPECT_EQ(-2, p.Calculate());
}
TEST(TPostfix, throw_if_expression_has_non_number_member) 
{
	TPostfix p("5 + 4 - 3 + a");
	ASSERT_ANY_THROW(p.Calculate());
}
TEST(TPostfix, can_calculate_double) 
{
	TPostfix p("1.34 + 5.24");
	EXPECT_EQ(6.58, p.Calculate());
}