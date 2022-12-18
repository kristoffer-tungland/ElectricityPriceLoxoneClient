#include "pch.h"
#include "CppUnitTest.h"
#include "../Loxone.Common/loxoneExtended.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ElectricityPriceLoxoneClientTests
{
	TEST_CLASS(ElectricityPriceLoxoneClientTests)
	{
	public:
		
		TEST_METHOD(batoitest)
		{
			int value = batoi(" 21");
            Assert::AreEqual(21, value);
		}
	};
}
