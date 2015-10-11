/**
 * \file TileCoalmine.cpp
 *
 * \author SHIYANG HE
 */

#include "stdafx.h"
#include "TileCoalmine.h"

using namespace std;
using namespace Gdiplus;

/// Image when the coalmine production is low
const wstring LowProductionImage = L"coalmine-low.png";

/// Time to reach low production level in seconds
const double LowProductionTime = 5;

/// Tons of coal at low production level
const double LowProduction = 1;

/// Image when the coalmine production is Medium
const wstring MediumProductionImage = L"coalmine-med.png";

/// Time to reach Medium production level in seconds
const double MediumProductionTime = 6;

/// Tons of coal at Medium production level
const double MediumProduction = 2.5;

/// Image when the coalmine production is Full
const wstring FullProductionImage = L"coalmine-full.png";

/// Time to reach Full production level in seconds
const double FullProductionTime = 4;

/// Tons of coal at Full production level
const double FullProduction = 4;

/// Image when the coalmine is destroyed
const wstring DestroyedImage = L"burnt_land.png";

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileCoalmine::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
    auto itemNode = CTile::XmlSave(node);
    itemNode->SetAttribute(L"type", L"coalmine");
    return itemNode;
}

void CTileCoalmine::Update(double elapsed)
{
	CTile::Update(elapsed);
	mDuration += elapsed;
	if (hits < 2){
		if (hits == 0){
			if (mProduction == 0 && mDuration >= LowProductionTime)
			{
				mProduction = LowProduction;
				SetImage(LowProductionImage);
				mDuration = 0;
			}
			else if (mProduction == LowProduction && mDuration >= MediumProductionTime)
			{
				mProduction = MediumProduction;
				SetImage(MediumProductionImage);
				mDuration = 0;
			}
			else if (mProduction == MediumProduction && mDuration >= FullProductionTime)
			{
				mProduction = FullProduction;
				SetImage(FullProductionImage);
				mDuration = 0;
			}
		}
		else
		{
			if (mProduction == 0 && mDuration >= LowProductionTime / 2)
			{
				mProduction = LowProduction;
				SetImage(LowProductionImage);
				mDuration = 0;
			}
			else if (mProduction == LowProduction && mDuration >= MediumProductionTime / 2)
			{
				mProduction = MediumProduction;
				SetImage(MediumProductionImage);
				mDuration = 0;
			}
			else if (mProduction == MediumProduction && mDuration >= FullProductionTime / 2)
			{
				mProduction = FullProduction;
				SetImage(FullProductionImage);
				mDuration = 0;
			}
		}
	}
}
void CTileCoalmine::ResetCoalmine()
{
	if (hits < 2)
	{
		mProduction = 0;
		SetImage(L"coalmine-empty.png");
	}
}

void CTileCoalmine::hit()
{ 
	if (hits < 3)
	{
		hits++;
		if (hits == 2 && mProduction != 0)
		{
			SetImage(DestroyedImage);
			mProduction = 0;
		}
	}
}