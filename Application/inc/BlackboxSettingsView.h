/* ====================================================================
 * File: BlackboxSettingsView.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXSETTINGSVIEW_H
#define C_BLACKBOXSETTINGSVIEW_H

// INCLUDES
#include <aknview.h>


// FORWARD DECLARATIONS
class CBlackboxSettingsContainer;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxSettingsView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxSettingsView: public CAknView
    {
public:   // Constructors and destructor

    static CBlackboxSettingsView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxSettingsView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxSettingsView();

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
    CBlackboxSettingsView( CBlackboxAppUi& aAppUi );
    
private: // Data
    CBlackboxAppUi& iAppUi;
    CBlackboxSettingsContainer* iContainer;
    TUid iIdentifier;
    };


#endif // C_BLACKBOXSETTINGSVIEW_H

// End of File
