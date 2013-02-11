/*******************************************************************************
* Copyright (c) 2012-2013, The Microsystems Design Labratory (MDL)
* Department of Computer Science and Engineering, The Pennsylvania State University
* Exascale Computing Lab, Hewlett-Packard Company
* All rights reserved.
* 
* This source code is part of NVSim - An area, timing and power model for both 
* volatile (e.g., SRAM, DRAM) and non-volatile memory (e.g., PCRAM, STT-RAM, ReRAM, 
* SLC NAND Flash). The source code is free and you can redistribute and/or modify it
* by providing that the following conditions are met:
* 
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
* 
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
* 
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
* FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
* SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
* OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
* OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
* 
* Author list: 
*   Cong Xu	    ( Email: czx102 at psu dot edu 
*                     Website: http://www.cse.psu.edu/~czx102/ )
*   Xiangyu Dong    ( Email: xydong at cse dot psu dot edu
*                     Website: http://www.cse.psu.edu/~xydong/ )
*******************************************************************************/


#ifndef WIRE_H_
#define WIRE_H_

#include <iostream>
#include "typedef.h"
#include "SenseAmp.h"

using namespace std;

class Wire {
public:
	Wire();
	virtual ~Wire();

	/* Functions */
	void PrintProperty();
	void Initialize(int _featureSizeInNano, WireType _wireType, WireRepeaterType _wireRepeaterType,
			int _temperature, bool _isLowSwing);
	void CalculateLatencyAndPower(double _wireLength, double *delay, double *dynamicEnergy, double *leakagePower);
	void findOptimalRepeater();
	void findPenalizedRepeater(double _penalty);
	double getRepeatedWireUnitDelay();				/* Return delay per unit, Unit: s/m */
	double getRepeatedWireUnitDynamicEnergy();		/* Return dynamic energy per unit, Unit: J/m */
	double getRepeatedWireUnitLeakage();			/* Return leakage power per unit, Unit: W/m */
	Wire & operator=(const Wire &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	int featureSizeInNano; /* Process feature size, Unit: nm */
	double featureSize;	/* Process feature size, Unit: m */
	WireType wireType;	/* Type of wire */
	WireRepeaterType wireRepeaterType;	/* Type of wire repeater */
	int temperature;	/* Unit: K */
	bool isLowSwing;	/* Whether to use Low Swing wire with transmitters and receivers */

	double barrierThickness;		/* Unit: m */
	double horizontalDielectric;	/* Unit: 1 */
	double wirePitch;				/* Unit: m */
	double aspectRatio;				/* Unit: 1 */
	double ildThickness;			/* Unit: m */
	double wireWidth;				/* Unit: m */
	double wireThickness;			/* Unit: m */
	double wireSpacing;				/* Unit: m */

	double repeaterSize;			/* For repeated wire only, non-repeated wire = 0, Unit: minimum driver size*/
	double repeaterSpacing;			/* For repeated wire only, non-repeated wire = inf, Unit: m */
	double repeaterHeight, repeaterWidth;	/* Unit: m */
	double repeatedWirePitch;		/* For repeated wire only, translate the repeaterSize into meter, Unit: m */

	double resWirePerUnit;			/* Unit: ohm/m */
	double capWirePerUnit;			/* Unit: F/m */

	SenseAmp * senseAmp;
};

#endif /* WIRE_H_ */
