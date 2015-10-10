/**
 * \file TileConstruction.cpp
 *
 * \author SHIYANG HE
 */

#include "stdafx.h"
#include "TileConstruction.h"

CTileConstruction::CTileConstruction(CCity *city) : CTile(city){
	SetImage(L"grass.png");
}

CTileConstruction::~CTileConstruction()
{
}

/** \brief Save this item to an XML node
* \param node The node we are going to be a child of
* \returns Allocated node
*/
std::shared_ptr<xmlnode::CXmlNode> CTileConstruction::XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	auto itemNode = CTile::XmlSave(node);
	itemNode->SetAttribute(L"type", L"grass");
	return itemNode;
}

/**
* brief Load the attributes for an item node.
* \param node The Xml node we are loading the item from
*/
void CTileConstruction::XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node)
{
	CTile::XmlLoad(node);
	SetImage(node->GetAttributeValue(L"file", L""));
}

void CTileConstruction::Update(double elapsed)
{
	if (this->GetZoning()==CTile::Zonings::GRASS)
	{
		switch (mMode)
		{
		case Stadium:
			SetImage(L"stadium.png");
			break;
		case Mine:
		{
			mDuration += elapsed;
			if (mDuration > 3){
				mDuration = 0;
				if (mAscending)
					mCount++;
				else
					mCount--;
				switch (mCount)
				{
				case 0:
				{
					SetImage(L"oremine1.png");
					mAscending = !mAscending;
					mCount++;
					break;
				}
				case 1:
					SetImage(L"oremine1.png");
					break;
				case 2:
					SetImage(L"oremine2.png");
					break;
				case 3:
					SetImage(L"oremine3.png");
					break;
				case 4:
					SetImage(L"oremine4.png");
					break;
				case 5:
					SetImage(L"oremine5.png");
					break;
				case 6:
					SetImage(L"oremine6.png");
					break;
				case 7:
					SetImage(L"oremine7.png");
					break;
				case 8:
				{
					SetImage(L"oremine8.png");
					mAscending = !mAscending;
					break;
				}
				}
			}
			break;
		}
		case Clearing:
		{
			mDuration += elapsed;
			if (mDuration > 3){
				mCount++;
				mDuration = 0;
				switch (mCount)
				{
				case 1:
					SetImage(L"clearing1.png");
					break;
				case 2:
					SetImage(L"clearing2.png");
					break;
				case 3:
					SetImage(L"clearing3.png");
					break;
				case 4:
					SetImage(L"clearing4.png");
					break;
				case 5:
					SetImage(L"clearing5.png");
					break;
				case 6:
					SetImage(L"clearing6.png");
					break;
				case 7:
					SetImage(L"clearing7.png");
					break;
				case 8:
				{
					SetImage(L"clearing8.png");
					mCount = 0;
					srand((unsigned)time(NULL));
					switch (rand() % 2)
					{
					case 0:
						mMode = Mine;
						break;
					case 1:
						mMode = Stadium;
						break;
					}
					break;
				}
				}
			}
			break;
		}
		}
	}
	else
		CTile::Update(elapsed);
}