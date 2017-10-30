/* ====================================================================
 * File: BlackboxHelpContainer.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXHELPCONTAINER_H
#define C_BLACKBOXHELPCONTAINER_H

// INCLUDES
#include <aknview.h>
#include <akndef.h>
#include <BrCtlLinkResolver.h>
#include <BrCtlInterface.h>

// FORWARD DECLARATIONS
class CAknsBasicBackgroundControlContext;
class CBrCtlInterface;
class CBlackboxHelpView;

typedef CBrCtlInterface* (*FuncPtr_CreateBrowserControlL) ( CCoeControl* aParent, TRect aRect,
    TUint aBrCtlCapabilities, TUint aCommandIdBase = TBrCtlDefs::ECommandIdBase,
    MBrCtlSoftkeysObserver* aBrCtlSoftkeysObserver = NULL,
    MBrCtlLinkResolver* aBrCtlLinkResolver = NULL,
    MBrCtlSpecialLoadObserver* aBrCtlSpecialLoadObserver = NULL,
    MBrCtlLayoutObserver* aBrCtlLayoutObserver = NULL,
    MBrCtlDialogsProvider* aBrCtlDialogsProvider = NULL,
    MBrCtlWindowObserver* aBrCtlWindowObserver = NULL,
    MBrCtlDownloadObserver* aBrCtlDownloadObserver = NULL );

// CLASS DECLARATION

/**
*  CBlackboxHelpContainer container control class.
*  An instance of CBlackboxHelpContainer contains the view drawn to the screen
*  for CBlackboxHelpView
*/
class CBlackboxHelpContainer : public CCoeControl,
public MBrCtlLinkResolver,
public MBrCtlLinkContent,
public MBrCtlLoadEventObserver,
public MBrCtlSoftkeysObserver,
public MBrCtlLayoutObserver
    {
public: // Constructors and destructor
    static CBlackboxHelpContainer* NewL( const TRect& aRect, CBlackboxHelpView& aHelpView );
    static CBlackboxHelpContainer* NewLC( const TRect& aRect, CBlackboxHelpView& aHelpView );
    virtual ~CBlackboxHelpContainer();

public: // from CoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void SizeChanged();
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    void HandleResourceChange( TInt aType );

private: // from MBrCtlLinkResolver
    TBool ResolveEmbeddedLinkL(const TDesC& aEmbeddedUrl,
                   const TDesC& aCurrentUrl,
                     TBrCtlLoadContentType aLoadContentType, 
                     MBrCtlLinkContent& aEmbeddedLinkContent); 

    TBool ResolveLinkL(const TDesC& aUrl, const TDesC& aCurrentUrl,
                   MBrCtlLinkContent& aBrCtlLinkContent );
    void CancelAll();

private: // from MBrCtlLinkContent
    void HandleResolveComplete( const TDesC& aContentType,
                                       const TDesC& aCharset,
                                       const HBufC8* aContentBuf );

    void HandleResolveError( TInt aError );

private: // from MBrCtlLoadEventObserver
    void HandleBrowserLoadEventL( TBrCtlDefs::TBrCtlLoadEvent aLoadEvent, 
            TUint aSize, TUint16 aTransactionId );

private: // from MBrCtlSoftkeysObserver
    void UpdateSoftkeyL( TBrCtlKeySoftkey aKeySoftkey,
            const TDesC& aLabel,
            TUint32 aCommandId,
            TBrCtlSoftkeyChangeReason aBrCtlSoftkeyChangeReason );

private: // from MBrCtlLayoutObserver
    void UpdateBrowserVScrollBarL( TInt aDocumentHeight, 
                                          TInt aDisplayHeight,
                                          TInt aDisplayPosY );
    void UpdateBrowserHScrollBarL( TInt aDocumentWidth, 
                                          TInt aDisplayWidth,
                                          TInt aDisplayPosX );

    void NotifyLayoutChange( TBrCtlLayout aNewLayout );
    void UpdateTitleL( const TDesC& aTitle ); 

private: // Constructor
    void ConstructL( const TRect& aRect );
    CBlackboxHelpContainer( CBlackboxHelpView& aHelpView );

private: // Data
    CBlackboxHelpView& iHelpView;
    RLibrary iBrLibrary;
    CBrCtlInterface* iBrCtrl; // owned
    CAknsBasicBackgroundControlContext* iBackGround; // owned
    };

#endif // C_BLACKBOXHELPCONTAINER_H


// End of File
