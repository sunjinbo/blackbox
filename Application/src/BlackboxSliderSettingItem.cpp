/* ====================================================================
 * File: BlackboxSliderSettingItem.cpp
 * Created: 10/09/10
 * Aucherry: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknSlider.h>
#include <StringLoader.h>
#include <AknSliderSettingPage.h>
#include <barsread.h>
#include <Blackbox.rsg>
#include "BlackboxSliderSettingItem.h"

// ============================ MEMBER FUNCTIONS ===============================

// -----------------------------------------------------------------------------
// CBlackboxSliderSettingItem::CBlackboxSliderSettingItem
// C++ default constructor can NOT contain any code, that
// might leave.
// -----------------------------------------------------------------------------
//
CBlackboxSliderSettingItem::CBlackboxSliderSettingItem( TInt aIdentifier, 
                                                TInt& aSliderValue )
: CAknSliderSettingItem( aIdentifier, aSliderValue )
    {
    // no implementation required
    }

// ----------------------------------------------------
// CBlackboxSliderSettingItem::CreateAndExecuteSettingPageL()
// Creates and executes a slider setting page.
// ----------------------------------------------------
//
void CBlackboxSliderSettingItem::CreateAndExecuteSettingPageL()
    {
    CAknSettingPage* dlg = CreateSettingPageL();

    SetSettingPage( dlg );
    SettingPage()->SetSettingPageObserver(this);

    SettingPage()->SetSettingTextL(SettingName());

    SettingPage()->ExecuteLD( CAknSettingPage::EUpdateWhenChanged );
    SetSettingPage(0);
    }

//  End of File  
