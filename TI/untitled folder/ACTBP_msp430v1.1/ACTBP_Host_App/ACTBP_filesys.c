/*******************************************************************************
 *
 *  ACTBP_filesys.c - c file for C55 booster pack file system navigation
 *                       commands  
 *
 *  Copyright (C) 2012 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 ******************************************************************************/
/******************************************************************************
 * SDK
 * Texas Instruments, Inc.
 * Ver 1.0 Feb 2012
 ******************************************************************************/ 
#include "ACTBP_HostVars.h"
#include "C55_APRF_UIF.h"
#include "ACTBP_uart.h"

extern UifRegNames RegAddr;
extern UifCommand OperationVal;
extern struct ContextABP context;
extern const struct StringsDisplay displayStrings;
extern const struct StringsDirNav dirnavStrings;

//------------------------------------------------------------------------------
// Function to update file and directory counts in current directory
//------------------------------------------------------------------------------
void UpdateContext_Count(void)
{
	unsigned long read_data = 0;
	Status status = FAILURE;

	//Get file count
	RegAddr = UIF_CMD_FILE_COUNT;
	status = uif_readScalar( RegAddr, &read_data);
	context.curr_file_count = (unsigned int) read_data;
	
	RegAddr = UIF_CMD_DIR_COUNT;
	read_data = 0;
	status = uif_readScalar( RegAddr, &read_data);
	context.curr_dir_count = (unsigned int) read_data;
}

//------------------------------------------------------------------------------
// Function to update current file number
//------------------------------------------------------------------------------
void UpdateContext_FileNum(void)
{
	unsigned long read_data = 0;
	Status status = FAILURE;

	//Get current file number
	RegAddr = UIF_CMD_PLAY_NUMBER;
	status = uif_readScalar( RegAddr, &read_data);
	context.curr_file_num = (unsigned int) read_data;
}
    
//------------------------------------------------------------------------------
// Function to update play status
//------------------------------------------------------------------------------
void UpdateContext_PlayStatus(void)
{
	unsigned long read_data = 0;
	Status status = FAILURE;

	//Get play status
	RegAddr = UIF_CMD_PLAY_STATUS;
	status = uif_readScalar( RegAddr, &read_data);
	context.curr_play_status = (unsigned int) read_data;
}

//------------------------------------------------------------------------------
// Function to update record status
//------------------------------------------------------------------------------
void UpdateContext_RecordStatus(void)
{
	unsigned long read_data = 0;
	Status status = FAILURE;

	//Get play status
	RegAddr = UIF_CMD_RECORD_STATUS;
	status = uif_readScalar( RegAddr, &read_data);
	context.curr_record_status = (unsigned int) read_data;
}

//------------------------------------------------------------------------------
// Function to send DIR command to Raga to update directory information
//------------------------------------------------------------------------------
void UpdateFileSys_Dir(void)
{
	Status status = FAILURE;

	// Send DIR command
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_DIR;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to CD to root directory
//------------------------------------------------------------------------------
void Go_RootDir(void)
{
	Status status = FAILURE;

	//Put '/' for root dir into $sys_file
	RegAddr = UIF_CMD_SYS_FILE;
	status = uif_writeArray( RegAddr, (unsigned int) 1, (char *) dirnavStrings.ROOT_DIR);
	
	//Send CD command
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_CD;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to CD to record directory in root directory
//------------------------------------------------------------------------------
void Go_RecDir(void)
{
	Status status = FAILURE;

	//Put 'RecDir' for root dir into $sys_file
	RegAddr = UIF_CMD_SYS_FILE;
	status = uif_writeArray( RegAddr, (unsigned int) 6, (char *) dirnavStrings.RECORD_DIR);
	
	//Send CD command
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_CD;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);

   	//Put '.' for current dir into $play_file
   	RegAddr = UIF_CMD_PLAY_FILE;
   	status = uif_writeArray( RegAddr, (unsigned int) 1, (char *) dirnavStrings.CURRENT_DIR);
}

//------------------------------------------------------------------------------
// Function to CD to first directory in root directory
//------------------------------------------------------------------------------
void Go_FirstDir(void)
{
	Status status = FAILURE;

	// Put first dir in $sys_file using FSTD command
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_FSTD;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);	
}

