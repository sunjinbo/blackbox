/* ====================================================================
 * File: LayoutManager.cpp
 * Created: 09/04/10
 * Author: Sun Jinbo
 * Copyright (c): Tieto, All rights reserved
 * ==================================================================== */

// INCLUDE FILES
#include <AknUtils.h>
#include <e32property.h>
#include "LayoutManager.h"

// ======== MEMBER FUNCTIONS ========

// ----------------------------------------------------------------------------
// CLayoutManager::NewL
// ----------------------------------------------------------------------------
//
CLayoutManager* CLayoutManager::NewL()
    {
    CLayoutManager* self = new (ELeave) CLayoutManager;
    CleanupStack::PushL (self );
    self->ConstructL ();
    CleanupStack::Pop();
    return self;
    }

// ----------------------------------------------------------------------------
// CLayoutManager::~CLayoutManager
// ----------------------------------------------------------------------------
//
CLayoutManager::~CLayoutManager()
    { 
    // No implementation required.
    }

// ----------------------------------------------------------------------------
// CLayoutManager::ResolutionChanged
//
// Function can be used to update internal resolution value.
// Typically called by container in startup,
// and when dynamic layout variant switch has occured.
//
// ----------------------------------------------------------------------------
//
void CLayoutManager::ResolutionChanged( TOrientation aOrientation )
    {
    // Get screen parameters for solving layout
    TRect screenRect;
    AknLayoutUtils::LayoutMetricsRect( AknLayoutUtils::EScreen, screenRect );

    switch ( screenRect.Width() )
        {
        case KQhdPortraitWidth:
            {
                {
                if ( aOrientation == ELandscape )
                    iResolution = EQhdLandscape;
                else
                    iResolution = EQhdPortrait;
                }
            }
            break;
        case KQhdLandscapeWidth: // Also KHvgaPortraitWidth
            {
            if ( screenRect.Height() == KQhdLandscapeHeight )
                {
                if ( aOrientation == EPortrait )
                    iResolution = EQhdPortrait;
                else
                    iResolution = EQhdLandscape;
                }
            }
            break;
        default:
            iResolution = ENotSupported;
            break;
        }
    }

