/* ====================================================================
 * File: IntroResource.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INTRORESOURCE_H
#define C_INTRORESOURCE_H

// INCLUDES
#include <e32std.h>
#include <e32base.h>
#include "Blackbox.hrh"

// CLASS DECLARATION

/**
 *  CIntroResource
 *  This class's main purpose is transfer data between container and loader
 */
class CIntroResource : public CBase
    {
public:
    // Constructors and destructor

    /**
     * Destructor.
     */
    virtual ~CIntroResource();

    /**
     * Two-phased constructor.
     */
    static CIntroResource* NewL();

    /**
     * Two-phased constructor.
     */
    static CIntroResource* NewLC();

private:

    /**
     * Constructor for performing 1st stage construction
     */
    CIntroResource();

public:

    /**
     * Get the index number of resource
     * @return get the the count of the resource item
     */
    TInt ResourceIndex();
    
    /**
     * Set the index number of rsource
     * @param aIndex the index which you want to set
     */
    void SetResourceIndex( const TInt aIndex );

    /**
     * Get the image's id
     * @return  get the pic's id which you want to display
     */
    TInt BitmapId();

    /**
     * Set the loaded image's id
     * @param aBitmapId set the pic's id which you want to display
     */
    void SetBitmapId( const TInt aBitmapId );

    /**
     * Get the string's type which need to be loaded 
     * @return TAboutItemType get the resource type defineed in .rh file
     */
    TBlackboxIntroItemType ResourceType();

    /**
     * Set the string's type which need to be loaded 
     * @param aType set the resource type
     */
    void SetResourceType( const TBlackboxIntroItemType aType );

    /**
     * Get about text or about image path
     * @return HBufC a buffer for transter data
     */
    HBufC* ResourceItem();

    /**
     * Set about text or about image path
     * @param aItem a buffer for transter data
     */
    void SetResourceItem( HBufC* aItem );
    
private:

    // The index of the resource
    TInt iResourceIndex;
    
    // Id for the bitmap
    TInt iBitmapId;
    
    // Resource item content
    HBufC* iResourceItem;
    
    // Resource item type
    TBlackboxIntroItemType iResourceType;
    };

#endif // C_INTRORESOURCE_H
