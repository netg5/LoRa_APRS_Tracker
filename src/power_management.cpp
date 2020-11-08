
#include "power_management.h"

// cppcheck-suppress uninitMemberVar
PowerManagement::PowerManagement()
{
}

// cppcheck-suppress unusedFunction
bool PowerManagement::begin(TwoWire & port)
{
	bool result = axp.begin(port, AXP192_SLAVE_ADDRESS);
	if(!result)
	{
		axp.setDCDC1Voltage(3300);
		// Enable AXP ADC function
		axp.adc1Enable(AXP202_BATT_CUR_ADC1 |
						AXP202_BATT_VOL_ADC1,
						true);
	}
	return result;
}

// cppcheck-suppress unusedFunction
void PowerManagement::activateLoRa()
{
	axp.setPowerOutPut(AXP192_LDO2, AXP202_ON);
}

// cppcheck-suppress unusedFunction
void PowerManagement::deactivateLoRa()
{
	axp.setPowerOutPut(AXP192_LDO2, AXP202_OFF);
}

// cppcheck-suppress unusedFunction
void PowerManagement::activateGPS()
{
	axp.setPowerOutPut(AXP192_LDO3, AXP202_ON);
}

// cppcheck-suppress unusedFunction
void PowerManagement::deactivateGPS()
{
	axp.setPowerOutPut(AXP192_LDO3, AXP202_OFF);
}

// cppcheck-suppress unusedFunction
void PowerManagement::activateOLED()
{
	axp.setPowerOutPut(AXP192_DCDC1, AXP202_ON);
}

// cppcheck-suppress unusedFunction
void PowerManagement::decativateOLED()
{
	axp.setPowerOutPut(AXP192_DCDC1, AXP202_OFF);
}

double PowerManagement::getBatteryVoltage()
{
	return axp.getBattVoltage() / 1000.0;
}

double PowerManagement::getBatteryChargeDischargeCurrent()
{
	if(axp.isChargeing())
	{
		return axp.getBattChargeCurrent();
	}
	return -1.0 * axp.getBattDischargeCurrent();
}
