/*
 * BL.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Mousa Mahmoud
 */

#ifndef INC_BL_H_
#define INC_BL_H_

#define BL_ACK					(0xA5U)
#define BL_NACK					(0x7FU)

#define BL_GET_VER				(0X51U)
#define BL_GET_HELP				(0X52U)
#define BL_GET_CID				(0X53U)
#define BL_GET_RDP_STATUS		(0X54U)
#define BL_GO_TO_ADDR			(0X55U)
#define BL_FLASH_ERASE			(0X56U)
#define BL_MEM_WRITE			(0X57U)
#define BL_EN_RW_PROTECT		(0X58U)
#define BL_MEM_READ				(0X59U)
#define BL_READ_SECTOR_STATUS	(0X5AU)
#define BL_OPT_READ				(0X5BU)
#define BL_DIS_WR_PROTECT		(0X5CU)

/* Fuctions Prototype */

void BL_voidHandleGetVerCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleGetHelpCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleGetCIDCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleGetRDPStatusCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleGoToAddressCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleFlashEraseCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleMemWriteCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleEnRWProtectCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleMemReadCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleReadSectorStatusCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleOTPReadCmd(uint8_t *Copy_pu8CmdPacket);

void BL_voidHandleDisRWProtectCmd(uint8_t *Copy_pu8CmdPacket);

#endif /* INC_BL_H_ */
