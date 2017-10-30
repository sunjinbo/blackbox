/* ====================================================================
 * File: BlackboxHelpContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <e32property.h>
#include <AknsSkinInstance.h>
#include <AknsUtils.h>
#include <AknsDrawUtils.h>
#include <AknUtils.h>
#include <AknQueryDialog.h>
#include <stringloader.h>
#include <Blackbox.rsg>
#include <Blackbox_promo.mbg>
#include "BlackboxPromoContainer.h"
#include "BlackboxPromoView.h"
#include "Blackbox.hrh"
#include "BlackboxBmpUtils.h"
#include "BlackboxPSKeys.h"
#include "LayoutManager.h"
#include "PropertySubscriber.h"

// CONSTANTS
const TInt KLongWaitTimeout = 8000000;
const TInt KShortWaitTimeout = 3000000;
const TInt KDoLoadDelayTimeout = 0;
const TInt KDoLoadUpdateTimeout = 500000;

#if defined( __WINS__ )
_LIT( KPromoFileName, "Z:\\resource\\apps\\Blackbox_promo.mbm" );
#else
_LIT( KPromoFileName, "\\resource\\apps\\Blackbox_promo.mbm" );
#endif // __WINS__

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxPromoContainer* CBlackboxPromoContainer::NewL( CBlackboxPromoView& aHelpView )
    {
    CBlackboxPromoContainer* self = CBlackboxPromoContainer::NewLC( aHelpView );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxPromoContainer* CBlackboxPromoContainer::NewLC( CBlackboxPromoView& aHelpView )
    {
    CBlackboxPromoContainer* self = new ( ELeave ) CBlackboxPromoContainer( aHelpView );
    CleanupStack::PushL( self );
    self->ConstructL();
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::~CBlackboxPromoContainer()
// Destructor
// -----------------------------------------------------------------------------
//
CBlackboxPromoContainer::~CBlackboxPromoContainer()
    {
    delete iTimeout;
    delete iBmpUtils;
    delete iLayoutManager;
    delete iPropertySubscriber;
    if ( iPeriodic )
        {  
        iPeriodic->Cancel();
        delete iPeriodic;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CBlackboxPromoContainer::CountComponentControls() const
    {
    TInt count = 0;
    return count;
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CBlackboxPromoContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::Draw( const TRect& /*aRect*/ ) const
    {
    CWindowGc& gc = SystemGc();
    gc.SetBrushColor( KRgbBlack );
    gc.Clear();
    
    gc.SetPenStyle( CGraphicsContext::ENullPen );
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );

    if ( iBmpUtils )
        {
        TRect theRect = iLayoutManager->LayoutRect( EPromoBrand );
        gc.BitBlt( 
                theRect.iTl,
                iBmpUtils->Bitmap( iPromoBrandBitmapId ),
                TRect( TPoint( 0, 0 ), theRect.Size() )
                );

        theRect = iLayoutManager->LayoutRect( EPromoLoading );
        gc.BitBlt( 
                theRect.iTl,
                iBmpUtils->Bitmap( iPromoLoadingBtimapId ),
                TRect( TPoint( 0, 0 ), theRect.Size() )
                );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::SizeChanged()
// -----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::SizeChanged()
    {
    CCoeControl::SizeChanged();
    if ( iLayoutManager && iBmpUtils )
        {
        ScaleBmpUtils();    
        }
    }

// ----------------------------------------------------------------------------
// CBlackboxPromoContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetExtentToWholeScreen();
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::HandleTimeoutL()
// -----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::HandleTimeoutL()
    {
	switch ( iPromoBrandBitmapId )
		{
		case EMbmBlackbox_promoPromo_01:
		    {
            iPromoBrandBitmapId = EMbmBlackbox_promoPromo_02;
            iTimeout->Start( KShortWaitTimeout );
		    }
			break;

		case EMbmBlackbox_promoPromo_02:
		    {
            iPromoBrandBitmapId = EMbmBlackbox_promoPromo_03;
            iTimeout->Start( KShortWaitTimeout );
		    }
			break;

		case EMbmBlackbox_promoPromo_03:
		    {
            if ( iPromo3State == EPromo3Phase1 )
                {
                if ( iStartupStatus == EStartupAllDone )
                    {
                    iHelpView.HandleCommandL( EBlackboxWelcomeCmd );
                    }
                else
                    {
                    iTimeout->Start( KLongWaitTimeout );
                    }
                iPromo3State = EPromo3Phase2;
                }
            else
                {
                CAknQueryDialog* query = new(ELeave) CAknQueryDialog;
                query->SetPromptL( _L( "Out of memory, do you want to quit Black-box for a while now?" ) );

                TBool result = query->ExecuteLD( R_BLACKBOX_PROMO_DIALOG );
                if ( result )
                    {
                    iHelpView.HandleCommandL( EAknSoftkeyExit );
                    }
                else
                    {
                    iTimeout->Start( KLongWaitTimeout );
                    }
                }
		    }
			break;

		default:
			break;
		}

	DrawNow();
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::HandlePropertyChangedL()
// -----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::HandlePropertyChangedL( 
                                            const TUid& aCategory, 
                                            TInt aKey )
    {
    TInt value = 0;
    TInt err = RProperty::Get( aCategory, aKey, value );
    User::LeaveIfError( err );
    
    iStartupStatus |= value;
    if ( iStartupStatus == EStartupAllDone && iPromo3State == EPromo3Phase2 )
        {
        iHelpView.HandleCommandL( EBlackboxWelcomeCmd );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::ConstructL()
    {
    CreateWindowL();

    SetExtentToWholeScreen();

    iLayoutManager = CLayoutManager::NewL();

    iBmpUtils = CBlackboxBmpUtils::NewL( 
            KPromoFileName,
            EMbmBlackbox_promoPromo_01,
            EMbmBlackbox_promoLastElement );

    ScaleBmpUtils();

    iPromoBrandBitmapId = EMbmBlackbox_promoPromo_01;
    iPromoLoadingBtimapId = EMbmBlackbox_promoPromo_loading_01;

    iTimeout = CRegistrationTimeout::NewL( *this );
    iTimeout->Start( KShortWaitTimeout );

    iPeriodic = CPeriodic::NewL( CActive::EPriorityStandard );
    iPeriodic->Cancel();
    iPeriodic->Start(
            KDoLoadDelayTimeout,
            KDoLoadUpdateTimeout,
            TCallBack( TimerCallback, this ) );

    iPropertySubscriber = CPropertySubscriber::NewL( 
                                this, 
                                KPSUidBlackbox,
                                KBlackboxStartupStatus
                                );
    iPropertySubscriber->Subscribe();

    iStartupStatus = EStartupAllDone; // ToDo:
    
    ActivateL();
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::CBlackboxPromoContainer()
// -----------------------------------------------------------------------------
//
CBlackboxPromoContainer::CBlackboxPromoContainer( CBlackboxPromoView& aHelpView )
: iHelpView( aHelpView )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxPromoContainer::ScaleBmpUtils()
// -----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::ScaleBmpUtils()
	{
	TRect rect = iLayoutManager->LayoutRect( EPromoBrand );
	for ( TInt m = EMbmBlackbox_promoPromo_01; m <= EMbmBlackbox_promoPromo_03; m += 2 )
		{
	    iBmpUtils->SetSize( m, rect.Size() );
		}

	rect = iLayoutManager->LayoutRect( EPromoLoading );
	for ( TInt n = EMbmBlackbox_promoPromo_loading_01; n <= EMbmBlackbox_promoPromo_loading_03; n += 2 )
		{
	    iBmpUtils->SetSize( n, rect.Size() );
		}
	}

// ----------------------------------------------------------------------------
// CBlackboxPromoContainer::DoLoading
// ----------------------------------------------------------------------------
//
void CBlackboxPromoContainer::DoLoading()
    {
	iPromoLoadingBtimapId += 2;
	if ( iPromoLoadingBtimapId > EMbmBlackbox_promoPromo_loading_03 )
		{
	    iPromoLoadingBtimapId = EMbmBlackbox_promoPromo_loading_01;
		}
	DrawNow();
    }

// ----------------------------------------------------------------------------
// CBlackboxPromoContainer::TimerCallback
// ----------------------------------------------------------------------------
//
TInt CBlackboxPromoContainer::TimerCallback( TAny* aPtr )
    {
	CBlackboxPromoContainer* self = static_cast<CBlackboxPromoContainer*> ( aPtr );
    self->DoLoading();
    return 0;
    }

// End of File
