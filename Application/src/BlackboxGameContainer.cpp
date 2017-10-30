/* ====================================================================
 * File: CBlackboxGameContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknutils.h>
#include <AknsSkinInstance.h>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <AknsControlContext.h>
#include <AknsBasicBackgroundControlContext.h>
#include <stringloader.h>
#include <Blackbox.rsg>
#include "BlackboxGameContainer.h"
#include "BlackboxGameView.h"
#include "ScenePane.h"
#include "AvatarPane.h"
#include "ScorePane.h"
#include "LayoutManager.h"
#include "Blackbox.hrh"

// CONSTANTS
const TInt KDoDelayTimeout = 0;
const TInt KDoFrameUpdateTimeout = 100000;

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxGameContainer* CBlackboxGameContainer::NewL( 
        const TRect& aRect, CBlackboxGameView& aView )
    {
    CBlackboxGameContainer* self = CBlackboxGameContainer::NewLC( aRect, aView );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxGameContainer* CBlackboxGameContainer::NewLC( 
        const TRect& aRect, CBlackboxGameView& aView )
    {
    CBlackboxGameContainer* self = new ( ELeave ) CBlackboxGameContainer( aView );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::~CBlackboxGameContainer()
// Destructor
// -----------------------------------------------------------------------------
//
CBlackboxGameContainer::~CBlackboxGameContainer()
    {
    Stop();
    ReleaseBmpBuffer();
    delete iScenePane;
    delete iAvatarPane;
    delete iScorePane;
    delete iLayoutManager;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::HandleCommandL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameContainer::HandleCommandL( TInt aCommand )
    {
    switch( aCommand )
        {
        case ESceneRestartCmd:
            {
            iSettings.InternalizedL();
            iAvatarPane->SetAvatar( iSettings.iAvatar );
            iScorePane->Reset();

            iAvatarPane->TalkL( CAvatarPane::ETalkOpening);
            }
            break;

        case ESceneSetScoreGuessCmd:
            {
            iScorePane->SetGuess();
            }
            break;

        case ESceneSetScoreGuessingCmd:
            {
            iScorePane->SetGuessing();
            }
            break;

        case ESceneSetScoreGuessSuccessCmd:
            {
            iScorePane->SetGuessSuccess();
            }
            break;

        case ESceneGuessCmd:
        case ESceneSkipGuessCmd:
        case ESceneSolvePuzzleCmd:
        case ESceneUpdateSettingsCmd:
        default:
            break;
        }

    iScenePane->HandleCommandL( aCommand );
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CBlackboxGameContainer::CountComponentControls() const
    {
    TInt count = 0;

    if ( iScenePane )
        {
        count++;
        }

    if ( iAvatarPane )
        {
        count++;
        }
    
    if ( iScorePane )
        {
        count++;
        }
    
    return count;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CBlackboxGameContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0:
            return iScenePane;
        case 1:
            return iAvatarPane;
        case 2:
            return iScorePane;
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CBlackboxGameContainer::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetBrushColor( KRgbBlack );
    gc.SetBrushStyle( CGraphicsContext::ESolidBrush );
    gc.Clear();
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        iLayoutManager->ResolutionChanged();
        SetRect( iGameView.ClientRect() );
        }
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::SizeChanged
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::SizeChanged()
    {
    TRAP_IGNORE( CreateBmpBufferL() );
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::StateChangedL
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::StateChangedL( TInt aNewState )
    {
    switch( aNewState )
        {
        case ESceneMaxRaysOverflow:
            {
            iAvatarPane->TalkL( _L( "You have no more rays to shoot!" ) );
            }
            break;

        case ESceneMaxNodesOverflow: // fall through
        case ESceneLightboxActivated: // fall through
        case ESceneBlackboxActivated: // fall through
            break;

        case ESceneGuessCompleted:
            {
            iGameView.SwitchToolbarL();
            }
            break;

        case ESceneGuessAdded:
            {
            iScorePane->AddGuess();
            }
            break;

        case ESceneGuessRemoved:
            {
            iScorePane->RemoveGuess();
            iGameView.SwitchToolbarL();
            }
            break;

        case ESceneGuessTransfered:
            {
            iScorePane->RemoveGuess();
            }
            break;

        case ESceneGuessFailed:
            {
            iAvatarPane->TalkL( CAvatarPane::ETalkCriticism );

            if ( iSettings.iGuessType == EAllAtATime )
                {
                iScorePane->RemoveGuess();
                }
            }
            break;

        case ESceneGuessSuccess:
            {
            iAvatarPane->TalkL( CAvatarPane::ETalkPraise );

            iScorePane->SetGuessSuccess();
            }
            break;

        case ESceneRaysCreated:
            {
            iGameView.EnableToolbarL();
            iScorePane->AddRay();
            }
            break;

        case ESceneGameOver:
            {
            iAvatarPane->TalkL( CAvatarPane::ETalkCongratulate );

            iScenePane->HandleCommandL( ESceneSolvePuzzleCmd );
            
            iGameView.SetItemDimmed( EBlackSolvePuzzleCmd, ETrue );
            }
            break;

        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxGameContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();

    SetRect( aRect );
    
    iSettings.InternalizedL();
    
    iLayoutManager = CLayoutManager::NewL();
    iLayoutManager->ResolutionChanged();

    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KDoDelayTimeout,
            KDoFrameUpdateTimeout,
            TCallBack( TimerCallback, this ) );

    iScenePane = CScenePane::NewL( *iBmpBufferContext, *this );
    iScenePane->SetContainerWindowL( *this );

    iAvatarPane = CAvatarPane::NewL( *iBmpBufferContext );
    iAvatarPane->SetContainerWindowL( *this );
    iAvatarPane->SetAvatar( iSettings.iAvatar );

    iScorePane = CScorePane::NewL( *iBmpBufferContext, iSettings );
    iScorePane->SetContainerWindowL( *this );
    
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CBlackboxGameContainer::CBlackboxGameContainer()
// -----------------------------------------------------------------------------
//
CBlackboxGameContainer::CBlackboxGameContainer( CBlackboxGameView& aView )
: iGameView( aView )
    {
    // no implementation required
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::CreateBmpBufferL
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::CreateBmpBufferL()
    {
    // If double buffer resouces has been created, 
    // release them at first.
    ReleaseBmpBuffer();

    TSize size = Size();
    
    // Create double buffer bitmap
    iBmpBuffer = new (ELeave) CFbsBitmap;
    //User::LeaveIfError( iBmpBuffer->Create( Size(), EColor16MAP ) );
    User::LeaveIfError( iBmpBuffer->Create( Size(), EColor16MA ) );

    // Create double buffer graphics context
    iBmpBufferDevice = CFbsBitmapDevice::NewL( iBmpBuffer );
    User::LeaveIfError( iBmpBufferDevice->CreateContext( iBmpBufferContext ) );
    iBmpBufferContext->SetPenStyle( CGraphicsContext::ESolidPen );
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::ReleaseBmpBuffer
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::ReleaseBmpBuffer()
    {
    delete iBmpBufferContext;
    iBmpBufferContext = NULL;
    delete iBmpBufferDevice;
    iBmpBufferDevice = NULL;
    delete iBmpBuffer;
    iBmpBuffer = NULL;
    }

// ----------------------------------------------------------------------------
// CScenePane::Stop
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::Stop()
    {
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        iPeriodic = NULL;   
        }
    }

// ----------------------------------------------------------------------------
// CScenePane::DoFrame
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::DoFrame()
    {
    Window().Invalidate( Rect() );
    ActivateGc();
    Window().BeginRedraw( Rect() );
    OnDraw();
    CWindowGc& gc = SystemGc();
    gc.BitBlt( TPoint( 0, 0 ), iBmpBuffer );
    Window().EndRedraw();
    DeactivateGc();
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::Stop
// ----------------------------------------------------------------------------
//
TInt CBlackboxGameContainer::TimerCallback( TAny* aPtr )
    {
    CBlackboxGameContainer* self = static_cast<CBlackboxGameContainer*> ( aPtr );
    self->DoFrame();
    return 0;
    }

// ----------------------------------------------------------------------------
// CBlackboxGameContainer::DoDraw
// ----------------------------------------------------------------------------
//
void CBlackboxGameContainer::OnDraw()
    {
    iBmpBufferContext->SetPenColor( KRgbBlack );
    iBmpBufferContext->SetPenStyle( CGraphicsContext::ESolidPen );
    iBmpBufferContext->SetBrushColor( KRgbBlack );
    iBmpBufferContext->SetBrushStyle( CGraphicsContext::ESolidBrush );
    iBmpBufferContext->Clear( TRect( TPoint( 0, 0 ), Rect().Size() ) );

    iScenePane->OnDraw();
    iScorePane->OnDraw();
    iAvatarPane->OnDraw();
    }

// End of File
