/*---------------------------------------------------------------------------/
/  Petit FatFs - FAT file system module include file  R0.02a   (C)ChaN, 2010
/----------------------------------------------------------------------------/
/ Petit FatFs module is an open source software to implement FAT file system to
/ small embedded systems. This is a free software and is opened for education,
/ research and commercial developments under license policy of following trems.
/
/  Copyright (C) 2010, ChaN, all right reserved.
/
/ * The Petit FatFs module is a free software and there is NO WARRANTY.
/ * No restriction on use. You can use, modify and redistribute it for
/   personal, non-profit or commercial use UNDER YOUR RESPONSIBILITY.
/ * Redistributions of source code must retain the above copyright notice.

/小FatFs模块是一个开放源码的软件实现FAT文件系统
小型嵌入式系统。这是一个自由软件和开放教育，
研究和商业发展的重点在以下许可政策。
/
/版权（C）2010，陈，保留所有权利。
/
／＊小FatFs模块是一个自由软件是没有担保。
/ *无限制使用。你可以使用，修改和重新发布它
/个人，非营利或商业用途在你的责任。
／＊传播源代码时必须保留上述版权声明。
/
/----------------------------------------------------------------------------*/

#include "integer.h"

/*---------------------------------------------------------------------------/
/ Petit FatFs Configuration Options
/
/ CAUTION! Do not forget to make clean the project after any changes to
/ the configuration options.
/

Petit FatFs /配置选项
/
注意安全。别忘了让清洁项目后的任何变化
/配置选项。
/----------------------------------------------------------------------------*/
#ifndef _FATFS
#define _FATFS

#define	_USE_READ	1	/* 1:Enable pf_read() 
                           有0 和1 两个值可被选择，
                           选择 0 则不使能文件读操作，
						   选择1 则使能读文件操作，在这里我们选择 1，使能读文件操作*/

#define	_USE_DIR	1	/* 1:Enable pf_opendir() and pf_readdir()
                           为1 时使能打开一个目录和读一个目录项操作，
						   为 0 时则不使能相应操作，
						   因为我们只测试文件的读/写操作，所以设置其值为 0。 */

#define	_USE_LSEEK	1	/* 1:Enable pf_lseek()
                           有 0 和1 两个选择项。
						   1 时使能移动读/写指针操作，为 0 时则禁止。 */

#define	_USE_WRITE	0	/* 1:Enable pf_write() 
                            为 1 时使能写文件操作，
							为 0 时禁止写文件操作。
							这里设置其值为1，使能写文件操作。
							*/

#define _FS_FAT12	1	/* 1:Enable FAT12 support */
#define _FS_FAT32	1	/* 1:Enable FAT32 support 
						   为 0 时仅支持FAT16 文件系统，
						   为1 时支持 FAT32 文件系统。
						   FAT32 文件系统是FAT16 文件系统的升级，
						   而且现在 SD 卡在出厂时一般都默认被格式化为FAT32 文件系统，所以设置其值为 1。
                             */


#define	_CODE_PAGE	1
/* Defines which code page is used for path name. Supported code pages are:
/  932, 936, 949, 950, 437, 720, 737, 775, 850, 852, 855, 857, 858, 862, 866,
/  874, 1250, 1251, 1252, 1253, 1254, 1255, 1257, 1258 and 1 (ASCII only).
/  SBCS code pages except for 1 requiers a case conversion table. This
/  might occupy 128 bytes on the RAM on some platforms, e.g. avr-gcc.

/ pdefines代码页用来路径名。支持的代码页：
932 936 949 950 437 720 737 775 850 852 855 857 858 862 866。
874，1250，1251，1252，1253，1254，1255，1257，1258和1（纯ASCII）。
/ SBCS代码页，除1例转换表的要求。这
也许在某些平台上占用128个字节的RAM，例如AVR单片机GCC。 */


