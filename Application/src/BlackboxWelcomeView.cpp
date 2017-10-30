/* ====================================================================
 * File: BlackboxWelcomeView.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h>
#include <StringLoader.h>
#include <Blackbox.rsg>
#include "BlackboxWelcomeView.h"
#include "BlackboxWelcomeContainer.h"
#include "QueryDialog.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"
#include "BlackboxGameView.h"
#include "BlackboxSettings.h"
#include "BlackboxUtils.h"

#include "Logger.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeView* CBlackboxWelcomeView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxWelcomeView* self = CBlackboxWelcomeView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeView* CBlackboxWelcomeView::NewLC(CBlackboxAppUi& aAppUi)
    {
    CBlackboxWelcomeView* self = new ( ELeave ) CBlackboxWelcomeView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::~CBlackboxWelcomeView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeView::~CBlackboxWelcomeView()
    {
    delete iIdle;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxWelcomeView::Id() const
    {
    return TUid::Uid( EBlackboxWelcomeViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::HandleCommandL()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            AppUi()->Exit();
            break;

        case EBlackboxStartCmd:
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxGameViewId ) );
            break;
        
        case EBlackboxOviCmd:
            iAppUi.LaunchBrowserL();
            break;

        case EBlackboxSettingsCmd:
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxSettingsViewId ) );
            break;

        case EBlackboxUserGuideCmd:
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxHelpViewId ) );
            break;

        case EBlackboxAboutCmd:
            iAppUi.ShowAboutDialogL();
            break;

        default:
            Panic( EBlackboxBadCommand);
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    INFO( "CBlackboxWelcomeView::DoActivateL()" )
    if ( !iContainer )
        {
        INFO( "Start to creating container.." )
        iContainer = CBlackboxWelcomeContainer::NewL( ClientRect(), *this );
        INFO( "The creation of Container was done!!" )
        AppUi()->AddToViewStackL( *this, iContainer );

        if ( iIdle )
            {
            iIdle->Start( TCallBack( CBlackboxWelcomeView::WelcomeCallback, this ) );
            }
        }
    INFO( "CBlackboxWelcomeView::DoActivateL() - End" )
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeView::DoDeactivate()
    {
    INFO( "CBlackboxWelcomeView::DoDeactivate()" )
    if ( iContainer )
        {
        // Remove View1's container form controllStack
        AppUi()->RemoveFromStack( iContainer );
        delete iContainer;
        iContainer = NULL;
        }
    INFO( "CBlackboxWelcomeView::DoDeactivate() - End" )
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeView::HandleSizeChange( TInt aType )
    {
    if( iContainer )
        {
        iContainer->HandleResourceChange( aType );
        
        if ( aType==KEikDynamicLayoutVariantSwitch )
            {        
            TRect rect;
            AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
            iContainer->SetRect( rect );
            }
        }         
    }

// ---------------------------------------------------------------------------
// CBlackboxWelcomeView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxWelcomeView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// ---------------------------------------------------------------------------
// CBlackboxWelcomeView::HyperLinkControlTappedL
// ---------------------------------------------------------------------------
//
void CBlackboxWelcomeView::HyperLinkControlTappedL()
    {
	AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxHelpViewId ) );
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_WELCOME_VIEW );
    
    TBlackboxSettings settings;
    settings.InternalizedL();

    if ( settings.iFirstTimeUse )
        {
        iIdle = CIdle::New( CActive::EPriorityStandard );

        settings.iFirstTimeUse = EFalse;
        settings.ExternalizedL();
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::CBlackboxWelcomeView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxWelcomeView::CBlackboxWelcomeView( CBlackboxAppUi& aAppUi)
    : iAppUi( aAppUi )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::WelcomeCallback()
// -----------------------------------------------------------------------------
//
TInt CBlackboxWelcomeView::WelcomeCallback( TAny* aPtr )
    {
    CBlackboxWelcomeView* self = static_cast<CBlackboxWelcomeView*> ( aPtr );
    TRAP_IGNORE( self->ShowWelcomeNoteL() );
    return 0;
    }

// -----------------------------------------------------------------------------
// CBlackboxWelcomeView::ShowWelcomeNoteL()
// -----------------------------------------------------------------------------
//
void CBlackboxWelcomeView::ShowWelcomeNoteL()
    {
    CQueryDialog* query = CQueryDialog::NewL( *this );
    query->ExecuteLD();

    delete iIdle;
    iIdle = NULL;
    }

// End of File
