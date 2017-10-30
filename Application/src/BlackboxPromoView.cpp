/* ====================================================================
 * File: BlackboxPromoContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


// INCLUDE FILES
#include <e32property.h>
#include <aknviewappui.h>
#include <aknconsts.h>
#include <aknutils.h> 
#include <Blackbox.rsg>
#include "BlackboxPromoView.h"
#include "BlackboxPromoContainer.h"
#include "Blackbox.hrh"
#include "BlackboxAppUi.h"
#include "Blackbox.pan"
#include "BlackboxPSKeys.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxPromoView::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxPromoView* CBlackboxPromoView::NewL(CBlackboxAppUi& aAppUi)
    {
    CBlackboxPromoView* self = CBlackboxPromoView::NewLC(aAppUi);
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxPromoView* CBlackboxPromoView::NewLC(CBlackboxAppUi& aAppUi)
    {
    CBlackboxPromoView* self = new ( ELeave ) CBlackboxPromoView(aAppUi);
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::~CBlackboxPromoView()
// Destructor.
// -----------------------------------------------------------------------------
//
CBlackboxPromoView::~CBlackboxPromoView()
    {
    // No implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::Id()
// Returns View's ID.
// -----------------------------------------------------------------------------
//
TUid CBlackboxPromoView::Id() const
    {
    return TUid::Uid( EBlackboxPromoViewId );
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::DoActivateL()
// -----------------------------------------------------------------------------
//
void CBlackboxPromoView::DoActivateL( const TVwsViewId& /*aPrevViewId*/,
                                    TUid /*aCustomMessageId*/,
                                    const TDesC8& /*aCustomMessage*/)
    {
    if ( !iContainer )
        {
        iContainer = CBlackboxPromoContainer::NewL( *this );
        AppUi()->AddToViewStackL( *this, iContainer );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::DoDeactivate()
// -----------------------------------------------------------------------------
//
void CBlackboxPromoView::DoDeactivate()
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
// CBlackboxPromoView::HandleCommandL()
// Takes care of Command handling.
// -----------------------------------------------------------------------------
//
void CBlackboxPromoView::HandleCommandL( TInt aCommand )
    {
    switch ( aCommand )
        {
        case EAknSoftkeyExit:
            AppUi()->Exit();
            break;
        case EBlackboxWelcomeCmd:
            AppUi()->ActivateLocalViewL( TUid::Uid( EBlackboxWelcomeViewId ) );
            break;
        default:
            Panic( EBlackboxBadCommand );
            break;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::HandleSizeChange()
// Called by HandleResourceChangeL() from CBlackboxAppUi when layout is 
// changed.
// -----------------------------------------------------------------------------
//
void CBlackboxPromoView::HandleSizeChange( TInt aType )
    {
    if( iContainer )
        {
        iContainer->HandleResourceChange( aType );
        
        if ( aType==KEikDynamicLayoutVariantSwitch )
            {        
            iContainer->SetExtentToWholeScreen();
            }
        }         
    }

// ---------------------------------------------------------------------------
// CBlackboxPromoView::HandleClientRectChange
// ---------------------------------------------------------------------------
//
void CBlackboxPromoView::HandleClientRectChange()
    {
    if ( iContainer )
        {
        iContainer->SetExtentToWholeScreen();
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxPromoView::ConstructL()
    {
    BaseConstructL( R_BLACKBOX_PROMO_VIEW );
    
    TInt err = RProperty::Define( 
                        KPSUidBlackbox, 
                        KBlackboxStartupStatus, 
                        RProperty::EInt 
                        );

    if( err != KErrNone
            && err != KErrAlreadyExists  )
        {
        User::LeaveIfError( err );
        }
    
    err = RProperty::Set( 
                        KPSUidBlackbox, 
                        KBlackboxStartupStatus, 
                        EStartupUninitialized 
                        );
    User::LeaveIfError( err );
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoView::CBlackboxPromoView()
// C++ default constructor can NOT contain any code, that might leave.
// -----------------------------------------------------------------------------
//
CBlackboxPromoView::CBlackboxPromoView(CBlackboxAppUi& aAppUi)
    : iAppUi( aAppUi )
    {
    // No implementation required
    }

// End of File
