/* ====================================================================
 * File: IntroResourceLoader.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INTRORESOURCELOADER_H
#define C_INTRORESOURCELOADER_H

#include <e32base.h>    // For CActive
#include <barsread.h>    // For TResourceReader
#include "Blackbox.hrh"

// Class declaration
class CEikonEnv;
class MResourceLoaderObserver;
class RConeResourceLoader;
class CIntroResource;

/*
 * CIntroResourceLoader class
 * The resource loader for about application.
 * Resource loader load the resource items asynchronously.
 */
class CIntroResourceLoader : public CActive
    {
public:
    // Cancel and destroy
    ~CIntroResourceLoader();

    // Two-phased constructor.
    static CIntroResourceLoader* NewL( CEikonEnv* aEikonEnv,
                            MResourceLoaderObserver* aObserver );

    // Two-phased constructor.
    static CIntroResourceLoader* NewLC( CEikonEnv* aEikonEnv, 
                            MResourceLoaderObserver* aObserver );

private:
    // C++ constructor
    CIntroResourceLoader( CEikonEnv* aEikonEnv, 
                    MResourceLoaderObserver* aObserver );

    // Second-phase constructor
    void ConstructL();

private: //From CActive
    void RunL();
    void DoCancel();
    TInt RunError( TInt aError );
    
private:
    /*
     * Activate itself.
     */
    void Activate();
    
public:
    
    /*
     * Start the loader. 
     * Note: The resource id must be set before this method called,
     * otherwise, leave with KErrGeneral.
     */
    void StartL();
    
    /**
     * Set the id of the resource to be loaded.
     * @Param aResourceId the id of the resource to be loaded.
     * @aLoaded Indicate the resource file has been loaded or not.
     * If the resource file is not load yet, the resource path must
     * pass to loader.
     * @aResourcePath the path of the resource file which the resouce stored in.
     */
    void SetResourceId( const TInt aResourceId, 
        const TBool aLoaded, const TDesC& aResourcePath );
    
    /**
     * Get the currentlly resource Id from the loader
     * @Return The current resource Id 
     */
    TInt CurrentResourceId();
    
    /*
     * Get the loaded items array.
     * @Return The loaded items array.
     */
    RPointerArray<CIntroResource>* LoadedResourceItems() const;
    
    /*
     * Delete the loaded items. 
     */
    void ReleaseLoadedItems();
    
    /*
     * Return the count of the item in the resource.
     */
    TInt ItemCount() const;

private:
    // Ref: Environment.
    CEikonEnv* iEnv;
    
    // The id of the resource which the stings stored in.
    TInt iResourceId;
    
    // The flag indicates the resource file has been loaded or not.
    TBool iLoaded;
    
    // The path of resource file
    TFileName iResourcePath;
    
    // Ref: Observer
    MResourceLoaderObserver* iObserver;
    
    // Iterator.
    TInt iItemIterator;
    
    // Owned: the buffer for the resource.
    HBufC8* iResourceBuffer;
    
    // Reader.
    TResourceReader iReader;
    
    // The count of the items in the resource.
    TInt iItemCount;
    
    // Owned: Resource file loader.
    RConeResourceLoader* iLoader;
    
    // Owned: the array store the loaded items.
    RPointerArray<CIntroResource>* iLoadedItem;

    };

#endif // C_INTRORESOURCELOADER_H
