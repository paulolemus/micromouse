#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Include project Makefile
ifeq "${IGNORE_LOCAL}" "TRUE"
# do not include local makefile. User is passing all local related variables already
else
include Makefile
# Include makefile containing local settings
ifeq "$(wildcard nbproject/Makefile-local-hardware_test.mk)" "nbproject/Makefile-local-hardware_test.mk"
include nbproject/Makefile-local-hardware_test.mk
endif
endif

# Environment
MKDIR=mkdir -p
RM=rm -f 
MV=mv 
CP=cp 

# Macros
CND_CONF=hardware_test
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
IMAGE_TYPE=debug
OUTPUT_SUFFIX=elf
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
else
IMAGE_TYPE=production
OUTPUT_SUFFIX=hex
DEBUGGABLE_SUFFIX=elf
FINAL_IMAGE=dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}
endif

ifeq ($(COMPARE_BUILD), true)
COMPARISON_BUILD=-mafrlcsj
else
COMPARISON_BUILD=
endif

ifdef SUB_IMAGE_ADDRESS
SUB_IMAGE_ADDRESS_COMMAND=--image-address $(SUB_IMAGE_ADDRESS)
else
SUB_IMAGE_ADDRESS_COMMAND=
endif

# Object Directory
OBJECTDIR=build/${CND_CONF}/${IMAGE_TYPE}

# Distribution Directory
DISTDIR=dist/${CND_CONF}/${IMAGE_TYPE}

# Source Files Quoted if spaced
SOURCEFILES_QUOTED_IF_SPACED=src/drivers/pic_hardware_test.c src/pic/components/oscillator.c src/pic/components/led.c src/core/floodfill.c src/core/maze.c src/pic/components/sensor.c src/pic/adc.c src/core/path.c src/pic/ble.c src/pic/ble_api.c src/pic/components/encoder.c src/pic/components/motor.c src/pic/qei.c src/pic/utils.c src/core/pid.c src/pic/motor_control.c

# Object Files Quoted if spaced
OBJECTFILES_QUOTED_IF_SPACED=${OBJECTDIR}/src/drivers/pic_hardware_test.o ${OBJECTDIR}/src/pic/components/oscillator.o ${OBJECTDIR}/src/pic/components/led.o ${OBJECTDIR}/src/core/floodfill.o ${OBJECTDIR}/src/core/maze.o ${OBJECTDIR}/src/pic/components/sensor.o ${OBJECTDIR}/src/pic/adc.o ${OBJECTDIR}/src/core/path.o ${OBJECTDIR}/src/pic/ble.o ${OBJECTDIR}/src/pic/ble_api.o ${OBJECTDIR}/src/pic/components/encoder.o ${OBJECTDIR}/src/pic/components/motor.o ${OBJECTDIR}/src/pic/qei.o ${OBJECTDIR}/src/pic/utils.o ${OBJECTDIR}/src/core/pid.o ${OBJECTDIR}/src/pic/motor_control.o
POSSIBLE_DEPFILES=${OBJECTDIR}/src/drivers/pic_hardware_test.o.d ${OBJECTDIR}/src/pic/components/oscillator.o.d ${OBJECTDIR}/src/pic/components/led.o.d ${OBJECTDIR}/src/core/floodfill.o.d ${OBJECTDIR}/src/core/maze.o.d ${OBJECTDIR}/src/pic/components/sensor.o.d ${OBJECTDIR}/src/pic/adc.o.d ${OBJECTDIR}/src/core/path.o.d ${OBJECTDIR}/src/pic/ble.o.d ${OBJECTDIR}/src/pic/ble_api.o.d ${OBJECTDIR}/src/pic/components/encoder.o.d ${OBJECTDIR}/src/pic/components/motor.o.d ${OBJECTDIR}/src/pic/qei.o.d ${OBJECTDIR}/src/pic/utils.o.d ${OBJECTDIR}/src/core/pid.o.d ${OBJECTDIR}/src/pic/motor_control.o.d

