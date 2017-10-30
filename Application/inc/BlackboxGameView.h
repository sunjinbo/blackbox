/* ====================================================================
 * File: BlackboxGameView.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXGAMEVIEW_H
#define C_BLACKBOXGAMEVIEW_H

// INCLUDES
#include <aknview.h>
#include <AknToolbarObserver.h> 
#include <AknToolbar.h>
#include "Blackbox.hrh"

// FORWARD DECLARATIONS
class CBlackboxGameContainer;
class CBlackboxAppUi;

// CLASS DECLARATION

/**
* CBlackboxGameView view class.
* An instance of the Application View object for the MultiViews
* example application
*/
class CBlackboxGameView: public CAknView, public MAknToolbarObserver
    {
public:   // Constructors and destructor

    static CBlackboxGameView* NewL( CBlackboxAppUi& aAppUi );
    static CBlackboxGameView* NewLC( CBlackboxAppUi& aAppUi );
    virtual ~CBlackboxGameView();

public: // new methods
    void SetToolbarL( TToolbarState aState );
    void SwitchToolbarL();
    void DisableToolbarL();
    void EnableToolbarL();
    void SetItemDimmed( TInt aItemId, TBool aDimmed );
    TToolbarState ToolbarState() const;

public: // from CAknView

    TUid Id() const;
    void HandleCommandL( TInt aCommand );
    void DoActivateL( const TVwsViewId& aPrevViewId,
                      TUid aCustomMessageId,
                      const TDesC8& aCustomMessage );
    void DoDeactivate();
    void HandleSizeChange( TInt aType );
    void HandleClientRectChange();

public: // from MAknToolbarObserver
    void DynInitToolbarL( TInt aResourceId, 
                    CAknToolbar* aToolbar );
    void OfferToolbarEventL( TInt aCommand );

private:   // Constructors and destructor
    void ConstructL();
    CBlackboxGameView( CBlackboxAppUi& aAppUi );

private: // New functions
    static TInt ToolbarCallback( TAny* aPtr );
    void ShowToolbarL();
    static TInt DimmedCallback( TAny* aPtr );
    void DoItemDimmed();

private: // Data
    CBlackboxAppUi& iAppUi;
    CBlackboxGameContainer* iContainer; // owned
    CIdle* iIdle; // owned
    CIdle* iDimmedIdle; // owned
    TToolbarState iToolbarState;
    TBool iSolvePuzzle;
    TBool iDimmed;
    TInt iDimmedItemId;
    };

#endif // C_BLACKBOXGAMEVIEW_H

// End of File
