/**
 * \file CityView.h
 *
 * \author SHIYANG HE
 *
 * 
 */

#pragma once
#include "ChildView.h"
class CCityView : public CChildView
{
public:
	/// \brief Default constructor (disabled)
	CCityView() = delete;

	/// \brief Copy constructor (disabled)
	CCityView(const CCityView &) = delete;

	/** Destructor*/
	virtual ~CCityView(){}
};

