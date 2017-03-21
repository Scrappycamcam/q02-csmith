/**
 * Unit Tests for Piezas
**/

#include <gtest/gtest.h>
#include "Piezas.h"
 
class PiezasTest : public ::testing::Test
{
	protected:
		PiezasTest(){} //constructor runs before each test
		virtual ~PiezasTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor) 
};

TEST(PiezasTest, sanityCheck)
{
	ASSERT_TRUE(true);
}
TEST(PiezasTest, oobDropTest)
{
	Piezas Test;
	Piece Out = Test.dropPiece(10);
	Piece Neg = Test.dropPiece(-10);
	ASSERT_EQ(Out, Neg);
	ASSERT_EQ(Out, Invalid);
}
TEST(PiezasTest, dropTest)
{
	Piezas Test;
	Piece Safe = Test.dropPiece(0);
	Piece Try = Test.pieceAt(0,0);
	ASSERT_EQ(Safe, Try);
}
TEST(PiezasTest, pieceAtTest)
{
	Piezas Test;
	Test.dropPiece(0);
	ASSERT_EQ(Test.pieceAt(0,0), X);
}
TEST(PiezasTest, winX)
{
	Piezas Test;
	Test.dropPiece(0);//x
	Test.dropPiece(0);//o
	Test.dropPiece(1);//x
	Test.dropPiece(0);//o
	Test.dropPiece(2);//x
	Test.dropPiece(1);//o
	Test.dropPiece(3);//x
	Test.dropPiece(2);//o
	Test.dropPiece(1);//x
	Test.dropPiece(2);//o
	Test.dropPiece(3);//x
	Test.dropPiece(3);//0
	ASSERT_EQ(Test.gameState(), X);
}
TEST(PiezasTest, winO)
{
	Piezas Test;
	Test.dropPiece(0);//x
	Test.dropPiece(1);//o
	Test.dropPiece(2);//x
	Test.dropPiece(0);//o
	Test.dropPiece(3);//x
	Test.dropPiece(1);//o
	Test.dropPiece(0);//x
	Test.dropPiece(2);//o
	Test.dropPiece(1);//x
	Test.dropPiece(3);//o
	Test.dropPiece(2);//x
	Test.dropPiece(3);//0
	ASSERT_EQ(Test.gameState(), O);
}
TEST(PiezasTest, tieTest)
{
	Piezas Test;
	Test.dropPiece(0);//x
	Test.dropPiece(0);//o
	Test.dropPiece(1);//x
	Test.dropPiece(1);//o
	Test.dropPiece(2);//x
	Test.dropPiece(2);//o
	Test.dropPiece(3);//x
	Test.dropPiece(3);//o
	Test.dropPiece(1);//x
	Test.dropPiece(2);//o
	Test.dropPiece(3);//x
	Test.dropPiece(0);//0
	ASSERT_EQ(Test.gameState(), Blank);
}
TEST(PiezasTest, resetTest)
{
	Piezas Test;
	Test.dropPiece(0);
	Test.reset();
	Piece empty = Test.pieceAt(0,0);
	ASSERT_EQ(empty, Blank);
}
TEST(PiezasTest, oobAtTest)
{
	Piezas Test;
	Piece Out = Test.pieceAt(20, 0);
	Piece Neg = Test.pieceAt(-20, 0);
	ASSERT_EQ(Out, Neg);
}
TEST(PiezasTest, Filler)
{
	Piezas Test;
	Test.dropPiece(0);
	ASSERT_EQ(Test.gameState(), Invalid);
}
