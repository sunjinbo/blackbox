/*
* ============================================================================
*  Name        : mpropertyobserver.h
*  Part of     : Welcome2
*  Interface   : Welcome2
*  Description : Welcome2 property observer
*  Version     : %version: 1 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright © 2008 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
* Template version: 4.0
*/

#ifndef __MPROPERTYOBSERVER_H__
#define __MPROPERTYOBSERVER_H__

// INCLUDES

// FORWARD DECLARATIONS

// CLASS DECLARATION

class MPropertyObserver
    {

    // New functions
    public:
    
        /**
         * Through this method the Property subscribers notify of 
         * Property changes
         *
         * @param aCategory The category of the property to be observed
         * @param aKey The subkey of the property to be observed
         */
        virtual void HandlePropertyChangedL( 
                                        const TUid& aCategory, 
                                        TInt aKey ) = 0;
};

#endif //__MPROPERTYOBSERVER_H__
