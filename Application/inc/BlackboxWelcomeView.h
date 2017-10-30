/* ====================================================================
 * File: BlackboxWelcomeView.h
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXWELCOMEVIEW_H
#define C_BLACKBOXWELCOMEVIEW_H

// INCLUDES
#include <aknview.h>
#include "HyperlinkControl.h"

// FORWARD DECLARATIONS
class CBlackboxWelcomeContainer;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxWelcomeView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxWelcomeView: public CAknView, public MHyperLinkControlObserver
    {
public:   // Constructors and destructor
    static CBlackboxWelcomeView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxWelcomeView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxWelcomeView();

public: // from CAknView

    TUid Id() const;
    void HandleCommandL( TInt aCommand );
    void DoActivateL( const TVwsViewId& aPrevViewId,
                      TUid aCustomMessageId,
                      const TDesC8& aCustomMessage );
    void DoDeactivate();
    void HandleSizeChange( TInt aType );
    void HandleClientRectChange();

private: // from MHyperLinkControlObserver
    void HyperLinkControlTappedL();

private:   // Constructors and destructor
    void ConstructL();
    CBlackboxWelcomeView( CBlackboxAppUi& aAppUi );

private: // New functions
    static TInt WelcomeCallback( TAny* aPtr );
    void ShowWelcomeNoteL();
    HBufC* ReadFirstTimeUseTextL();

private: // Data
    CBlackboxAppUi& iAppUi;
    CBlackboxWelcomeContainer* iContainer; // owned
    CIdle* iIdle; // owned
    TUid iIdentifier;
    };

#endif // C_BLACKBOXWELCOMEVIEW_H

// End of File
