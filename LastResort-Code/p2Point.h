// ----------------------------------------------------
// Point class    -----------
// ----------------------------------------------------

#ifndef __P2POINT_H__
#define __P2POINT_H__

#include "Globals.h"
#include <math.h>

template<class TYPE>
class p2Point
{
public:

	TYPE x, y;

	p2Point()
	{}

	p2Point(const p2Point& v)
	{
		this->x = v.x;
		this->y = v.y;
	}

	p2Point(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;
	}

	p2Point& create(const TYPE& x, const TYPE& y)
	{
		this->x = x;
		this->y = y;

		return(*this);
	}

	// Math ------------------------------------------------
	p2Point operator -(const p2Point &v) const
	{
		p2Point r;

		r.x = x - v.x;
		r.y = y - v.y;

		return(r);
	}

	p2Point operator + (const p2Point &v) const
	{
		p2Point r;

		r.x = x + v.x;
		r.y = y + v.y;

		return(r);
	}

	const p2Point& operator -=(const p2Point &v)
	{
		x -= v.x;
		y -= v.y;

		return(*this);
	}

	const p2Point& operator +=(const p2Point &v)
	{
		x += v.x;
		y += v.y;

		return(*this);
	}

	bool operator ==(const p2Point& v) const
	{
		return (x == v.x && y == v.y);
	}

	bool operator !=(const p2Point& v) const
	{
		return (x != v.x || y != v.y);
	}

	// Utils ------------------------------------------------
	bool IsZero() const
	{
		return (x == 0 && y == 0);
	}

	p2Point& SetToZero()
	{
		x = y = 0;
		return(*this);
	}

	p2Point& Negate()
	{
		x = -x;
		y = -y;

		return(*this);
	}

	// Distances ---------------------------------------------
	TYPE DistanceTo(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (TYPE)sqrtf(float(fx*fx) + float(fy*fy));
	}

	TYPE DistanceNoSqrt(const p2Point& v) const
	{
		TYPE fx = x - v.x;
		TYPE fy = y - v.y;

		return (fx*fx) + (fy*fy);
	}

	TYPE DistanceManhattan(const p2Point& v) const
	{
		return abs(v.x - x) + abs(v.y - y);
	}

	// Custom ------------------------------------------------

	//- This function makes the unit vector (a vector with module 1) from a source postion to a target postion
	void UnitVector(p2Point targetPos, p2Point sourcePos)
	{
		p2Point unitVec;
		TYPE unitVecModule;
		//- We create a vector from the player to the unit
		unitVec.x = targetPos.x - sourcePos.x;
		unitVec.y = targetPos.y - sourcePos.y;
		//- We find the module of the vectors
		unitVecModule = sqrt(pow(unitVec.x, 2) + (pow(unitVec.y, 2)));
		//- We divide each component by the module
		unitVec.x /= unitVecModule;
		unitVec.y /= unitVecModule;
		this->x = unitVec.x;
		this->y = unitVec.y;
	}
	//- This function makes the unit vector (a vector with module 1) from a source postion to a target postion
	p2Point VectU()
	{
		p2Point Vecu;
		TYPE unitVecModule;
		Vecu.x = this->x;
		Vecu.y = this->y;
		//- We find the module of the vectors
		unitVecModule = sqrt(pow(Vecu.x, 2) + (pow(Vecu.y, 2)));
		//- We divide each component by the module
		if (unitVecModule != 0)
		{
			Vecu.x /= unitVecModule;
			Vecu.y /= unitVecModule;
		}
		if (unitVecModule == 0)
		{
			Vecu.x = 0;
				Vecu.y = 0;
		}
		return Vecu;
	}

};

typedef p2Point<int> iPoint;
typedef p2Point<float> fPoint;
typedef p2Point<double> dPoint;

#endif // __P2POINT_H__