// ----------------------------------------------------------------------------
// CLayoutManager::LayoutRect
// LayoutRect should be called from control's SizeChanged() method.
// ----------------------------------------------------------------------------
//
TRect CLayoutManager::LayoutRect( TComponent aComponent ) const
    {
    TRect layoutRect( 0, 0, 0,0 );

    switch ( aComponent )
        {
        // Screen
        case EScreen:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscBgLeft,
                            KQhdLscBgTop,
                            KQhdLscBgRight,
                            KQhdLscBgBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtBgLeft,
                            KQhdPrtBgTop,
                            KQhdPrtBgRight,
                            KQhdPrtBgBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }
        
        // Button Start
        case EButtonStart:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscButtonStartLeft,
                            KQhdLscButtonStartTop,
                            KQhdLscButtonStartRight,
                            KQhdLscButtonStartBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtButtonStartLeft,
                            KQhdPrtButtonStartTop,
                            KQhdPrtButtonStartRight,
                            KQhdPrtButtonStartBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Button Ovi
        case EButtonOvi:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscButtonOviLeft,
                            KQhdLscButtonOviTop,
                            KQhdLscButtonOviRight,
                            KQhdLscButtonOviBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtButtonOviLeft,
                            KQhdPrtButtonOviTop,
                            KQhdPrtButtonOviRight,
                            KQhdPrtButtonOviBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

            // Scene Pane
            case EScenePane:
                {
                switch ( iResolution )
                    {
                    case EQhdLandscape:
                        {
                        layoutRect.SetRect( 
                                KQhdLscScenePaneLeft,
                                KQhdLscScenePaneTop,
                                KQhdLscScenePaneRight,
                                KQhdLscScenePaneBottom );
                        break;
                        }
                    case EQhdPortrait:
                        {
                        layoutRect.SetRect( 
                                KQhdPrtScenePaneLeft,
                                KQhdPrtScenePaneTop,
                                KQhdPrtScenePaneRight,
                                KQhdPrtScenePaneBottom );
                        break;
                        }
                    default:
                        break;
                    }
                break;
                }
            
        // Score Pane
        case EScorePane:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscScorePaneLeft,
                            KQhdLscScorePaneTop,
                            KQhdLscScorePaneRight,
                            KQhdLscScorePaneBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtScorePaneLeft,
                            KQhdPrtScorePaneTop,
                            KQhdPrtScorePaneRight,
                            KQhdPrtScorePaneBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

		// Score Guess Pane
		case EScoreGuessPane:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscScoreGuessPaneLeft,
							KQhdLscScoreGuessPaneTop,
							KQhdLscScoreGuessPaneRight,
							KQhdLscScoreGuessPaneBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtScoreGuessPaneLeft,
							KQhdPrtScoreGuessPaneTop,
							KQhdPrtScoreGuessPaneRight,
							KQhdPrtScoreGuessPaneBottom );
					break;
					}
				default:
					break;
				}
			break;
			}
            
		// Score Rays Pane
		case EScoreRaysPane:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscScoreRaysPaneLeft,
							KQhdLscScoreRaysPaneTop,
							KQhdLscScoreRaysPaneRight,
							KQhdLscScoreRaysPaneBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtScoreRaysPaneLeft,
							KQhdPrtScoreRaysPaneTop,
							KQhdPrtScoreRaysPaneRight,
							KQhdPrtScoreRaysPaneBottom );
					break;
					}
				default:
					break;
				}
			break;
			}
			
        // Welcome icon
        case EWelcIcon:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscWelcIconLeft,
                            KQhdLscWelcIconTop,
                            KQhdLscWelcIconRight,
                            KQhdLscWelcIconBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtWelcIconLeft,
                            KQhdPrtWelcIconTop,
                            KQhdPrtWelcIconRight,
                            KQhdPrtWelcIconBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Welcome greeting text
        case EWelcGreetingText:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscWelcGreetingTextLeft,
                            KQhdLscWelcGreetingTextTop,
                            KQhdLscWelcGreetingTextRight,
                            KQhdLscWelcGreetingTextBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtWelcGreetingTextLeft,
                            KQhdPrtWelcGreetingTextTop,
                            KQhdPrtWelcGreetingTextRight,
                            KQhdPrtWelcGreetingTextBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

		// Welcome query
		case EWelcQuery:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscWelcQueryLeft,
							KQhdLscWelcQueryTop,
							KQhdLscWelcQueryRight,
							KQhdLscWelcQueryBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtWelcQueryLeft,
							KQhdPrtWelcQueryTop,
							KQhdPrtWelcQueryRight,
							KQhdPrtWelcQueryBottom );
					break;
					}
				default:
					break;
				}
			break;
			}

		// Welcome query title
		case EWelcQueryTitle:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscWelcQueryTitleLeft,
							KQhdLscWelcQueryTitleTop,
							KQhdLscWelcQueryTitleRight,
							KQhdLscWelcQueryTitleBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtWelcQueryTitleLeft,
							KQhdPrtWelcQueryTitleTop,
							KQhdPrtWelcQueryTitleRight,
							KQhdPrtWelcQueryTitleBottom );
					break;
					}
				default:
					break;
				}
			break;
			}

		// Welcome query main pane
		case EWelcQueryMainPane:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscWelcQueryMainPaneLeft,
							KQhdLscWelcQueryMainPaneTop,
							KQhdLscWelcQueryMainPaneRight,
							KQhdLscWelcQueryMainPaneBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtWelcQueryMainPaneLeft,
							KQhdPrtWelcQueryMainPaneTop,
							KQhdPrtWelcQueryMainPaneRight,
							KQhdPrtWelcQueryMainPaneBottom );
					break;
					}
				default:
					break;
				}
			break;
			}

		// Welcome query hyperLink
		case EWelcQueryHyperLink:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscWelcQueryHyperLinkLeft,
							KQhdLscWelcQueryHyperLinkTop,
							KQhdLscWelcQueryHyperLinkRight,
							KQhdLscWelcQueryHyperLinkBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtWelcQueryHyperLinkLeft,
							KQhdPrtWelcQueryHyperLinkTop,
							KQhdPrtWelcQueryHyperLinkRight,
							KQhdPrtWelcQueryHyperLinkBottom );
					break;
					}
				default:
					break;
				}
			break;
			}

		// Promo brand
		case EPromoBrand:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscPromoBrandLeft,
							KQhdLscPromoBrandTop,
							KQhdLscPromoBrandRight,
							KQhdLscPromoBrandBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtPromoBrandLeft,
							KQhdPrtPromoBrandTop,
							KQhdPrtPromoBrandRight,
							KQhdPrtPromoBrandBottom );
					break;
					}
				default:
					break;
				}
			break;
			}

		// Promo loading
		case EPromoLoading:
			{
			switch ( iResolution )
				{
				case EQhdLandscape:
					{
					layoutRect.SetRect( 
							KQhdLscPromoLoadingLeft,
							KQhdLscPromoLoadingTop,
							KQhdLscPromoLoadingRight,
							KQhdLscPromoLoadingBottom );
					break;
					}
				case EQhdPortrait:
					{
					layoutRect.SetRect( 
							KQhdPrtPromoLoadingLeft,
							KQhdPrtPromoLoadingTop,
							KQhdPrtPromoLoadingRight,
							KQhdPrtPromoLoadingBottom );
					break;
					}
				default:
					break;
				}
			break;
			}

        // Avatar pane
        case EAvatarPane:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscAvatarPaneLeft,
                            KQhdLscAvatarPaneTop,
                            KQhdLscAvatarPaneRight,
                            KQhdLscAvatarPaneBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtAvatarPaneLeft,
                            KQhdPrtAvatarPaneTop,
                            KQhdPrtAvatarPaneRight,
                            KQhdPrtAvatarPaneBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Avatar
        case EAvatar:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscAvatarLeft,
                            KQhdLscAvatarTop,
                            KQhdLscAvatarRight,
                            KQhdLscAvatarBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtAvatarLeft,
                            KQhdPrtAvatarTop,
                            KQhdPrtAvatarRight,
                            KQhdPrtAvatarBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Avatar dialog
        case EAvatarDialog:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscAvatarDialogLeft,
                            KQhdLscAvatarDialogTop,
                            KQhdLscAvatarDialogRight,
                            KQhdLscAvatarDialogBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtAvatarDialogLeft,
                            KQhdPrtAvatarDialogTop,
                            KQhdPrtAvatarDialogRight,
                            KQhdPrtAvatarDialogBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }

        // Avatar dialog text
        case EAvatarDialogText:
            {
            switch ( iResolution )
                {
                case EQhdLandscape:
                    {
                    layoutRect.SetRect( 
                            KQhdLscAvatarDialogTextLeft,
                            KQhdLscAvatarDialogTextTop,
                            KQhdLscAvatarDialogTextRight,
                            KQhdLscAvatarDialogTextBottom );
                    break;
                    }
                case EQhdPortrait:
                    {
                    layoutRect.SetRect( 
                            KQhdPrtAvatarDialogTextLeft,
                            KQhdPrtAvatarDialogTextTop,
                            KQhdPrtAvatarDialogTextRight,
                            KQhdPrtAvatarDialogTextBottom );
                    break;
                    }
                default:
                    break;
                }
            break;
            }
            
        default:
            break;
        }
    return layoutRect;
    }

// ----------------------------------------------------------------------------
// CLayoutManager::LayoutRect
// ----------------------------------------------------------------------------
//
CLayoutManager::CLayoutManager()
    { 
    // no implementation required.
    }

// ----------------------------------------------------------------------------
// CLayoutManager::ConstructL
// ----------------------------------------------------------------------------
//
void CLayoutManager::ConstructL()
    { 
    // no implementation required.
    }

// End of File
