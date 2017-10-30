/* ====================================================================
 * File: Box.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Box.h"
#include "BoxObserver.h"
#include "BoxHelper.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CBox::Position()
// ---------------------------------------------------------------------------
//
TPoint CBox::Position() const
    {
    return iPosition;
    }

// ---------------------------------------------------------------------------
// CBox::Compare()
// ---------------------------------------------------------------------------
//
TBool CBox::Compare( const CBox& aFirst, const CBox& aSecond )
    {
    if ( aFirst.Position() == aSecond.Position() )
        {
        return ETrue;
        }
    return EFalse;
    }

// ---------------------------------------------------------------------------
// CBox::ConstructL()
// ---------------------------------------------------------------------------
//
void CBox::ConstructL()
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CBox::CBox()
// ---------------------------------------------------------------------------
//
CBox::CBox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos ) 
: iObserver( aObs ), iHelper( aHelper ), iPosition( aPos )
    {
    // no implementation required
    }

// End of file
