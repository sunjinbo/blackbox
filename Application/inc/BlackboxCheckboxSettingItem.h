/* ====================================================================
 * File: BlackboxCheckboxSettingItem.h
 * Created: 09/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXCHECKBOXSETTINGITEM_H
#define C_BLACKBOXCHECKBOXSETTINGITEM_H

// INCLUDE FILES
#include <aknsettingitemlist.h>
#include <aknCheckBoxSettingPage.h>

// CLASS DECLARATION

/**
 *  CBox class
 */
class CBlackboxCheckboxSettingItem : public CAknEnumeratedTextSettingItem
    {
public: // Constructor and destructor
    CBlackboxCheckboxSettingItem(
        TInt aIdentifier, CArrayFix<TInt>& aExternalValueArray );
    virtual ~CBlackboxCheckboxSettingItem();

public: // from CAknEnumeratedTextSettingItem
    void LoadL();
    void StoreL();
    void EditItemL( TBool aCalledFromMenu );
    void CompleteConstructionL();
    const TDesC& SettingTextL();

private:
    void SetTextRepresentationL() ;

private: // Member data
    CSelectionItemList* iSelectionItemListData;
    CArrayFix<TInt>& iExternalValueArray; 
    HBufC* iTextRepresentation; // Owned
    };

#endif //C_BLACKBOXCHECKBOXSETTINGITEM_H
