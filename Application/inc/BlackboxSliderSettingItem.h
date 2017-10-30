/* ====================================================================
 * File: BlackboxSliderSettingItem.h
 * Created: 10/09/10
 * Aucherry: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef BLACKBOXSLIDERSETTINGITEM_H
#define BLACKBOXSLIDERSETTINGITEM_H

//  INCLUDES
#include <AknSettingItemList.h>

// CLASS DECLARATION

/**
* CBlackboxSliderSettingItem class derived from CAknSliderSettingItem.
*
* Overwrites functions SettingTextL() and CreateBitmapL() in order to enable displaying
* textual current value instead of a bitmap in the settings item list. Should not be
* further derived.
*
*/
class CBlackboxSliderSettingItem : public CAknSliderSettingItem
    {
public:
    /**
    * C++ default constructor.
    */
    CBlackboxSliderSettingItem( TInt aIdentifier, TInt& aSliderValue );

public: // from CAknSliderSettingItem
    void CreateAndExecuteSettingPageL();
    };

#endif // BLACKBOXSLIDERSETTINGITEM_H   

// End of File
