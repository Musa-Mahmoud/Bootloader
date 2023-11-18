/*
 * BL.c
 *
 *  Created on: Oct 21, 2023
 *      Author: Mousa Mahmoud
 */

#include <stdint.h>

#include "main.h"
#include "BL.h"
#include "BL_prv.h"

/* External Variables */

extern CRC_HandleTypeDef hcrc;

extern UART_HandleTypeDef huart2;

/* Public Functions */

void BL_voidHandleGetVerCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8BLVersion, Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		voidSendAck(1U);	// Bootloader version has a size of 1 byte

		Local_u8BLVersion = BL_VERSION;

		HAL_UART_Transmit(&huart2, &Local_u8BLVersion, 1U, HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleGetHelpCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint8_t Local_u8BLCommands[] =
		{
				BL_GET_VER,
				BL_GET_HELP,
				BL_GET_CID,
				BL_GET_RDP_STATUS,
				BL_GO_TO_ADDR,
				BL_FLASH_ERASE,
				BL_MEM_WRITE,
				BL_EN_RW_PROTECT,
				BL_MEM_READ,
				BL_READ_SECTOR_STATUS,
				BL_OPT_READ,
				BL_DIS_WR_PROTECT
		};

		voidSendAck(sizeof(Local_u8BLCommands));

		HAL_UART_Transmit(&huart2, Local_u8BLCommands, sizeof(Local_u8BLCommands), HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleGetCIDCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint16_t Local_u16DeviceID = DBGMCU->IDCODE;

		voidSendAck(2U);

		HAL_UART_Transmit(&huart2, (uint8_t *) &Local_u16DeviceID, 2U, HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleGetRDPStatusCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint8_t Local_u8RDPStatus = (uint8_t) ((RDB_USER_OPTION_WORD >> RDP_BITS_ACCESS) & RDP_MASK);

		voidSendAck(1U);

		HAL_UART_Transmit(&huart2, &Local_u8RDPStatus, 1U, HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleGoToAddressCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint8_t Local_u8AddressValidStatus;
		uint32_t Local_u32Address;

		voidSendAck(1U);

		Local_u32Address = *((uint32_t *) &Copy_pu8CmdPacket[2]);

		Local_u8AddressValidStatus = u8ValidateAddress(Local_u32Address);

		HAL_UART_Transmit(&huart2, &Local_u8AddressValidStatus, 1U, HAL_MAX_DELAY); // Send the address status to the host

		if (VALID_ADDRESS == Local_u8AddressValidStatus)
		{
			/* Define a pointer to function */
			void (*Local_pvFuncPtr) (void) = NULL;

			Local_u32Address |= 1U; // Oring the address with 1 to make T-bit = 1

			Local_pvFuncPtr = (void*) Local_u32Address;

			Local_pvFuncPtr();
		}
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleFlashEraseCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint8_t Local_u8EraseStatus;

		voidSendAck(1U);

		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

		Local_u8EraseStatus = u8ExcuteFlashErase(Copy_pu8CmdPacket[CMD_SECTOR_NUM_IDX], Copy_pu8CmdPacket[CMD_NUM_OF_SECTORS_IDX]);

		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

		HAL_UART_Transmit(&huart2, &Local_u8EraseStatus, 1U, HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleMemWriteCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint8_t Local_u8WritingStatus;

		uint32_t Local_u32BaseAddress = *((uint32_t *) &Copy_pu8CmdPacket[2]); // Copy_pu8CmdPacket[2] = Base Memory Address

		uint8_t Local_u8AddressStatus  = u8ValidateAddress(Local_u32BaseAddress);

		voidSendAck(1U);

		if (VALID_ADDRESS == Local_u8AddressStatus)
		{
			uint8_t Local_u8PayLoadLength = Copy_pu8CmdPacket[6];
			Local_u8WritingStatus = u8ExcuteMemWrite(&Copy_pu8CmdPacket[7U], Local_u32BaseAddress, Local_u8PayLoadLength);
		}
		else
		{
			Local_u8WritingStatus = WRITING_ERROR;
		}

		HAL_UART_Transmit(&huart2, &Local_u8WritingStatus, 1U, HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleEnRWProtectCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		uint8_t Local_u8SectorDetails, Local_u8ProtectionMode, Local_u8EnableStatus;

		Local_u8SectorDetails = Copy_pu8CmdPacket[CMD_SECTOR_DTLS_IDX];
		Local_u8ProtectionMode = Copy_pu8CmdPacket[CMD_PROTECT_MODE_IDX];

		voidSendAck(1U);

		Local_u8EnableStatus = u8ExcuteEnRWProtect(Local_u8SectorDetails, Local_u8ProtectionMode);

		HAL_UART_Transmit(&huart2, &Local_u8EnableStatus, 1U, HAL_MAX_DELAY);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleMemReadCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		voidSendAck(1U);

	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleReadSectorStatusCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		voidSendAck(1U);
	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleOTPReadCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		voidSendAck(1U);

	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

void BL_voidHandleDisRWProtectCmd(uint8_t *Copy_pu8CmdPacket)
{
	uint8_t Local_u8CRCStatus, Local_u8CmdLen;
	uint32_t Local_u32HostCRC;

	Local_u8CmdLen = Copy_pu8CmdPacket[0U] + 1U; 	// Copy_pu8CmdPacket[0] is the length to follow

	Local_u32HostCRC = *((uint32_t *)(Copy_pu8CmdPacket + Local_u8CmdLen - 4U)); // This is the CRC value calculated by the host

	Local_u8CRCStatus = u8VerfiyCRC(Copy_pu8CmdPacket, (Local_u8CmdLen - 4U), Local_u32HostCRC);

	if (CRC_SUCCESS == Local_u8CRCStatus)
	{
		voidSendAck(1U);

	}
	else if (CRC_FAIL == Local_u8CRCStatus)
	{
		voidSendNack();
	}
}

/* Private Functions */

static uint8_t u8VerfiyCRC(uint8_t *Copy_pu8DataArr, uint8_t Copy_pu8Length, uint32_t Copy_u32HostCRC)
{
	uint8_t Local_u8Iterator, Local_u8CRCStatus;
	uint32_t Local_u32AccCRC, Local_u32Temp;

	for (Local_u8Iterator = 0; Local_u8Iterator < Copy_pu8Length; Local_u8Iterator++)
	{
		Local_u32Temp = Copy_pu8DataArr[Local_u8Iterator];
		Local_u32AccCRC = HAL_CRC_Accumulate(&hcrc, &Local_u32Temp, 1U);
	}

	/* Reset the CRC calculation unit */
	__HAL_CRC_DR_RESET(&hcrc);

	if (Local_u32AccCRC == Copy_u32HostCRC)
	{
		Local_u8CRCStatus = CRC_SUCCESS;
	}
	else
	{
		Local_u8CRCStatus = CRC_FAIL;
	}

	return Local_u8CRCStatus;
}

static void voidSendAck(uint8_t Copy_u8ReplayLength)
{
	uint8_t Local_u8AckBuffer[2] = {BL_ACK, Copy_u8ReplayLength};

	HAL_UART_Transmit(&huart2, Local_u8AckBuffer, 2U, HAL_MAX_DELAY);
}

static void voidSendNack(void)
{
	uint8_t Local_u8Nack = BL_NACK;

	HAL_UART_Transmit(&huart2, &Local_u8Nack, 1U, HAL_MAX_DELAY);
}

/* Address is valid if it is within: SRAM or Flash */
static uint8_t u8ValidateAddress(uint32_t Copy_u32Address)
{
	uint8_t Local_u8AddressStatus;

	if ((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else if ((Copy_u32Address >= SRAM1_BASE) && (Copy_u32Address <= (SRAM1_BASE + (128U * 1024U))))
	{
		Local_u8AddressStatus = VALID_ADDRESS;
	}
	else
	{
		Local_u8AddressStatus = INVALID_ADDRESS;
	}

	return Local_u8AddressStatus;
}

static uint8_t u8ExcuteFlashErase(uint8_t Copy_u8SectorNumber, uint8_t Copy_u8NumberOfSectors)
{
	HAL_StatusTypeDef Local_ErrorStatus = HAL_OK;

	if ((Copy_u8NumberOfSectors > NUMBER_OF_SECTORS) && (MASS_ERASE_CODE != Copy_u8SectorNumber))
	{
		Local_ErrorStatus = HAL_ERROR;
	}
	else if ((Copy_u8SectorNumber > LAST_SECTOR_NUMBER) && (MASS_ERASE_CODE != Copy_u8SectorNumber))
	{
		Local_ErrorStatus = HAL_ERROR;
	}
	else
	{
		FLASH_EraseInitTypeDef Local_EraseConfig;
		uint32_t Local_u32SectorError;

		if (MASS_ERASE_CODE == Copy_u8SectorNumber)
		{
			/* Mass erase operation is required */
			Local_EraseConfig.TypeErase = FLASH_TYPEERASE_MASSERASE;
		}
		else
		{
			/* Sector erase operation is required */
			uint8_t Local_u8RemainingSectors = NUMBER_OF_SECTORS - Copy_u8NumberOfSectors;

			if (Copy_u8NumberOfSectors > Local_u8RemainingSectors)
			{
				/* If number of sectors is bigger than max, make it equal to the maximum */
				Copy_u8NumberOfSectors = Local_u8RemainingSectors;
			}

			Local_EraseConfig.TypeErase = FLASH_TYPEERASE_SECTORS;
			Local_EraseConfig.Sector = Copy_u8SectorNumber;
			Local_EraseConfig.NbSectors = Copy_u8NumberOfSectors;
		}

		Local_EraseConfig.VoltageRange = FLASH_VOLTAGE_RANGE_3;
		Local_EraseConfig.Banks = FLASH_BANK_1;

		/* Unlock the flash before erasing */
		HAL_FLASH_Unlock();

		Local_ErrorStatus = HAL_FLASHEx_Erase(&Local_EraseConfig, &Local_u32SectorError);

		/* Lock the flash again */
		HAL_FLASH_Lock();
	}

	return Local_ErrorStatus;
}

static uint8_t u8ExcuteMemWrite(uint8_t *Copy_pu8Buffer, uint32_t Copy_u32Address, uint8_t Copy_u8Length)
{
	HAL_StatusTypeDef Local_ErrorStatus = HAL_OK;

	if ((Copy_u32Address >= FLASH_BASE) && (Copy_u32Address <= FLASH_END))
	{
		uint8_t Local_u8Iterator;

		/* Unlock the flash before writing */
		HAL_FLASH_Unlock();

		for (Local_u8Iterator = 0; Local_u8Iterator < Copy_u8Length; Local_u8Iterator++)
		{
			Local_ErrorStatus = HAL_FLASH_Program(FLASH_TYPEPROGRAM_BYTE, (Copy_u32Address + Local_u8Iterator), (uint64_t) Copy_pu8Buffer[Local_u8Iterator]);
		}

		/* Lock the flash again */
		HAL_FLASH_Lock();
	}
	else if ((Copy_u32Address >= SRAM1_BASE) && (Copy_u32Address <= (SRAM1_BASE + (128U * 1024U))))
	{
		/* Writing in SRAM case */
		uint8_t Local_u8Iterator;

		uint8_t *Local_pu8Dst = (uint8_t *) Copy_u32Address;

		for (Local_u8Iterator = 0; Local_u8Iterator < Copy_u8Length; Local_u8Iterator++)
		{
			Local_pu8Dst[Local_u8Iterator] = Copy_pu8Buffer[Local_u8Iterator];
		}
	}


	return Local_ErrorStatus;
}

static uint8_t u8ExcuteEnRWProtect(uint8_t Copy_u8SectorsProtectionState, uint8_t Copy_u8ProtectionMode)
{
	if ((Copy_u8ProtectionMode != WRITE_PROTECTION) && (Copy_u8ProtectionMode != READ_WRITE_PROTECTION))
	{
		return HAL_ERROR;
	}

	uint8_t Local_u8ErrorStatus;

	/* Enabel write protection */

	/* Unlock the option bytes sector to unable operation on it */
	Local_u8ErrorStatus = HAL_FLASH_OB_Unlock();

	/* Wait until there is no ongiong operation */
	Local_u8ErrorStatus = FLASH_WaitForLastOperation(FLASH_TIMEOUT_VALUE);


	/* Select the protection mode as: write */
	CLEAR_BIT(FLASH->OPTCR, FLASH_OPTCR_SPRMOD);

	/* Set the sectors that will be write protected */
	FLASH_OPTCR_nWRP_BYTE = (~Copy_u8SectorsProtectionState);

	/* Set the start bit and wait for the BSY flag */
	Local_u8ErrorStatus = HAL_FLASH_OB_Launch();

	if (READ_WRITE_PROTECTION == Copy_u8ProtectionMode)
	{
		/* Select the protection mode as: write */
		SET_BIT(FLASH->OPTCR, FLASH_OPTCR_SPRMOD);

		/* Set the sectors that will be write protected */
		FLASH_OPTCR_nWRP_BYTE = Copy_u8SectorsProtectionState;

		/* Set the start bit and wait for the BSY flag */
		Local_u8ErrorStatus = HAL_FLASH_OB_Launch();
	}

	/* Lock the option bytes sector again */
	Local_u8ErrorStatus = HAL_FLASH_OB_Lock();

	return Local_u8ErrorStatus;
}
