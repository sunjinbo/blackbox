/* ====================================================================
 * File: BlackboxHelpContainer.cpp
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
#include "BlackboxHelpContainer.h"
#include "BlackboxEditor.h"
#include "BlackboxHelpView.h"

// CONSTANTS
_LIT( KBrowserEngineDLL,"BrowserEngine.dll" );
_LIT( KHelpUrl, "c:\\private\\AFF0567A\\help.htm");

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::NewL()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxHelpContainer* CBlackboxHelpContainer::NewL( 
        const TRect& aRect, CBlackboxHelpView& aHelpView )
    {
    CBlackboxHelpContainer* self = CBlackboxHelpContainer::NewLC( aRect, aHelpView );
    CleanupStack::Pop( self );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::NewLC()
// Two-phased constructor.
// -----------------------------------------------------------------------------
//
CBlackboxHelpContainer* CBlackboxHelpContainer::NewLC( const TRect& aRect, CBlackboxHelpView& aHelpView )
    {
    CBlackboxHelpContainer* self = new ( ELeave ) CBlackboxHelpContainer( aHelpView );
    CleanupStack::PushL( self );
    self->ConstructL( aRect );
    return self;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::~CBlackboxHelpContainer()
// Destructor
// -----------------------------------------------------------------------------
//
CBlackboxHelpContainer::~CBlackboxHelpContainer()
    {
    if( iBrCtrl )
        {
        iBrCtrl->RemoveLoadEventObserver( this );
        delete iBrCtrl;
        iBrLibrary.Close();
        }

    delete iBackGround;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::CountComponentControls() const
// returns number of controls inside this container.
// -----------------------------------------------------------------------------
//
TInt CBlackboxHelpContainer::CountComponentControls() const
    {
    TInt count = 0;
    if ( iBrCtrl )
        {
        count++;
        }
    return count;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::ComponentControl() const
// returns pointer of controls inside this container
// -----------------------------------------------------------------------------
//
CCoeControl* CBlackboxHelpContainer::ComponentControl( TInt aIndex ) const
    {
    switch ( aIndex )
        {
        case 0:
            return iBrCtrl;
        default:
            return NULL;
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::Draw() const
// Draws the display
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::Draw( const TRect& aRect ) const
    {
    CWindowGc& gc = SystemGc();
    gc.Clear();
    MAknsSkinInstance* skin = AknsUtils::SkinInstance();
    AknsDrawUtils::Background( skin, iBackGround, gc, aRect );

    const CFont* logicalFont = AknLayoutUtils::FontFromId( 
        EAknLogicalFontSecondaryFont );

    TRgb textCol;
    AknsUtils::GetCachedColor( AknsUtils::SkinInstance(),
        textCol, KAknsIIDQsnTextColors, EAknsCIQsnTextColorsCG6 );
    gc.SetBrushStyle( CGraphicsContext::ENullBrush );
    gc.SetPenColor( textCol );
    gc.SetPenStyle( CGraphicsContext::ESolidPen );
    gc.UseFont( logicalFont );
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::SizeChanged()
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::SizeChanged()
    {
    if ( iBrCtrl )
        {
        iBrCtrl->SetRect( Rect() );
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
TTypeUid::Ptr CBlackboxHelpContainer::MopSupplyObject( TTypeUid aId )
    {
    if ( aId.iUid == MAknsControlContext::ETypeId && iBackGround )
        {
        return MAknsControlContext::SupplyMopObject( aId, iBackGround );
        }
    return CCoeControl::MopSupplyObject(aId);
    }

// ----------------------------------------------------------------------------
// CBlackboxHelpContainer::HandleResourceChange
// ----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::HandleResourceChange( TInt aType )
    {
    CCoeControl::HandleResourceChange( aType );
    if ( aType == KEikDynamicLayoutVariantSwitch )
        {
        SetRect( iHelpView.ClientRect() );
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::ResolveEmbeddedLinkL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
TBool CBlackboxHelpContainer::ResolveEmbeddedLinkL(const TDesC& /*aEmbeddedUrl*/,
                                   const TDesC& /*aCurrentUrl*/,
                                   TBrCtlLoadContentType /*aLoadContentType*/, 
                                   MBrCtlLinkContent& /*aEmbeddedLinkContent*/)
    {
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::ResolveLinkL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
// -----------------------------------------------------------------------------
// CTestAppHtmlContainer::ResolveLinkL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
TBool CBlackboxHelpContainer::ResolveLinkL(const TDesC& /*aUrl*/,
        const TDesC& /*aCurrentUrl*/, MBrCtlLinkContent& /*aBrCtlLinkContent*/)
    {
    return EFalse;
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::CancelAll()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::CancelAll()
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::HandleResolveComplete()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::HandleResolveComplete(const TDesC& /*aContentType*/,
                                           const TDesC& /*aCharset*/,
                                           const HBufC8* /*aContentBuf*/)
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::HandleResolveError()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::HandleResolveError(TInt /*aError*/)
    {
    // no implementation required
    }

// --------------------------------------------------------------------------
// CBlackboxHelpContainer::HandleBrowserLoadEventL()
// This callback function is used for the following
// 1) When an HTML page is loaded, this callback function will be called. If 
// this callback is invoked for hyperlink navigation, then the display topic
// has to be updated. For example, the Application Topics option menu is
// dependent on the dipslay topic.
// 2) Updation of the softkey from Options-Close to Options-Back (& Vice-Versa)
// in the context view as a result of hyperlink traveral
// --------------------------------------------------------------------------
void CBlackboxHelpContainer::HandleBrowserLoadEventL(
        TBrCtlDefs::TBrCtlLoadEvent aLoadEvent, 
        TUint /*aSize*/, TUint16 /*aTransactionId*/ )
    {
    if( aLoadEvent == TBrCtlDefs::EEventLoadFinished )
        {
        // do nothing.
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::UpdateSoftkeyL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::UpdateSoftkeyL(TBrCtlKeySoftkey /*aKeySoftkey*/,
                                    const TDesC& /*aLabel*/,
                                    TUint32 /*aCommandId*/,
                                    TBrCtlSoftkeyChangeReason /*aBrCtlSoftkeyChangeReason*/)
    {
    // no implementation required
    }


// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::UpdateBrowserVScrollBarL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::UpdateBrowserVScrollBarL(TInt /*aDocumentHeight*/, 
                                              TInt /*aDisplayHeight*/,
                                              TInt /*aDisplayPosY*/ ) 
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::UpdateBrowserHScrollBarL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::UpdateBrowserHScrollBarL(TInt /*aDocumentWidth*/, 
                                              TInt /*aDisplayWidth*/,
                                              TInt /*aDisplayPosX*/ )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::NotifyLayoutChange()
// Standard construction sequence
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::NotifyLayoutChange( TBrCtlLayout /*aNewLayout*/ )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::UpdateTitleL()
// Standard construction sequence
// -----------------------------------------------------------------------------
//      
void CBlackboxHelpContainer::UpdateTitleL( const TDesC& /*aTitle*/ )
    {
    // no implementation required
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::ConstructL()
// Symbian 2nd phase constructor can leave.
// -----------------------------------------------------------------------------
//
void CBlackboxHelpContainer::ConstructL( const TRect& aRect )
    {
    CreateWindowL();
    
    // Load browser engine library
    if( KErrNone != iBrLibrary.Load( KBrowserEngineDLL ) )
        {
        // Handle out of memory error
        }     

#ifdef __WINS__
    const TInt KLookupOrdinal = 10;
#else
    const TInt KLookupOrdinal = 1;
#endif
    TLibraryFunction result = iBrLibrary.Lookup(KLookupOrdinal);

    // Get browser control
    FuncPtr_CreateBrowserControlL fptr  = (FuncPtr_CreateBrowserControlL)result;

    // Capabilities
    const TUint KBrCtrlCapabilities = 
        TBrCtlDefs::ECapabilityDisplayScrollBar| 
        TBrCtlDefs::ECapabilityClientResolveEmbeddedURL|
        TBrCtlDefs::ECapabilityCursorNavigation|
        TBrCtlDefs::ECapabilityWebKitLite|
        TBrCtlDefs::ECapabilityClientNotifyURL;

    // Create browser control
    iBrCtrl = (*fptr)(
                    this, // coecontrol parent
                    aRect,
                    KBrCtrlCapabilities, // cap
                    TBrCtlDefs::ECommandIdBase, // command base
                    this, // MBrCtlSoftkeysObserver
                    this, // MBrCtlLinkResolver
                    NULL, // MBrCtlSpecialLoadObserver
                    this // MBrCtlLayoutObserver
                    );
    
    // Enable CSS
    iBrCtrl->SetBrowserSettingL(TBrCtlDefs::ESettingsCSSFetchEnabled,1);    
    iBrCtrl->AddLoadEventObserverL(this);   
    iBrCtrl->MakeVisible(ETrue);

    iBrCtrl->LoadUrlL( KHelpUrl );
    
    iBackGround = CAknsBasicBackgroundControlContext::NewL( 
        KAknsIIDQsnBgAreaMain, aRect, EFalse );

    SetRect( aRect );

    ActivateL();
    }

// -----------------------------------------------------------------------------
// CBlackboxHelpContainer::CBlackboxHelpContainer()
// -----------------------------------------------------------------------------
//
CBlackboxHelpContainer::CBlackboxHelpContainer( CBlackboxHelpView& aHelpView )
: iHelpView( aHelpView )
    {
    // no implementation required
    }

// End of File

