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


#ifndef CONSTANT_H_
#define CONSTANT_H_

#define WARNING	0

#define INV		0
#define NOR		1
#define NAND	2

#define NMOS	0
#define PMOS	1

#define MAX_INV_CHAIN_LEN	20
#define OPT_F				4

#define COMPARATOR_INV_CHAIN_LEN 4

#define MAX_NMOS_SIZE	100
#define MIN_NMOS_SIZE	1.5

#define AREA_OPT_CONSTRAIN 1

#define MAX_TRANSISTOR_HEIGHT 20

#define MIN_GAP_BET_P_AND_N_DIFFS	2
#define MIN_GAP_BET_SAME_TYPE_DIFFS	1.5
#define MIN_GAP_BET_POLY			1.5
#define MIN_GAP_BET_CONTACT_POLY	0.75
#define CONTACT_SIZE				1
#define MIN_WIDTH_POWER_RAIL		2

#define AVG_RATIO_LEAK_2INPUT_NAND 0.48
#define AVG_RATIO_LEAK_3INPUT_NAND 0.31
#define AVG_RATIO_LEAK_2INPUT_NOR  0.95
#define AVG_RATIO_LEAK_3INPUT_NOR  0.62

#define W_SENSE_P		7.5
#define W_SENSE_N		3.75
#define W_SENSE_ISO		12.5
#define W_SENSE_EN		5.0
#define W_SENSE_MUX		9.0
#define VBITSENSEMIN	0.08
#define IV_CONVERTER_AREA 50000 /*TO-DO: technology and design dependent parameter, 649606 is used in PCRAMSim*/

#define STITCHING_OVERHEAD	7.5

#define DRAM_REFRESH_PERIOD	64e-3

#define SHAPER_EFFICIENCY_CONSERVATIVE	0.2
#define SHAPER_EFFICIENCY_AGGRESSIVE	1.0

#define COPPER_RESISTIVITY	2.2e-8			/* Unit: ohm*m at 20 celcius degree */
#define COPPER_RESISTIVITY_TEMPERATURE_COEFFICIENT	0.0039
#define PERMITTIVITY		8.85e-12		/* Unit: F/m */

#define TUNNEL_CURRENT_FLOW 10				/* Unit: A/m^2 */
#define DELTA_V_TH 5.0						/* Unit: V, Threshold difference of floating gate */

#define RES_ADJ 8.6
#define VOL_SWING .1

#define CONSTRAINT_ASPECT_RATIO_BANK	10	

#define BITLINE_LEAKAGE_TOLERANCE	1
#define IR_DROP_TOLERANCE 			0.2

#define TOTAL_ADDRESS_BIT	48

#endif /* CONSTANT_H_ */
