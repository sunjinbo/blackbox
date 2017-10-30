/* ====================================================================
 * File: CBlackboxTipsView.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h> 
#include <Blackbox.rsg>
#include "BlackboxTipsView.h"
#include "BlackboxTipsContainer.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"
#include "TipsManager.h"
#include "Tips.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxTipsView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxTipsView* CBlackboxTipsView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxTipsView* self = CBlackboxTipsView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxTipsView* CBlackboxTipsView::NewLC(CBlackboxAppUi& aAppUi)
    {
    CBlackboxTipsView* self = new ( ELeave ) CBlackboxTipsView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::~CBlackboxTipsView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxTipsView::~CBlackboxTipsView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxTipsView::Id() const
    {
    return TUid::Uid( EBlackboxTipsViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxTipsView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if ( !iContainer )
        {
        iContainer = CBlackboxTipsContainer::NewL( ClientRect(), *this );
        iContainer->SetTipsL( *( iTipsManager->Tips() ) );
        AppUi()->AddToViewStackL( *this, iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxTipsView::DoDeactivate()
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
// CBlackboxTipsView::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxTipsView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyBack:
            iTipsManager->Next();
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxGameViewId ) );
            break;

        case EAknSoftkeyNext:
            iTipsManager->Next();
            iContainer->SetTipsL( *( iTipsManager->Tips() ) );
            break;

        default:
            Panic( EBlackboxBadCommand );
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxTipsView::HandleSizeChange( TInt aType )
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
// CBlackboxTipsView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxTipsView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxTipsView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_TIPS_VIEW );
    
    iTipsManager = iAppUi.TipsManager();
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsView::CBlackboxTipsView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxTipsView::CBlackboxTipsView(CBlackboxAppUi& aAppUi)
    : iAppUi( aAppUi )
    {
    // No implementation required
    }

// End of File