#define _WORD_ACCESS	0	 //有0 和1 两个值可被选择。为 0 时选择字节寻址方式，为1 时选择字寻址方式
/* The _WORD_ACCESS option defines which access method is used to the word
/  data in the FAT structure.
/
/   0: Byte-by-byte access. Always compatible with all platforms.
/   1: Word access. Do not choose this unless following condition is met.
/
/  When the byte order on the memory is big-endian or address miss-aligned
/  word access results incorrect behavior, the _WORD_ACCESS must be set to 0.
/  If it is not the case, the value can also be set to 1 to improve the
/  performance and code efficiency. 

该_word_access选项定义的访问方法的话
在FAT结构数据。
/
0：按字节访问字节。总是兼容所有平台。
1：字访问。不选择这除非是满足下列条件。
/
当对内存的字节顺序是大端字节序或地址对齐
/字访问的结果不正确的行为，这_word_access必须设置为0。
如果情况不是这样，值也可以设置为1提高
/性能和编码效率。*/


/* End of configuration options. Do not change followings without care.    
端的配置选项。不改变以下无忧 */
/*--------------------------------------------------------------------------*/



#if _FS_FAT32
#define	CLUST	DWORD
#else
#define	CLUST	WORD
#endif


/* File system object structure 文件系统对象的结构*/

typedef struct {
	BYTE	fs_type;	/* FAT sub type SD类型 1 fat12  2 fat16  3 fat32*/
	BYTE	flag;		/* File status flags 文件状态标志 FA_OPENED已打开   FA_WPRT写保护   FA__WIP正在工作*/
	BYTE	csize;		/* Number of sectors per cluster 每簇的扇区数*/
	BYTE	pad1;
	WORD	n_rootdir;	/* Number of root directory entries (0 on FAT32) 根目录区目录项的数目 （0对FAT32）*/
	CLUST	n_fatent;	/* Number of FAT entries (= number of clusters + 2) fat的项目数（=簇数+ 2） 卡的总簇数加2*/
	DWORD	fatbase;	/* FAT start sector 文件分配表开始扇区  FAT1表 所在物理扇区*/
	DWORD	dirbase;	/* Root directory start sector (Cluster# on FAT32) 根目录所在的簇 一般是2  如果是FAT32，根目录开始扇区需要首先得到。*/
	DWORD	database;	/* Data start sector 数据开始扇区 即SD卡根目录 */

															   //以下为打开一个文件以后  才会有对应的值 
	DWORD	fptr;		/* File R/W pointer 文件读/写指针*/    //偏移值 指针          
	DWORD	fsize;		/* File size 文件大小*/			                  
	CLUST	org_clust;	/* File start cluster 文件开始簇*/	             
	CLUST	curr_clust;	/* File current cluster 文件当前簇*/	          
	DWORD	dsect;		/* File current data sector 文件当前数据扇区*/	  
} FATFS;




/* Directory object structure 文件夹结构体变量 所有数值 都是要打开的文件的数据 要打开文件里的数据*/

typedef struct {
	WORD	index;		/* Current read/write index number 目前读写索引代码  当前的读/写指数*/
	BYTE*	fn;			/* Pointer to the SFN (in/out) {file[8],ext[3],status[1]}  短文件名指针  
	                                                    file[8] 文件名  ext[3]扩展名  status[1]该文件状态 是否被删除
														查找时 直接 dir.fn[n]即可得到相应值
														这个也是要打开文件夹的 文件名*/
	CLUST	sclust;		/* Table start cluster (0:Static table) 文件数据区开始簇  （0：静态表）*/
	CLUST	clust;		/* Current cluster 对应打开文件夹当前簇  目前处理的簇 */
	DWORD	sect;		/* Current sector 当前物理扇区   目前簇里对应的扇区 */
} DIR;



/* File status structure 文件结构体*/

typedef struct {
	DWORD	fsize;		/* File size 文件大小*/
	WORD	fdate;		/* Last modified date 最后修改日期*/
	WORD	ftime;		/* Last modified time 最后修改时间*/
	BYTE	fattrib;	/* Attribute 属性*/
	char	fname[13];	/* File name 文件名*/
} FILINFO;



