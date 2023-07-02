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

/СFatFsģ����һ������Դ������ʵ��FAT�ļ�ϵͳ
С��Ƕ��ʽϵͳ������һ����������Ϳ��Ž�����
�о�����ҵ��չ���ص�������������ߡ�
/
/��Ȩ��C��2010���£���������Ȩ����
/
����СFatFsģ����һ�����������û�е�����
/ *������ʹ�á������ʹ�ã��޸ĺ����·�����
/���ˣ���Ӫ������ҵ��;��������Ρ�
��������Դ����ʱ���뱣��������Ȩ������
/
/----------------------------------------------------------------------------*/

#include "integer.h"

/*---------------------------------------------------------------------------/
/ Petit FatFs Configuration Options
/
/ CAUTION! Do not forget to make clean the project after any changes to
/ the configuration options.
/

Petit FatFs /����ѡ��
/
ע�ⰲȫ���������������Ŀ����κα仯
/����ѡ�
/----------------------------------------------------------------------------*/
#ifndef _FATFS
#define _FATFS

#define	_USE_READ	1	/* 1:Enable pf_read() 
                           ��0 ��1 ����ֵ�ɱ�ѡ��
                           ѡ�� 0 ��ʹ���ļ���������
						   ѡ��1 ��ʹ�ܶ��ļ�����������������ѡ�� 1��ʹ�ܶ��ļ�����*/

#define	_USE_DIR	1	/* 1:Enable pf_opendir() and pf_readdir()
                           Ϊ1 ʱʹ�ܴ�һ��Ŀ¼�Ͷ�һ��Ŀ¼�������
						   Ϊ 0 ʱ��ʹ����Ӧ������
						   ��Ϊ����ֻ�����ļ��Ķ�/д����������������ֵΪ 0�� */

#define	_USE_LSEEK	1	/* 1:Enable pf_lseek()
                           �� 0 ��1 ����ѡ���
						   1 ʱʹ���ƶ���/дָ�������Ϊ 0 ʱ���ֹ�� */

#define	_USE_WRITE	0	/* 1:Enable pf_write() 
                            Ϊ 1 ʱʹ��д�ļ�������
							Ϊ 0 ʱ��ֹд�ļ�������
							����������ֵΪ1��ʹ��д�ļ�������
							*/

#define _FS_FAT12	1	/* 1:Enable FAT12 support */
#define _FS_FAT32	1	/* 1:Enable FAT32 support 
						   Ϊ 0 ʱ��֧��FAT16 �ļ�ϵͳ��
						   Ϊ1 ʱ֧�� FAT32 �ļ�ϵͳ��
						   FAT32 �ļ�ϵͳ��FAT16 �ļ�ϵͳ��������
						   �������� SD ���ڳ���ʱһ�㶼Ĭ�ϱ���ʽ��ΪFAT32 �ļ�ϵͳ������������ֵΪ 1��
                             */


#define	_CODE_PAGE	1
/* Defines which code page is used for path name. Supported code pages are:
/  932, 936, 949, 950, 437, 720, 737, 775, 850, 852, 855, 857, 858, 862, 866,
/  874, 1250, 1251, 1252, 1253, 1254, 1255, 1257, 1258 and 1 (ASCII only).
/  SBCS code pages except for 1 requiers a case conversion table. This
/  might occupy 128 bytes on the RAM on some platforms, e.g. avr-gcc.

/ pdefines����ҳ����·������֧�ֵĴ���ҳ��
932 936 949 950 437 720 737 775 850 852 855 857 858 862 866��
874��1250��1251��1252��1253��1254��1255��1257��1258��1����ASCII����
/ SBCS����ҳ����1��ת�����Ҫ����
Ҳ����ĳЩƽ̨��ռ��128���ֽڵ�RAM������AVR��Ƭ��GCC�� */


#define _WORD_ACCESS	0	 //��0 ��1 ����ֵ�ɱ�ѡ��Ϊ 0 ʱѡ���ֽ�Ѱַ��ʽ��Ϊ1 ʱѡ����Ѱַ��ʽ
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

��_word_accessѡ���ķ��ʷ����Ļ�
��FAT�ṹ���ݡ�
/
0�����ֽڷ����ֽڡ����Ǽ�������ƽ̨��
1���ַ��ʡ���ѡ�����������������������
/
�����ڴ���ֽ�˳���Ǵ���ֽ�����ַ����
/�ַ��ʵĽ������ȷ����Ϊ����_word_access��������Ϊ0��
����������������ֵҲ��������Ϊ1���
/���ܺͱ���Ч�ʡ�*/


/* End of configuration options. Do not change followings without care.    
�˵�����ѡ����ı��������� */
/*--------------------------------------------------------------------------*/



#if _FS_FAT32
#define	CLUST	DWORD
#else
#define	CLUST	WORD
#endif


/* File system object structure �ļ�ϵͳ����Ľṹ*/

