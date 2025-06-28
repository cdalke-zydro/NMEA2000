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

#include "N2kTypes.h"
#include "N2kZydro.h"
#include <string.h>

#define ZydroProprietary 0x3600 // Random placeholder number

/**************************************************************************/
// PGN 65280: Zydro "Product Heartbeat"

void SetN2kPGN65280(tN2kMsg &N2kMsg, unsigned char SID, tN2kZydroDeviceModel ModelID, tN2kZydroDeviceHealth Health) {
    N2kMsg.SetPGN(65280L);
    N2kMsg.Priority=5;
    N2kMsg.Add2ByteUInt(ZydroProprietary);
    N2kMsg.AddByte(SID);
    N2kMsg.AddByte((unsigned char)ModelID);
    N2kMsg.AddByte((unsigned char)Health);
}

bool ParseN2kPGN65280(const tN2kMsg &N2kMsg, unsigned char &SID, tN2kZydroDeviceModel &ModelID, tN2kZydroDeviceHealth &Health) {
  if (N2kMsg.PGN!=65280L) return false;
  int Index=0;
  if (N2kMsg.Get2ByteUInt(Index)!=ZydroProprietary) return false;
  SID=N2kMsg.GetByte(Index);
  ModelID=(tN2kZydroDeviceModel)(N2kMsg.GetByte(Index));
  Health=(tN2kZydroDeviceHealth)(N2kMsg.GetByte(Index));
  return true;
}