/* File function return code (FRESULT) 文件中的函数的返回代码（fresult）*/

typedef enum {
	FR_OK = 0,			/* 0 */
	FR_DISK_ERR,		/* 1 */
	FR_NOT_READY,		/* 2 */
	FR_NO_FILE,			/* 3 */
	FR_NO_PATH,			/* 4 */
	FR_NOT_OPENED,		/* 5 */
	FR_NOT_ENABLED,		/* 6 */
	FR_NO_FILESYSTEM	/* 7 */
} FRESULT;



/*--------------------------------------------------------------*/
/* Petit FatFs module application interface        Petit FatFs模块的应用程序接口             */

FRESULT pf_mount (FATFS*);						/* Mount/Unmount a logical drive 安装/退出一个逻辑驱动器*/
FRESULT pf_open (const char*);					/* Open a file 打开一个文件*/
FRESULT pf_read (void*, WORD, WORD*);			/* Read data from the open file 从文件中读取数据*/
FRESULT pf_write (const void*, WORD, WORD*);	/* Write data to the open file 向文件写数据*/
FRESULT pf_lseek (DWORD);						/* Move file pointer of the open file 将打开的文件的文件指针*/
FRESULT pf_opendir (DIR*, const char*);			/* Open a directory 打开目录 文件夹*/
FRESULT pf_readdir (DIR*, FILINFO*);			/* Read a directory item from the open directory 从开放式目录/文件夹 读一个目录项*/



/*--------------------------------------------------------------*/
/* Flags and offset address        标志和偏移地址                             */

/* File status flag (FATFS.flag) 文件状态标志（标志概述。）*/

#define	FA_OPENED	0x01		 //已打开
#define	FA_WPRT		0x02		 //写保护
#define	FA__WIP		0x40		 //正在工作


/* FAT sub type (FATFS.fs_type) */

#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3


/* File attribute bits for directory entry 对目录项文件属性字节*/

#define	AM_RDO	0x01	/* Read only 只读*/
#define	AM_HID	0x02	/* Hidden 隐藏*/
#define	AM_SYS	0x04	/* System 系统*/
#define	AM_VOL	0x08	/* Volume label 卷标*/
#define AM_LFN	0x0F	/* LFN entry 进入*/
#define AM_DIR	0x10	/* Directory 目录*/
#define AM_ARC	0x20	/* Archive 档案*/
#define AM_MASK	0x3F	/* Mask of defined bits 定义的位掩码*/


/*--------------------------------*/
/* Multi-byte word access macros  多字节字访问宏*/

#if _WORD_ACCESS == 1	/* Enable word access to the FAT structure 使词进入fat组织*/
#define	LD_WORD(ptr)		(WORD)(*(WORD*)(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(*(DWORD*)(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(WORD*)(BYTE*)(ptr)=(WORD)(val)
#define	ST_DWORD(ptr,val)	*(DWORD*)(BYTE*)(ptr)=(DWORD)(val)
#else					/* Use byte-by-byte access to the FAT structure */
#define	LD_WORD(ptr)		(WORD)(((WORD)*((BYTE*)(ptr)+1)<<8)|(WORD)*(BYTE*)(ptr))
#define	LD_DWORD(ptr)		(DWORD)(((DWORD)*((BYTE*)(ptr)+3)<<24)|((DWORD)*((BYTE*)(ptr)+2)<<16)|((WORD)*((BYTE*)(ptr)+1)<<8)|*(BYTE*)(ptr))
#define	ST_WORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8)
#define	ST_DWORD(ptr,val)	*(BYTE*)(ptr)=(BYTE)(val); *((BYTE*)(ptr)+1)=(BYTE)((WORD)(val)>>8); *((BYTE*)(ptr)+2)=(BYTE)((DWORD)(val)>>16); *((BYTE*)(ptr)+3)=(BYTE)((DWORD)(val)>>24)
#endif


#endif /* _FATFS */
