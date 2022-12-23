#include "CppUnitTest.h"
extern "C" {
#include "../../UpdateHourPrices/UpdateHourPrices.c"
}

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UpdateHourPricesTests
{
	TEST_CLASS(UpdateHourPricesTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char* averagePrices = getAveragePrices("no2", "NOK");

			Assert::AreEqual("va", "");
		}
	};
}
