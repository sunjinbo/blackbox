/* ====================================================================
 * File: BlackboxHelpView.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h> 
#include <Blackbox.rsg>
#include "BlackboxHelpView.h"
#include "BlackboxHelpContainer.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxHelpView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxHelpView* CBlackboxHelpView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxHelpView* self = CBlackboxHelpView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxHelpView* CBlackboxHelpView::NewLC( CBlackboxAppUi& aAppUi )
    {
    CBlackboxHelpView* self = new ( ELeave ) CBlackboxHelpView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::~CBlackboxHelpView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxHelpView::~CBlackboxHelpView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxHelpView::Id() const
    {
    return TUid::Uid( EBlackboxHelpViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxHelpView::DoActivateL( const TVwsViewId& aPrevViewId,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if ( !iContainer )
        {
        iPrevViewUid = aPrevViewId.iViewUid;
        iContainer = CBlackboxHelpContainer::NewL( ClientRect(), *this );
        AppUi()->AddToViewStackL( *this, iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxHelpView::DoDeactivate()
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
// CBlackboxHelpView::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxHelpView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            AppUi()->ActivateLocalViewL( iPrevViewUid );
            break;

        default:
            Panic( EBlackboxBadCommand);
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxHelpView::HandleSizeChange( TInt aType )
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
// CBlackboxHelpView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxHelpView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxHelpView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_HELP_VIEW );
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpView::CBlackboxHelpView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxHelpView::CBlackboxHelpView(CBlackboxAppUi& aAppUi)
    : iAppUi( aAppUi )
    {
    // No implementation required
    }

// End of File
