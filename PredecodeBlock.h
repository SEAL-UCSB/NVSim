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


#ifndef PREDECODEBLOCK_H_
#define PREDECODEBLOCK_H_

#include "FunctionUnit.h"
#include "RowDecoder.h"
#include "BasicDecoder.h"

class PredecodeBlock: public FunctionUnit {
public:
	PredecodeBlock();
	virtual ~PredecodeBlock();

	/* Functions */
	void PrintProperty();
	void Initialize(int _numAddressBit, double _capLoad, double _resLoad);
	void CalculateArea();
	void CalculateRC();
	void CalculateLatency(double _rampInput);
	void CalculatePower();
	PredecodeBlock & operator=(const PredecodeBlock &);

	/* Properties */
	bool initialized;	/* Initialization flag */
	RowDecoder * rowDecoderStage1A;
	RowDecoder * rowDecoderStage1B;
	RowDecoder * rowDecoderStage1C;
	int numNandInputStage1A, numNandInputStage1B, numNandInputStage1C;
	int numAddressBitStage1A, numAddressBitStage1B, numAddressBitStage1C;
	RowDecoder * rowDecoderStage2;
	BasicDecoder * basicDecoderA1;
	BasicDecoder * basicDecoderA2;
	BasicDecoder * basicDecoderB;
	BasicDecoder * basicDecoderC;
	double capLoad;		/* Load capacitance Unit: F */
	double resLoad;     /* Load resistance Unit: ohm */
	int numAddressBit;   /* Number of Address Bits assigned to the block */
	int numOutputAddressBit;
	int numDecoder12;          /* Number of 1 to 2 Decoders */
	int numDecoder24;          /* Number of 2 to 4 Decoders */
	int numDecoder38;          /* Number of 3 to 8 Decoders */
	int numBasicDecoderA1, numBasicDecoderA2;
	double capLoadBasicDecoderA1, capLoadBasicDecoderA2, capLoadBasicDecoderB, capLoadBasicDecoderC;
	double rampInput, rampOutput;
	/* TO-DO: Predecoder so far does not take OptPriority input because the output driver is already quite fixed in this module */
};

#endif /* PREDECODEBLOCK_H_ */
