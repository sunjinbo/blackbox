/* ====================================================================
 * File: BlackboxHelpView.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXHELPVIEW_H
#define C_BLACKBOXHELPVIEW_H

// INCLUDES
#include <aknview.h>

// FORWARD DECLARATIONS
class CBlackboxHelpContainer;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxHelpView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxHelpView: public CAknView
    {
public:   // Constructors and destructor

    static CBlackboxHelpView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxHelpView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxHelpView();

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
    CBlackboxHelpView( CBlackboxAppUi& aAppUi );
    
private: // Data
    CBlackboxAppUi& iAppUi;
    CBlackboxHelpContainer* iContainer;
    TUid iPrevViewUid;
    };

#endif // C_BLACKBOXHELPVIEW_H

// End of File
