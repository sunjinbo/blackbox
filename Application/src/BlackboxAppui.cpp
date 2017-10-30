/* ====================================================================
 * File: BlackboxAppUi.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <avkon.hrh>
#include <aknmessagequerydialog.h>
#include <aknnotewrappers.h>
#include <stringloader.h>
#include <f32file.h>
#include <s32file.h>
#include <eikbtgpc.h>
#include <apgcli.h>
#include <AknUtils.h>
#include <Blackbox.rsg>
#include "Blackbox.hrh"
#include "Blackbox.pan"
#include "BlackboxAppUi.h"
#include "BlackboxPromoView.h"
#include "BlackboxWelcomeView.h"
#include "BlackboxGameView.h"
#include "BlackboxSettingsView.h"
#include "BlackboxTipsView.h"
#include "BlackboxHelpView.h"
#include "TipsManager.h"
#include "ScreensaverBlocker.h"

#include "Logger.h"

// CONSTANS
_LIT( KWebUrl, "http://www.ovi.com/" );

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBlackboxAppUi::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxAppUi::ConstructL()
    {
    INFO( "CBlackboxAppUi::ConstructL()" )

    // Initialise app UI with standard value.
    BaseConstructL( CAknAppUi::EAknEnableSkin );
    
    // Only support portrait mode for a while
    SetOrientationL( EAppUiOrientationPortrait );

    CEikStatusPane* sp = StatusPane();
    if ( sp )
        {
        sp->SwitchLayoutL( R_AVKON_STATUS_PANE_LAYOUT_USUAL );
        }

    // Create tips manager object
    iTipsManager = CTipsManager::NewL();

    // Create screen saver blocker
    iBlocker = CScreenSaverBlocker::NewL();
    iBlocker->DeactivateLightTimeoutAndScreenSaver();

    // Create view object
    iPromoView = CBlackboxPromoView::NewL(*this);
    INFO( "Created Promo view" )
    iWelcomeView = CBlackboxWelcomeView::NewL(*this);
    INFO( "Created Welcome view" )
    iGameView = CBlackboxGameView::NewL(*this);
    INFO( "Created Game view" )
    iSettingsView = CBlackboxSettingsView::NewL(*this);
    INFO( "Created Settings view" )
    iTipsView = CBlackboxTipsView::NewL(*this);
    INFO( "Created Tips view" )
    iHelpView = CBlackboxHelpView::NewL(*this);
    INFO( "Created Help view" )

    // Transfer ownership to base class
    AddViewL( iPromoView );
    AddViewL( iWelcomeView );
    AddViewL( iGameView );
    AddViewL( iSettingsView );
    AddViewL( iTipsView );
    AddViewL( iHelpView );

    INFO( "Views were added to AppUi framwork" )
    
    SetDefaultViewL( *iPromoView );
    }

// -----------------------------------------------------------------------------
// CBlackboxAppUi::CBlackboxAppUi()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxAppUi::CBlackboxAppUi()
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxAppUi::~CBlackboxAppUi()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxAppUi::~CBlackboxAppUi()
    {
    delete iTipsManager;
    delete iBlocker;
    }

// -----------------------------------------------------------------------------
// CBlackboxAppUi::ShowAboutDialogL()
// -----------------------------------------------------------------------------
//
void CBlackboxAppUi::ShowAboutDialogL()
    {
    CAknNoteDialog* dlg = new(ELeave) CAknNoteDialog;
    dlg->SetTimeout( CAknNoteDialog::ELongTimeout );
    dlg->SetTone( CAknNoteDialog::EConfirmationTone );
    dlg->SetTextPluralityL( ETrue );
    dlg->ExecuteLD( R_BLACKBOX_ABOUT_DIALOG );
    }

// ----------------------------------------------------------------------------
// CBlackboxAppUi::LaunchBrowserL
// ----------------------------------------------------------------------------
//
void CBlackboxAppUi::LaunchBrowserL()
    {
    TUid browserUid = TUid::Uid( 0x10008D39 );                          

    TApaTaskList taskList( iEikonEnv->WsSession() );
    TApaTask task = taskList.FindApp( browserUid );

    // browser is already running
    if ( task.Exists() )
        {
        HBufC8* param8 = HBufC8::NewLC( /*webUrl->Length()*/ 128 );
        param8->Des().Append( KWebUrl );
        task.SendMessage( TUid::Uid( 0 ), *param8 );
        CleanupStack::PopAndDestroy( param8 );
        }
    // browser is not running, start it
    else
        {
        RApaLsSession appArcSession;
        User::LeaveIfError( appArcSession.Connect() );       

        CleanupClosePushL( appArcSession );
        TThreadId id;
        appArcSession.StartDocument( KWebUrl, browserUid, id );
        CleanupStack::PopAndDestroy( &appArcSession );
       }
    }

// -----------------------------------------------------------------------------
// CBlackboxAppUi::TipsManager()
// -----------------------------------------------------------------------------
//
CTipsManager* CBlackboxAppUi::TipsManager() const
    {
    return iTipsManager;
    }

// -----------------------------------------------------------------------------
// CBlackboxAppUi::HandleCommandL()
// Takes care of command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxAppUi::HandleCommandL(TInt aCommand)
    {
    switch (aCommand)
        {
        case EEikCmdExit:
        case EAknSoftkeyExit:
            Exit();
            break;

        default:
            Panic( EBlackboxBadCommand );
            break;
        }
    }

// -----------------------------------------------------------------------------
//  Called by the framework when the application status pane
//  size is changed.  Passes the new client rectangle to the
//  AppView
// -----------------------------------------------------------------------------
//
void CBlackboxAppUi::HandleStatusPaneSizeChange()
    {
    }

// -----------------------------------------------------------------------------
// CBlackboxAppUi::HandleResourceChangeL()
// -----------------------------------------------------------------------------
//
void CBlackboxAppUi::HandleResourceChangeL( TInt aType )
    {
    CAknAppUi::HandleResourceChangeL( aType );
    }

// End of File
