/* ====================================================================
 * File: BlackboxGameView.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h>
#include <AknQueryDialog.h>
#include <Blackbox.rsg>
#include "BlackboxGameView.h"
#include "BlackboxGameContainer.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"
#include "TipsManager.h"
#include "Tips.h"

// Constants

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxGameView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxGameView* CBlackboxGameView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxGameView* self = CBlackboxGameView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxGameView* CBlackboxGameView::NewLC( CBlackboxAppUi& aAppUi )
    {
    CBlackboxGameView* self = new ( ELeave ) CBlackboxGameView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::~CBlackboxGameView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxGameView::~CBlackboxGameView()
    {
    delete iIdle;
    delete iDimmedIdle;
    delete iContainer;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::SetToolbarL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::SetToolbarL( TToolbarState aState )
    {
    if ( !iIdle->IsActive() )
        {
        iToolbarState = aState;
        TCallBack callback( ToolbarCallback, this );
        iIdle->Start( callback );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::DisableToolbarL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::DisableToolbarL()
    {
    switch ( iToolbarState )
        {
        case EToolbarGuess:
            SetToolbarL( EToolbarGuessDisabled );
            break;
        case EToolbarGuessDisabled:
            break;
        case EToolbarSkip:
            SetToolbarL( EToolbarSkipDisabled );
            break;
        case EToolbarSkipDisabled:
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::EnableToolbarL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::EnableToolbarL()
    {
    switch ( iToolbarState )
        {
        case EToolbarGuess:
            break;
        case EToolbarGuessDisabled:
            SetToolbarL( EToolbarGuess );
            break;
        case EToolbarSkip:
            break;
        case EToolbarSkipDisabled:
            SetToolbarL( EToolbarSkip );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::SwitchToolbarL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::SwitchToolbarL()
    {
    switch ( iToolbarState )
        {
        case EToolbarGuess:
            SetToolbarL( EToolbarSkip );
            break;
        case EToolbarGuessDisabled:
            SetToolbarL( EToolbarSkipDisabled );
            break;
        case EToolbarSkip:
            SetToolbarL( EToolbarGuess );
            break;
        case EToolbarSkipDisabled:
            SetToolbarL( EToolbarGuessDisabled );
            break;
        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::SetItemDimmed()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::SetItemDimmed( TInt aItemId, TBool aDimmed )
    {
    if ( !iDimmedIdle->IsActive() )
        {
        iDimmedItemId = aItemId;
        iDimmed = aDimmed;
        TCallBack callback( DimmedCallback, this );
        iDimmedIdle->Start( callback );
        }
    else
        {
        CAknToolbar* toolbar = Toolbar();
        if( toolbar )
            {
            toolbar->SetItemDimmed( aItemId, aDimmed, ETrue );
            }
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::ToolbarState()
// -----------------------------------------------------------------------------
//
TToolbarState CBlackboxGameView::ToolbarState() const
    {
    return iToolbarState;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxGameView::Id() const
    {
    return TUid::Uid( EBlackboxGameViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::DoActivateL( const TVwsViewId& aPrevViewId,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if ( iContainer )
        {
        if ( aPrevViewId.iViewUid.iUid == EBlackboxWelcomeViewId )
            {
            /* Removes flicker on game toolbar */
            iToolbarState = EToolbarSkipDisabled;
            ShowToolbarL();

            iDimmedItemId = EBlackSolvePuzzleCmd;
            iDimmed = EFalse;
            DoItemDimmed();
            /* End */

            iContainer->HandleCommandL( ESceneUpdateSettingsCmd );
            iContainer->HandleCommandL( ESceneRestartCmd );
            }

        iContainer->MakeVisible( ETrue );
        AppUi()->AddToViewStackL( *this, iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::DoDeactivate()
    {
    if ( iContainer )
        {
        iContainer->MakeVisible( EFalse );
        // Remove View1's container form controllStack
        AppUi()->RemoveFromStack( iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            {
            // Clear container earlier to prevent flicker
            iContainer->HandleCommandL( ESceneRestartCmd );
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxWelcomeViewId ) );
            }
            break;

        case EBlackboxRestartCmd:
            {
            iContainer->HandleCommandL( ESceneRestartCmd );
            SetToolbarL( EToolbarSkipDisabled );
            SetItemDimmed( EBlackSolvePuzzleCmd, EFalse );
            }
            break;

        case EBlackboxUserGuideCmd:
            {
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxHelpViewId ) );
            }
            break;
        
        case EBlackboxAboutCmd:
            {
            iAppUi.ShowAboutDialogL();
            }
            break;

        default:
            {
            Panic( EBlackboxBadCommand);
            }
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::HandleSizeChange( TInt aType )
    {
    if( iContainer )
        {
        iContainer->HandleResourceChange( aType );
        
        if ( aType == KEikDynamicLayoutVariantSwitch )
            {        
            TRect rect;
            AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
            iContainer->SetRect(rect);
            }
        }         
    }