# Object Files
OBJECTFILES=${OBJECTDIR}/src/drivers/pic_hardware_test.o ${OBJECTDIR}/src/pic/components/oscillator.o ${OBJECTDIR}/src/pic/components/led.o ${OBJECTDIR}/src/core/floodfill.o ${OBJECTDIR}/src/core/maze.o ${OBJECTDIR}/src/pic/components/sensor.o ${OBJECTDIR}/src/pic/adc.o ${OBJECTDIR}/src/core/path.o ${OBJECTDIR}/src/pic/ble.o ${OBJECTDIR}/src/pic/ble_api.o ${OBJECTDIR}/src/pic/components/encoder.o ${OBJECTDIR}/src/pic/components/motor.o ${OBJECTDIR}/src/pic/qei.o ${OBJECTDIR}/src/pic/utils.o ${OBJECTDIR}/src/core/pid.o ${OBJECTDIR}/src/pic/motor_control.o

# Source Files
SOURCEFILES=src/drivers/pic_hardware_test.c src/pic/components/oscillator.c src/pic/components/led.c src/core/floodfill.c src/core/maze.c src/pic/components/sensor.c src/pic/adc.c src/core/path.c src/pic/ble.c src/pic/ble_api.c src/pic/components/encoder.c src/pic/components/motor.c src/pic/qei.c src/pic/utils.c src/core/pid.c src/pic/motor_control.c


CFLAGS=
ASFLAGS=
LDLIBSOPTIONS=

############# Tool locations ##########################################
# If you copy a project from one host to another, the path where the  #
# compiler is installed may be different.                             #
# If you open this project with MPLAB X in the new host, this         #
# makefile will be regenerated and the paths will be corrected.       #
#######################################################################
# fixDeps replaces a bunch of sed/cat/printf statements that slow down the build
FIXDEPS=fixDeps

.build-conf:  ${BUILD_SUBPROJECTS}
ifneq ($(INFORMATION_MESSAGE), )
	@echo $(INFORMATION_MESSAGE)
endif
	${MAKE}  -f nbproject/Makefile-hardware_test.mk dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}

MP_PROCESSOR_OPTION=33FJ128MC804
MP_LINKER_FILE_OPTION=,--script=p33FJ128MC804.gld
# ------------------------------------------------------------------------------------
# Rules for buildStep: compile
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
${OBJECTDIR}/src/drivers/pic_hardware_test.o: src/drivers/pic_hardware_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/pic_hardware_test.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/pic_hardware_test.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/pic_hardware_test.c  -o ${OBJECTDIR}/src/drivers/pic_hardware_test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/drivers/pic_hardware_test.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/pic_hardware_test.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/oscillator.o: src/pic/components/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/oscillator.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/oscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/oscillator.c  -o ${OBJECTDIR}/src/pic/components/oscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/oscillator.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/oscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/led.o: src/pic/components/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/led.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/led.c  -o ${OBJECTDIR}/src/pic/components/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/led.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/floodfill.o: src/core/floodfill.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/floodfill.o.d 
	@${RM} ${OBJECTDIR}/src/core/floodfill.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/floodfill.c  -o ${OBJECTDIR}/src/core/floodfill.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/floodfill.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/floodfill.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/maze.o: src/core/maze.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/maze.o.d 
	@${RM} ${OBJECTDIR}/src/core/maze.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/maze.c  -o ${OBJECTDIR}/src/core/maze.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/maze.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/maze.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/sensor.o: src/pic/components/sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/sensor.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/sensor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/sensor.c  -o ${OBJECTDIR}/src/pic/components/sensor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/sensor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/sensor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/adc.o: src/pic/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/adc.o.d 
	@${RM} ${OBJECTDIR}/src/pic/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/adc.c  -o ${OBJECTDIR}/src/pic/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/adc.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/path.o: src/core/path.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/path.o.d 
	@${RM} ${OBJECTDIR}/src/core/path.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/path.c  -o ${OBJECTDIR}/src/core/path.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/path.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/path.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/ble.o: src/pic/ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/ble.o.d 
	@${RM} ${OBJECTDIR}/src/pic/ble.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/ble.c  -o ${OBJECTDIR}/src/pic/ble.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/ble.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/ble.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/ble_api.o: src/pic/ble_api.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/ble_api.o.d 
	@${RM} ${OBJECTDIR}/src/pic/ble_api.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/ble_api.c  -o ${OBJECTDIR}/src/pic/ble_api.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/ble_api.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/ble_api.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/encoder.o: src/pic/components/encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/encoder.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/encoder.c  -o ${OBJECTDIR}/src/pic/components/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/encoder.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/motor.o: src/pic/components/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/motor.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/motor.c  -o ${OBJECTDIR}/src/pic/components/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/motor.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/qei.o: src/pic/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/qei.o.d 
	@${RM} ${OBJECTDIR}/src/pic/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/qei.c  -o ${OBJECTDIR}/src/pic/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/qei.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/utils.o: src/pic/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/utils.o.d 
	@${RM} ${OBJECTDIR}/src/pic/utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/utils.c  -o ${OBJECTDIR}/src/pic/utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/utils.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/pid.o: src/core/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/pid.o.d 
	@${RM} ${OBJECTDIR}/src/core/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/pid.c  -o ${OBJECTDIR}/src/core/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/pid.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/motor_control.o: src/pic/motor_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/motor_control.o.d 
	@${RM} ${OBJECTDIR}/src/pic/motor_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/motor_control.c  -o ${OBJECTDIR}/src/pic/motor_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/motor_control.o.d"      -g -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1    -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/motor_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
