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


#include "Technology.h"
#include <math.h>

Technology::Technology() {
	// TODO Auto-generated constructor stub
	initialized = false;
}

Technology::~Technology() {
	// TODO Auto-generated destructor stub
}

void Technology::Initialize(int _featureSizeInNano, DeviceRoadmap _deviceRoadmap) {
	if (initialized)
		cout << "Warning: Already initialized!" << endl;

	featureSizeInNano = _featureSizeInNano;
	featureSize = _featureSizeInNano * 1e-9;
	deviceRoadmap = _deviceRoadmap;

	if (_featureSizeInNano >= 200) { //TO-DO : only for test
		if (_deviceRoadmap == HP) {
			vdd = 1.5;
			vth = 300e-3;
			phyGateLength = 0.1e-6;
			capIdealGate = 8e-10;
			capFringe = 2.5e-10;
			capJunction = 1.00e-3;
			capOx = 1e-2;
			effectiveElectronMobility = 320e-4;
			effectiveHoleMobility = 80e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 750;
			currentOnNmos[10] = 750;
			currentOnNmos[20] = 750;
			currentOnNmos[30] = 750;
			currentOnNmos[40] = 750;
			currentOnNmos[50] = 750;
			currentOnNmos[60] = 750;
			currentOnNmos[70] = 750;
			currentOnNmos[80] = 750;
			currentOnNmos[90] = 750;
			currentOnNmos[100] = 750;
			currentOnPmos[0] = 350;
			currentOnPmos[10] = 350;
			currentOnPmos[20] = 350;
			currentOnPmos[30] = 350;
			currentOnPmos[40] = 350;
			currentOnPmos[50] = 350;
			currentOnPmos[60] = 350;
			currentOnPmos[70] = 350;
			currentOnPmos[80] = 350;
			currentOnPmos[90] = 350;
			currentOnPmos[100] = 350;
			currentOffNmos[0] = 8e-3;
			currentOffNmos[10] = 8e-3;
			currentOffNmos[20] = 8e-3;
			currentOffNmos[30] = 8e-3;
			currentOffNmos[40] = 8e-3;
			currentOffNmos[50] = 8e-3;
			currentOffNmos[60] = 8e-3;
			currentOffNmos[70] = 8e-3;
			currentOffNmos[80] = 8e-3;
			currentOffNmos[90] = 8e-3;
			currentOffNmos[100] = 8e-3;
			currentOffPmos[0] = 1.6e-2;
			currentOffPmos[10] = 1.6e-2;
			currentOffPmos[20] = 1.6e-2;
			currentOffPmos[30] = 1.6e-2;
			currentOffPmos[40] = 1.6e-2;
			currentOffPmos[50] = 1.6e-2;
			currentOffPmos[60] = 1.6e-2;
			currentOffPmos[70] = 1.6e-2;
			currentOffPmos[80] = 1.6e-2;
			currentOffPmos[90] = 1.6e-2;
			currentOffPmos[100] = 1.6e-2;
		} else if (_deviceRoadmap == LSTP) {
			vdd = 1.5;
			vth = 600e-3;
			phyGateLength = 0.16e-6;
			capIdealGate = 8e-10;
			capFringe = 2.5e-10;
			capJunction = 1.00e-3;
			capOx = 1e-2;
			effectiveElectronMobility = 320e-4;
			effectiveHoleMobility = 80e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 330;
			currentOnNmos[10] = 330;
			currentOnNmos[20] = 330;
			currentOnNmos[30] = 330;
			currentOnNmos[40] = 330;
			currentOnNmos[50] = 330;
			currentOnNmos[60] = 330;
			currentOnNmos[70] = 330;
			currentOnNmos[80] = 330;
			currentOnNmos[90] = 330;
			currentOnNmos[100] = 330;
			currentOnPmos[0] = 168;
			currentOnPmos[10] =  168;
			currentOnPmos[20] =  168;
			currentOnPmos[30] =  168;
			currentOnPmos[40] =  168;
			currentOnPmos[50] =  168;
			currentOnPmos[60] =  168;
			currentOnPmos[70] =  168;
			currentOnPmos[80] =  168;
			currentOnPmos[90] =  168;
			currentOnPmos[100] =  168;
			currentOffNmos[0] = 4.25e-6;
			currentOffNmos[10] = 4.25e-6;
			currentOffNmos[20] = 4.25e-6;
			currentOffNmos[30] = 4.25e-6;
			currentOffNmos[40] = 4.25e-6;
			currentOffNmos[50] = 4.25e-6;
			currentOffNmos[60] = 4.25e-6;
			currentOffNmos[70] = 4.25e-6;
			currentOffNmos[80] = 4.25e-6;
			currentOffNmos[90] = 4.25e-6;
			currentOffNmos[100] = 4.25e-6;
			currentOffPmos[0] = 8.5e-6;
			currentOffPmos[10] = 8.5e-6;
			currentOffPmos[20] = 8.5e-6;
			currentOffPmos[30] = 8.5e-6;
			currentOffPmos[40] = 8.5e-6;
			currentOffPmos[50] = 8.5e-6;
			currentOffPmos[60] = 8.5e-6;
			currentOffPmos[70] = 8.5e-6;
			currentOffPmos[80] = 8.5e-6;
			currentOffPmos[90] = 8.5e-6;
			currentOffPmos[100] = 8.5e-6;
		} else {
			vdd = 1.2;
			vth = 450e-3;
			phyGateLength = 0.135e-6;
			capIdealGate = 8e-10;
			capFringe = 2.5e-10;
			capJunction = 1.00e-3;
			capOx = 1e-2;
			effectiveElectronMobility = 330e-4;
			effectiveHoleMobility = 90e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 490;
			currentOnNmos[10] = 490;
			currentOnNmos[20] = 490;
			currentOnNmos[30] = 490;
			currentOnNmos[40] = 490;
			currentOnNmos[50] = 490;
			currentOnNmos[60] = 490;
			currentOnNmos[70] = 490;
			currentOnNmos[80] = 490;
			currentOnNmos[90] = 490;
			currentOnNmos[100] = 490;
			currentOnPmos[0] = 230;
			currentOnPmos[10] = 230;
			currentOnPmos[20] = 230;
			currentOnPmos[30] = 230;
			currentOnPmos[40] = 230;
			currentOnPmos[50] = 230;
			currentOnPmos[60] = 230;
			currentOnPmos[70] = 230;
			currentOnPmos[80] = 230;
			currentOnPmos[90] = 230;
			currentOnPmos[100] = 230;
			currentOffNmos[0] = 4e-4;
			currentOffNmos[10] = 4e-4;
			currentOffNmos[20] = 4e-4;
			currentOffNmos[30] = 4e-4;
			currentOffNmos[40] = 4e-4;
			currentOffNmos[50] = 4e-4;
			currentOffNmos[60] = 4e-4;
			currentOffNmos[70] = 4e-4;
			currentOffNmos[80] = 4e-4;
			currentOffNmos[90] = 4e-4;
			currentOffNmos[100] = 4e-4;
			currentOffPmos[0] = 8e-4;
			currentOffPmos[10] = 8e-4;
			currentOffPmos[20] = 8e-4;
			currentOffPmos[30] = 8e-4;
			currentOffPmos[40] = 8e-4;
			currentOffPmos[50] = 8e-4;
			currentOffPmos[60] = 8e-4;
			currentOffPmos[70] = 8e-4;
			currentOffPmos[80] = 8e-4;
			currentOffPmos[90] = 8e-4;
			currentOffPmos[100] = 8e-4;
		}
	} else if (_featureSizeInNano >= 120) {	/* TO-DO: actually 100nm */
		if (_deviceRoadmap == HP) {
			/* MASTAR 5 - HP100.pro, HP100p.pro */
			vdd = 1.2;
			vth = 218.04e-3;
			phyGateLength = 0.0451e-6;
			capIdealGate = 7.41e-10;
			capFringe = 2.4e-10;
			capJunction = 1.00e-3;
			capOx = 1.64e-2;
			effectiveElectronMobility = 249.59e-4;
			effectiveHoleMobility = 59.52e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 960.9;
			currentOnNmos[10] = 947.9;
			currentOnNmos[20] = 935.1;
			currentOnNmos[30] = 922.5;
			currentOnNmos[40] = 910.0;
			currentOnNmos[50] = 897.7;
			currentOnNmos[60] = 885.5;
			currentOnNmos[70] = 873.6;
			currentOnNmos[80] = 861.8;
			currentOnNmos[90] = 850.1;
			currentOnNmos[100] = 838.6;
			currentOnPmos[0] = 578.4;
			currentOnPmos[10] = 567.8;
			currentOnPmos[20] = 557.5;
			currentOnPmos[30] = 547.4;
			currentOnPmos[40] = 537.5;
			currentOnPmos[50] = 527.8;
			currentOnPmos[60] = 518.3;
			currentOnPmos[70] = 509.1;
			currentOnPmos[80] = 500.0;
			currentOnPmos[90] = 491.1;
			currentOnPmos[100] = 482.5;
			currentOffNmos[0] = 1.90e-2;
			currentOffNmos[10] = 2.35e-2;
			currentOffNmos[20] = 2.86e-2;
			currentOffNmos[30] = 3.45e-2;
			currentOffNmos[40] = 4.12e-2;
			currentOffNmos[50] = 4.87e-2;
			currentOffNmos[60] = 5.71e-2;
			currentOffNmos[70] = 6.64e-2;
			currentOffNmos[80] = 7.67e-2;
			currentOffNmos[90] = 8.80e-2;
			currentOffNmos[100] = 1.00e-1;
			currentOffPmos[0] = 3.82e-2;
			currentOffPmos[10] = 3.84e-2;
			currentOffPmos[20] = 3.87e-2;
			currentOffPmos[30] = 3.90e-2;
			currentOffPmos[40] = 3.93e-2;
			currentOffPmos[50] = 3.97e-2;
			currentOffPmos[60] = 4.01e-2;
			currentOffPmos[70] = 4.05e-2;
			currentOffPmos[80] = 4.10e-2;
			currentOffPmos[90] = 4.16e-2;
			currentOffPmos[100] = 4.22e-2;
		} else if (_deviceRoadmap == LSTP) {
			/* MASTAR 5 - LSTP100.pro */
			vdd = 1.2;
			vth = 501.25e-3;
			phyGateLength = 0.075e-6;
			capIdealGate = 8.62e-10;
			capFringe = 2.5e-10;
			capJunction = 1.00e-3;
			capOx = 1.15e-2;
			effectiveElectronMobility = 284.97e-4;
			effectiveHoleMobility = 61.82e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 422.5;
			currentOnNmos[10] = 415.0;
			currentOnNmos[20] = 407.7;
			currentOnNmos[30] = 400.5;
			currentOnNmos[40] = 393.6;
			currentOnNmos[50] = 386.8;
			currentOnNmos[60] = 380.1;
			currentOnNmos[70] = 373.7;
			currentOnNmos[80] = 367.4;
			currentOnNmos[90] = 361.3;
			currentOnNmos[100] = 355.5;
			currentOnPmos[0] = 204.9;
			currentOnPmos[10] = 200.3;
			currentOnPmos[20] = 195.9;
			currentOnPmos[30] = 191.7;
			currentOnPmos[40] = 187.5;
			currentOnPmos[50] = 183.5;
			currentOnPmos[60] = 179.7;
			currentOnPmos[70] = 175.9;
			currentOnPmos[80] = 172.3;
			currentOnPmos[90] = 168.8;
			currentOnPmos[100] = 165.4;
			currentOffNmos[0] = 1.01e-5;
			currentOffNmos[10] = 1.04e-5;
			currentOffNmos[20] = 1.06e-5;
			currentOffNmos[30] = 1.09e-5;
			currentOffNmos[40] = 1.12e-5;
			currentOffNmos[50] = 1.16e-5;
			currentOffNmos[60] = 1.20e-5;
			currentOffNmos[70] = 1.24e-5;
			currentOffNmos[80] = 1.28e-5;
			currentOffNmos[90] = 1.32e-5;
			currentOffNmos[100] = 1.37e-5;
			currentOffPmos[0] = 2.21e-5;
			currentOffPmos[10] = 2.27e-5;
			currentOffPmos[20] = 2.33e-5;
			currentOffPmos[30] = 2.40e-5;
			currentOffPmos[40] = 2.47e-5;
			currentOffPmos[50] = 2.54e-5;
			currentOffPmos[60] = 2.62e-5;
			currentOffPmos[70] = 2.71e-5;
			currentOffPmos[80] = 2.80e-5;
			currentOffPmos[90] = 2.90e-5;
			currentOffPmos[100] = 3.01e-5;
		} else {	/* LOP */
			/* MASTAR 5 - LOP100.pro */
			vdd = 1.0;
			vth = 312.60e-3;
			phyGateLength = 0.065e-6;
			capIdealGate = 6.34e-10;
			capFringe = 2.5e-10;
			capJunction = 1.00e-3;
			capOx = 1.44e-2;
			effectiveElectronMobility = 292.43e-4;
			effectiveHoleMobility = 64.53e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 531.4;
			currentOnNmos[10] = 522.6;
			currentOnNmos[20] = 514.0;
			currentOnNmos[30] = 505.5;
			currentOnNmos[40] = 497.3;
			currentOnNmos[50] = 489.2;
			currentOnNmos[60] = 481.3;
			currentOnNmos[70] = 473.6;
			currentOnNmos[80] = 466.1;
			currentOnNmos[90] = 458.8;
			currentOnNmos[100] = 451.6;
			currentOnPmos[0] = 278.5;
			currentOnPmos[10] = 272.5;
			currentOnPmos[20] = 266.8;
			currentOnPmos[30] = 261.2;
			currentOnPmos[40] = 255.8;
			currentOnPmos[50] = 250.5;
			currentOnPmos[60] = 245.4;
			currentOnPmos[70] = 240.4;
			currentOnPmos[80] = 235.6;
			currentOnPmos[90] = 231.0;
			currentOnPmos[100] = 226.4;
			currentOffNmos[0] = 9.69e-4;
			currentOffNmos[10] = 9.87e-4;
			currentOffNmos[20] = 1.01e-3;
			currentOffNmos[30] = 1.03e-3;
			currentOffNmos[40] = 1.05e-3;
			currentOffNmos[50] = 1.08e-3;
			currentOffNmos[60] = 1.10e-3;
			currentOffNmos[70] = 1.13e-3;
			currentOffNmos[80] = 1.16e-3;
			currentOffNmos[90] = 1.19e-3;
			currentOffNmos[100] = 1.23e-3;
			currentOffPmos[0] = 2.20e-3;
			currentOffPmos[10] = 2.25e-3;
			currentOffPmos[20] = 2.29e-3;
			currentOffPmos[30] = 2.34e-3;
			currentOffPmos[40] = 2.39e-3;
			currentOffPmos[50] = 2.45e-3;
			currentOffPmos[60] = 2.51e-3;
			currentOffPmos[70] = 2.57e-3;
			currentOffPmos[80] = 2.64e-3;
			currentOffPmos[90] = 2.72e-3;
			currentOffPmos[100] = 2.79e-3;
		}
	} else if (_featureSizeInNano >= 90) {
		if (_deviceRoadmap == HP) {
			/* MASTAR 5 - HP90.pro */
			vdd = 1.2;
			vth = 197.95e-3;
			phyGateLength = 0.037e-6;
			capIdealGate = 6.38e-10;
			capFringe = 2.5e-10;
			capJunction = 1.00e-3;
			capOx = 1.73e-2;
			effectiveElectronMobility = 243.43e-4;
			effectiveHoleMobility = 58.32e-4;
			pnSizeRatio = 2.45;						/* from CACTI */
			effectiveResistanceMultiplier = 1.54;	/* from CACTI */
			currentOnNmos[0] = 1050.5;
			currentOnNmos[10] = 1037.0;
			currentOnNmos[20] = 1023.6;
			currentOnNmos[30] = 1010.3;
			currentOnNmos[40] = 997.2;
			currentOnNmos[50] = 984.2;
			currentOnNmos[60] = 971.4;
			currentOnNmos[70] = 958.8;
			currentOnNmos[80] = 946.3;
			currentOnNmos[90] = 933.9;
			currentOnNmos[100] = 921.7;
			currentOnPmos[0] = 638.7;
			currentOnPmos[10] = 627.5;
			currentOnPmos[20] = 616.5;
			currentOnPmos[30] = 605.8;
			currentOnPmos[40] = 595.2;
			currentOnPmos[50] = 584.9;
			currentOnPmos[60] = 574.7;
			currentOnPmos[70] = 564.8;
			currentOnPmos[80] = 555.1;
			currentOnPmos[90] = 545.5;
			currentOnPmos[100] = 536.2;
			currentOffNmos[0] = 1.90e-2 * 2.73;		/* correct from MASTAR */
			currentOffNmos[10] = 2.35e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[20] = 2.86e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[30] = 3.45e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[40] = 4.12e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[50] = 4.87e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[60] = 5.71e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[70] = 6.64e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[80] = 7.67e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[90] = 8.80e-2 * 2.73;	/* correct from MASTAR */
			currentOffNmos[100] = 1.00e-1 * 2.73;	/* correct from MASTAR */
			currentOffPmos[0] = 5.26e-2;
			currentOffPmos[10] = 5.26e-2;
			currentOffPmos[20] = 5.26e-2;
			currentOffPmos[30] = 5.27e-2;
			currentOffPmos[40] = 5.28e-2;
			currentOffPmos[50] = 5.29e-2;
			currentOffPmos[60] = 5.31e-2;
			currentOffPmos[70] = 5.34e-2;
			currentOffPmos[80] = 5.36e-2;
			currentOffPmos[90] = 5.40e-2;
			currentOffPmos[100] = 5.43e-2;
		} else if (_deviceRoadmap == LSTP) {
			/* MASTAR 5 - LSTP90.pro */
			vdd = 1.2;
			vth = 502.36e-3;
			phyGateLength = 0.065e-6;
			capIdealGate = 7.73e-10;
			capFringe = 2.4e-10;
			capJunction = 1.00e-3;
			capOx = 1.19e-2;
			effectiveElectronMobility = 277.94e-4;
			effectiveHoleMobility = 60.64e-4;
			pnSizeRatio = 2.44;						/* from CACTI */
			effectiveResistanceMultiplier = 1.92;	/* from CACTI */
			currentOnNmos[0] = 446.6;
			currentOnNmos[10] = 438.7;
			currentOnNmos[20] = 431.2;
			currentOnNmos[30] = 423.8;
			currentOnNmos[40] = 416.7;
			currentOnNmos[50] = 409.7;
			currentOnNmos[60] = 402.9;
			currentOnNmos[70] = 396.3;
			currentOnNmos[80] = 389.8;
			currentOnNmos[90] = 383.5;
			currentOnNmos[100] = 377.3;
			currentOnPmos[0] = 221.5;
			currentOnPmos[10] = 216.6;
			currentOnPmos[20] = 212.0;
			currentOnPmos[30] = 207.4;
			currentOnPmos[40] = 203.1;
			currentOnPmos[50] = 198.8;
			currentOnPmos[60] = 194.7;
			currentOnPmos[70] = 190.7;
			currentOnPmos[80] = 186.9;
			currentOnPmos[90] = 183.1;
			currentOnPmos[100] = 179.5;
			currentOffNmos[0] = 9.45e-6;
			currentOffNmos[10] = 9.67e-6;
			currentOffNmos[20] = 9.91e-5;
			currentOffNmos[30] = 1.02e-5;
			currentOffNmos[40] = 1.05e-5;
			currentOffNmos[50] = 1.08e-5;
			currentOffNmos[60] = 1.11e-5;
			currentOffNmos[70] = 1.14e-5;
			currentOffNmos[80] = 1.28e-5;
			currentOffNmos[90] = 1.32e-5;
			currentOffNmos[100] = 1.37e-5;
			currentOffPmos[0] = 2.05e-5;
			currentOffPmos[10] = 2.10e-5;
			currentOffPmos[20] = 2.15e-5;
			currentOffPmos[30] = 2.21e-5;
			currentOffPmos[40] = 2.27e-5;
			currentOffPmos[50] = 2.34e-5;
			currentOffPmos[60] = 2.41e-5;
			currentOffPmos[70] = 2.48e-5;
			currentOffPmos[80] = 2.56e-5;
			currentOffPmos[90] = 2.65e-5;
			currentOffPmos[100] = 2.74e-5;
		} else {
			/* MASTAR 5 - LOP90.pro */
			vdd = 0.9;
			vth = 264.54e-3;
			phyGateLength = 0.053e-6;
			capIdealGate = 7.95e-10;
			capFringe = 2.4e-10;
			capJunction = 1.00e-3;
			capOx = 1.50e-2;
			effectiveElectronMobility = 309.04e-4;
			effectiveHoleMobility = 67.88e-4;
			pnSizeRatio = 2.54;						/* from CACTI */
			effectiveResistanceMultiplier = 1.77;	/* from CACTI */
			currentOnNmos[0] = 534.5;
			currentOnNmos[10] = 525.7;
			currentOnNmos[20] = 517.0;
			currentOnNmos[30] = 508.5;
			currentOnNmos[40] = 500.2;
			currentOnNmos[50] = 492.1;
			currentOnNmos[60] = 484.1;
			currentOnNmos[70] = 476.3;
			currentOnNmos[80] = 468.7;
			currentOnNmos[90] = 461.2;
			currentOnNmos[100] = 453.9;
			currentOnPmos[0] = 294.2;
			currentOnPmos[10] = 287.8;
			currentOnPmos[20] = 281.7;
			currentOnPmos[30] = 275.7;
			currentOnPmos[40] = 269.9;
			currentOnPmos[50] = 264.2;
			currentOnPmos[60] = 258.7;
			currentOnPmos[70] = 253.4;
			currentOnPmos[80] = 248.2;
			currentOnPmos[90] = 243.2;
			currentOnPmos[100] = 238.3;
			currentOffNmos[0] = 2.74e-3;
			currentOffNmos[10] = 2.6e-3;
			currentOffNmos[20] = 2.79e-3;
			currentOffNmos[30] = 2.81e-3;
			currentOffNmos[40] = 2.84e-3;
			currentOffNmos[50] = 2.88e-3;
			currentOffNmos[60] = 2.91e-3;
			currentOffNmos[70] = 2.95e-3;
			currentOffNmos[80] = 2.99e-3;
			currentOffNmos[90] = 3.04e-3;
			currentOffNmos[100] =3.09e-3;
			currentOffPmos[0] = 6.51e-3;
			currentOffPmos[10] = 6.56e-3;
			currentOffPmos[20] = 6.61e-3;
			currentOffPmos[30] = 6.67e-3;
			currentOffPmos[40] = 6.74e-3;
			currentOffPmos[50] = 6.82e-3;
			currentOffPmos[60] = 6.91e-3;
			currentOffPmos[70] = 7.00e-3;
			currentOffPmos[80] = 7.10e-3;
			currentOffPmos[90] = 7.21e-3;
			currentOffPmos[100] = 7.33e-3;
		}
	} else if (_featureSizeInNano >= 65) {
		if (_deviceRoadmap == HP) {
			/* MASTAR 5 - hp-bulk-2007.pro */
			vdd = 1.1;
			vth = 163.98e-3;
			phyGateLength = 0.025e-6;
			capIdealGate = 4.70e-10;
			capFringe = 2.4e-10;
			capJunction = 1.00e-3;
			capOx = 1.88e-2;
			effectiveElectronMobility = 445.74e-4;
			effectiveHoleMobility = 113.330e-4;
			pnSizeRatio = 2.41;						/* from CACTI */
			effectiveResistanceMultiplier = 1.50;	/* from CACTI */
			currentOnNmos[0] = 1211.4;
			currentOnNmos[10] = 1198.4;
			currentOnNmos[20] = 1185.4;
			currentOnNmos[30] = 1172.5;
			currentOnNmos[40] = 1156.9;
			currentOnNmos[50] = 1146.7;
			currentOnNmos[60] = 1133.6;
			currentOnNmos[70] = 1119.9;
			currentOnNmos[80] = 1104.3;
			currentOnNmos[90] = 1084.6;
			currentOnNmos[100] = 1059.0;
			currentOnPmos[0] = 888.7;
			currentOnPmos[10] = 875.8;
			currentOnPmos[20] = 861.7;
			currentOnPmos[30] = 848.5;
			currentOnPmos[40] = 835.4;
			currentOnPmos[50] = 822.6;
			currentOnPmos[60] = 809.9;
			currentOnPmos[70] = 797.3;
			currentOnPmos[80] = 784.8;
			currentOnPmos[90] = 772.2;
			currentOnPmos[100] = 759.4;
			currentOffNmos[0] = 3.43e-1;
			currentOffNmos[10] = 3.73e-1;
			currentOffNmos[20] = 4.03e-1;
			currentOffNmos[30] = 4.35e-1;
			currentOffNmos[40] = 4.66e-1;
			currentOffNmos[50] = 4.99e-1;
			currentOffNmos[60] = 5.31e-1;
			currentOffNmos[70] = 5.64e-1;
			currentOffNmos[80] = 5.96e-1;
			currentOffNmos[90] = 6.25e-1;
			currentOffNmos[100] = 6.51e-1;
			currentOffPmos[0] = 5.68e-1;
			currentOffPmos[10] = 6.07e-1;
			currentOffPmos[20] = 6.46e-1;
			currentOffPmos[30] = 6.86e-1;
			currentOffPmos[40] = 7.26e-1;
			currentOffPmos[50] = 7.66e-1;
			currentOffPmos[60] = 8.06e-1;
			currentOffPmos[70] = 8.46e-1;
			currentOffPmos[80] = 8.86e-1;
			currentOffPmos[90] = 9.26e-1;
			currentOffPmos[100] = 9.65e-1;
		} else if (_deviceRoadmap == LSTP) {
			/* MASTAR 5 - lstp-bulk-2007.pro */
			vdd = 1.1;
			vth = 563.92e-3;
			phyGateLength = 0.045e-6;
			capIdealGate = 6.17e-10;
			capFringe = 2.4e-10;
			capJunction = 1.00e-3;
			capOx = 1.37e-2;
			effectiveElectronMobility = 457.86e-4;
			effectiveHoleMobility = 102.64e-4;
			pnSizeRatio = 2.23;						/* from CACTI */
			effectiveResistanceMultiplier = 1.96;	/* from CACTI */
			currentOnNmos[0] = 465.4;
			currentOnNmos[10] = 458.5;
			currentOnNmos[20] = 451.8;
			currentOnNmos[30] = 445.1;
			currentOnNmos[40] = 438.4;
			currentOnNmos[50] = 431.6;
			currentOnNmos[60] = 423.9;
			currentOnNmos[70] = 414.2;
			currentOnNmos[80] = 400.6;
			currentOnNmos[90] = 383.5;
			currentOnNmos[100] = 367.2;
			currentOnPmos[0] = 234.2;
			currentOnPmos[10] = 229.7;
			currentOnPmos[20] = 225.3;
			currentOnPmos[30] = 221.0;
			currentOnPmos[40] = 216.8;
			currentOnPmos[50] = 212.7;
			currentOnPmos[60] = 208.8;
			currentOnPmos[70] = 204.8;
			currentOnPmos[80] = 200.7;
			currentOnPmos[90] = 196.6;
			currentOnPmos[100] = 192.6;
			currentOffNmos[0] = 3.03e-5;
			currentOffNmos[10] = 4.46e-5;
			currentOffNmos[20] = 6.43e-5;
			currentOffNmos[30] = 9.06e-5;
			currentOffNmos[40] = 1.25e-4;
			currentOffNmos[50] = 1.70e-4;
			currentOffNmos[60] = 2.25e-4;
			currentOffNmos[70] = 2.90e-4;
			currentOffNmos[80] = 3.61e-4;
			currentOffNmos[90] = 4.35e-4;
			currentOffNmos[100] = 5.20e-4;
			currentOffPmos[0] = 3.85e-5;
			currentOffPmos[10] = 5.64e-5;
			currentOffPmos[20] = 8.09e-5;
			currentOffPmos[30] = 1.14e-4;
			currentOffPmos[40] = 1.57e-4;
			currentOffPmos[50] = 2.12e-4;
			currentOffPmos[60] = 2.82e-4;
			currentOffPmos[70] = 3.70e-4;
			currentOffPmos[80] = 4.78e-4;
			currentOffPmos[90] = 6.09e-4;
			currentOffPmos[100] = 7.66e-4;
		} else {
			/* MASTAR 5 - lop-bulk-2007.pro */
			vdd = 0.8;
			vth = 323.75e-3;
			phyGateLength = 0.032e-6;
			capIdealGate = 6.01e-10;
			capFringe = 2.4e-10;
			capJunction = 1.00e-3;
			capOx = 1.88e-2;
			effectiveElectronMobility = 491.59e-4;
			effectiveHoleMobility = 110.95e-4;
			pnSizeRatio = 2.28;						/* from CACTI */
			effectiveResistanceMultiplier = 1.82;	/* from CACTI */
			currentOnNmos[0] = 562.9;
			currentOnNmos[10] = 555.2;
			currentOnNmos[20] = 547.5;
			currentOnNmos[30] = 539.8;
			currentOnNmos[40] = 532.2;
			currentOnNmos[50] = 524.5;
			currentOnNmos[60] = 516.1;
			currentOnNmos[70] = 505.7;
			currentOnNmos[80] = 491.1;
			currentOnNmos[90] = 471.7;
			currentOnNmos[100] = 451.6;
			currentOnPmos[0] = 329.5;
			currentOnPmos[10] = 323.3;
			currentOnPmos[20] = 317.2;
			currentOnPmos[30] = 311.2;
			currentOnPmos[40] = 305.4;
			currentOnPmos[50] = 299.8;
			currentOnPmos[60] = 294.2;
			currentOnPmos[70] = 288.7;
			currentOnPmos[80] = 283.2;
			currentOnPmos[90] = 277.5;
			currentOnPmos[100] = 271.8;
			currentOffNmos[0] = 9.08e-3;
			currentOffNmos[10] = 1.11e-2;
			currentOffNmos[20] = 1.35e-2;
			currentOffNmos[30] = 1.62e-2;
			currentOffNmos[40] = 1.92e-2;
			currentOffNmos[50] = 2.25e-2;
			currentOffNmos[60] = 2.62e-2;
			currentOffNmos[70] = 2.99e-2;
			currentOffNmos[80] = 3.35e-2;
			currentOffNmos[90] = 3.67e-2;
			currentOffNmos[100] = 3.98e-2;
			currentOffPmos[0] = 1.30e-2;
			currentOffPmos[10] = 1.57e-2;
			currentOffPmos[20] = 1.89e-2;
			currentOffPmos[30] = 2.24e-2;
			currentOffPmos[40] = 2.64e-2;
			currentOffPmos[50] = 3.08e-2;
			currentOffPmos[60] = 3.56e-2;
			currentOffPmos[70] = 1.09e-2;
			currentOffPmos[80] = 4.65e-2;
			currentOffPmos[90] = 5.26e-2;
			currentOffPmos[100] = 5.91e-2;
		}
	} else if (_featureSizeInNano >= 45) {
		if (_deviceRoadmap == HP) {
			/* MASTAR 5 - hp-bulk-2010.pro */
			vdd = 1.0;
			vth = 126.79e-3;
			phyGateLength = 0.018e-6;
			capIdealGate = 6.78e-10;
			capFringe = 1.7e-10;
			capJunction = 1.00e-3;
			capOx = 3.77e-2;
			effectiveElectronMobility = 297.70e-4;
			effectiveHoleMobility = 95.27e-4;
			pnSizeRatio = 2.41;						/* from CACTI */
			effectiveResistanceMultiplier = 1.51;	/* from CACTI */
			currentOnNmos[0] = 1823.8;
			currentOnNmos[10] = 1808.2;
			currentOnNmos[20] = 1792.6;
			currentOnNmos[30] = 1777.0;
			currentOnNmos[40] = 1761.4;
			currentOnNmos[50] = 1745.8;
			currentOnNmos[60] = 1730.3;
			currentOnNmos[70] = 1714.7;
			currentOnNmos[80] = 1699.1;
			currentOnNmos[90] = 1683.2;
			currentOnNmos[100] = 1666.6;
			currentOnPmos[0] = 1632.2;
			currentOnPmos[10] = 1612.8;
			currentOnPmos[20] = 1593.6;
			currentOnPmos[30] = 1574.1;
			currentOnPmos[40] = 1554.7;
			currentOnPmos[50] = 1535.5;
			currentOnPmos[60] = 1516.4;
			currentOnPmos[70] = 1497.6;
			currentOnPmos[80] = 1478.8;
			currentOnPmos[90] = 1460.3;
			currentOnPmos[100] = 1441.8;
			/* NMOS off current, Unit: A/m, these values are calculated by Sheng Li offline */
			currentOffNmos[0] = 2.80e-1;
			currentOffNmos[10] = 3.28e-1;
			currentOffNmos[20] = 3.81e-1;
			currentOffNmos[30] = 4.39e-1;
			currentOffNmos[40] = 5.02e-1;
			currentOffNmos[50] = 5.69e-1;
			currentOffNmos[60] = 6.42e-1;
			currentOffNmos[70] = 7.20e-1;
			currentOffNmos[80] = 8.03e-1;
			currentOffNmos[90] = 8.91e-1;
			currentOffNmos[100] = 9.84e-1;
			/* PMOS off current, Unit: A/m. TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[0] = currentOffNmos[0];
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} else if (_deviceRoadmap == LSTP) {
			/* MASTAR 5 - lstp-bulk-2010.pro */
			vdd = 1.0;
			vth = 564.52e-3;
			phyGateLength = 0.028e-6;
			capIdealGate = 5.58e-10;
			capFringe = 2.1e-10;
			capJunction = 1.00e-3;
			capOx = 1.99e-2;
			effectiveElectronMobility = 456.14e-4;
			effectiveHoleMobility = 96.98e-4;
			pnSizeRatio = 2.23;						/* from CACTI */
			effectiveResistanceMultiplier = 1.99;	/* from CACTI */
			currentOnNmos[0] = 527.5;
			currentOnNmos[10] = 520.2;
			currentOnNmos[20] = 512.9;
			currentOnNmos[30] = 505.8;
			currentOnNmos[40] = 498.6;
			currentOnNmos[50] = 491.4;
			currentOnNmos[60] = 483.7;
			currentOnNmos[70] = 474.4;
			currentOnNmos[80] = 461.2;
			currentOnNmos[90] = 442.6;
			currentOnNmos[100] = 421.3;
			currentOnPmos[0] = 497.9;
			currentOnPmos[10] = 489.5;
			currentOnPmos[20] = 481.3;
			currentOnPmos[30] = 473.2;
			currentOnPmos[40] = 465.3;
			currentOnPmos[50] = 457.6;
			currentOnPmos[60] = 450.0;
			currentOnPmos[70] = 442.5;
			currentOnPmos[80] = 435.1;
			currentOnPmos[90] = 427.5;
			currentOnPmos[100] = 419.7;
			/* NMOS off current, Unit: A/m, these values are calculated by Sheng Li offline */
			currentOffNmos[0] = 1.01e-5;
			currentOffNmos[10] = 1.65e-5;
			currentOffNmos[20] = 2.62e-5;
			currentOffNmos[30] = 4.06e-5;
			currentOffNmos[40] = 6.12e-5;
			currentOffNmos[50] = 9.02e-5;
			currentOffNmos[60] = 1.30e-4;
			currentOffNmos[70] = 1.83e-4;
			currentOffNmos[80] = 2.51e-4;
			currentOffNmos[90] = 3.29e-4;
			currentOffNmos[100] = 4.10e-4;
			/* PMOS off current, Unit: A/m. TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[0] = currentOffNmos[0];
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} else {
			/* MASTAR 5 - lop-bulk-2010.pro */
			vdd = 0.7;
			vth = 288.94e-3;
			phyGateLength = 0.022e-6;
			capIdealGate = 6.13e-10;
			capFringe = 2.0e-10;
			capJunction = 1.00e-3;
			capOx = 2.79e-2;
			effectiveElectronMobility = 606.95e-4;
			effectiveHoleMobility = 124.60e-4;
			pnSizeRatio = 2.28;						/* from CACTI */
			effectiveResistanceMultiplier = 1.76;	/* from CACTI */
			currentOnNmos[0] = 682.1;
			currentOnNmos[10] = 672.3;
			currentOnNmos[20] = 662.5;
			currentOnNmos[30] = 652.8;
			currentOnNmos[40] = 643.0;
			currentOnNmos[50] = 632.8;
			currentOnNmos[60] = 620.9;
			currentOnNmos[70] = 605.0;
			currentOnNmos[80] = 583.6;
			currentOnNmos[90] = 561.0;
			currentOnNmos[100] = 542.7;
			currentOnPmos[0] = 772.4;
			currentOnPmos[10] = 759.6;
			currentOnPmos[20] = 746.9;
			currentOnPmos[30] = 734.4;
			currentOnPmos[40] = 722.1;
			currentOnPmos[50] = 710.0;
			currentOnPmos[60] = 698.1;
			currentOnPmos[70] = 686.3;
			currentOnPmos[80] = 674.4;
			currentOnPmos[90] = 662.3;
			currentOnPmos[100] = 650.2;
			/* NMOS off current, Unit: A/m, these values are calculated by Sheng Li offline */
			currentOffNmos[0] = 4.03e-3;
			currentOffNmos[10] = 5.02e-3;
			currentOffNmos[20] = 6.18e-3;
			currentOffNmos[30] = 7.51e-3;
			currentOffNmos[40] = 9.04e-3;
			currentOffNmos[50] = 1.08e-2;
			currentOffNmos[60] = 1.27e-2;
			currentOffNmos[70] = 1.47e-2;
			currentOffNmos[80] = 1.66e-2;
			currentOffNmos[90] = 1.84e-2;
			currentOffNmos[100] = 2.03e-2;
			/* PMOS off current, Unit: A/m. TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[0] = currentOffNmos[0];
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		}
	} else if (_featureSizeInNano >= 32) {	/* TO-DO: actually 36nm */
		if (_deviceRoadmap == HP) {
			/* MASTAR 5 - hp-bulk-2012.pro */
			vdd = 0.9;
			vth = 131.72e-3;
			phyGateLength = 0.014e-6;
			capIdealGate = 6.42e-10;
			capFringe = 1.6e-10;
			capJunction = 1.00e-3;
			capOx = 4.59e-2;
			effectiveElectronMobility = 257.73e-4;
			effectiveHoleMobility = 89.92e-4;
			pnSizeRatio = 2.41;						/* from CACTI */
			effectiveResistanceMultiplier = 1.49;	/* from CACTI */
			currentOnNmos[0] = 1785.8;
			currentOnNmos[10] = 1771.8;
			currentOnNmos[20] = 1757.8;
			currentOnNmos[30] = 1743.8;
			currentOnNmos[40] = 1729.8;
			currentOnNmos[50] = 1715.7;
			currentOnNmos[60] = 1701.7;
			currentOnNmos[70] = 1687.6;
			currentOnNmos[80] = 1673.5;
			currentOnNmos[90] = 1659.4;
			currentOnNmos[100] = 1645.0;
			currentOnPmos[0] = 1713.5;
			currentOnPmos[10] = 1662.8;
			currentOnPmos[20] = 1620.1;
			currentOnPmos[30] = 1601.6;
			currentOnPmos[40] = 1583.3;
			currentOnPmos[50] = 1565.1;
			currentOnPmos[60] = 1547.1;
			currentOnPmos[70] = 1529.1;
			currentOnPmos[80] = 1511.3;
			currentOnPmos[90] = 1493.7;
			currentOnPmos[100] = 1476.1;
			currentOffNmos[0] = 8.34e-1;
			currentOffNmos[10] = 9.00e-1;
			currentOffNmos[20] = 9.68e-1;
			currentOffNmos[30] = 1.04;
			currentOffNmos[40] = 1.11;
			currentOffNmos[50] = 1.18;
			currentOffNmos[60] = 1.25;
			currentOffNmos[70] = 1.32;
			currentOffNmos[80] = 1.39;
			currentOffNmos[90] = 1.46;
			currentOffNmos[100] = 1.54;
			currentOffPmos[0] = currentOffNmos[0];	/* TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} else if (_deviceRoadmap == LSTP) {
			/* MASTAR 5 - lstp-bulk-2012.pro */
			vdd = 1;
			vth = 581.81e-3;
			phyGateLength = 0.022e-6;
			capIdealGate = 5.02e-10;
			capFringe = 1.9e-10;
			capJunction = 1.00e-3;
			capOx = 2.19e-2;
			effectiveElectronMobility = 395.20e-4;
			effectiveHoleMobility = 88.67e-4;
			pnSizeRatio = 2.23;						/* from CACTI */
			effectiveResistanceMultiplier = 1.99;	/* from CACTI */
			currentOnNmos[0] = 560.0;
			currentOnNmos[10] = 553.0;
			currentOnNmos[20] = 546.1;
			currentOnNmos[30] = 539.3;
			currentOnNmos[40] = 532.5;
			currentOnNmos[50] = 525.8;
			currentOnNmos[60] = 518.9;
			currentOnNmos[70] = 511.5;
			currentOnNmos[80] = 502.3;
			currentOnNmos[90] = 489.2;
			currentOnNmos[100] = 469.7;
			currentOnPmos[0] = 549.6;
			currentOnPmos[10] = 541.1;
			currentOnPmos[20] = 532.8;
			currentOnPmos[30] = 524.6;
			currentOnPmos[40] = 516.5;
			currentOnPmos[50] = 508.7;
			currentOnPmos[60] = 500.9;
			currentOnPmos[70] = 493.3;
			currentOnPmos[80] = 485.8;
			currentOnPmos[90] = 478.3;
			currentOnPmos[100] = 470.7;
			currentOffNmos[0] = 3.02e-5;
			currentOffNmos[10] = 4.51e-5;
			currentOffNmos[20] = 6.57e-5;
			currentOffNmos[30] = 9.35e-5;
			currentOffNmos[40] = 1.31e-4;
			currentOffNmos[50] = 1.79e-4;
			currentOffNmos[60] = 2.41e-4;
			currentOffNmos[70] = 3.19e-4;
			currentOffNmos[80] = 4.15e-4;
			currentOffNmos[90] = 5.29e-4;
			currentOffNmos[100] = 6.58e-4;
			currentOffPmos[0] = currentOffNmos[0];	/* TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} else {
			/* MASTAR 5 - lop-bulk-2012.pro */
			vdd = 0.7;
			vth = 278.52e-3;
			phyGateLength = 0.018e-6;
			capIdealGate = 5.54e-10;
			capFringe = 2.0e-10;
			capJunction = 1.00e-3;
			capOx = 3.08e-2;
			effectiveElectronMobility = 581.62e-4;
			effectiveHoleMobility = 120.30e-4;
			pnSizeRatio = 2.28;						/* from CACTI */
			effectiveResistanceMultiplier = 1.73;	/* from CACTI */
			currentOnNmos[0] = 760.3;
			currentOnNmos[10] = 750.4;
			currentOnNmos[20] = 740.5;
			currentOnNmos[30] = 730.7;
			currentOnNmos[40] = 720.8;
			currentOnNmos[50] = 710.9;
			currentOnNmos[60] = 700.3;
			currentOnNmos[70] = 687.6;
			currentOnNmos[80] = 670.5;
			currentOnNmos[90] = 647.4;
			currentOnNmos[100] = 623.6;
			currentOnPmos[0] = 878.6;  //TO-DO currentOnPmos even larger than currentOnNmos ?
			currentOnPmos[10] = 865.1;
			currentOnPmos[20] = 851.8;
			currentOnPmos[30] = 838.7;
			currentOnPmos[40] = 825.7;
			currentOnPmos[50] = 813.0;
			currentOnPmos[60] = 800.3;
			currentOnPmos[70] = 787.9;
			currentOnPmos[80] = 775.5;
			currentOnPmos[90] = 763.0;
			currentOnPmos[100] = 750.3;
			currentOffNmos[0] = 3.57e-2;
			currentOffNmos[10] = 4.21e-2;
			currentOffNmos[20] = 4.91e-2;
			currentOffNmos[30] = 5.68e-2;
			currentOffNmos[40] = 6.51e-2;
			currentOffNmos[50] = 7.42e-2;
			currentOffNmos[60] = 8.43e-2;
			currentOffNmos[70] = 9.57e-2;
			currentOffNmos[80] = 1.10e-1;
			currentOffNmos[90] = 1.28e-1;
			currentOffNmos[100] = 1.48e-1;
			currentOffPmos[0] = currentOffNmos[0];	/* TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		}
	} else if (_featureSizeInNano >= 22) {
		if (_deviceRoadmap == HP) {
			/* MASTAR 5 - hp-soi-2015.pro */ /* TO-DO: actually 25nm */
			vdd = 0.9;
			vth = 128.72e-3;
			phyGateLength = 0.010e-6;
			capIdealGate = 3.83e-10;
			capFringe = 1.6e-10;
			capJunction = 0;
			capOx = 3.83e-2;
			effectiveElectronMobility = 397.26e-4;
			effectiveHoleMobility = 83.60e-4;
			pnSizeRatio = 2;						/* from CACTI */
			effectiveResistanceMultiplier = 1.45;	/* from CACTI */
			currentOnNmos[0] = 2029.9;
			currentOnNmos[10] = 2009.8;
			currentOnNmos[20] = 1989.6;
			currentOnNmos[30] = 1969.6;
			currentOnNmos[40] = 1949.8;
			currentOnNmos[50] = 1930.7;
			currentOnNmos[60] = 1910.5;
			currentOnNmos[70] = 1891.0;
			currentOnNmos[80] = 1871.7;
			currentOnNmos[90] = 1852.5;
			currentOnNmos[100] = 1834.4;
			currentOnPmos[0] = currentOnNmos[0] / 2; /* TO-DO: MASTER values are absolutely wrong so that CACTI method is temporarily used here */
			currentOnPmos[10] = currentOnNmos[0] / 2;
			currentOnPmos[20] = currentOnNmos[10] / 2;
			currentOnPmos[30] = currentOnNmos[20] / 2;
			currentOnPmos[40] = currentOnNmos[30] / 2;
			currentOnPmos[50] = currentOnNmos[40] / 2;
			currentOnPmos[60] = currentOnNmos[50] / 2;
			currentOnPmos[70] = currentOnNmos[60] / 2;
			currentOnPmos[80] = currentOnNmos[70] / 2;
			currentOnPmos[90] = currentOnNmos[80] / 2;
			currentOnPmos[100] = currentOnNmos[90] / 2;
			currentOffNmos[0] = 1.52e-7 * 3.93e6; /* TO-DO: MASTER values are absolutely wrong so that data are translated from 32nm */
			currentOffNmos[10] = 1.55e-7 * 3.93e6;
			currentOffNmos[20] = 1.59e-7 * 3.93e6;
			currentOffNmos[30] = 1.68e-7 * 3.93e6;
			currentOffNmos[40] = 1.90e-7 * 3.93e6;
			currentOffNmos[50] = 2.69e-7 * 3.93e6;
			currentOffNmos[60] = 5.32e-7 * 3.93e6;
			currentOffNmos[70] = 1.02e-6 * 3.93e6;
			currentOffNmos[80] = 1.62e-6 * 3.93e6;
			currentOffNmos[90] = 2.73e-6 * 3.93e6;
			currentOffNmos[100] = 6.1e-6 * 3.93e6;
			currentOffPmos[0] = currentOffNmos[0];	/* TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} else if (_deviceRoadmap == LSTP) {
			/* MASTAR 5 - lstp-bulk-2016.pro */
			vdd = 0.8;
			vth = 445.71e-3;
			phyGateLength = 0.016e-6;
			capIdealGate = 4.25e-10;
			capFringe = 2e-10;
			capJunction = 0;
			capOx = 2.65e-2;
			effectiveElectronMobility = 731.29e-4;
			effectiveHoleMobility = 111.22e-4;
			pnSizeRatio = 2.23;						/* from CACTI */
			effectiveResistanceMultiplier = 1.99;	/* from CACTI */
			currentOnNmos[0] = 745.5;
			currentOnNmos[10] = 735.2;
			currentOnNmos[20] = 725.1;
			currentOnNmos[30] = 715.2;
			currentOnNmos[40] = 705.4;
			currentOnNmos[50] = 695.7;
			currentOnNmos[60] = 686.2;
			currentOnNmos[70] = 676.9;
			currentOnNmos[80] = 667.7;
			currentOnNmos[90] = 658.7;
			currentOnNmos[100] = 649.8;
			currentOnPmos[0] = currentOnNmos[0] / 2; /* TO-DO: MASTER values are absolutely wrong so that CACTI method is temporarily used here */
			currentOnPmos[10] = currentOnNmos[0] / 2;
			currentOnPmos[20] = currentOnNmos[10] / 2;
			currentOnPmos[30] = currentOnNmos[20] / 2;
			currentOnPmos[40] = currentOnNmos[30] / 2;
			currentOnPmos[50] = currentOnNmos[40] / 2;
			currentOnPmos[60] = currentOnNmos[50] / 2;
			currentOnPmos[70] = currentOnNmos[60] / 2;
			currentOnPmos[80] = currentOnNmos[70] / 2;
			currentOnPmos[90] = currentOnNmos[80] / 2;
			currentOnPmos[100] = currentOnNmos[90] / 2;
			currentOffNmos[0] = 3.02e-5 / 1.86; /* TO-DO: MASTER values are absolutely wrong so that data are translated from 32nm */
			currentOffNmos[10] = 4.51e-5 / 1.86;
			currentOffNmos[20] = 6.57e-5 / 1.86;
			currentOffNmos[30] = 9.35e-5 / 1.86;
			currentOffNmos[40] = 1.31e-4 / 1.86;
			currentOffNmos[50] = 1.79e-4 / 1.86;
			currentOffNmos[60] = 2.41e-4 / 1.86;
			currentOffNmos[70] = 3.19e-4 / 1.86;
			currentOffNmos[80] = 4.15e-4 / 1.86;
			currentOffNmos[90] = 5.29e-4 / 1.86;
			currentOffNmos[100] = 6.58e-4 / 1.86;
			currentOffPmos[0] = currentOffNmos[0];	/* TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		} else {
			/* MASTAR 5 - lop-bulk-2016.pro */
			vdd = 0.5;
			vth = 217.39e-3;
			phyGateLength = 0.011e-6;
			capIdealGate = 3.45e-10;
			capFringe = 1.7e-10;
			capJunction = 0;
			capOx = 3.14e-2;
			effectiveElectronMobility = 747.37e-4;
			effectiveHoleMobility = 118.35e-4;
			pnSizeRatio = 2.28;						/* from CACTI */
			effectiveResistanceMultiplier = 1.73;	/* from CACTI */
			currentOnNmos[0] = 716.1;
			currentOnNmos[10] = 704.3;
			currentOnNmos[20] = 692.6;
			currentOnNmos[30] = 681.2;
			currentOnNmos[40] = 669.9;
			currentOnNmos[50] = 658.8;
			currentOnNmos[60] = 647.9;
			currentOnNmos[70] = 637.1;
			currentOnNmos[80] = 626.5;
			currentOnNmos[90] = 616.0;
			currentOnNmos[100] = 605.7;
			currentOnPmos[0] = currentOnNmos[0] / 2; /* TO-DO: MASTER values are absolutely wrong so that CACTI method is temporarily used here */
			currentOnPmos[10] = currentOnNmos[0] / 2;
			currentOnPmos[20] = currentOnNmos[10] / 2;
			currentOnPmos[30] = currentOnNmos[20] / 2;
			currentOnPmos[40] = currentOnNmos[30] / 2;
			currentOnPmos[50] = currentOnNmos[40] / 2;
			currentOnPmos[60] = currentOnNmos[50] / 2;
			currentOnPmos[70] = currentOnNmos[60] / 2;
			currentOnPmos[80] = currentOnNmos[70] / 2;
			currentOnPmos[90] = currentOnNmos[80] / 2;
			currentOnPmos[100] = currentOnNmos[90] / 2;
			currentOffNmos[0] = 3.57e-2 / 1.7;
			currentOffNmos[10] = 4.21e-2 / 1.7;
			currentOffNmos[20] = 4.91e-2 / 1.7;
			currentOffNmos[30] = 5.68e-2 / 1.7;
			currentOffNmos[40] = 6.51e-2 / 1.7;
			currentOffNmos[50] = 7.42e-2 / 1.7;
			currentOffNmos[60] = 8.43e-2 / 1.7;
			currentOffNmos[70] = 9.57e-2 / 1.7;
			currentOffNmos[80] = 1.10e-1 / 1.7;
			currentOffNmos[90] = 1.28e-1 / 1.7;
			currentOffNmos[100] = 1.48e-1 / 1.7;
			currentOffPmos[0] = currentOffNmos[0];	/* TO-DO: set PMOS = NMOS because MASTAR value is obviously wrong */
			currentOffPmos[10] = currentOffNmos[10];
			currentOffPmos[20] = currentOffNmos[20];
			currentOffPmos[30] = currentOffNmos[30];
			currentOffPmos[40] = currentOffNmos[40];
			currentOffPmos[50] = currentOffNmos[50];
			currentOffPmos[60] = currentOffNmos[60];
			currentOffPmos[70] = currentOffNmos[70];
			currentOffPmos[80] = currentOffNmos[80];
			currentOffPmos[90] = currentOffNmos[90];
			currentOffPmos[100] = currentOffNmos[100];
		}
	}

	capOverlap = capIdealGate * 0.2;
	//capSidewall = 2.5e-10;	/* Unit: F/m, this value is from CACTI, PTM model shows the value is 5e-10 */
	double cjd = 1e-3;             /* Bottom junction capacitance, Unit: F/m^2*/
	double cjswd = 2.5e-10;           /* Isolation-edge sidewall junction capacitance, Unit: F/m */
	double cjswgd = 0.5e-10;          /* Gate-edge sidewall junction capacitance, Unit: F/m */
	double mjd = 0.5;             /* Bottom junction capacitance grating coefficient */
	double mjswd = 0.33;           /* Isolation-edge sidewall junction capacitance grading coefficient */
	double mjswgd = 0.33;          /* Gate-edge sidewall junction capacitance grading coefficient */
	buildInPotential = 0.9;			/* This value is from BSIM4 */
	capJunction = cjd / pow(1 + vdd / buildInPotential, mjd);
	capSidewall = cjswd / pow(1 + vdd / buildInPotential, mjswd);
	capDrainToChannel = cjswgd / pow(1 + vdd / buildInPotential, mjswgd);

	vdsatNmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveElectronMobility;
	vdsatPmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveHoleMobility;

	/* Properties not used so far */
	capPolywire = 0.0;	/* TO-DO: we need to find the values */

	/* Interpolate */
	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOnNmos[i / 10 * 10];
			double b = currentOnNmos[i / 10 * 10 + 10];
			currentOnNmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOnPmos[i / 10 * 10];
			double b = currentOnPmos[i / 10 * 10 + 10];
			currentOnPmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOffNmos[i / 10 * 10];
			double b = currentOffNmos[i / 10 * 10 + 10];
			currentOffNmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	for (int i = 1; i < 100; i++) {
		if (i % 10) {
			double a = currentOffPmos[i / 10 * 10];
			double b = currentOffPmos[i / 10 * 10 + 10];
			currentOffPmos[i] = a + (b-a) * (i % 10) / 10;
		}
	}

	initialized = true;
}
void Technology::PrintProperty() {
	cout << "Fabrication Process Technology Node:" << endl;
	cout << "TO-DO" << endl;
}

void Technology::InterpolateWith(Technology rhs, double _alpha) {
	if (featureSizeInNano != rhs.featureSizeInNano) {
		vdd = (1 - _alpha) * vdd + _alpha * rhs.vdd;
		vth = (1 - _alpha) * vth + _alpha * rhs.vth;
		phyGateLength = (1 - _alpha) * phyGateLength + _alpha * rhs.phyGateLength;
		capIdealGate = (1 - _alpha) * capIdealGate + _alpha * rhs.capIdealGate;
		capFringe = (1 - _alpha) * capFringe + _alpha * rhs.capFringe;
		capJunction = (1 - _alpha) * capJunction + _alpha * rhs.capJunction;
		capOx = (1 - _alpha) * capOx + _alpha * rhs.capOx;
		effectiveElectronMobility = (1 - _alpha) * effectiveElectronMobility + _alpha * rhs.effectiveElectronMobility;
		effectiveHoleMobility = (1 - _alpha) * effectiveHoleMobility + _alpha * rhs.effectiveHoleMobility;
		pnSizeRatio = (1 - _alpha) * pnSizeRatio + _alpha * rhs.pnSizeRatio;
		effectiveResistanceMultiplier = (1 - _alpha) * effectiveResistanceMultiplier + _alpha * rhs.effectiveResistanceMultiplier;
		for (int i = 0; i <= 100; i++){
			currentOnNmos[i] = (1 - _alpha) * currentOnNmos[i] + _alpha * rhs.currentOnNmos[i];
			currentOnPmos[i] = (1 - _alpha) * currentOnPmos[i] + _alpha * rhs.currentOnPmos[i];
			currentOffNmos[i] = pow(currentOffNmos[i], 1 - _alpha) * pow(rhs.currentOffNmos[i], _alpha);
			currentOffPmos[i] = pow(currentOffPmos[i], 1 - _alpha) * pow(rhs.currentOffPmos[i], _alpha);
		}
		//capSidewall = 2.5e-10;	/* Unit: F/m, this value is from CACTI, PTM model shows the value is 5e-10 */
		double cjd = 1e-3;             /* Bottom junction capacitance, Unit: F/m^2*/
		double cjswd = 2.5e-10;           /* Isolation-edge sidewall junction capacitance, Unit: F/m */
		double cjswgd = 0.5e-10;          /* Gate-edge sidewall junction capacitance, Unit: F/m */
		double mjd = 0.5;             /* Bottom junction capacitance grating coefficient */
		double mjswd = 0.33;           /* Isolation-edge sidewall junction capacitance grading coefficient */
		double mjswgd = 0.33;          /* Gate-edge sidewall junction capacitance grading coefficient */
		buildInPotential = 0.9;			/* This value is from BSIM4 */
		capJunction = cjd / pow(1 + vdd / buildInPotential, mjd);
		capSidewall = cjswd / pow(1 + vdd / buildInPotential, mjswd);
		capDrainToChannel = cjswgd / pow(1 + vdd / buildInPotential, mjswgd);

		vdsatNmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveElectronMobility;
		vdsatPmos = phyGateLength * 1e5 /* Silicon saturatio velocity, Unit: m/s */ / effectiveHoleMobility;
	}
}
