/**
 * \file City.h
 *
 * \author Charles B. Owen
 *
 * \brief Class that implements a simple city with tiles we can manipulate
 */

#pragma once

#include <memory>
#include <vector>
#include <map>
#include <utility>
#include "XmlNode.h"
#include "Tile.h"

/**
 * \brief Implements a simple city with tiles we can manipulate
 */
class CCity
{
public:
	CCity();
	virtual ~CCity();

	/// The spacing between grid locations
	static const int GridSpacing = 32;

	void Add(std::shared_ptr<CTile> item);
	std::shared_ptr<CTile> HitTest(int x, int y);
	void MoveToFront(std::shared_ptr<CTile> item);
	void DeleteItem(std::shared_ptr<CTile> item);

	void OnDraw(Gdiplus::Graphics *graphics);

	void Save(const std::wstring &filename);
	void Load(const std::wstring &filename);
	void Clear();

	void Update(double elapsed);
	void SortTiles();

	std::shared_ptr<CTile> GetAdjacent(std::shared_ptr<CTile> tile, int dx, int dy);
	std::shared_ptr<CTile> GetAdjacent(CTile *tile, int dx, int dy);

	/** Trump mode controller */
	void TrumpController(){
		if (mTrump)
			mTrump = false;
		else
			mTrump = true;
	}

	/** Trump mode tracker
	* \return true if active, false otherwise
	*/
	bool TrumpActive(){ return mTrump; }

	/** \brief Iterator that iterates over the city tiles */
	class Iter
	{
	public:
		/** \brief Constructor
		* \param city The city we are iterating over
		* \param pos position of the item
		*/
		Iter(CCity *city, int pos) : mCity(city), mPos(pos) {}

		/** \brief Test for end of the iterator
		* \param other other object
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const Iter &other) const
		{
			return mPos != other.mPos;
		}

		/** \brief Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** \brief Increment the iterator
		* \returns Reference to this iterator */
		const Iter& operator++()
		{
			mPos++;
			return *this;
		}


	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
	};


	/** \brief Get an iterator for the beginning of the collection
	* \returns Iter object at position 0 */
	Iter begin() { return Iter(this, 0); }

	/** \brief Get an iterator for the end of the collection
	* \returns Iter object at position past the end */
	Iter end() { return Iter(this, mTiles.size()); }



	/** \brief Iterator that iterates over the city tiles */
	class ZoningIter
	{
	public:
		/** \brief Constructor
		* \param city The city we are iterating over
		* \param pos The position
		* \param zone The zone
		*/
		ZoningIter(CCity *city, int pos, CTile::Zonings zone) : mCity(city), mPos(pos), mZone(zone) {}

		/** \brief Test for end of the iterator
		* \param other Other object
		* \returns True if we this position equals not equal to the other position */
		bool operator!=(const ZoningIter &other) const
		{
			return mPos != other.mPos;
		}

		/** \brief Get value at current position
		* \returns Value at mPos in the collection */
		std::shared_ptr<CTile> operator *() const { return mCity->mTiles[mPos]; }

		/** \brief Increment the iterator
		* \returns Reference to this iterator */
		const ZoningIter& operator++()
		{
			mPos++;
			for (auto iter = mPos; iter != (mCity->mTiles.size()); iter++)
			{
				if (mCity->mTiles[iter]->GetZoning() == mZone)
				{
					break;
				}
				mPos++;
			}
			return *this;
		}

	private:
		CCity *mCity;   ///< City we are iterating over
		int mPos;       ///< Position in the collection
		CTile::Zonings mZone;	///< The zone we are iterating over
	};


	/** \brief A class we return to support iterating over
	* only specific zonings in the collection */
	class ZoningIterSupport
	{
	public:
		/** \brief Constructor
		* \param city The city we are iteratoring over
		* \param zoning The zoning we are interested in */
		ZoningIterSupport(CCity *city, CTile::Zonings zoning) : mCity(city), mZoning(zoning) {}

		/** \brief Get an iterator for the beginning of the collection
		* \returns Iter object at position 0 */
		ZoningIter begin()
		{
			for (unsigned int i = 0; i < mCity->mTiles.size(); i++)
			{
				if (mCity->mTiles[i]->GetZoning() == mZoning)
				{
					return ZoningIter(mCity, i, mZoning);
				}
			}
			return ZoningIter(mCity, mCity->mTiles.size(), mZoning);
		}

		/** \brief Get an iterator for the end of the collection
		* \returns Iter object at position past the end */
		ZoningIter end()
		{
			/*for (int i = mCity->mTiles.size() - 1; i > 0; i--)
			{
				if (mCity->mTiles[i]->GetZoning() == mZoning)
				{
					return ZoningIter(mCity, i, mZoning);
				}
			}*/
			return ZoningIter(mCity, mCity->mTiles.size(), mZoning);
		}
	private:
		/// The city we are iterating over
		CCity *mCity;
		/// The zone type we are trying to find
		CTile::Zonings mZoning;
	};

	/** \brief Get a zoning iterator support object
	* \param zoning The zoning we are interested in
	* \returns ZoningIterSupport object
	*/
	ZoningIterSupport GetZoning(CTile::Zonings zoning) { return ZoningIterSupport(this, zoning); }

	/** Accept a visitor for the collection
	* \param visitor The visitor for the collection
	*/
	void Accept(CTileVisitor *visitor);

private:
	/// The XmlTile 
	void XmlTile(const std::shared_ptr<xmlnode::CXmlNode> &node);

	/// Build the adjacent tiles
	void BuildAdjacencies();

	/// All of the tiles that make up our city
	std::vector<std::shared_ptr<CTile> > mTiles;

	/// Adjacency lookup support
	std::map<std::pair<int, int>, std::shared_ptr<CTile> > mAdjacency;

	/// Trump mode
	bool mTrump = false;
};