/* ====================================================================
 * File: QueryDialog.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_QUERYDIALOG_H_
#define C_QUERYDIALOG_H_

// INCLUDE FILES
#include <AknQueryDialog.h>
#include "HyperlinkControl.h"

// FORWARD DECLARATIONS
class CLayoutManager;

// CLASS DECLARATION

/**
 *  CQueryDialog class
 */
class CQueryDialog : public CAknQueryDialog
                     , public MHyperLinkControlObserver
    {
public: // Symbian 2nd constructor and destructor
    static CQueryDialog* NewL( MHyperLinkControlObserver& aObserver );
    virtual ~CQueryDialog();

public: // New function
    TInt ExecuteLD();

private: // from CAknQueryDialog
    void PreLayoutDynInitL();
    void PostLayoutDynInitL();

private: // from MHyperLinkControlObserver
    void HyperLinkControlTappedL();

private: // From base classes
    void SizeChanged();
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void SetSizeAndPosition( const TSize &aSize );

private: // Default c++ constructor
    CQueryDialog( MHyperLinkControlObserver& aObserver );
    void ConstructL();
    
private: // Internal methods
    void RectForTitle( TRect& aRect ) const;
    void RectForMain( TRect& aRect ) const;
    void RectForHyperLink( TRect& aRect ) const;

private: // enums
    enum TQueryDialogControls
        {
        ETitleControl,
        EMainControl,
        EHyperLinkControl,
        ELastControl
        };  

private: // Data
    MHyperLinkControlObserver& iObserver;
    CLayoutManager* iLayoutManager; // owned
    CEikEdwin*  iTitlePane; // owned
    CEikEdwin*  iMainPane; // owned
    CHyperLinkControl* iHyperLinkControl; // owned
    };

#endif /* C_QUERYDIALOG_H_ */
