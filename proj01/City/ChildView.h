/**
* \file ChildView.h
*
* \author Charles B. Owen
*
* \brief Class that implements the child window our program draws in.
*
* The window is a child of the main frame, which holds this
* window, the menu bar, and the status bar.
*/

#pragma once

#include "City.h"

class CTile;

/** \brief The child window our program draws in. */
class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()

private:
    void AddBuilding(const std::wstring &file);
    void AddLandscape(const std::wstring &file);

    /// The city
    CCity mCity;

    /// True until the first time we draw
    bool mFirstDraw = true;

    long long mLastTime;    ///< Last time we read the timer
    double mTimeFreq;       ///< Rate the timer updates

    /// Any item we are currently dragging
    std::shared_ptr<CTile> mGrabbedItem;

    std::unique_ptr<Gdiplus::Bitmap> mTrashcan; ///< Trashcan image to use
    int mTrashcanTop = 0;           ///< Top line of the trashcan in pixels
    int mTrashcanRight = 0;         ///< Right side of the trashcan in pixels

	std::unique_ptr<Gdiplus::Bitmap> mNavigation;	///< Navigation image to use
	int mNavTop = 0;	///< Top line of the navigation in pixels
	int mNavLeft = 0;	///< Left side of the navigation in pixels
	bool mNav = false;	///< Contraller of Navigation

	double mScale = 1;	///< Scale factor of City

	/* Mouse recoder */
	int mMouseX = 0;	///< Mouse recoder
	int mMouseY = 0;	///< Mouse recoder

	/// The zone type we are trying to find
	CTile::Zonings mZoning = CTile::Zonings::NONE;
public:
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnFileOpen();
    afx_msg void OnFileSaveas();
    /** \cond */
    afx_msg void OnBuildingsFarmhouse();
    afx_msg void OnLandscapingGrass();
    afx_msg void OnLandscapingSpartystatue();
    afx_msg void OnBuildingsBlacksmithshop();
    afx_msg void OnLandscapingTallgrass();
    afx_msg void OnBuildingsBrownhouse();
    afx_msg void OnBuildingsYellowhouse();
    afx_msg void OnBuildingsF();
    afx_msg void OnBuildingsHospital();
    afx_msg void OnBuildingsMarket();
    afx_msg void OnBuildingsCondos();
    afx_msg void OnLandscapingTree();
    afx_msg void OnLandscapingTrees();
    afx_msg void OnLandscapingBigtrees();
    afx_msg void OnLandscapingRoad();
    afx_msg void OnBusinessesCoalmine();
    /** \endcond */
    afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnTileNonetile();
	afx_msg void OnUpdateTileNonetile(CCmdUI *pCmdUI);
	afx_msg void OnTileAgriculturatile();
	afx_msg void OnUpdateTileAgriculturatile(CCmdUI *pCmdUI);
	afx_msg void OnTileIndustrialtile();
	afx_msg void OnUpdateTileIndustrialtile(CCmdUI *pCmdUI);
	afx_msg void OnTileResidentialtile();
	afx_msg void OnUpdateTileResidentialtile(CCmdUI *pCmdUI);
	afx_msg void OnBuildingsCount();
	afx_msg void OnBusinessesHaulcoal();
	afx_msg void OnBusinessesTrump();
	afx_msg void OnUpdateBusinessesTrump(CCmdUI *pCmdUI);
	afx_msg void OnTileGrass();
	afx_msg void OnUpdateTileGrass(CCmdUI *pCmdUI);
	afx_msg void OnStatisticsTotaltiles();
	afx_msg void OnStatisticsPartiallyoverlappingcount();
	afx_msg void OnStatisticsFullyoverlappingcount();
};
                                                                                   /*7MBMBL        
                                                                                   BBMBM:        
                                                                                  OBMBM,         
                                                                                  BMBM.          
                                                                                 OMBM,           
                                                  :uBBBR               s0H;     .MBM.            
                                               ;DBMBMBMB,             MBMBM     RBM,             
                                            :MBMBMBMBBB:             MBMBB     .BM:              
                                          7BMBH sBMBMB,            :MBBBM      BM:               
                                        UMBM,   BBBMB:            2MBBBM       r.                
                                      vBMO     BMBMBi            BBBBBM                  rEBMBR, 
                                      uS      BMBMBr           :BMBMBM                .RBMBMBMBM 
                                             BMBMB7           SBMBMBB.               FMB    :BMB 
                                            BMBMBs          :MBMBMBB.               BMB       ,  
                                           BMBMBF          EMBMBMBM,               FMBM          
                                          MBBMBX         iBMBMBBBM:                MBBBS         
                                         OMBMB0        .MBM:uBBBB;                 OMBMB:        
                                        DMBMBM        RBB7 ;BMBM;                   BMBMB        
                                       ZMBMBB       DBM1  ;BMBMr      r.            cBMBMS       
                                      1MBMBM      WMBS   ;BBBMc     sBB:             RBMBD       
                                     JMBMBM    :MBBK    ;BMBMc    JBMB.               BBMc       
                                    rBBMBB   iBMBS     ,BMBMS  .RMBM:                 BMB        
                                   ;MBBBMBZBMBMJ      .BBBMBZUBBMR.        .MBM:    .BMZ         
                                  :MBMBMBMBMB;       .BMBBBMBMB7           RBBBMBFPMBB,          
                                 .MBMBMBMBX.         BMBBBBM7               RBMBBBM0.            
                                 MBMB:;:.             i;:                      .                 
                                BBMO                                                             
                               MBMO                                                              
                              MBBB                                                               
                             MBBB                                                                
                            RBMB;                                                                
                           WBMBR                                                                 
                          EBBBM.                                                                 
                         UBMBMB                                                                  
                        2BMBBB3                                                                  
                       uBMBMBZ                                                                   
                      LBBBMB;                                                                    
                      :GSr*/