// ---------------------------------------------------------------------------
// CBlackboxGameView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxGameView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::DynInitToolbarL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::DynInitToolbarL( TInt /*aResourceId*/, 
                                      CAknToolbar* /*aToolbar*/ )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::OfferToolbarEventL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::OfferToolbarEventL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EBlackboxGuessCmd:
            {
            iContainer->HandleCommandL( ESceneGuessCmd );
            SetToolbarL( EToolbarSkipDisabled );
            }
            break;

        case EBlackboxSkipGuessCmd:
            {
            SetToolbarL( EToolbarSkipDisabled );
            }
            break;

        case EBlackSolvePuzzleCmd:
            {
            iContainer->HandleCommandL( ESceneSolvePuzzleCmd );
            DisableToolbarL();
            SetItemDimmed( EBlackSolvePuzzleCmd, ETrue );
            }
            break;

        case EBlackboxTipsCmd:
            {
            CTipsManager* tipsMan = iAppUi.TipsManager();
            HBufC* tipsText = tipsMan->Tips()->ShortTipsText();
            
            CAknQueryDialog* query = new(ELeave) CAknQueryDialog;
            query->SetPromptL( *tipsText );
            
            
            TBool result = query->ExecuteLD( R_BLACKBOX_TIPS_DIALOG );
            if ( result )
                {
                AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxTipsViewId ) );
                }
            else
                {
                tipsMan->Next();
                }
            }
            break;

        default:
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_GAME_VIEW );

    iIdle = CIdle::New( CActive::EPriorityUserInput );
    iDimmedIdle = CIdle::New( CActive::EPriorityStandard );
    
    iContainer = CBlackboxGameContainer::NewL( ClientRect(), *this );

    CAknToolbar* toolbar = Toolbar();
    if( toolbar )
        {
        toolbar->SetToolbarObserver( this );
        }

    //SetToolbarL( EToolbarSkipDisabled );
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::CBlackboxGameView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxGameView::CBlackboxGameView( CBlackboxAppUi& aAppUi )
 : iAppUi( aAppUi )
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::ToolbarCallback()
// -----------------------------------------------------------------------------
//
TInt CBlackboxGameView::ToolbarCallback( TAny* aPtr )
    {
    CBlackboxGameView* self = static_cast<CBlackboxGameView*> ( aPtr );
    TRAP_IGNORE( self->ShowToolbarL() );
    return 0;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::ShowToolbarL()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::ShowToolbarL()
    {
    switch( iToolbarState )
        {
        case EToolbarGuess:
            CreateAndSetToolbarL( R_BLACKBOX_GAME_TOOLBAR );
            iContainer->HandleCommandL( ESceneSetScoreGuessingCmd );
            break;
        case EToolbarGuessDisabled:
            CreateAndSetToolbarL( R_BLACKBOX_GAME_TOOLBAR );
            SetItemDimmed( EBlackboxGuessCmd, ETrue );
            iContainer->HandleCommandL( ESceneSetScoreGuessCmd );
            break;
        case EToolbarSkip:
            CreateAndSetToolbarL( R_BLACKBOX_GAME_TOOLBAR2 );
            iContainer->HandleCommandL( ESceneSetScoreGuessCmd );
            break;
        case EToolbarSkipDisabled:
            CreateAndSetToolbarL( R_BLACKBOX_GAME_TOOLBAR2 );
            SetItemDimmed( EBlackboxSkipGuessCmd, ETrue );
            iContainer->HandleCommandL( ESceneSetScoreGuessCmd );
            break;
        default:
            break;
        }

    CAknToolbar* toolbar = Toolbar();
    if( toolbar )
        {
        toolbar->SetToolbarObserver( this );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::DimmedCallback()
// -----------------------------------------------------------------------------
//
TInt CBlackboxGameView::DimmedCallback( TAny* aPtr )
    {
    CBlackboxGameView* self = static_cast<CBlackboxGameView*> ( aPtr );
    self->DoItemDimmed();
    return 0;
    }

// -----------------------------------------------------------------------------
// CBlackboxGameView::DoItemDimmed()
// -----------------------------------------------------------------------------
//
void CBlackboxGameView::DoItemDimmed()
    {
    CAknToolbar* toolbar = Toolbar();
    if( toolbar )
        {
        toolbar->SetItemDimmed( iDimmedItemId, iDimmed, ETrue );
        }
    }

// End of File
