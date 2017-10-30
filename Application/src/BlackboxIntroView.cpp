/* ====================================================================
 * File: BlackboxIntroView.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h> 
#include <Blackbox.rsg>
#include "BlackboxIntroView.h"
#include "BlackboxIntroContainer.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxIntroView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxIntroView* CBlackboxIntroView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxIntroView* self = CBlackboxIntroView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxIntroView* CBlackboxIntroView::NewLC(CBlackboxAppUi& aAppUi)
    {
    CBlackboxIntroView* self = new ( ELeave ) CBlackboxIntroView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::~CBlackboxIntroView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxIntroView::~CBlackboxIntroView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxIntroView::Id() const
    {
    return TUid::Uid( EBlackboxIntroViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxIntroView::DoActivateL( const TVwsViewId& aPrevViewId,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if ( !iContainer )
        {
        iPrevViewUid = aPrevViewId.iViewUid;
        iContainer = CBlackboxIntroContainer::NewL( ClientRect(), *this );
        AppUi()->AddToViewStackL( *this, iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxIntroView::DoDeactivate()
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
// CBlackboxIntroView::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxIntroView::HandleCommandL( TInt aCommand )
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
// CBlackboxIntroView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxIntroView::HandleSizeChange( TInt aType )
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
// CBlackboxIntroView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxIntroView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetRect( ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxIntroView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_INTRO_VIEW );
    }

// -----------------------------------------------------------------------------
// CBlackboxIntroView::CBlackboxIntroView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxIntroView::CBlackboxIntroView(CBlackboxAppUi& aAppUi)
    : iAppUi( aAppUi )
    {
    // No implementation required
    }

// End of File
