/* ====================================================================
 * File: IntroResource.cpp
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include "IntroResource.h"

// CONSTANTS
const TInt KDefaultResourceIndex( -1 ); // Default resource index.
const TInt KDefaultBitmapId( -1 ); // Default bitmap id.

// ---------------------------------------------------------
// CIntroResource::CIntroResource()
//
// ---------------------------------------------------------
CIntroResource::CIntroResource():iResourceIndex( KDefaultResourceIndex ),
                                 iBitmapId( KDefaultBitmapId ),
                                 iResourceItem( NULL ),
                                 iResourceType( EIntroTextItem )
    {
    }

// ---------------------------------------------------------
// CIntroResource::~CIntroResource()
//
// ---------------------------------------------------------
CIntroResource::~CIntroResource()
    {
    if ( iResourceItem )
        {
        delete iResourceItem;
        iResourceItem = NULL;
        }
    }

// ---------------------------------------------------------
// CIntroResource::NewLC()
//
// ---------------------------------------------------------
CIntroResource* CIntroResource::NewLC()
    {
    CIntroResource* self = new ( ELeave ) CIntroResource();
    CleanupStack::PushL(self);
    return self;
    }

// ---------------------------------------------------------
// CIntroResource::NewL()
//
// ---------------------------------------------------------
CIntroResource* CIntroResource::NewL()
    {
    CIntroResource* self = CIntroResource::NewLC();
    CleanupStack::Pop(); // self;
    return self;
    }

// ---------------------------------------------------------
// CIntroResource::ResourceIndex()
//
// ---------------------------------------------------------
TInt CIntroResource::ResourceIndex()
    {
    return iResourceIndex;
    }

// ---------------------------------------------------------
// CIntroResource::SetResourceIndex()
//
// ---------------------------------------------------------
void CIntroResource::SetResourceIndex( const TInt aIndex )
    {
    iResourceIndex = aIndex;
    }

// ---------------------------------------------------------
// CIntroResource::BitmapId()
//
// ---------------------------------------------------------
TInt CIntroResource::BitmapId()
    {
    return iBitmapId;
    }

// ---------------------------------------------------------
// CIntroResource::SetBitmapId()
//
// ---------------------------------------------------------
void CIntroResource::SetBitmapId( const TInt aBitmapId )
    {
    iBitmapId = aBitmapId;
    }

// ---------------------------------------------------------
// CIntroResource::ResourceType()
//
// ---------------------------------------------------------
TBlackboxIntroItemType CIntroResource::ResourceType()
    {
    return iResourceType;
    }

// ---------------------------------------------------------
// CIntroResource::SetResourceType()
//
// ---------------------------------------------------------
void CIntroResource::SetResourceType( TBlackboxIntroItemType aType )
    {
    iResourceType = aType;
    }

// ---------------------------------------------------------
// CIntroResource::ResourceItem()
//
// ---------------------------------------------------------
HBufC* CIntroResource::ResourceItem()
    {
    return iResourceItem;
    }

// ---------------------------------------------------------
// CIntroResource::SetResourceItem()
//
// ---------------------------------------------------------
void CIntroResource::SetResourceItem( HBufC* aItem )
    {
    iResourceItem = aItem;
    }

// End of file

