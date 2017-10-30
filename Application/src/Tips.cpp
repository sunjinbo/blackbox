/* ====================================================================
 * File: Tips.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "Tips.h"
#include "Animation.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CTips::NewL()
// ---------------------------------------------------------------------------
//
CTips* CTips::NewL( TResourceReader& aReader )
    {
    CTips* self = new (ELeave)CTips;
    CleanupStack::PushL( self );
    self->ConstructL( aReader );
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CTips::~CTips()
// ---------------------------------------------------------------------------
//
CTips::~CTips()
    {
    delete iAnimation;
    delete iShortTipsText;
    delete iTipsText;
    }

// ---------------------------------------------------------------------------
// CTips::Compare()
// ---------------------------------------------------------------------------
//
TInt CTips::Compare( const CTips& aFirst, const CTips& aSecond )
    {
    if ( aFirst.Id() > aSecond.Id() )
        return 1; 
    if ( aFirst.Id() < aSecond.Id() )
        return -1;
    return 0;
    }

// ---------------------------------------------------------------------------
// CTips::Id()
// ---------------------------------------------------------------------------
//
TInt CTips::Id() const
    {
    return iId;
    }

// ---------------------------------------------------------------------------
// CTips::Animation()
// ---------------------------------------------------------------------------
//
CAnimation* CTips::Animation() const
    {
    return iAnimation;
    }

// ---------------------------------------------------------------------------
// CTips::ShortTipsText()
// ---------------------------------------------------------------------------
//
HBufC* CTips::ShortTipsText() const
    {
    return iShortTipsText;
    }

// ---------------------------------------------------------------------------
// CTips::TipsText()
// ---------------------------------------------------------------------------
//
HBufC* CTips::TipsText() const
    {
    return iTipsText;
    }

// ---------------------------------------------------------------------------
// CTips::AnimationPreparedL()
// ---------------------------------------------------------------------------
//
void CTips::AnimationPreparedL()
    {
    // Do nothing..
    }

// ---------------------------------------------------------------------------
// CTips::ConstructL()
// ---------------------------------------------------------------------------
//
void CTips::ConstructL( TResourceReader& aReader )
    {
    iId = aReader.ReadUint8();
    iShortTipsText = aReader.ReadHBufCL();
    iTipsText = aReader.ReadHBufCL();
    iAnimation = CAnimation::NewL( aReader, *this );
    }

// ---------------------------------------------------------------------------
// CTips::CTips()
// ---------------------------------------------------------------------------
//
CTips::CTips()
    {
    // no implementation required
    }

// End of file
