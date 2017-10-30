/* ====================================================================
 * File: BlackboxEditor.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_BLACKBOXEDITOR_H
#define C_BLACKBOXEDITOR_H

// INCLUDE FILES
#include <e32base.h>
#include <eikrted.h>

// FORWARD DECLARATION
class CGulIcon;
class CEikRichTextEditor;

// CLASS DECLARATION

/**
 *  CBlackboxEditor class
 */
class CBlackboxEditor : public CBase
    {
public: // Constructors and destructor
    static CBlackboxEditor* NewL(const CCoeControl* aControl);
    virtual ~CBlackboxEditor();

public: // New methods
    void InsertTextL(const TDesC& aText);
    void InitFormatsL();
    inline CEikRichTextEditor* Editor() { return iEditor; }
    void SetRect( const TRect& aRect );
    void HandleSkinChangeL();

private:  // Constructors
    CBlackboxEditor();
    void ConstructL(const CCoeControl* aControl);

private: // New methods
    CRichText& RichText() const;
    void SetRectL( const TRect& aRect );

private: // Data
    CEikRichTextEditor* iEditor; // Owns

    TInt iPos;
    CParaFormat iParaFormat;
    TParaFormatMask iParaFormatMask;
    TCharFormat iCharFormat;
    TCharFormatMask iCharFormatMask;
    TRgb iTextColor;
    };

#endif // C_BLACKBOXEDITOR_H

// End of file
