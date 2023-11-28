#include "pch.h"
#include "CppUnitTest.h"
#include "D:/Visual Studio 2019 ( C++ )/Проекты/3 курс/Курсовая/Программа получения радиус_векторов положения СМКА по данным TLE/TLEDecoder/TLEDecoder.h";

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using TLE::OneTLEDecoder;
using TLE::TLEDecoder;

namespace TLEUnitTest1
{
	TEST_CLASS(TLEUnitTest1)
	{
	private:
		OneTLEDecoder oneTLEDecoder;
		const wchar_t* pFileName = L"D:\\Visual Studio 2019 ( C++ )\\"
			"Проекты\\WinAPI\\Программы с Интернета\\HTMLFromInternet\\TLE\\Space Stations.txt";
	public:
		
		TEST_METHOD(TestReadDataFromFile)
		{
			Assert::IsFalse(oneTLEDecoder.OneTLERead(pFileName, L"ISS (ZARYA)"));
			Assert::AreEqual(oneTLEDecoder.GetFileName().c_str(), pFileName);
		}

		TEST_METHOD(TestReadingFileData)
		{
			// необязательная строка названия спутника
			Assert::AreEqual(oneTLEDecoder.GetSpaceName(), std::wstring(L"ISS (ZARYA)"));	
			// обязательная 1-ая строка
			Assert::AreEqual(oneTLEDecoder.GetStringNumber1(), 1);							// 1
			Assert::AreEqual(oneTLEDecoder.GetSpaceNumberInNORAD1(), 25544);				// 2
			//wchar_t* strClassification = nullptr;
			//std::size_t nLength = 0;
			//oneTLEDecoder.GetClassification()
			Assert::AreEqual(oneTLEDecoder.GetClassification(), std::wstring(L"U"));		// 3
			Assert::AreEqual(oneTLEDecoder.GetStartYear(), 98);								// 4
			Assert::AreEqual(oneTLEDecoder.GetStartNumber(), 067);							// 5
			Assert::AreEqual(oneTLEDecoder.GetStartPart(), std::wstring(L"A"));				// 6
			Assert::AreEqual(oneTLEDecoder.GetEpochYear(), 23);								// 7
			Assert::AreEqual(oneTLEDecoder.GetEpochTime(), 80.26813490);					// 8
			Assert::AreEqual(oneTLEDecoder.GetFirstDerivative(), .00015338);				// 9
			Assert::AreEqual(oneTLEDecoder.GetSecondDerivative(), 0.0);						// 10
			Assert::AreEqual(oneTLEDecoder.GetBSTARcoefficient(), 0.28250e-3);				// 11
			Assert::AreEqual(oneTLEDecoder.GetEfemeridType(), 0);							// 12
			Assert::AreEqual(oneTLEDecoder.GetSetOfElements(), 999);						// 13
			Assert::AreEqual(oneTLEDecoder.GetCheckSum1(), 5);								// 14

			// обязательная 2-ая строка
			Assert::AreEqual(oneTLEDecoder.GetStringNumber2(), 2);															// 1
			Assert::AreEqual(oneTLEDecoder.GetSpaceNumberInNORAD2(), 25544);												// 2
			Assert::AreEqual(oneTLEDecoder.GetInclination(), OneTLEDecoder::FromDegreesToRadians(51.6415));					// 3
			Assert::AreEqual(oneTLEDecoder.GetLongitudeOfTheAscendingNode(), OneTLEDecoder::FromDegreesToRadians(44.1101));	// 4
			Assert::AreEqual(oneTLEDecoder.GetEccentricity(), 0.0006135);													// 5
			Assert::AreEqual(oneTLEDecoder.GetPerigeeArgument(), OneTLEDecoder::FromDegreesToRadians(114.9983));			// 6
			Assert::AreEqual(oneTLEDecoder.GetMeanAnomaly(), OneTLEDecoder::FromDegreesToRadians(27.6264));					// 7
			Assert::AreEqual(oneTLEDecoder.GetTreatmentFrequency(), 15.49342139);											// 8
			Assert::AreEqual(oneTLEDecoder.GetTurnNumber(), 38815);															// 9
			Assert::AreEqual(oneTLEDecoder.GetCheckSum2(), 8);																// 10
		}
	};
}
