/* ====================================================================
 * File: Blackbox.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <bitstd.h>
#include <Blackbox_scene.mbg>
#include "Blackbox.h"
#include "BoxObserver.h"
#include "BoxHelper.h"
#include "BlackboxConfig.h"
#include "Blackbox.hrh"

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CBlackbox::NewL()
// ---------------------------------------------------------------------------
//
CBlackbox* CBlackbox::NewL( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos )
    {
    CBlackbox* self = new ( ELeave ) CBlackbox( aObs, aHelper, aPos );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CBlackbox::~CBlackbox()
// ---------------------------------------------------------------------------
//
CBlackbox::~CBlackbox()
    {
    // no implementation required
    }

// ---------------------------------------------------------------------------
// CBlackbox::OnDraw()
// ---------------------------------------------------------------------------
//
void CBlackbox::OnDraw()
    {
    TInt bitmap(0), mask(0);
    switch ( iBlackboxState )
        {
        case EUnguess:
            bitmap = EMbmBlackbox_sceneUnguess;
            mask = EMbmBlackbox_sceneUnguess_mask;
            break;
        case EGuessing:
            bitmap = EMbmBlackbox_sceneGuessing;
            mask = EMbmBlackbox_sceneGuessing_mask;
            break;
        case EGuessFailed:
            bitmap = EMbmBlackbox_sceneGuessfailed;
            mask = EMbmBlackbox_sceneGuessfailed_mask;
            break;
        case EGuessed:
            bitmap = EMbmBlackbox_sceneGuessed;
            mask = EMbmBlackbox_sceneGuessed_mask;
            break;
        default:
            break;
        }
    
    TRect theRect;
    theRect = iHelper.BoxRect( iPosition.iX, iPosition.iY );
    iHelper.BmpContext().SetBrushStyle( CGraphicsContext::ENullBrush );

    iHelper.BmpContext().BitBlt( 
            theRect.iTl,
            iHelper.Bitmap( bitmap ),
            TRect( TPoint( 0, 0 ), theRect.Size() )
            );
    }

// ---------------------------------------------------------------------------
// CBlackbox::UpdateStateL()
// ---------------------------------------------------------------------------
//
void CBlackbox::UpdateStateL( TInt aState )
    {
    iBlackboxState = (TBlackboxState)aState;
    iHelper.DoEffectL( iBlackboxState, iPosition.iX, iPosition.iY );
    
    switch ( aState )
        {
        case EGuessFailed:
            iObserver.StateChangedL( ESceneGuessFailed );
            break;
        case EGuessed:
            iObserver.StateChangedL( ESceneGuessSuccess );
            break;
        default:
            break;
        }
    }

// ---------------------------------------------------------------------------
// CBlackbox::State()
// ---------------------------------------------------------------------------
//
TInt CBlackbox::State() const
    {
    return iBlackboxState;
    }

// ---------------------------------------------------------------------------
// CBlackbox::TriggerL()
// ---------------------------------------------------------------------------
//
void CBlackbox::TriggerL()
    {
    if ( iBlackboxState == EUnguess || iBlackboxState == EGuessing )
        {
        if ( iBlackboxState == EGuessing )
            {
            UpdateStateL( EUnguess );
            iObserver.StateChangedL( ESceneGuessRemoved );
            }
        else
            {
            if ( iHelper.Settings().iGuessType == EAllAtATime )
                {
                TInt x = 0, y = 0;
                for ( TInt i = 1; i < KHorizBoxNumber - 1; i++ )
                    for ( TInt j = 1; j < KVerticalBoxNumber - 1; j++ )
                        {
                        CBox* box = iHelper.Box( i, j );
                        if ( box && box->State() == EGuessing )
                            {
                            x = i;
                            y = j;
                            break;
                            }
                        }

                if ( x != 0 && y != 0 )
                    {
                    iHelper.Box( x, y )->UpdateStateL( EUnguess );
                    iObserver.StateChangedL( ESceneGuessTransfered );
                    }
                else
                    {
                    iObserver.StateChangedL( ESceneGuessCompleted );
                    }

                UpdateStateL( EGuessing );
                iObserver.StateChangedL( ESceneGuessAdded );
                }
            else
                {
                TInt numberOfNodes = 0;
                for ( TInt i = 1; i < KHorizBoxNumber - 1; i++ )
                    for ( TInt j = 1; j < KVerticalBoxNumber - 1; j++ )
                        {
                        CBox* box = iHelper.Box( i, j );
                        if ( box && box->State() == EGuessing )
                            {
                            ++numberOfNodes;
                            }
                        }
                
                if ( iHelper.Settings().iNumberOfNodes > numberOfNodes )
                    {
                    UpdateStateL( EGuessing );
                    iObserver.StateChangedL( ESceneGuessAdded );

                    ++numberOfNodes;
                    if ( iHelper.Settings().iNumberOfNodes == numberOfNodes )
                        {
                        iObserver.StateChangedL( ESceneGuessCompleted );
                        }
                    }
                else
                    {
                    iObserver.StateChangedL( ESceneMaxNodesOverflow );
                    }
                }
            }
        }
    }

// ---------------------------------------------------------------------------
// CBlackbox::ConstructL()
// ---------------------------------------------------------------------------
//
void CBlackbox::ConstructL()
    {
    CBox::ConstructL();
    }

// ---------------------------------------------------------------------------
// CBlackbox::CBlackbox()
// ---------------------------------------------------------------------------
//
CBlackbox::CBlackbox( MBoxObserver& aObs, MBoxHelper& aHelper, const TPoint& aPos )
: CBox( aObs, aHelper, aPos )
    {
    // no implementation required
    }


// End of file
