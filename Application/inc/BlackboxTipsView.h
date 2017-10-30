/* ====================================================================
 * File: BlackboxTipsView.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXTIPSVIEW_H
#define C_BLACKBOXTIPSVIEW_H

// INCLUDES
#include <aknview.h>

// FORWARD DECLARATIONS
class CBlackboxTipsContainer;
class CTipsManager;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxTipsView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxTipsView: public CAknView
    {
public:   // Constructors and destructor
    static CBlackboxTipsView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxTipsView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxTipsView();

public: // from CAknView

    TUid Id() const;
    void HandleCommandL( TInt aCommand );

    void DoActivateL( const TVwsViewId& aPrevViewId,
                      TUid aCustomMessageId,
                      const TDesC8& aCustomMessage );
    void DoDeactivate();
    void HandleSizeChange( TInt aType );
    void HandleClientRectChange();

private:   // Constructors and destructor
    void ConstructL();
    CBlackboxTipsView( CBlackboxAppUi& aAppUi );

private: // Data
    CBlackboxAppUi& iAppUi;
    CTipsManager* iTipsManager; // no owned
    CBlackboxTipsContainer* iContainer;
    TUid iIdentifier;
    };


#endif // C_BLACKBOXTIPSVIEW_H

// End of File
