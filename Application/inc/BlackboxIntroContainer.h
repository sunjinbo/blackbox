/* ====================================================================
 * File: BlackboxIntroContainer.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXINTROCONTAINER_H
#define C_BLACKBOXINTROCONTAINER_H

// INCLUDES
#include <coecntrl.h>
#include <gdi.h>  
#include <eiksbobs.h> 
#include <gulicon.h>
#include "MResourceLoaderObserver.h"

// FORWARD DECLARATIONS
class CEikScrollBarFrame;
class CIntroImage;
class CFont;
class TRect;
class TBidiText;
class CAknsBasicBackgroundControlContext;
class CIntroResourceLoader;
class CBlackboxIntroView;

// CLASS DECLARATION

/**
*  CBlackboxIntroContainer  container control class.
*  The container for intro. It handle the system event. 
*  And it draws correct texts and images to screen base on the scroll bar.
*
*/

class CBlackboxIntroContainer : public CCoeControl,
                        public MEikScrollBarObserver,
                        public MResourceLoaderObserver
    {
public: // Constructors and destructor
    static CBlackboxIntroContainer* NewL( 
            const TRect& aRect, CBlackboxIntroView& aIntroView );
    virtual ~CBlackboxIntroContainer();

public: // from CCoeControl
    void SizeChanged();
    void Draw( const TRect& aRect ) const;
    void ActivateL();
    TKeyResponse OfferKeyEventL( const TKeyEvent& aKeyEvent,
                                 TEventCode aModifiers );
    TTypeUid::Ptr MopSupplyObject( TTypeUid aId );
    void HandleResourceChange( TInt aType );

private: // From MResourceLoaderObserver
    void HandleItemsLoadedL( TInt aError );
    void HandleResourceLoadCompletedL( const TInt aResourceId, TInt aError );

private: // From MEikScrollBarObserver
    void HandleScrollEventL(CEikScrollBar* aScrollBar,TEikScrollEvent aEventType); 

private: // Constructor
    CBlackboxIntroContainer( CBlackboxIntroView& aIntroView );
    void ConstructL( const TRect& aRect );

private: // new functions
    void SetTextL( const TDesC& aText , const TInt aItem );
    void SetImageL( const TDesC& aFileName, TInt aBitmapId );
    void UpdateScrollIndicatorL();
    void CalculateL( const TRect& aRect );

private: // Data
    CBlackboxIntroView& iIntroView;
    CArrayPtr<HBufC>* iText;
    CArrayPtr<CIntroImage>* iImages;
    CArrayFixFlat<TInt>* iScreenStarts;
    TInt iCurrentScreen;
    TBool iDoNotShowLastLineAgain;
    CGraphicsContext::TTextAlign iTextAlign;
    CEikScrollBarFrame* iSBFrame;
    const CFont* iFont; // not owned
    TInt iLineWidth;
    TInt iBaseLineDelta;
    TInt iTopBaseLineX;
    TInt iTopBaseLineY;
    TInt iLinesPerScreen;
    CAknsBasicBackgroundControlContext* iSkinContext; // skin data
    CGulIcon* iIcon;
    
    // Judge whether scroll bar is dragged. 
    TBool iScrollBarDragged;
    
    //Owned: Resource loader.
    CIntroResourceLoader* iLoader;
    
    // Judge the break between "real" about box language and the full OSS texts 
    TBool iBreakFlag;
    
    // Store the resource path for load the file
    TFileName iResourcePath;
    
    // Store the the count of the loaded content's items
    TInt iFinalCount;
    };

#endif // C_BLACKBOXINTROCONTAINER_H

// End of File