else
${OBJECTDIR}/src/drivers/pic_hardware_test.o: src/drivers/pic_hardware_test.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/drivers" 
	@${RM} ${OBJECTDIR}/src/drivers/pic_hardware_test.o.d 
	@${RM} ${OBJECTDIR}/src/drivers/pic_hardware_test.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/drivers/pic_hardware_test.c  -o ${OBJECTDIR}/src/drivers/pic_hardware_test.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/drivers/pic_hardware_test.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/drivers/pic_hardware_test.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/oscillator.o: src/pic/components/oscillator.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/oscillator.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/oscillator.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/oscillator.c  -o ${OBJECTDIR}/src/pic/components/oscillator.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/oscillator.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/oscillator.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/led.o: src/pic/components/led.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/led.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/led.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/led.c  -o ${OBJECTDIR}/src/pic/components/led.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/led.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/led.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/floodfill.o: src/core/floodfill.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/floodfill.o.d 
	@${RM} ${OBJECTDIR}/src/core/floodfill.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/floodfill.c  -o ${OBJECTDIR}/src/core/floodfill.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/floodfill.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/floodfill.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/maze.o: src/core/maze.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/maze.o.d 
	@${RM} ${OBJECTDIR}/src/core/maze.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/maze.c  -o ${OBJECTDIR}/src/core/maze.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/maze.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/maze.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/sensor.o: src/pic/components/sensor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/sensor.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/sensor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/sensor.c  -o ${OBJECTDIR}/src/pic/components/sensor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/sensor.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/sensor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/adc.o: src/pic/adc.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/adc.o.d 
	@${RM} ${OBJECTDIR}/src/pic/adc.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/adc.c  -o ${OBJECTDIR}/src/pic/adc.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/adc.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/adc.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/path.o: src/core/path.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/path.o.d 
	@${RM} ${OBJECTDIR}/src/core/path.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/path.c  -o ${OBJECTDIR}/src/core/path.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/path.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/path.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/ble.o: src/pic/ble.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/ble.o.d 
	@${RM} ${OBJECTDIR}/src/pic/ble.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/ble.c  -o ${OBJECTDIR}/src/pic/ble.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/ble.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/ble.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/ble_api.o: src/pic/ble_api.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/ble_api.o.d 
	@${RM} ${OBJECTDIR}/src/pic/ble_api.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/ble_api.c  -o ${OBJECTDIR}/src/pic/ble_api.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/ble_api.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/ble_api.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/encoder.o: src/pic/components/encoder.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/encoder.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/encoder.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/encoder.c  -o ${OBJECTDIR}/src/pic/components/encoder.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/encoder.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/encoder.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/components/motor.o: src/pic/components/motor.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic/components" 
	@${RM} ${OBJECTDIR}/src/pic/components/motor.o.d 
	@${RM} ${OBJECTDIR}/src/pic/components/motor.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/components/motor.c  -o ${OBJECTDIR}/src/pic/components/motor.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/components/motor.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/components/motor.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/qei.o: src/pic/qei.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/qei.o.d 
	@${RM} ${OBJECTDIR}/src/pic/qei.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/qei.c  -o ${OBJECTDIR}/src/pic/qei.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/qei.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/qei.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/utils.o: src/pic/utils.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/utils.o.d 
	@${RM} ${OBJECTDIR}/src/pic/utils.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/utils.c  -o ${OBJECTDIR}/src/pic/utils.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/utils.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/utils.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/core/pid.o: src/core/pid.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/core" 
	@${RM} ${OBJECTDIR}/src/core/pid.o.d 
	@${RM} ${OBJECTDIR}/src/core/pid.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/core/pid.c  -o ${OBJECTDIR}/src/core/pid.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/core/pid.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/core/pid.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
