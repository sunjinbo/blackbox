/* ====================================================================
 * File: BlackboxAppUi.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


#ifndef C_BLACKBOXAPPUI_H
#define C_BLACKBOXAPPUI_H

// INCLUDES
#include <aknviewappui.h>

// FORWARD DECLARATIONS
class CBlackboxPromoView;
class CBlackboxWelcomeView;
class CBlackboxGameView;
class CBlackboxSettingsView;
class CBlackboxTipsView;
class CBlackboxHelpView;
class CScreenSaverBlocker;
class CTipsManager;

// CLASS DECLARATION
/**
 * CBlackboxAppUi application UI class.
 * Interacts with the user through the UI and request message processing
 * from the handler class
 */
class CBlackboxAppUi : public CAknViewAppUi
    {
public:
    // Constructors and destructor

    /**
     * ConstructL.
     * 2nd phase constructor.
     */
    void ConstructL();
	
    CBlackboxAppUi();
    virtual ~CBlackboxAppUi();

public: // New methods
    void ShowAboutDialogL();
    void LaunchBrowserL();
    CTipsManager* TipsManager() const;
    
private: // from base class
    void HandleCommandL(TInt aCommand);
    void HandleStatusPaneSizeChange();
    void HandleResourceChangeL( TInt aType );

private: // Data
    /** views **/
    CBlackboxPromoView* iPromoView;
    CBlackboxWelcomeView* iWelcomeView;
    CBlackboxGameView* iGameView;
    CBlackboxSettingsView* iSettingsView;
    CBlackboxTipsView* iTipsView;
    CBlackboxHelpView* iHelpView;
    /** tips manager, owned **/
    CTipsManager* iTipsManager;
    /** screen saver blocker, owned **/
    CScreenSaverBlocker* iBlocker;
    };

#endif // C_BLACKBOXAPPUI_H

// End of File
