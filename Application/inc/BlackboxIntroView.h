/* ====================================================================
 * File: BlackboxIntroView.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXIntroVIEW_H
#define C_BLACKBOXIntroVIEW_H

// INCLUDES
#include <aknview.h>

// FORWARD DECLARATIONS
class CBlackboxIntroContainer;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxIntroView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxIntroView: public CAknView
    {
public:   // Constructors and destructor

    static CBlackboxIntroView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxIntroView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxIntroView();

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
    CBlackboxIntroView( CBlackboxAppUi& aAppUi );
    
private: // Data
    CBlackboxAppUi& iAppUi;
    CBlackboxIntroContainer* iContainer;
    TUid iPrevViewUid;
    };

#endif // C_BLACKBOXIntroVIEW_H

// End of File
