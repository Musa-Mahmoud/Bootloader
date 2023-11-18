/*
 * BL_prv.h
 *
 *  Created on: Oct 21, 2023
 *      Author: Mousa Mahmoud
 */

#ifndef INC_BL_PRV_H_
#define INC_BL_PRV_H_

#define VALID_ADDRESS			(0U)
#define INVALID_ADDRESS			(1U)

#define WRITING_SUCCESS			(0U)
#define WRITING_ERROR			(1U)

#define CRC_FAIL				(0U)
#define CRC_SUCCESS				(1U)

#define BL_VERSION				(1U)

#define DBGMCU_IDCODE_REG		*((volatile uint32_t *) 0xE0042000U)

#define DEV_ID_MASK				(0x0FFFU)

#define RDB_USER_OPTION_WORD	*((volatile uint32_t *) 0x1FFFC000U)

#define RDP_BITS_ACCESS			(8U)

#define RDP_MASK				(0xFFU)

#define NUMBER_OF_SECTORS		(8U)
#define LAST_SECTOR_NUMBER		(7U)

#define MASS_ERASE_CODE			(0xFFU)

#define CMD_SECTOR_NUM_IDX		(2U)
#define CMD_NUM_OF_SECTORS_IDX	(3U)

#define PROTECTION_DISABLED		(0U)
#define PROTECTION_ENABLED		(1U)

#define WRITE_PROTECTION		(1U)
#define READ_WRITE_PROTECTION	(2U)

#define FLASH_TIMEOUT_VALUE		(10000U)

#define FLASH_OPTCR_nWRP_BYTE	(*((volatile uint8_t *)OPTCR_BYTE2_ADDRESS))

#define CMD_SECTOR_DTLS_IDX		(2U)
#define CMD_PROTECT_MODE_IDX	(3U)

/* Private Functions Prortotype */

static uint8_t u8VerfiyCRC(uint8_t *Copy_pu8DataArr, uint8_t Copy_pu8Length, uint32_t Copy_u32HostCRC);

static void voidSendAck(uint8_t Copy_u8ReplayLength);

static void voidSendNack(void);

static uint8_t u8ValidateAddress(uint32_t Copy_u32Address);

static uint8_t u8ExcuteFlashErase(uint8_t Copy_u8SectorNumber, uint8_t Copy_u8NumberOfSector);

static uint8_t u8ExcuteMemWrite(uint8_t *Copy_pu8Buffer, uint32_t Copy_u32Address, uint8_t Copy_u8Length);

static uint8_t u8ExcuteEnRWProtect(uint8_t Copy_u8SectorsProtectionState, uint8_t Copy_u8ProtectionMode);

#endif /* INC_BL_PRV_H_ */
