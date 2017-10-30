/* ====================================================================
 * File: Nookbox.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Blackbox_scene.mbg>
#include "Nookbox.h"
#include "BoxObserver.h"
#include "BoxHelper.h"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CNookbox::NewL()
// ---------------------------------------------------------------------------
//
CNookbox* CNookbox::NewL( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos )
    {
    CNookbox* self = new ( ELeave ) CNookbox( aObs, aHelper, aPos );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CNookbox::~CNookbox()
// ---------------------------------------------------------------------------
//
CNookbox::~CNookbox()
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CNookbox::OnDraw()
// ---------------------------------------------------------------------------
//
void CNookbox::OnDraw()
    {
    TRect theRect;
    theRect = iHelper.BoxRect( iPosition.iX, iPosition.iY );
    iHelper.BmpContext().SetPenStyle( CGraphicsContext::ESolidPen );
    iHelper.BmpContext().SetBrushStyle( CGraphicsContext::ENullBrush );
    /*
    iHelper.BmpContext().BitBltMasked( 
            theRect.iTl,
            iHelper.Bitmap( EMbmBlackbox_sceneNookbox ),
            TRect( TPoint( 0, 0 ), theRect.Size() ),
            iHelper.Bitmap( EMbmBlackbox_sceneNookbox_mask ),
            ETrue 
            );
    */
    iHelper.BmpContext().BitBlt( 
            theRect.iTl,
            iHelper.Bitmap( EMbmBlackbox_sceneNookbox ),
            TRect( TPoint( 0, 0 ), theRect.Size() )
            );
    }

// ---------------------------------------------------------------------------
// CNookbox::UpdateStateL()
// ---------------------------------------------------------------------------
//
void CNookbox::UpdateStateL( TInt /*aState*/ )
    {
    // no need to implementation required
    }

// ---------------------------------------------------------------------------
// CNookbox::State()
// ---------------------------------------------------------------------------
//
TInt CNookbox::State() const
    {
    return EInitState;
    }

// ---------------------------------------------------------------------------
// CNookbox::TriggerL()
// ---------------------------------------------------------------------------
//
void CNookbox::TriggerL()
    {

    }

// ---------------------------------------------------------------------------
// CNookbox::ConstructL()
// ---------------------------------------------------------------------------
//
void CNookbox::ConstructL()
    {
    CBox::ConstructL();
    }

// ---------------------------------------------------------------------------
// CNookbox::CNookbox()
// ---------------------------------------------------------------------------
//
CNookbox::CNookbox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos )
: CBox( aObs, aHelper, aPos )
    {
    // no implementation required
    }

// End of file
