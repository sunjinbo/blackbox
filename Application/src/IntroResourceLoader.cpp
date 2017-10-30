/* ====================================================================
 * File: IntroResourceLoader.cpp
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <StringLoader.h>               // For StringLoader
#include <ConeResLoader.h>              // For RConeResourceLoader
#include <eikenv.h>                     // For CEikonEnv
#include <StringLoader.h>               // For StringLoader
#include <f32file.h>
#include <bautils.h>

#include "IntroResourceLoader.h"
#include "IntroResource.h"              // For CIntroResource
#include "MResourceLoaderObserver.h"    // For MResourceLoaderObserver

// CONSTANTS
const TInt KDefaultResourceId( -1 ); // Default resource id.
// The count for the resouce that to be loaded in one time.
const TInt KDefaultItemLoadingCount( 10 );

// ---------------------------------------------------------
// CIntroResourceLoader::CIntroResourceLoader()
//
// ---------------------------------------------------------
CIntroResourceLoader::CIntroResourceLoader( CEikonEnv* aEikonEnv,
                                    MResourceLoaderObserver* aObserver ) 
                     : CActive( EPriorityLow ),
                       iEnv( aEikonEnv ),
                       iResourceId( KDefaultResourceId ),
                       iObserver( aObserver )
    {
    
    }

// ---------------------------------------------------------
// CIntroResourceLoader::NewLC()
//
// ---------------------------------------------------------
CIntroResourceLoader* CIntroResourceLoader::NewLC( CEikonEnv* aEikonEnv, 
                                        MResourceLoaderObserver* aObserver )
    {
    CIntroResourceLoader* self = new ( ELeave ) CIntroResourceLoader( 
                                                    aEikonEnv, aObserver );
    CleanupStack::PushL(self);
    self->ConstructL();
    return self;
    }

// ---------------------------------------------------------
// CIntroResourceLoader::NewL()
//
// ---------------------------------------------------------
CIntroResourceLoader* CIntroResourceLoader::NewL( CEikonEnv* aEikonEnv, 
                                        MResourceLoaderObserver* aObserver )
    {
    CIntroResourceLoader* self = CIntroResourceLoader::NewLC( 
                                            aEikonEnv, aObserver );
    CleanupStack::Pop(); // self;
    return self;
    }

// ---------------------------------------------------------
// CIntroResourceLoader::ConstructL()
//
// ---------------------------------------------------------
void CIntroResourceLoader::ConstructL()
    {
    CActiveScheduler::Add(this); // Add to scheduler
    iLoadedItem = new(ELeave) RPointerArray<CIntroResource>();
    iLoader = new(ELeave) RConeResourceLoader( *iEnv );
    }

// ---------------------------------------------------------
// CIntroResourceLoader::CIntroResourceLoader()
// 
// ---------------------------------------------------------
CIntroResourceLoader::~CIntroResourceLoader()
    {
    Cancel(); // Cancel any request, if outstanding
    if ( iLoadedItem )
        {
        iLoadedItem->ResetAndDestroy();
        delete iLoadedItem;
        iLoadedItem = NULL;
        }
    if ( iResourceBuffer )
        {
        delete iResourceBuffer;
        iResourceBuffer = NULL;
        }
    if ( iLoader )
        {
        iLoader->Close();
        delete iLoader;
        iLoader = NULL;
        }
    }

// ---------------------------------------------------------
// CIntroResourceLoader::DoCancel()
// 
// ---------------------------------------------------------
void CIntroResourceLoader::DoCancel()
    {
    iItemIterator = 0;
    // Delete the resource buffer.
    if ( iResourceBuffer )
        {
        delete iResourceBuffer;
        iResourceBuffer = NULL;
        }
    
    if ( iLoader )
        {
        iLoader->Close();
        }
    }

// ---------------------------------------------------------
// CIntroResourceLoader::StartL()
// 
// ---------------------------------------------------------
void CIntroResourceLoader::StartL()
    {
    // Leave with KErrGeneral if the resource id is not set.
    if ( iResourceId == KDefaultResourceId )
        {
        User::Leave( KErrGeneral );
        }
    
    Cancel();
    
    iItemIterator = 0;
    ReleaseLoadedItems();
    
    if ( !iLoaded )
        {
        // Init the rsc file path
        TFileName filePath( iResourcePath );
        BaflUtils::NearestLanguageFile( iEnv->FsSession(), filePath );
        iLoader->Close();
        iLoader->OpenL( filePath );
        }
    
    if ( iResourceBuffer )
        {
        delete iResourceBuffer;
        iResourceBuffer = NULL;
        }
    
    iResourceBuffer = iEnv->AllocReadResourceAsDes8LC( iResourceId );
    iReader.SetBuffer( iResourceBuffer );
    iItemCount = iReader.ReadInt16();
    CleanupStack::Pop(); // iResourceBuffer
    
    Activate();
    }

// ---------------------------------------------------------
// CIntroResourceLoader::RunL()
// 
// ---------------------------------------------------------
void CIntroResourceLoader::RunL()
    {
    TInt err = KErrNone;
    for ( ; iItemIterator < iItemCount; iItemIterator++ )
        {
        CIntroResource* aboutResource = CIntroResource::NewL();
        CleanupStack::PushL( aboutResource );
        TInt type = iReader.ReadInt8();
        
        // Load Text
        if ( type == EIntroTextItem )
            {
            HBufC* resourceItem( NULL );
            // There are two different text, one is direct output and another needs format
            if ( iReader.ReadInt8() == EIntroUpdateTime )
                {
                // About text needs format
                TTime time;
                time.UniversalTime();
                TDateTime currentTime = time.DateTime();
                resourceItem = StringLoader::LoadLC( iReader.ReadInt32(), 
                                            currentTime.Year(), CEikonEnv::Static() );
                }
            else
                {
                // Direct output about text
                resourceItem = iEnv->AllocReadResourceLC( iReader.ReadInt32() );
                }
            // Set the loaded item
            aboutResource->SetResourceItem( resourceItem );
            // Set the loaded item
            aboutResource->SetResourceIndex( iItemIterator );
            iLoadedItem->AppendL( aboutResource );
            CleanupStack::Pop( 2 ); // resourceItem and aboutResource
            }
        // Load image.
        else if ( type == EIntroImageItem )
            {
            TPtrC imageFile = iReader.ReadTPtrC();
            aboutResource->SetResourceItem( imageFile.AllocL() );
            aboutResource->SetBitmapId( iReader.ReadInt16() );
            aboutResource->SetResourceType( EIntroImageItem );
            iLoadedItem->AppendL( aboutResource );
            CleanupStack::Pop(); // aboutResource
            }
        else
            {
            err = KErrNotSupported;
            CleanupStack::PopAndDestroy(); // aboutResource
            break;
            }
        
        // Ten items per loading and calculate the number of loaded
        if ( ( iItemIterator % KDefaultItemLoadingCount ) 
                            == ( KDefaultItemLoadingCount - 1 ) )
            {
            // Once the value of iItemIterator > 10, we should break
            iItemIterator++;
            break;
            }
        }
    
    // Notify observer.
    if ( err == KErrNone && iItemIterator < iItemCount )
        {
        // Ten items loading over, Notify HandleItemsLoadedL observer
        iObserver->HandleItemsLoadedL( err );
        Activate();
        }
    else
        {
        // Once there is not enough ten items, need run this function again
        iObserver->HandleItemsLoadedL( err );
        // One resource loading over, Notify HandleResourceLoadCompletedL observer
        iObserver->HandleResourceLoadCompletedL( iResourceId, err );
        }
    }

// ---------------------------------------------------------
// CIntroResourceLoader::RunError()
//
// ---------------------------------------------------------
TInt CIntroResourceLoader::RunError( TInt aError )
    {
    return aError;
    }

// ---------------------------------------------------------
// CIntroResourceLoader::Activate()
//
// ---------------------------------------------------------
void CIntroResourceLoader::Activate()
    {
    TRequestStatus* status = &iStatus;
    *status = KRequestPending;
    User::RequestComplete( status, KErrNone );
    SetActive();
    }

// ---------------------------------------------------------
// CIntroResourceLoader::SetResourceId()
//
// ---------------------------------------------------------
void CIntroResourceLoader::SetResourceId( const TInt aResourceId, 
                        const TBool aLoaded, const TDesC& aResourcePath )
    {
    iResourceId = aResourceId;
    iLoaded = aLoaded;
    iResourcePath.Copy( aResourcePath );
    }

// ---------------------------------------------------------
// CIntroResourceLoader::CurrentResourceId()
//
// ---------------------------------------------------------
TInt CIntroResourceLoader::CurrentResourceId()
    {
    return iResourceId;
    }

// ---------------------------------------------------------
// CIntroResourceLoader::LoadedResourceItems()
//
// ---------------------------------------------------------
RPointerArray<CIntroResource>* CIntroResourceLoader::LoadedResourceItems() const
    {
    return iLoadedItem;
    }

// ---------------------------------------------------------
// CIntroResourceLoader::RleaseLoadedItems()
//
// ---------------------------------------------------------
void CIntroResourceLoader::ReleaseLoadedItems()
    {
    iLoadedItem->ResetAndDestroy();
    }

// ---------------------------------------------------------
// CIntroResourceLoader::ItemCount()
//
// ---------------------------------------------------------
TInt CIntroResourceLoader::ItemCount() const
    {
    return iItemCount;
    }

// End of file
