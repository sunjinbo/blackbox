/* ====================================================================
 * File: IntroImage.h
 * Created: 09/03/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

#ifndef C_INTROIMAGE_H
#define C_INTROIMAGE_H

// INCLUDES

// FORWARD DECLARATIONS
class CFbsBitmap;

// CONSTANTS

const TInt KImageTopMargin = 4 ;
const TInt KImageBottomMargin = 4;

// CLASS DECLARATION

/**
*  CIntroImage class
*/
class CIntroImage : public CBase
    {
public: // Constructors and destructor
        
    static CIntroImage* NewLC( 
		        const TDesC& aFileName, 
		        TInt aBitmapId,
                TInt aStartLine, 
				TInt aBaseLineDelta, 
				TBool aTypeFlag 
				);

        /**
        * Destructor
        */
        virtual ~CIntroImage();

public: // New functions

    TInt HeightInPixels() const;
    TInt WidthInPixels() const;
    TInt StartLine() const;
    TInt EndLine() const;
    TInt Lines() const;
    const CFbsBitmap* Bitmap() const;
    const CFbsBitmap* BitmapMask() const;

private: // private constructor

    /**
     * C++ default constructor.
     */
    CIntroImage();

private:  // Data

    CFbsBitmap* iBitmap; // owned
    CFbsBitmap* iBitmapMask; //owned
    TInt iStartLine;
    TInt iEndLine;
    };

#endif // C_INTROIMAGE_H

// End of File
