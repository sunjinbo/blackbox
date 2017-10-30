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
#include "RegistrationTimeout.h"
#include "PropertyObserver.h"

// FORWARD DECLARATIONS
class CBlackboxPromoView;
class CRegistrationTimeout;
class CBlackboxBmpUtils;
class CLayoutManager;
class CPropertySubscriber;

// CLASS DECLARATION

/**
*  CBlackboxPromoContainer container control class.
*  An instance of CBlackboxPromoContainer contains the view drawn to the screen
*  for CBlackboxPromoView
*/
class CBlackboxPromoContainer : public CCoeControl
, public MTimeoutCallback, public MPropertyObserver
    {
public: // Constructors and destructor
    static CBlackboxPromoContainer* NewL( CBlackboxPromoView& aHelpView );
    static CBlackboxPromoContainer* NewLC( CBlackboxPromoView& aHelpView );
    virtual ~CBlackboxPromoContainer();

public: // from CoeControl
    TInt CountComponentControls() const;
    CCoeControl* ComponentControl( TInt aIndex ) const;
    void Draw( const TRect& aRect ) const;
    void SizeChanged();
    void HandleResourceChange( TInt aType );

public: // from MTimeoutCallback
    void HandleTimeoutL();

public: // from MPropertyObserver
    void HandlePropertyChangedL( 
                    const TUid& aCategory, 
                    TInt aKey );
    
private: // Constructor
    void ConstructL();
    CBlackboxPromoContainer( CBlackboxPromoView& aHelpView );

private: // New methods
    void ScaleBmpUtils();
    void DoLoading();
    static TInt TimerCallback( TAny* aPtr );

private: // Data
    CBlackboxPromoView& iHelpView;
    CRegistrationTimeout* iTimeout; // owned
    CBlackboxBmpUtils* iBmpUtils; // owned
    CLayoutManager* iLayoutManager; // owned
    CPeriodic* iPeriodic; // owned
    CPropertySubscriber* iPropertySubscriber;
    TInt iPromoBrandBitmapId;
    TInt iPromoLoadingBtimapId;
    TInt iStartupStatus;
    enum TPromo3State
        {
        EPromo3Phase1 = 0,
        EPromo3Phase2
        };
    TPromo3State iPromo3State;
    };

#endif // C_BLACKBOXHELPCONTAINER_H

// End of File
