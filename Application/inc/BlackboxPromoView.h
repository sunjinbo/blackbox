/* ====================================================================
 * File: BlackboxPromoView.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXPROMOVIEW_H
#define C_BLACKBOXPROMOVIEW_H

// INCLUDES
#include <aknview.h>


// FORWARD DECLARATIONS
class CBlackboxPromoContainer;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxPromoView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxPromoView: public CAknView
    {
public:   // Constructors and destructor

    static CBlackboxPromoView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxPromoView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxPromoView();

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
    CBlackboxPromoView( CBlackboxAppUi& aAppUi );

private: // Data
    CBlackboxAppUi& iAppUi;
    CBlackboxPromoContainer* iContainer;
    };

#endif // C_BLACKBOXPROMOVIEW_H

// End of File
