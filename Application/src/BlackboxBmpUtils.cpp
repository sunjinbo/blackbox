/* ====================================================================
 * File: BlackboxBmpUtils.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <akniconutils.h>
#include <fbs.h>
#include "BlackboxBmpUtils.h"
#include "Blackbox.pan"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::NewL
//
// ----------------------------------------------------------------------------
//
CBlackboxBmpUtils* CBlackboxBmpUtils::NewL( const TDesC& aFileName, TInt aFrom, TInt aTo  )
    {
    CBlackboxBmpUtils* self = new(ELeave) CBlackboxBmpUtils( aFrom, aTo );
    CleanupStack::PushL( self );
    self->ConstructL( aFileName );
    CleanupStack::Pop( self );
    return self;
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::~CBlackboxBmpUtils
//
// ----------------------------------------------------------------------------
//
CBlackboxBmpUtils::~CBlackboxBmpUtils()
    {
    iBitmapArray.ResetAndDestroy();
    delete iFileName;
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::SetSize
//
// ----------------------------------------------------------------------------
//
void CBlackboxBmpUtils::SetSize( TInt aIndex, TSize aSize )
    {
    CFbsBitmap* bitmap = Bitmap( aIndex );
    if ( bitmap )
        {
        AknIconUtils::SetSize( bitmap, aSize, EAspectRatioNotPreserved );
        }
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::Rotate
//
// ----------------------------------------------------------------------------
//
void CBlackboxBmpUtils::SetSizeAndRotation( TInt aIndex, TSize aSize, TInt aAngle )
    {
    CFbsBitmap* bitmap( Bitmap( aIndex ) );

    AknIconUtils::SetSizeAndRotation ( 
            bitmap, 
            aSize, 
            EAspectRatioNotPreserved, 
            aAngle 
            );
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::Bitmap
//
// ----------------------------------------------------------------------------
//
CFbsBitmap* CBlackboxBmpUtils::Bitmap( TInt aIndex ) const
    {
    TInt index = aIndex - iFrom;
    __ASSERT_ALWAYS( ( index >= 0 ) && ( index < iBitmapArray.Count() ), Panic( EBlackboxBadIndex ) );
    return iBitmapArray[ index ];
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::CBlackboxBmpUtils
//
// ----------------------------------------------------------------------------
//
CBlackboxBmpUtils::CBlackboxBmpUtils( TInt aFrom, TInt aTo  )
    : iFrom( aFrom ), iTo( aTo )
    { // no implementation required.
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::ConstructL
//
// ----------------------------------------------------------------------------
//
void CBlackboxBmpUtils::ConstructL( const TDesC& aFileName )
    {
    iFileName = HBufC::NewL( aFileName.Length() );
    TPtr fileName( iFileName->Des() );
    fileName.Append( aFileName );
    LoadBitmapL();
    }

// ----------------------------------------------------------------------------
// CBlackboxBmpUtils::LoadBitmapL
//
// ----------------------------------------------------------------------------
//
void CBlackboxBmpUtils::LoadBitmapL ()
    {
    for (TInt index = iFrom ; index < iTo ; index++ )
        {
        CFbsBitmap* bitmap = AknIconUtils::CreateIconL( *iFileName, index );
        iBitmapArray.Append( bitmap );
        }
    }

// End of File
