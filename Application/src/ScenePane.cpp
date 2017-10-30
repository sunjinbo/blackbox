/* ====================================================================
 * File: ScenePane.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32property.h>
#include <Blackbox_effects.mbg>
#include "ScenePane.h"
#include "LayoutManager.h"
#include "SceneTaskScheduler.h"
#include "SceneTask.h"
#include "SceneObserver.h"
#include "SceneModel.h"
#include "BlackboxConfig.h"
#include "Blackbox.hrh"
#include "BlackboxBmpUtils.h"
#include "BlackboxPSKeys.h"

// CONSTANTS
const TInt KInvalidEffectType = 0;

#if defined( __WINS__ )
_LIT( KEffectsFileName, "Z:\\resource\\apps\\Blackbox_effects.mbm" );
#else
_LIT( KEffectsFileName, "\\resource\\apps\\Blackbox_effects.mbm" );
#endif // __WINS__

// ============================ MEMBER FUNCTIONS ===============================

// ---------------------------------------------------------------------------
// CScenePane::NewL()
// ---------------------------------------------------------------------------
//
CScenePane* CScenePane::NewL( CFbsBitGc& aBmpContext, MSceneObserver& aObserver )
    {
    CScenePane* self = new ( ELeave ) CScenePane( aBmpContext, aObserver );
    CleanupStack::PushL( self );
    self->ConstructL();
    CleanupStack::Pop( self );
    return self;
    }

// ---------------------------------------------------------------------------
// CScenePane::~CScenePane()
// ---------------------------------------------------------------------------
//
CScenePane::~CScenePane()
    {
    delete iLayoutManager;
    delete iScheduler;
    delete iModel;
    delete iBmpUtils;
    }

// ----------------------------------------------------------------------------
// CScenePane::DoDraw
// ----------------------------------------------------------------------------
//
void CScenePane::OnDraw()
    {
    iModel->OnDraw();
    iScheduler->OnDraw();
    }

// ----------------------------------------------------------------------------
// CScenePane::HandleCommandL
// ----------------------------------------------------------------------------
//
void CScenePane::HandleCommandL( TInt aCommand )
    {
    switch( aCommand )
        {
        case ESceneGuessCmd:
        case ESceneSkipGuessCmd:
            break;
        case ESceneSolvePuzzleCmd:
            iGameOver = ETrue;
            break;
        case ESceneRestartCmd:
            iGameOver = EFalse;
            break;
        case ESceneUpdateSettingsCmd:
            break;
        default:
            break;
        }
    iModel->HandleCommandL( aCommand );
    }

// ----------------------------------------------------------------------------
// CScenePane::HandlePointerEventL
// ----------------------------------------------------------------------------
//
void CScenePane::HandlePointerEventL(const TPointerEvent& aPointerEvent)
    {
    if ( aPointerEvent.iType == TPointerEvent::EButton1Up )
        {
        if ( !iGameOver && Rect().Contains( aPointerEvent.iPosition ) )
            {
            TInt w = Rect().Width() / KHorizBoxNumber;
            TInt h = Rect().Height() / KVerticalBoxNumber;
            TInt x = aPointerEvent.iPosition.iX / w;
            TInt y = aPointerEvent.iPosition.iY / h;
            iModel->TriggerL( x, y );
            }
        }
    }

// ---------------------------------------------------------------------------
// CScenePane::StateChangedL()
// ---------------------------------------------------------------------------
//
void CScenePane::StateChangedL( TInt aNewState )
    {
    iObserver.StateChangedL( aNewState );
    }

// ---------------------------------------------------------------------------
// CScenePane::DoEffectL()
// ---------------------------------------------------------------------------
//
void CScenePane::DoEffectL( TInt aEffectType, TInt aX, TInt aY )
    {
    if ( aEffectType > KInvalidEffectType )
        {
        CSceneTask* task = CSceneTask::NewL( *this, *iScheduler );
        task->SetRect( iModel->BoxRect( aX, aY ) );
        task->SetUtils( iBmpUtils );
        task->SetTaskType( (TSceneTaskType)aEffectType );
        iScheduler->AddTask( task );
        }
    }

// ---------------------------------------------------------------------------
// CScenePane::ConstructL()
// ---------------------------------------------------------------------------
//
void CScenePane::ConstructL()
    {
    // Create a window for this application view
    CreateWindowL();
    
    iLayoutManager = CLayoutManager::NewL();
    TRect theRect( iLayoutManager->LayoutRect( EScenePane ) );
    SetRect( theRect );

    iModel = CSceneModel::NewL( *this, iBmpContext, theRect );

    iBmpUtils = CBlackboxBmpUtils::NewL( 
            KEffectsFileName,
            EMbmBlackbox_effectsGuessed01,
            EMbmBlackbox_effectsLastElement );

    ScaleBmpUtils();

    TInt err = RProperty::Set( 
                        KPSUidBlackbox, 
                        KBlackboxStartupStatus, 
                        EStartupScaleScoreImagesDone 
                        );
    User::LeaveIfError( err );

    iScheduler = CSceneTaskScheduler::NewL();

    DrawableWindow()->SetOrdinalPosition( 0 );
    
#if defined ( __S60_50__ )
    // Enables handling of drag events
    EnableDragEvents();
#endif // __S60_50__

    // Activate the window, which makes it ready to be drawn
    ActivateL();
    }

// ---------------------------------------------------------------------------
// CScenePane::CScenePane()
// ---------------------------------------------------------------------------
//
CScenePane::CScenePane( CFbsBitGc& aBmpContext, MSceneObserver& aObserver )
: iBmpContext( aBmpContext ), iObserver( aObserver )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CScenePane::ScaleBmpUtils
// ----------------------------------------------------------------------------
//
void CScenePane::ScaleBmpUtils()
    {
    TInt w = Rect().Width() / KHorizBoxNumber;
    TInt h = Rect().Height() / KVerticalBoxNumber;
    
    for ( TInt i = EMbmBlackbox_effectsGuessed01; i < EMbmBlackbox_effectsLastElement; i++ )
        {
        iBmpUtils->SetSize( i, TSize( w, h ) );
        }
    }

// End of file
