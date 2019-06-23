/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2016        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "ff.h"			/* Obtains integer types */
#include "diskio.h"		/* Declarations of disk functions */

/* Definitions of physical drive number for each drive */
#define DEV_RAM		0	/* Example: Map Ramdisk to physical drive 0 */
#define DEV_MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define DEV_USB		2	/* Example: Map USB MSD to physical drive 2 */

// the os libs
#include <io/Ata.h>
#include <main/Res.h>

/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE /*pdrv*/		/* Physical drive nmuber to identify the drive */
)
{
  if (Res::getAta().isInitialized())
    return 0;

  return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE /*pdrv*/				/* Physical drive nmuber to identify the drive */
)
{
  switch (Res::getAta().init())
  {
  case Ata::InitStatus::NoDrivesDetected:
  case Ata::InitStatus::NoPrimaryMaster:
  case Ata::InitStatus::NotAtaDevice:
    return STA_NODISK;
  case Ata::InitStatus::Ok:
    return 0;
  case Ata::InitStatus::Error:
  default:
    return STA_NOINIT;
  }
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE /*pdrv*/,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
  switch (Res::getAta().read(sector, count, buff))
  {
  case Ata::Result::Ok:
    return RES_OK;
  case Ata::Result::NotInitialized:
    return RES_NOTRDY;
  case Ata::Result::SectorNbTooBig:
    return RES_PARERR;
  case Ata::Result::Error:
  default:
    return RES_ERROR;
  }
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE /*pdrv*/,			/* Physical drive nmuber to identify the drive */
	const BYTE* /*buff*/,	/* Data to be written */
	DWORD /*sector*/,		/* Start sector in LBA */
	UINT /*count*/			/* Number of sectors to write */
)
{
	/* DRESULT res; */
	/* int result; */

	/* switch (pdrv) { */
	/* case DEV_RAM : */
	/* 	// translate the arguments here */

	/* 	result = RAM_disk_write(buff, sector, count); */

	/* 	// translate the reslut code here */

	/* 	return res; */

	/* case DEV_MMC : */
	/* 	// translate the arguments here */

	/* 	result = MMC_disk_write(buff, sector, count); */

	/* 	// translate the reslut code here */

	/* 	return res; */

	/* case DEV_USB : */
	/* 	// translate the arguments here */

	/* 	result = USB_disk_write(buff, sector, count); */

	/* 	// translate the reslut code here */

	/* 	return res; */
	/* } */

	return RES_PARERR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE /*pdrv*/,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
  // TODO: make it properly!
  switch (cmd)
  {
    case GET_SECTOR_COUNT:
      *((DWORD*)buff) = 79872;
      break;
    case GET_SECTOR_SIZE:
      *((WORD*)buff) = 512;
      break;
    case GET_BLOCK_SIZE:
      *((DWORD*)buff) = 1;
      break;
  }

  return RES_OK;
}

DWORD get_fattime()
{
  return 999999;
}
