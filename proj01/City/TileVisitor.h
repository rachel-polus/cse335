/**
 * \file TileVisitor.h
 *
 * \author SHIYANG HE
 *
 * 
 */

#pragma once

// Forward references to all tile types
class CTileBuilding;
class CTileCoalmine;
class CTileLandscape;
class CTileRoad;
class CTileConstruction;

/** Tile visitor base class */
class CTileVisitor
{
public:
	CTileVisitor(){}
	virtual ~CTileVisitor(){}

	/** Visit a CTileBuilding object
	*\param building Building we are visiting */
	virtual void VisitBuilding(CTileBuilding *building) {}

	/** Visit a CTileCoalmine object
	*\param coalmine Coal mine we are visiting */
	virtual void VisitCoalmine(CTileCoalmine *coalmine) {}

	/** Visit a CTileLandscape object
	*\param landscape Landscape tile we are visiting */
	virtual void VisitLandscape(CTileLandscape *landscape) {}

	/** Visit a CTileRoad object
	*\param road Road we are visiting */
	virtual void VisitRoad(CTileRoad *road) {}

	/** Hitting a Coalmine object
	*\param coalmine Coalmine tile we are hitting */
	virtual void HitCoalmine(CTileCoalmine *coalmine) {}

	/** Hitting a CTileLandscape object
	*\param landscape Landscape tile we are Hitting */
	virtual void HitLandscape(CTileLandscape *landscape) {}

	/** Hitting a CTileRoad object
	*\param road Road we are Hitting */
	virtual void HitRoad(CTileRoad *road) {}

	/** Visit a grass object
	*\param grass Grass we are visiting */
	virtual void VisitGrass(CTileConstruction *grass) {}

	/** Hitting a grass object
	*\param grass Grass we are hitting */
	virtual void HitGrass(CTileConstruction *grass) {}
};