typedef struct {
	BYTE	fs_type;	/* FAT sub type SD���� 1 fat12  2 fat16  3 fat32*/
	BYTE	flag;		/* File status flags �ļ�״̬��־ FA_OPENED�Ѵ�   FA_WPRTд����   FA__WIP���ڹ���*/
	BYTE	csize;		/* Number of sectors per cluster ÿ�ص�������*/
	BYTE	pad1;
	WORD	n_rootdir;	/* Number of root directory entries (0 on FAT32) ��Ŀ¼��Ŀ¼�����Ŀ ��0��FAT32��*/
	CLUST	n_fatent;	/* Number of FAT entries (= number of clusters + 2) fat����Ŀ����=����+ 2�� �����ܴ�����2*/
	DWORD	fatbase;	/* FAT start sector �ļ������ʼ����  FAT1�� ������������*/
	DWORD	dirbase;	/* Root directory start sector (Cluster# on FAT32) ��Ŀ¼���ڵĴ� һ����2  �����FAT32����Ŀ¼��ʼ������Ҫ���ȵõ���*/
	DWORD	database;	/* Data start sector ���ݿ�ʼ���� ��SD����Ŀ¼ */

															   //����Ϊ��һ���ļ��Ժ�  �Ż��ж�Ӧ��ֵ 
	DWORD	fptr;		/* File R/W pointer �ļ���/дָ��*/    //ƫ��ֵ ָ��          
	DWORD	fsize;		/* File size �ļ���С*/			                  
	CLUST	org_clust;	/* File start cluster �ļ���ʼ��*/	             
	CLUST	curr_clust;	/* File current cluster �ļ���ǰ��*/	          
	DWORD	dsect;		/* File current data sector �ļ���ǰ��������*/	  
} FATFS;




/* Directory object structure �ļ��нṹ����� ������ֵ ����Ҫ�򿪵��ļ������� Ҫ���ļ��������*/

typedef struct {
	WORD	index;		/* Current read/write index number Ŀǰ��д��������  ��ǰ�Ķ�/дָ��*/
	BYTE*	fn;			/* Pointer to the SFN (in/out) {file[8],ext[3],status[1]}  ���ļ���ָ��  
	                                                    file[8] �ļ���  ext[3]��չ��  status[1]���ļ�״̬ �Ƿ�ɾ��
														����ʱ ֱ�� dir.fn[n]���ɵõ���Ӧֵ
														���Ҳ��Ҫ���ļ��е� �ļ���*/
	CLUST	sclust;		/* Table start cluster (0:Static table) �ļ���������ʼ��  ��0����̬��*/
	CLUST	clust;		/* Current cluster ��Ӧ���ļ��е�ǰ��  Ŀǰ����Ĵ� */
	DWORD	sect;		/* Current sector ��ǰ��������   Ŀǰ�����Ӧ������ */
} DIR;



/* File status structure �ļ��ṹ��*/

typedef struct {
	DWORD	fsize;		/* File size �ļ���С*/
	WORD	fdate;		/* Last modified date ����޸�����*/
	WORD	ftime;		/* Last modified time ����޸�ʱ��*/
	BYTE	fattrib;	/* Attribute ����*/
	char	fname[13];	/* File name �ļ���*/
} FILINFO;



/* File function return code (FRESULT) �ļ��еĺ����ķ��ش��루fresult��*/

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
/* Petit FatFs module application interface        Petit FatFsģ���Ӧ�ó���ӿ�             */

FRESULT pf_mount (FATFS*);						/* Mount/Unmount a logical drive ��װ/�˳�һ���߼�������*/
FRESULT pf_open (const char*);					/* Open a file ��һ���ļ�*/
FRESULT pf_read (void*, WORD, WORD*);			/* Read data from the open file ���ļ��ж�ȡ����*/
FRESULT pf_write (const void*, WORD, WORD*);	/* Write data to the open file ���ļ�д����*/
FRESULT pf_lseek (DWORD);						/* Move file pointer of the open file ���򿪵��ļ����ļ�ָ��*/
FRESULT pf_opendir (DIR*, const char*);			/* Open a directory ��Ŀ¼ �ļ���*/
FRESULT pf_readdir (DIR*, FILINFO*);			/* Read a directory item from the open directory �ӿ���ʽĿ¼/�ļ��� ��һ��Ŀ¼��*/



/*--------------------------------------------------------------*/
/* Flags and offset address        ��־��ƫ�Ƶ�ַ                             */

/* File status flag (FATFS.flag) �ļ�״̬��־����־��������*/

#define	FA_OPENED	0x01		 //�Ѵ�
#define	FA_WPRT		0x02		 //д����
#define	FA__WIP		0x40		 //���ڹ���


/* FAT sub type (FATFS.fs_type) */

#define FS_FAT12	1
#define FS_FAT16	2
#define FS_FAT32	3


/* File attribute bits for directory entry ��Ŀ¼���ļ������ֽ�*/

#define	AM_RDO	0x01	/* Read only ֻ��*/
#define	AM_HID	0x02	/* Hidden ����*/
#define	AM_SYS	0x04	/* System ϵͳ*/
#define	AM_VOL	0x08	/* Volume label ���*/
#define AM_LFN	0x0F	/* LFN entry ����*/
#define AM_DIR	0x10	/* Directory Ŀ¼*/
#define AM_ARC	0x20	/* Archive ����*/
#define AM_MASK	0x3F	/* Mask of defined bits �����λ����*/


/*--------------------------------*/
/* Multi-byte word access macros  ���ֽ��ַ��ʺ�*/

#if _WORD_ACCESS == 1	/* Enable word access to the FAT structure ʹ�ʽ���fat��֯*/
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
