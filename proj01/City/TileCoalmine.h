/**
* \file TileCoalmine.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Landscape tile
*/

#pragma once

#include "Tile.h"

class CBuildingCounter;
/**
* \brief A Landscape tile
*/
class CTileCoalmine : public CTile
{
public:
	/** Constructor
	* \param city The city this is a member of */
	CTileCoalmine(CCity *city) : CTile(city){ SetImage(L"coalmine-empty.png"); }

    /// \brief Default constructor (disabled)
    CTileCoalmine() = delete;

    /// \brief Copy constructor (disabled)
    CTileCoalmine(const CTileCoalmine &) = delete;

	/** Destructor */
	virtual ~CTileCoalmine(){}

    virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitCoalmine(this); }

	/**
	* Called before the image is drawn
	* \param elapsed Time since last draw*/
	void Update(double elapsed);

	/** Coalmine production getter
	* \return double mProduction
	*/
	double getProduction(){ return mProduction; }

	/** Reset coalmine production*/
	void ResetCoalmine();

	/** Accept a hitvisitor
	* \param agent The visitor we accept */
	virtual void HitAccept(CTileVisitor *agent)override { agent->HitCoalmine(this); };

	/** Hit me*/
	void hit();
private:
	/// Time count
	double mDuration = 0;

	/// Coal count
	double mProduction = 0;

	/// hit record
	int hits = 0;
};