${OBJECTDIR}/src/pic/motor_control.o: src/pic/motor_control.c  nbproject/Makefile-${CND_CONF}.mk
	@${MKDIR} "${OBJECTDIR}/src/pic" 
	@${RM} ${OBJECTDIR}/src/pic/motor_control.o.d 
	@${RM} ${OBJECTDIR}/src/pic/motor_control.o 
	${MP_CC} $(MP_EXTRA_CC_PRE)  src/pic/motor_control.c  -o ${OBJECTDIR}/src/pic/motor_control.o  -c -mcpu=$(MP_PROCESSOR_OPTION)  -MMD -MF "${OBJECTDIR}/src/pic/motor_control.o.d"        -g -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -O0 -I"include" -msmart-io=1 -Wall -msfr-warn=off  
	@${FIXDEPS} "${OBJECTDIR}/src/pic/motor_control.o.d" $(SILENT)  -rsi ${MP_CC_DIR}../ 
	
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemble
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: assemblePreproc
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
else
endif

# ------------------------------------------------------------------------------------
# Rules for buildStep: link
ifeq ($(TYPE_IMAGE), DEBUG_RUN)
dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk    
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -D__DEBUG -D__MPLAB_DEBUGGER_PK3=1  -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)   -mreserve=data@0x800:0x81F -mreserve=data@0x820:0x821 -mreserve=data@0x822:0x823 -mreserve=data@0x824:0x825 -mreserve=data@0x826:0x84F   -Wl,,,--defsym=__MPLAB_BUILD=1,--defsym=__MPLAB_DEBUG=1,--defsym=__DEBUG=1,--defsym=__MPLAB_DEBUGGER_PK3=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	
else
dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${OUTPUT_SUFFIX}: ${OBJECTFILES}  nbproject/Makefile-${CND_CONF}.mk   
	@${MKDIR} dist/${CND_CONF}/${IMAGE_TYPE} 
	${MP_CC} $(MP_EXTRA_LD_PRE)  -o dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX}  ${OBJECTFILES_QUOTED_IF_SPACED}      -mcpu=$(MP_PROCESSOR_OPTION)        -omf=elf -DXPRJ_hardware_test=$(CND_CONF)  -legacy-libc  $(COMPARISON_BUILD)  -Wl,,,--defsym=__MPLAB_BUILD=1,$(MP_LINKER_FILE_OPTION),--stack=16,--check-sections,--data-init,--pack-data,--handles,--isr,--no-gc-sections,--fill-upper=0,--stackguard=16,--no-force-link,--smart-io,-Map="${DISTDIR}/${PROJECTNAME}.${IMAGE_TYPE}.map",--report-mem,--memorysummary,dist/${CND_CONF}/${IMAGE_TYPE}/memoryfile.xml$(MP_EXTRA_LD_POST) 
	${MP_CC_DIR}/xc16-bin2hex dist/${CND_CONF}/${IMAGE_TYPE}/micromouse.${IMAGE_TYPE}.${DEBUGGABLE_SUFFIX} -a  -omf=elf  
	
endif


# Subprojects
.build-subprojects:


# Subprojects
.clean-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/hardware_test
	${RM} -r dist/hardware_test

# Enable dependency checking
.dep.inc: .depcheck-impl

DEPFILES=$(shell "${PATH_TO_IDE_BIN}"mplabwildcard ${POSSIBLE_DEPFILES})
ifneq (${DEPFILES},)
include ${DEPFILES}
endif
