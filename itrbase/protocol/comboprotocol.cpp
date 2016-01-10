//
// Created by ghdawn on 16-1-10.
//

#include "comboprotocol.h"
#include "combopackage.h"

namespace itr_protocol
{
    U32 ComboProtocol::processByte(U8 *buffer, int offset, int length)
    {
        U32 receiveFrameNum = 0;
        int i = offset;
        while (i < offset + length)
        {
            if (buffer[i] == ComboPackage::S0Default && buffer[i + 1] == ComboPackage::S1Default)
            {
                ComboPackage cp;
                FormatErrorEnum formatError = cp.readFrom(buffer, i, (U32) (offset + length - i));
                if (formatError == None)
                {
                    for (int j = 0; j < receiveList.size(); ++j)
                    {
                        receiveList[j]->Do(cp.F0, cp.F1, cp.data, cp.length);
                    }
                    receiveFrameNum++;
                }
                else
                {
                    return receiveFrameNum;
                }
            }
            else
            {
                ++i;
            }
        }
        return receiveFrameNum;
    }

    void ComboProtocol::addReceiveFun(onReceive *receive)
    {
        receiveList.push_back(receive);
    }
}
