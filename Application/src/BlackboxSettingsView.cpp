/* ====================================================================
 * File: BlackboxSettingsView.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h> 
#include <Blackbox.rsg>
#include "BlackboxSettingsView.h"
#include "BlackboxSettingsContainer.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxSettingsView* CBlackboxSettingsView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxSettingsView* self = CBlackboxSettingsView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxSettingsView* CBlackboxSettingsView::NewLC(CBlackboxAppUi& aAppUi)
    {
    CBlackboxSettingsView* self = new ( ELeave ) CBlackboxSettingsView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::~CBlackboxSettingsView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxSettingsView::~CBlackboxSettingsView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxSettingsView::Id() const
    {
    return TUid::Uid( EBlackboxSettingsViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if ( !iContainer )
        {
        iContainer = CBlackboxSettingsContainer::NewL( ClientRect(), *this );
        AppUi()->AddToViewStackL( *this, iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsView::DoDeactivate()
    {

    if ( iContainer )
        {
        // Remove View1's container form controllStack
        AppUi()->RemoveFromStack( iContainer );
        delete iContainer;
        iContainer = NULL;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxWelcomeViewId ) );
            break;

        default:
            Panic( EBlackboxBadCommand);
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsView::HandleSizeChange( TInt aType )
    {
    if( iContainer )
        {
        iContainer->HandleResourceChange( aType );
        
        if ( aType==KEikDynamicLayoutVariantSwitch )
            {        
            TRect rect;
            AknLayoutUtils::LayoutMetricsRect(AknLayoutUtils::EMainPane, rect);
            iContainer->SetRect(rect);
            }
        }         
    }

// ---------------------------------------------------------------------------
// CBlackboxSettingsView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxSettingsView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxSettingsView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_SETTINGS_VIEW );
    }

// -----------------------------------------------------------------------------
// CBlackboxSettingsView::CBlackboxSettingsView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxSettingsView::CBlackboxSettingsView( CBlackboxAppUi& aAppUi )
    : iAppUi( aAppUi )
    {
    // No implementation required
    }

// End of File
