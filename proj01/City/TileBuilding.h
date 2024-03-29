/**
* \file TileBuilding.h
*
* \author Charles B. Owen
*
* \brief Class that implements a Building tile
*/

#pragma once

#include "Tile.h"

/**
* \brief A Building tile
*/
class CTileBuilding : public CTile
{
public:
	/** Constructor
	* \param city The city this is a member of */
	CTileBuilding(CCity *city) : CTile(city){}

    /// \brief Default constructor (disabled)
    CTileBuilding() = delete;

    /// \brief Copy constructor (disabled)
    CTileBuilding(const CTileBuilding &) = delete;

	/** Destructor */
	virtual ~CTileBuilding(){}

    virtual std::shared_ptr<xmlnode::CXmlNode>
		XmlSave(const std::shared_ptr<xmlnode::CXmlNode> &node) override;
    virtual void XmlLoad(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/** Accept a visitor
	* \param visitor The visitor we accept */
	virtual void Accept(CTileVisitor *visitor) override { visitor->VisitBuilding(this); }

	/** Accept a hitvisitor
	* \param agent The visitor we accept */
	virtual void HitAccept(CTileVisitor *agent) override { agent->VisitBuilding(this); }
};