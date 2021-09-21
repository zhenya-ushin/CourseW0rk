#include "pch.h"
#include "CppUnitTest.h"
#include "pch.h"
#include "CppUnitTest.h"
#include "../CourseW0rk/Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace courseworkUnitTests
{
	TEST_CLASS(courseworkUnitTests)
	{
	public:

		TEST_METHOD(get_max_flow_size_check1)
		{
			ofstream tester("tester.txt");
			tester << "S;O;3\n";
			tester << "S;P;3\n";
			tester << "O;Q;3\n";
			tester << "O;P;2\n";
			tester << "P;R;2\n";
			tester << "Q;R;4\n";
			tester << "Q;T;2\n";
			tester << "R;T;3";
			tester.close();
			Graphs gr("tester.txt");
			Assert::AreEqual(5, gr.get_max_flow_size());
		}

		TEST_METHOD(get_max_flow_size_check2)
		{
			ofstream tester("tester.txt");
			tester << "S;A;8\n";
			tester << "S;B;4\n";
			tester << "S;C;2\n";
			tester << "A;B;2\n";
			tester << "B;C;1\n";
			tester << "A;D;9\n";
			tester << "C;F;2\n";
			tester << "D;G;8\n";
			tester << "F;I;1\n";
			tester << "G;H;5\n";
			tester << "H;I;1\n";
			tester << "G;T;4\n";
			tester << "H;T;3\n";
			tester << "I;T;6";
			tester.close();
			Graphs gr("tester.txt");
			Assert::AreEqual(9, gr.get_max_flow_size());
		}

		TEST_METHOD(get_max_flow_size_check3)
		{
			ofstream tester("tester.txt");
			tester << "S;O;3\n";
			tester << "S;P;3\n";
			tester << "O;Q;3\n";
			tester << "O;P;2\n";
			tester << "P;R;2\n";
			tester << "Q;R;4\n";
			tester << "X;T;1";
			tester.close();
			Graphs gr("tester.txt");
			Assert::AreEqual(0, gr.get_max_flow_size());
		}
	};
}
