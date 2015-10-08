#include "stdafx.h"
#include "CppUnitTest.h"
#include "City.h"
#include "TileRoad.h"
#include "TileRoad.h"
#include "TileLandscape.h"
#include "TileCoalmine.h"
#include "TileBuilding.h"

using namespace std;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Testing
{

	/** Visitor test */
	class CTestVisitor : public CTileVisitor
	{
	public:
		/** Visit a CTileRoad object
		* \param road Road we are visiting */
		virtual void VisitRoad(CTileRoad *road) { mNumRoads++; }

		/** Visit a CTileBuilding object
		* \param building Building we are visiting */
		virtual void VisitBuilding(CTileBuilding *building) { mNumBuildings++; }

		/** Visit a CTileLandscape object
		* \param landscape Landscape tile we are visiting */
		virtual void VisitLandscape(CTileLandscape *landscape) { mNumLandscapes++; }

		/** Visit a CTileCoalmine object
		* \param coalmine Coal mine we are visiting */
		virtual void VisitCoalmine(CTileCoalmine *coalmine) { mNumCoalmines++; }

		/// Counter
		int mNumRoads = 0;

		/// Counter
		int mNumBuildings = 0;

		/// Counter
		int mNumLandscapes = 0;

		/// Counter
		int mNumCoalmines = 0;
	};

	TEST_CLASS(CCityTest)
	{
	public:
        TEST_METHOD_INITIALIZE(methodName)
        {
            extern wchar_t g_dir[];
            ::SetCurrentDirectory(g_dir);
        }

		TEST_METHOD(TestCCityConstructor)
		{
            CCity city;
		}

        /** \brief Tests for the GetAdjacent function
         */
        TEST_METHOD(TestCCityAdjacent)
        {
            CCity city;
            int grid = CCity::GridSpacing;

            // Add a center tile to test
            auto center = make_shared<CTileRoad>(&city);
            center->SetLocation(grid * 10, grid * 17);
            city.Add(center);

            // Upper left
            auto ul = make_shared<CTileRoad>(&city);
            ul->SetLocation(grid * 8, grid * 16);
            city.Add(ul);
            city.SortTiles();

            Assert::IsTrue(city.GetAdjacent(center, -1, -1) == ul, L"Upper left test");
            Assert::IsTrue(city.GetAdjacent(center, 1, -1) == nullptr, L"Upper right null test");

            // Upper right
            auto ur = make_shared<CTileRoad>(&city);
            ur->SetLocation(grid * 12, grid * 16);
            city.Add(ur);

            // Lower left
            auto ll = make_shared<CTileRoad>(&city);
            ll->SetLocation(grid * 8, grid * 18);
            city.Add(ll);

            // Lower right
            auto lr = make_shared<CTileRoad>(&city);
            lr->SetLocation(grid * 12, grid * 18);
            city.Add(lr);

            city.SortTiles();

            Assert::IsTrue(city.GetAdjacent(center, 1, -1) == ur, L"Upper right test");
            Assert::IsTrue(city.GetAdjacent(center, -1, 1) == ll, L"Lower left test");
            Assert::IsTrue(city.GetAdjacent(center, 1, 1) == lr, L"Lower right test");
        }

		TEST_METHOD(TestCCityIterator)
		{
			// Construct a city object
			CCity city;

			// Add some tiles
			auto tile1 = make_shared<CTileRoad>(&city);
			auto tile2 = make_shared<CTileRoad>(&city);
			auto tile3 = make_shared<CTileRoad>(&city);

			city.Add(tile1);
			city.Add(tile2);
			city.Add(tile3);

			// Begin points to the first item
			auto iter1 = city.begin();

			// End points after the last item
			auto iter2 = city.end();

			Assert::IsTrue(tile1 == *iter1, L"First item correct");
			++iter1;
			Assert::IsTrue(tile2 == *iter1, L"Second item correct");
			++iter1;
			Assert::IsTrue(tile3 == *iter1, L"Third item correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);
		}

		TEST_METHOD(TestCCityZoningIterator)
		{
			// Construct a city object
			CCity city;

			/*
			* Test on an empty city
			*/
			// Get the iterator support object
			auto itersupport = city.GetZoning(CTile::AGRICULTURAL);

			// Begin points to the first item
			auto iter1 = itersupport.begin();

			// End points after the last item
			auto iter2 = itersupport.end();

			Assert::IsFalse(iter1 != iter2);

			/*
			* Add some tiles and test
			*/
			auto tile1 = make_shared<CTileRoad>(&city);
			tile1->SetZoning(CTile::AGRICULTURAL);
			auto tile2 = make_shared<CTileRoad>(&city);
			tile2->SetZoning(CTile::INDUSTRIAL);
			auto tile3 = make_shared<CTileRoad>(&city);
			tile3->SetZoning(CTile::AGRICULTURAL);
			auto tile4 = make_shared<CTileRoad>(&city);
			tile4->SetZoning(CTile::NONE);
			auto tile5 = make_shared<CTileRoad>(&city);
			tile5->SetZoning(CTile::INDUSTRIAL);

			city.Add(tile1);
			city.Add(tile2);
			city.Add(tile3);
			city.Add(tile4);
			city.Add(tile5);

			//
			// First test: AGRICULTURAL tiles
			//
			// Get the iterator support object
			itersupport = city.GetZoning(CTile::AGRICULTURAL);

			// Begin points to the first item
			iter1 = itersupport.begin();

			// End points after the last item
			iter2 = itersupport.end();

			Assert::IsTrue(tile1 == *iter1, L"First agricultural correct");
			++iter1;
			Assert::IsTrue(tile3 == *iter1, L"Second agricultural correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);

			//
			// Second test: INDUSTRIAL tiles
			//
			// Get the iterator support object
			itersupport = city.GetZoning(CTile::INDUSTRIAL);

			// Begin points to the first item
			iter1 = itersupport.begin();

			// End points after the last item
			iter2 = itersupport.end();

			Assert::IsTrue(tile2 == *iter1, L"First industrial correct");
			++iter1;
			Assert::IsTrue(tile5 == *iter1, L"Second industrial correct");
			++iter1;
			Assert::IsFalse(iter1 != iter2);

			//
			// Third test: zoning with no results
			//
			// Get the iterator support object
			itersupport = city.GetZoning(CTile::RESIDENTIAL);

			// Begin points to the first item
			iter1 = itersupport.begin();

			// End points after the last item
			iter2 = itersupport.end();

			Assert::IsFalse(iter1 != iter2);
		}

		TEST_METHOD(TestCCityVisitor)
		{
			// Construct a city object
			CCity city;

			// Add some tiles of each time
			auto tile1 = make_shared<CTileRoad>(&city);
			auto tile2 = make_shared<CTileBuilding>(&city);
			auto tile3 = make_shared<CTileLandscape>(&city);
			auto tile4 = make_shared<CTileCoalmine>(&city);

			city.Add(tile1);
			city.Add(tile2);
			city.Add(tile3);
			city.Add(tile4);

			CTestVisitor visitor;
			city.Accept(&visitor);
			Assert::AreEqual(1, visitor.mNumRoads, L"Visitor number of roads");
			Assert::AreEqual(1, visitor.mNumBuildings, L"Visitor number of buildings");
			Assert::AreEqual(1, visitor.mNumLandscapes, L"Visitor number of landscapes");
			Assert::AreEqual(1, visitor.mNumCoalmines, L"Visitor number of coalmines");
		}
	};
}