//------------------------------------------------------------------------------
// Function to CD to next directory in root directory
//------------------------------------------------------------------------------
void Go_NextDir(void)
{
	int loop_count=0;
	Status status = FAILURE;

	context.curr_dir_num += 1;
	if ((context.last_state != NXT_DIR) && (context.last_state != PRV_DIR))
    {
		//Put '/' for root dir into $sys_file
	    Go_RootDir();
	    UpdateFileSys_Dir();
	    UpdateContext_Count();
	        
	    //if system should wrap around to first dir then just update context
	    //and send CD command
	    //else if system should change to next dir, send NEXTD command
	    //the required number of times with reference to the first dir which
	    //is in $sys_file
#if 0
	    if ((context.curr_dir_num <= context.curr_dir_count))// && (context.curr_dir_num != 0))
	    {
	    	Go_FirstDir();
	      	RegAddr = UIF_CMD_OPERATION;
	      	OperationVal = UIF_CMD_NEXTD;
	      	for (loop_count=0; loop_count<(context.curr_dir_num-1); loop_count++)
	      	{
	      		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	      	}
	    }
	    else
	    {
	    	context.curr_dir_num = context.curr_dir_count;
	    }
#endif
	    if ((context.curr_dir_num > context.curr_dir_count))// && (context.curr_dir_num != 0))
	    {
	    	context.curr_dir_num = context.curr_dir_count;
	    }
    	Go_FirstDir();
      	RegAddr = UIF_CMD_OPERATION;
      	OperationVal = UIF_CMD_NEXTD;
      	for (loop_count=0; loop_count<(context.curr_dir_num-1); loop_count++)
      	{
      		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
      	}
    }
    else
    {
	    if (context.curr_dir_num == 1)
	    {
	    	Go_FirstDir();
	    }
	    else
	    {
		    if ((context.curr_dir_num <= context.root_dir_count) )//&& (context.curr_dir_num != 0))
		    {
		      	RegAddr = UIF_CMD_OPERATION;
		      	OperationVal = UIF_CMD_NEXTD;
		      	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
		    }
		    else
		    {
		    	context.curr_dir_num = context.curr_dir_count;
		    }
	    }	    
    }
}

//------------------------------------------------------------------------------
// Function to CD to next directory in root directory
//------------------------------------------------------------------------------
void Go_PrevDir(void)
{
	int loop_count=0;
	Status status = FAILURE;

    context.curr_dir_num -= 1;
	if ((context.last_state != NXT_DIR) && (context.last_state != PRV_DIR))
    {
    	Go_RootDir();	    
	    UpdateFileSys_Dir();
	    UpdateContext_Count();
	    //if changing directory to previous dir in root
	    if (context.curr_dir_num > 0)
	    {
	    	Go_FirstDir();
	    	RegAddr = UIF_CMD_OPERATION;
	      	OperationVal = UIF_CMD_NEXTD;
	      	for (loop_count=0; loop_count<(context.curr_dir_num-1); loop_count++)
	      	{
	      		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	      	}
	    }
	    else
	    {
	    	context.curr_dir_num = 0;
	    }
    }
    else
    {
	    if (context.curr_dir_num >= 1)
	    {
	    	RegAddr = UIF_CMD_OPERATION;
	    	OperationVal = UIF_CMD_PREVD;
	    	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	    }
	    else
	    {
	    	Go_RootDir();
	    	context.curr_dir_num = 0;
	    }
    }
}

