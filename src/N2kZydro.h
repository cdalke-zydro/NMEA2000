/*
 * N2kZydro.h
 * 
 * Copyright (c) 2019-2025 Chris Dalke, www.zydromarine.com, 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS 
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
*/

/****************************************************************************
 * \file   N2kZydro.h
 * \brief  Collection of functions for handling NMEA2000 Zydro Marine messages
 *
 * This is collection of functions for handling NMEA2000 Zydro Marine messages.
 * This is a set of non-standard, open messages used by Zydro products to 
 * supplement standard NMEA 2000 PGNs.
 * 
 * This file contains functions to create and parse messages. Each PGN has a
 * a function to SetN2kPGN<id> and ParseN2kPGN<id>.
 * 
 * If you do not send any Zydro-specific messages you do not need this library.
 * 
 * \note  These are non-standard open messages created and used by Zydro Marine!
 *        see the [Zydro Marine Website] (https://www.zydromarine.com/)
 * 
 * \authors Chris Dalke
*/

#ifndef _N2kZydro_H_
#define _N2kZydro_H_

#include "N2kMsg.h"
#include "N2kTypes.h"
#include <stdint.h>

enum tN2kZydroDeviceModel {
    tN2kZydroDeviceModel_invalid=0,
    tN2kZydroDeviceModel_estop=1
};

enum tN2kZydroDeviceHealth {
    tN2kZydroDeviceHealth_invalid=0,
    tN2kZydroDeviceHealth_pending=1,
    tN2kZydroDeviceHealth_healthy=2,
    tN2kZydroDeviceHealth_unhealthy=3,
    tN2kZydroDeviceHealth_emergencyStop=4
};

/**************************************************************************
 * \brief Setting up PGN 65280 for Zydro "Product Heartbeat"
 * 
 * This message is broadcast periodically by all Zydro products to provide
 * a heartbeat used for auto-detection purposes.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param SID             Sequence identifier. In most cases you can use just 0xff for SID. See \ref secRefTermSID. \n
 *                        \n
 *                        The sequence identifier field is used to tie different PGNs data together to the same 
 *                        sampling or calculation time.
 * \param ModelID         Zydro-specific product model ID, from a Zydro internal enumeration.
 * \param Health          Health status for the device, from a Zydro internal enumeration.
 */
void SetN2kPGN65280(tN2kMsg &N2kMsg, unsigned char SID, tN2kZydroDeviceModel ModelID, tN2kZydroDeviceHealth Health);

/**************************************************************************
 * \brief Parsing PGN 65280 for Zydro "Product Heartbeat"
 * 
 * This message is broadcast periodically by all Zydro products to provide
 * a heartbeat used for auto-detection purposes.
 * 
 * \param N2kMsg          Reference to a N2kMsg Object, 
 *                        Output: NMEA2000 message ready to be send.
 * \param SID             Sequence ID. Normally you can just forget its value. See \ref secRefTermSID.
 * \param ModelID         Zydro-specific product model ID, from a Zydro internal enumeration.
 * \param Health          Health status for the device, from a Zydro internal enumeration.
 *
 * \return true     Parsing of PGN Message successful
 * \return false    Parsing of PGN Message aborted
 *
 */
bool ParseN2kPGN65280(const tN2kMsg &N2kMsg, unsigned char &SID, tN2kZydroDeviceModel &ModelID, tN2kZydroDeviceHealth &Health);

/**************************************************************************/

#endif

