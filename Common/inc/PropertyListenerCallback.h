/*
* ============================================================================
*  Name        : mpropertylistenercallback.h
*  Part of     : ?Subsystem_name / ?Module_name
*  Interface   : ?Interface_category, ?Interface_name
*  Description : ?Description
*  Version     : %version: 2 % << Don't touch! Updated by Synergy at check-out.
*
*  Copyright (c) 2009 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ==============================================================================
*/

#ifndef M_PROPERTYLISTENERCALLBACK_H
#define M_PROPERTYLISTENERCALLBACK_H

/**
* Property listener call back interface. 
*/
class MPropertyListenerCallBack
    {
    public:
    
        /**
        * Notifies that property value has changed. 
        * @param None
        * @return None
        */
        virtual void HandlePropertyChangedL() = 0;
    
    protected:
    
        // Deny destruction through this class
        virtual ~MPropertyListenerCallBack(){};
    };
    
#endif//M_PROPERTYLISTENERCALLBACK_H