//------------------------------------------------------------------------------
// Function to make sure current dir name is in SYS_FILE register
//------------------------------------------------------------------------------
void Go_CurrentDir(void)
{
	Status status = FAILURE;

	if (context.curr_dir_num == context.curr_dir_count)
	{
		// Already last dir
		Go_PrevDir();
		Go_NextDir();
	}
	else
	{
		Go_NextDir();
		Go_PrevDir();
	}
	//Send CD command
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_CD;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to CD to first file in current directory
//------------------------------------------------------------------------------
void Go_FirstFile(void)
{
	Status status = FAILURE;

	// Put first file in $sys_file using FSTF command
	RegAddr = UIF_CMD_OPERATION;
	OperationVal = UIF_CMD_FSTF;
	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);	
}

//------------------------------------------------------------------------------
// Function to CD to next file in current directory
//------------------------------------------------------------------------------
void Go_NextFile(void)
{
	unsigned int loop_count;
	Status status = FAILURE;

	if ((context.last_state != NXT_FILE) && (context.last_state != PRV_FILE))
    {
    	//increment only when current file num is less than
    	//file count of current dirctory as
    	//system should not wrap around to first file
    	if (context.curr_file_num < context.curr_file_count)
    	{
    		Go_FirstFile();
    		if (context.curr_file_num != 0)
    		{
    			context.curr_file_num += 1;
    			RegAddr = UIF_CMD_OPERATION;
    			OperationVal = UIF_CMD_NEXTF;
    			for (loop_count=0; loop_count<(context.curr_file_num-1); loop_count++)
    			{
    				status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
    			}
    		}
    		else
    		{
    			context.curr_file_num = 1;
    		}
    	}
    }
    else
    {
    	if (context.curr_file_num < context.curr_file_count)
    	{
    		context.curr_file_num += 1;
    		RegAddr = UIF_CMD_OPERATION;
    		OperationVal = UIF_CMD_NEXTF;
    		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
    	}
    }
    RegAddr = UIF_CMD_PLAY_NUMBER;
    status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num), (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to go to previous file in current directory
//------------------------------------------------------------------------------
void Go_PrevFile(void)
{
    unsigned int loop_count;
	Status status = FAILURE;

	if ((context.last_state != PRV_FILE) && (context.last_state != NXT_FILE))
    {
	    Go_FirstFile();    
	    context.curr_file_num -= 1;
	    //change file when current file num is not the first
	    //file of current dirctory or if it is not zero as
	    //system should not wrap around to last file
	    if (context.curr_file_num > 1)
	    {
	    	RegAddr = UIF_CMD_OPERATION;
	      	OperationVal = UIF_CMD_NEXTF;
	      	for (loop_count=0; loop_count<(context.curr_file_num-1); loop_count++)
	      	{
	      		status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	      	}
	    }
	    else
	    {
	    	context.curr_file_num = 1;
	    }
    }
    else
    {
	    context.curr_file_num -= 1;
	    //change file when current file num is not the first
	    //file of current dirctory or if it is not zero as
	    //system should not wrap around to last file
	    if (context.curr_file_num >= 1)
	    {
	    	RegAddr = UIF_CMD_OPERATION;
	      	OperationVal = UIF_CMD_PREVF;
	      	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
	    }
	    else
	    {
	    	context.curr_file_num = 1;
	    }
    }
    RegAddr = UIF_CMD_PLAY_NUMBER;
    status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num), (unsigned int) ACK_EXPECT);
}

//------------------------------------------------------------------------------
// Function to go to the last file in current directory
//------------------------------------------------------------------------------
void Go_LastFile(void)
{
	Status status = FAILURE;

    Go_FirstFile();    
    context.curr_file_num = 1;
    RegAddr = UIF_CMD_OPERATION;
    OperationVal = UIF_CMD_NEXTF;
    while (context.curr_file_num < context.curr_file_count)
    {
    	status = uif_writeScalar( RegAddr, OperationVal, (unsigned int) ACK_EXPECT);
    	context.curr_file_num++;
    }
        
    RegAddr = UIF_CMD_PLAY_NUMBER;
    status = uif_writeScalar( RegAddr, (unsigned long)(context.curr_file_num), (unsigned int) ACK_EXPECT);
}
