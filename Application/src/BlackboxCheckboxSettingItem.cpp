/* ====================================================================
 * File: BlackboxCheckboxSettingItem.cpp
 * Created: 09/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <avkon.rsg>
#include <Blackbox.rsg>
#include "BlackboxCheckboxSettingItem.h"

// CONSTANTS

const TInt KCheckBoxItemListGranularity = 3;
// size allocated to internal representation of checkbox states
const TInt KInternalRepSize = 128;

// ========================= MEMBER FUNCTIONS ==================================

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::CBlackboxCheckboxSettingItem()
// Default C++ constructor.
// -----------------------------------------------------------------------------
//
CBlackboxCheckboxSettingItem::CBlackboxCheckboxSettingItem(
    TInt aIdentifier, CArrayFix<TInt>& aValueList )
: CAknEnumeratedTextSettingItem(aIdentifier), iExternalValueArray(aValueList)
    {
    // no specific construction code required
    }


// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::~CBlackboxCheckboxSettingItem()
// -----------------------------------------------------------------------------
//
CBlackboxCheckboxSettingItem::~CBlackboxCheckboxSettingItem()
    {
    if ( iSelectionItemListData    ) // if list data has been created
        {
        // delete all items in the array
        iSelectionItemListData->ResetAndDestroy();
        // delete the array itself
        delete iSelectionItemListData;
        }

    // delete the text representation descriptor
    delete iTextRepresentation;
    }

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::CompleteConstructionL()
// -----------------------------------------------------------------------------
//
void CBlackboxCheckboxSettingItem::CompleteConstructionL()
    {
    // finish constructing base class
    CAknEnumeratedTextSettingItem::CompleteConstructionL();

    // construct the item list array
    iSelectionItemListData = new (ELeave) CSelectionItemList( 
                                            KCheckBoxItemListGranularity );

    // the number of variables we have names for - 
    // EnumeratedTextArray is from CAknEnumeratedTextSettingItem
    TInt count = EnumeratedTextArray()->Count();            

    // the number of variables in the external array (from data object)
    TInt numExternals = iExternalValueArray.Count();        


    for ( TInt index = 0; index < count; index++ )
        {
        // create a new CSelectableItem based on the string from the enumerated
        // text array
        CSelectableItem* selectionItem = new(ELeave)CSelectableItem( 
                                *(EnumeratedTextArray()->At(index)->Value()),
                                EFalse );

        CleanupStack::PushL(selectionItem);
        // second-stage construction
        selectionItem->ConstructL();

        // if a corresponding external data item exists
        if (index < numExternals)
            {
            // set the selection status according to the external data value
            selectionItem->SetSelectionStatus(iExternalValueArray[index]);
            }

        // add the item to the SelectionItemListData array
        // selectionItem is now "owned" by CheckboxSettingItem and must be 
        // ResetAndDestroyed at destruction
        iSelectionItemListData->AppendL(selectionItem); 

        CleanupStack::Pop(selectionItem);
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::LoadL()
// -----------------------------------------------------------------------------
//
void CBlackboxCheckboxSettingItem::LoadL()
    {

    // number of items in external data array
    TInt numExternals = iExternalValueArray.Count();

    // copy all items from the external data representation into the internal
    for (TInt i=0;i<numExternals;i++)
        {
        (*iSelectionItemListData)[i]->SetSelectionStatus(iExternalValueArray[i]);
        }

    // make sure the text reflects what's actually stored
    SetTextRepresentationL();
    }

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::StoreL()
// -----------------------------------------------------------------------------
//
void CBlackboxCheckboxSettingItem::StoreL()
    {
    // number of items in external data array
    TInt numExternals = iExternalValueArray.Count();

    // copy all items from the internal data representation to the external
    for (TInt i=0;i<numExternals;i++)
        {
        iExternalValueArray[i] = 
                    (*iSelectionItemListData)[i]->SelectionStatus();
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::EditItemL()
// -----------------------------------------------------------------------------
//
void CBlackboxCheckboxSettingItem::EditItemL( TBool  /*aCalledFromMenu */)
    {
    
    // construct the settings page 
    // based on R_BLACKBOX_SETTING_PAGE_UNLIMITEDRAYS resource
    CAknCheckBoxSettingPage* dlg = 
            new ( ELeave )CAknCheckBoxSettingPage( 
                             R_BLACKBOX_SETTING_PAGE_UNLIMITEDRAYS, 
                             iSelectionItemListData 
                             );

    // execute the dialog - will display the settings page
    if ( dlg->ExecuteLD( CAknSettingPage::EUpdateWhenAccepted ) )
        { 
        // something changed - so update internal representation 
        // of display text
        SetTextRepresentationL();
        // and update the text being displayed
        UpdateListBoxTextL();
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::SettingTextL()
// -----------------------------------------------------------------------------
//
const TDesC& CBlackboxCheckboxSettingItem::SettingTextL()
    {

    // if external data is not available or the text representation has not
    // been created
    if ( ( iExternalValueArray.Count() == 0 ) 
        || !iTextRepresentation ) 
        {
        // ToDo:
        _LIT( KEmptyItemText, "8 rays at most" );
        return KEmptyItemText;
        }
    else
        {
        return *( iTextRepresentation ); // internal representation
        }
    }

// -----------------------------------------------------------------------------
// CBlackboxCheckboxSettingItem::SetTextRepresentationL()
// -----------------------------------------------------------------------------
//
void CBlackboxCheckboxSettingItem::SetTextRepresentationL()
    {

    // if internal representation has not been created
    if (!iTextRepresentation)
        {
        iTextRepresentation = HBufC::NewL(KInternalRepSize); // create it
        }

    // get modifiable pointer to descriptor
    TPtr text = iTextRepresentation->Des();

    // clear descriptor
    text.Zero();
    
    TBool addComma=EFalse;
    _LIT(KComma,", ");

    // number of items in selection list
    TInt nItems = iSelectionItemListData->Count();
    if ( nItems > 0
        && (*iSelectionItemListData)[0]->SelectionStatus() )
        {
        // add item's select string to display string
        text.Append( *(EnumeratedTextArray()->At(0)->Value()));   
        }
    else
        {
        // ToDo:
        _LIT( KItemText, "8 rays at most" );
        text.Append( KItemText );
        }
    }

// End of File
