#include "pch.h"
#include "CppUnitTest.h"
extern "C" {
#include "../../Loxone.Common/loxoneExtended.h"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace LoxoneCommonTests
{
	namespace Extended
	{
		TEST_CLASS(LoxoneExtendedTests)
		{
		public:

			TEST_METHOD(batoi_acepts_blanks_in_string_before_int)
			{
				int value = batoi(" 23");
				Assert::AreEqual(23, value);
			}

			TEST_METHOD(batoi_converts_string_to_int)
			{
				int value = batoi("230");
				Assert::AreEqual(230, value);
			}

			TEST_METHOD(batoi_fails)
			{
				int value = batoi("some value");
				Assert::AreEqual(0, value);
			}

			TEST_METHOD(batoi_negative_numbers)
			{
				int value = batoi("-1");
				Assert::AreEqual(-1, value);
			}
		};
	}
}