/**
 * \file BuildingCounter.h
 *
 * \author SHIYANG HE
 *
 * 
 */

#pragma once
#include "TileVisitor.h"
#include "TileCoalmine.h"

/** Visitor class for counting the buildings in a city
* 
*
* This visitor visits tiles and increases the count if the tile is a building
*/
class CBuildingCounter : public CTileVisitor
{
public:
	/** Constructor */
	CBuildingCounter();

	/** Destructor */
	virtual ~CBuildingCounter();

	/** Get the number of buildings
	* \returns Number of buildings */
	int GetNumBuildings() const { return mNumBuildings; }

	/** Visit a CTileBuilding object
	* \param building Building we are visiting */
	void VisitBuilding(CTileBuilding *building) { mNumBuildings++; }

	/** Visit a Coalmine object
	* \param coalmine Coalmine we are visiting*/
	void VisitCoalmine(CTileCoalmine *coalmine)
	{
		if (CoalmineController)
			coalmine->ResetCoalmine();
		else
			mCoalmineProduction += coalmine->getProduction();
	}

	/** Coalmine production getter
	* \return double mCoalmineProduction */
	double getCoalmineProduction()const{ return mCoalmineProduction; }

	/** Reset coalmine production*/
	void ResetCoalmine(){ CoalmineController = true; }

	/** Hit the mine
	*\param coalmine Coalmine we are hitting*/
	void HitCoalmine(CTileCoalmine *coalmine){ coalmine->hit(); }
private:
	/// Buildings counter
	int mNumBuildings = 0;

	/// Coal counter
	double mCoalmineProduction = 0;

	/// Coalmine controller
	bool CoalmineController = false;
};