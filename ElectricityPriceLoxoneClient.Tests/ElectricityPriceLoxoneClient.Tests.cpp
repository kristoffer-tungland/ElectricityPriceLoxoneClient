#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace ElectricityPriceLoxoneClientTests
{
	TEST_CLASS(ElectricityPriceLoxoneClientTests)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
           std::string first = first_numberstring("\"ScoreNow\": 22,\r\n");
            std::string name = "22";
            Assert::AreEqual(first, name);
		}

        std::string first_numberstring(std::string const& str)
        {
            char const* digits = "0123456789";
            std::size_t const n = str.find_first_of(digits);
            if (n != std::string::npos)
            {
                std::size_t const m = str.find_first_not_of(digits, n);
                return str.substr(n, m != std::string::npos ? m - n : m);
            }
            return std::string();
        }
	};
}
