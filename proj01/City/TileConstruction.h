/**
 * \file TileConstruction.h
 *
 * \author SHIYANG HE
 *
 * 
 */

#pragma once

#include <stdlib.h>
#include <time.h>
#include "Tile.h"

/** Grass tile */
class CTileConstruction : public CTile
{
public:
	/** Constructor
	*\param city The city this is a member of */
	CTileConstruction(CCity *city);

	/// \brief Default constructor (disabled)
	CTileConstruction() = delete;

	/// \brief Copy constructor (disabled)
	CTileConstruction(const CTileConstruction &) = delete;

	/** Destructor*/
	virtual ~CTileConstruction(){}

	virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitGrass(this); }

	/// Possible mode options
	enum Modes { Clearing, Mine, Stadium };

	/// \brief Handle updates for animation
	/// \param elapsed The time since the last update
	void Update(double elapsed)override;

	/** Accept a hitvisitor
	* \param agent The visitor we accept */
	virtual void HitAccept(CTileVisitor *agent)override { agent->HitGrass(this); };

private:
	/// Current mode
	Modes mMode = Clearing;

	/// true when Ascending, false otherwise
	bool mAscending = true;

	/// counter for Clearing & ore mine
	int mCount = 0;

	/// time counter for construction
	double mDuration = 0;
};