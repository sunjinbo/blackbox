/* ====================================================================
 * File: Mirror.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32math.h>
#include <bitstd.h>
#include <Blackbox_scene.mbg>
#include "Mirror.h"
#include "SceneModel.h"

// CONSTANTS
const TInt KMirrorEffectTimeout = 150000;
const TInt KMirrorEffectNumber = 5;

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CRays::NewL()
// ---------------------------------------------------------------------------
//
CMirror* CMirror::NewL( CSceneModel& aModel, const TPoint& aPos )
    {
    CMirror* self = new ( ELeave ) CMirror( aModel, aPos );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CMirror::~CMirror()
// ---------------------------------------------------------------------------
//
CMirror::~CMirror()
    {
    delete iTimeout;
    }

// ---------------------------------------------------------------------------
// CMirror::Radius()
// ---------------------------------------------------------------------------
//
TInt CMirror::Radius() const
    {
    return 0;
    }

// ---------------------------------------------------------------------------
// CMirror::Position()
// ---------------------------------------------------------------------------
//
TPoint CMirror::Position() const
    {
    return iPosition;
    }

// ---------------------------------------------------------------------------
// CMirror::SetFullMirror()
// ---------------------------------------------------------------------------
//
void CMirror::SetFullMirror( TBool aFullMirror )
    {
    iFullMirror = aFullMirror;
    /*
    if ( iFullMirror )
        {
        iTimeout->Start( KFullMirrorEffectTimeout );
        }
    */
    }

// ---------------------------------------------------------------------------
// CMirror::IsFullMirror()
// ---------------------------------------------------------------------------
//
TBool CMirror::IsFullMirror() const
    {
    return iFullMirror;
    }

// ---------------------------------------------------------------------------
// CMirror::SetVisible()
// ---------------------------------------------------------------------------
//
void CMirror::SetVisible( TBool aVisible )
    {
    iVisible = aVisible;

    if ( iVisible )
        {
        if ( iGuessed )
            {
            iMirrorBitmapId = EMbmBlackbox_sceneMirror1;
            iMirrorMaskId = EMbmBlackbox_sceneMirror1_mask;
            }
        else
            {
            iMirrorBitmapId = EMbmBlackbox_sceneMirrorfailed1;
            iMirrorMaskId = EMbmBlackbox_sceneMirrorfailed1_mask;
            }
    
        TInt random = Rand( KMirrorEffectNumber - 1 );
        iMirrorBitmapId += ( 2 * random );
        iMirrorMaskId += ( 2 * random );

        iMirrorEffectRevert = ETrue;

        iTimeout->Start( KMirrorEffectTimeout );
        }
    }

// ---------------------------------------------------------------------------
// CMirror::IsVisible()
// ---------------------------------------------------------------------------
//
TBool CMirror::IsVisible() const
    {
    return iVisible;
    }

// ---------------------------------------------------------------------------
// CMirror::SetGuessed()
// ---------------------------------------------------------------------------
//
void CMirror::SetGuessed( TBool aGuessed )
    {
    iGuessed = aGuessed;
    }

// ---------------------------------------------------------------------------
// CMirror::IsGuessed()
// ---------------------------------------------------------------------------
//
TBool CMirror::IsGuessed() const
    {
    return iGuessed;
    }

// ---------------------------------------------------------------------------
// CMirror::OnDraw()
// ---------------------------------------------------------------------------
//
void CMirror::OnDraw()
    {
    TRect theRect;
    if ( iVisible )
        {
        theRect = iModel.BoxRect( iPosition.iX, iPosition.iY );
        iModel.BmpContext().SetPenStyle( CGraphicsContext::ENullPen );
        iModel.BmpContext().SetBrushStyle( CGraphicsContext::ENullBrush );
        /*
        iModel.BmpContext().BitBltMasked( 
                theRect.iTl,
                iModel.Bitmap( EMbmBlackbox_sceneMirror ),
                TRect( TPoint( 0, 0 ), theRect.Size() ),
                iModel.Bitmap( EMbmBlackbox_sceneMirror_mask ),
                ETrue
                );
        */
        iModel.BmpContext().BitBlt( 
                theRect.iTl,
                iModel.Bitmap( iMirrorBitmapId ),
                TRect( TPoint( 0, 0 ), theRect.Size() )
                );
        }

    if ( iFullMirror )
        {
        theRect.Grow( theRect.Size() );
        
        if ( iGuessed )
            {
            iModel.BmpContext().SetPenColor( TRgb( 149, 163, 6 ) );
            }
        else
            {
            iModel.BmpContext().SetPenColor( TRgb( 254, 12, 94 ) );
            }

        if ( iMirrorEffectRevert )
            {
            iModel.BmpContext().SetPenSize( TSize( 1,1 ) );
            }
        else
            {
            iModel.BmpContext().SetPenSize( TSize( 2,2 ) );
            }

        iModel.BmpContext().SetPenStyle( CGraphicsContext::ESolidPen );
        iModel.BmpContext().SetBrushStyle( CGraphicsContext::ENullBrush );
        iModel.BmpContext().DrawEllipse( theRect );
        }
    }

// ---------------------------------------------------------------------------
// CMirror::HandleTimeoutL()
// ---------------------------------------------------------------------------
//
void CMirror::HandleTimeoutL()
    {
    if ( iMirrorEffectRevert )
        {
        iMirrorBitmapId += 2;
        iMirrorMaskId += 2;
        
        if ( iGuessed )
            {
            if ( ( iMirrorBitmapId >= EMbmBlackbox_sceneMirror5 )
                    || ( iMirrorMaskId >= EMbmBlackbox_sceneMirror5_mask ) )
                {
                iMirrorEffectRevert = EFalse;
                }
            }
        else
            {
            if ( ( iMirrorBitmapId >= EMbmBlackbox_sceneMirrorfailed5 )
                    || ( iMirrorMaskId >= EMbmBlackbox_sceneMirrorfailed5_mask ) )
                {
                iMirrorEffectRevert = EFalse;
                }
            }
        }
    else
        {
        iMirrorBitmapId -= 2;
        iMirrorMaskId -= 2;

        if ( iGuessed )
            {
            if ( ( iMirrorBitmapId <= EMbmBlackbox_sceneMirror1 )
                    || ( iMirrorMaskId <= EMbmBlackbox_sceneMirror1_mask ) )
                {
                iMirrorEffectRevert = ETrue;
                }
            }
        else
            {
            if ( ( iMirrorBitmapId <= EMbmBlackbox_sceneMirrorfailed1 )
                    || ( iMirrorMaskId <= EMbmBlackbox_sceneMirrorfailed1_mask ) )
                {
                iMirrorEffectRevert = ETrue;
                }
            }
        }

    iTimeout->Start( KMirrorEffectTimeout );
    }

// ---------------------------------------------------------------------------
// CMirror::ConstructL()
// ---------------------------------------------------------------------------
//
void CMirror::ConstructL()
    {
    iTimeout = CRegistrationTimeout::NewL( *this );
    }

// ---------------------------------------------------------------------------
// CMirror::CMirror()
// ---------------------------------------------------------------------------
//
CMirror::CMirror( CSceneModel& aModel, const TPoint& aPos )
: iModel( aModel ), iPosition( aPos )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CMirror::Rand
// ----------------------------------------------------------------------------
//
TInt CMirror::Rand( TInt aRange ) const
    {
    return Math::Random() % aRange;
    }

// End of file
