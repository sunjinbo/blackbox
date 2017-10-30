/* ====================================================================
 * File: MResourceLoaderObserver.h
 * Created: 07/10/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */


#ifndef M_RESOURCELOADEROBSERVER_H
#define M_RESOURCELOADEROBSERVER_H

/*
 * MResourceLoaderObserver class.
 */
class MResourceLoaderObserver
    {
public:
    /*
     * Handle items loaded event. The items loaded event will be emit 
     * when fixed items loaded.
     * @aError KErrNone if there is no error occurs, 
     * otherwise return system wide error code.
     */
    virtual void HandleItemsLoadedL( TInt aError ) = 0;
    
    /*
     * Handle the resouce loading completed event.
     * @aResourceId the id for the resource which has been loaded.
     * @aError KErrNone if there is no error occurs, 
     * otherwise retrurn system wide error code.
     */
    virtual void HandleResourceLoadCompletedL( const TInt aResourceId, TInt aError ) = 0;
    };

#endif /* M_RESOURCELOADEROBSERVER_H */

// End of file

