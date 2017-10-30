/* ====================================================================
 * File: CBlackboxTipsContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknsSkinInstance.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <AknsControlContext.h>
#include <AknsBasicBackgroundControlContext.h>
#include <stringloader.h>
#include <Blackbox.rsg>
#include "BlackboxTipsContainer.h"
#include "BlackboxEditor.h"
#include "Tips.h"
#include "Animation.h"
#include "BlackboxTipsView.h"

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxTipsContainer* CBlackboxTipsContainer::NewL( 
        const TRect& aRect, CBlackboxTipsView& aTipsView )
    {
    CBlackboxTipsContainer* self = CBlackboxTipsContainer::NewLC( aRect, aTipsView );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxTipsContainer* CBlackboxTipsContainer::NewLC( 
        const TRect& aRect, CBlackboxTipsView& aTipsView )
    {
    CBlackboxTipsContainer* self = new ( ELeave ) CBlackboxTipsContainer( aTipsView );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::~CBlackboxTipsContainer()
// Destructor
// -----------------------------------------------------------------------------
//
CBlackboxTipsContainer::~CBlackboxTipsContainer()
    {
    delete iEditor;
    delete iBackGround;
    if ( iAnimation )
        {
        iAnimation->DisableControl();
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::SetTipsL()
// -----------------------------------------------------------------------------
//
void CBlackboxTipsContainer::SetTipsL( const CTips& aTips )
    {
    HBufC* tipsText = aTips.TipsText();
    iEditor->InitFormatsL();
    iEditor->InsertTextL( *tipsText );
    
    if ( iAnimation )
        {
        iAnimation->DisableControl();
        }
    iAnimation = aTips.Animation();
    iAnimation->EnableControl( this );
    iAnimation->Start();
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CBlackboxTipsContainer::CountComponentControls() const
    {
    TInt count = 0;
    if ( iEditor )
        {
        count++;
        }
    return count;
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CBlackboxTipsContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0:
            return iEditor->Editor();
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CBlackboxTipsContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.Clear();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::Background( skin, iBackGround, gc, aRect );
    
    if ( iAnimation )
        {
        TRect theRect( 25, 25, 100, 100 );
        iAnimation->Draw( gc, theRect );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::SizeChanged()
// -----------------------------------------------------------------------------
//
void CBlackboxTipsContainer::SizeChanged()
    {
    if ( iEditor )
        {
        TRect theRect( Rect() );
        theRect.iTl.iY = theRect.Height() / 2;
        iEditor->SetRect( theRect );
        }

    if ( iBackGround )
        {
        iBackGround->SetRect( Rect() );
        }
    }

// --------------------------------------------------------------------------
// CSmartPromoUiSignupContainer::MopSupplyObject()
// Pass skin information if need.
// --------------------------------------------------------------------------
//
TTypeUid::Ptr CBlackboxTipsContainer::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId && iBackGround )
        {
        return MAknsControlContext::SupplyMopObject( aId, iBackGround );
        }
    return CCoeControl::MopSupplyObject(aId);
    }

// ----------------------------------------------------------------------------
// CBlackboxTipsContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CBlackboxTipsContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetRect( iTipsView.ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxTipsContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    
    iEditor = CBlackboxEditor::NewL( this );
    iEditor->InitFormatsL();

    iBackGround = CAknsBasicBackgroundControlContext::NewL( 
        KAknsIIDQsnBgAreaMain, aRect, EFalse );

    SetRect( aRect );

    ActivateL();
    }

// -----------------------------------------------------------------------------
// CBlackboxTipsContainer::CBlackboxTipsContainer()
// -----------------------------------------------------------------------------
//
CBlackboxTipsContainer::CBlackboxTipsContainer( CBlackboxTipsView& aTipsView )
: iTipsView( aTipsView )
    {
    // No implementation required
    }

// End of File

