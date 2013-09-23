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


#ifndef MEMCELL_H_
#define MEMCELL_H_

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "typedef.h"

using namespace std;

class MemCell {
public:
	MemCell();
	virtual ~MemCell();

	/* Functions */
	void ReadCellFromFile(const std::string & inputFile);
	void CellScaling(int _targetProcessNode);
	double GetMemristance(double _relativeReadVoltage);  /* Get the LRS resistance of memristor at log-linera region of I-V curve */
	void CalculateWriteEnergy();
	double CalculateReadPower();
	void PrintCell();

	/* Properties */
	MemCellType memCellType;	/* Memory cell type (like MRAM, PCRAM, etc.) */
	int processNode;        /* Cell original process technology node, Unit: nm*/
	double area;			/* Cell area, Unit: F^2 */
	double aspectRatio;		/* Cell aspect ratio, H/W */
	double widthInFeatureSize;	/* Cell width, Unit: F */
	double heightInFeatureSize;	/* Cell height, Unit: F */
	double resistanceOn;	/* Turn-on resistance */
	double resistanceOff;	/* Turn-off resistance */
	double capacitanceOn;   /* Cell capacitance when memristor is on */
	double capacitanceOff;  /* Cell capacitance when memristor is off */
	bool   readMode;		/* true = voltage-mode, false = current-mode */
	double readVoltage;		/* Read voltage */
	double readCurrent;		/* Read current */
	double minSenseVoltage; /* Minimum sense voltage */
        double wordlineBoostRatio; /*TO-DO: function not realized: ratio of boost wordline voltage to vdd */
	double readPower;       /* Read power per bitline (uW)*/
	bool   resetMode;		/* true = voltage-mode, false = current-mode */
	double resetVoltage;	/* Reset voltage */
	double resetCurrent;	/* Reset current */
	double resetPulse;		/* Reset pulse duration (ns) */
	double resetEnergy;     /* Reset energy per cell (pJ) */
	bool   setMode;			/* true = voltage-mode, false = current-mode */
	double setVoltage;		/* Set voltage */
	double setCurrent;		/* Set current */
	double setPulse;		/* Set pulse duration (ns) */
	double setEnergy;       /* Set energy per cell (pJ) */
	CellAccessType accessType;	/* Cell access type: CMOS, BJT, or diode */

	/* Optional properties */
	int stitching;			/* If non-zero, add stitching overhead for every x cells */
	double gateOxThicknessFactor; /* The oxide thickness of FBRAM could be larger than the traditional SOI MOS */
	double widthSOIDevice; /* The gate width of SOI device as FBRAM element, Unit: F*/
	double widthAccessCMOS;	/* The gate width of CMOS access transistor, Unit: F */
	double voltageDropAccessDevice;  /* The voltage drop on the access device, Unit: V */
	double leakageCurrentAccessDevice;  /* Reverse current of access device, Unit: uA */
	double capDRAMCell;		/* The DRAM cell capacitance if the memory cell is DRAM, Unit: F */
	double widthSRAMCellNMOS;	/* The gate width of NMOS in SRAM cells, Unit: F */
	double widthSRAMCellPMOS;	/* The gate width of PMOS in SRAM cells, Unit: F */

	/* For memristor */
	bool readFloating;      /* If unselected wordlines/bitlines are floating to reduce total leakage */
	double resistanceOnAtSetVoltage; /* Low resistance state when set voltage is applied */
	double resistanceOffAtSetVoltage; /* High resistance state when set voltage is applied */
	double resistanceOnAtResetVoltage; /* Low resistance state when reset voltage is applied */
	double resistanceOffAtResetVoltage; /* High resistance state when reset voltage is applied */
	double resistanceOnAtReadVoltage; /* Low resistance state when read voltage is applied */
	double resistanceOffAtReadVoltage; /* High resistance state when read voltage is applied */
	double resistanceOnAtHalfReadVoltage; /* Low resistance state when 1/2 read voltage is applied */
	double resistanceOffAtHalfReadVoltage; /* High resistance state when 1/2 read voltage is applied */
	double resistanceOnAtHalfResetVoltage; /* Low resistance state when 1/2 reset voltage is applied */

	/* For NAND flash */
	double flashEraseVoltage;		/* The erase voltage, Unit: V, highest W/E voltage in ITRS sheet */
	double flashPassVoltage;		/* The voltage applied on the unselected wordline within the same block during programming, Unit: V */
	double flashProgramVoltage;		/* The program voltage, Unit: V */
	double flashEraseTime;			/* The flash erase time, Unit: s */
	double flashProgramTime;		/* The SLC flash program time, Unit: s */
	double gateCouplingRatio;		/* The ratio of control gate to total floating gate capacitance */
};

#endif /* MEMCELL_H_ */
