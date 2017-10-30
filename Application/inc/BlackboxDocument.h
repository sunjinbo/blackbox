/* ====================================================================
 * File: BlackboxDocument.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef __BLACKBOX_DOCUMENT_H__
#define __BLACKBOX_DOCUMENT_H__


#include <akndoc.h>

// Forward references
class CBlackboxAppUi;
class CEikApplication;


/*! 
  @class CBlackboxDocument
  
  @discussion An instance of class CBlackboxDocument is the Document part of the AVKON
  application framework for the Blackbox example application
  */
class CBlackboxDocument : public CAknDocument
    {
public:

/*!
  @function NewL
  
  @discussion Construct a CBlackboxDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBlackboxDocument
  */
    static CBlackboxDocument* NewL(CEikApplication& aApp);

/*!
  @function NewLC
  
  @discussion Construct a CBlackboxDocument for the AVKON application aApp 
  using two phase construction, and return a pointer to the created object
  @param aApp application creating this document
  @result a pointer to the created instance of CBlackboxDocument
  */
    static CBlackboxDocument* NewLC(CEikApplication& aApp);

/*!
  @function ~CBlackboxDocument
  
  @discussion Destroy the object and release all memory objects
  */
    ~CBlackboxDocument();

public: // from CAknDocument
/*!
  @function CreateAppUiL 
  
  @discussion Create a CBlackboxAppUi object and return a pointer to it
  @result a pointer to the created instance of the AppUi created
  */
    CEikAppUi* CreateAppUiL();

private:

/*!
  @function ConstructL
  
  @discussion Perform the second phase construction of a CBlackboxDocument object
  */
    void ConstructL();

/*!
  @function CBlackboxDocument
  
  @discussion Perform the first phase of two phase construction 
  @param aApp application creating this document
  */
    CBlackboxDocument(CEikApplication& aApp);

    };


#endif // __BLACKBOX_DOCUMENT_H__
