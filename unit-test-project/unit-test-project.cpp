#include "pch.h"
#include "CppUnitTest.h"
#include "..\9 software\9 software.cpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{
    TEST_CLASS(TalkTests)
    {
    public:
        TEST_METHOD(DurationTest)
        {
            Talk talk1 = { "09:00", "10:00", "Doe", "John", "Middle", "Theme" };
            Talk talk2 = { "13:30", "15:00", "Doe", "Jane", "Middle", "Theme" };
            Assert::AreEqual(talk1.duration(), 60);
            Assert::AreEqual(talk2.duration(), 90);
        }

    };
}
