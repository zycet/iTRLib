//
// Created by ghdawn on 16-1-10.
//

#include "standardexchangeprotocolserial.h"
namespace itr_protocol
{
    U32 StandardExchangeProtocolSerial::FillBuffer(const StandardExchangePackage &SEPackage, U8 *buffer)
    {
        StandardExchangePackageSerial seps(SEPackage);
        return (U32) seps.writeTo(buffer);
    }

    U32 StandardExchangeProtocolSerial::ProcessByte(U8 *buffer, S32 offset, S32 length)
    {
        U32 receiveFrameNum = 0;
        for (int i = offset; i < length + offset; i++)
        {
            U8 b = buffer[i];
            if (receiveBufferState == 0)//S0
            {
                if (b == S0)
                {
                    receiveBuffer[receiveBufferState] = b;
                    receiveBufferState = 1;
                }
            }
            else if (receiveBufferState == 1)//S1
            {
                if (b == S1)
                {
                    receiveBuffer[receiveBufferState] = b;
                    receiveBufferState = 2;
                }
                else
                {
                    receiveBufferState = 0;
                }
            }
            else if (receiveBufferState >= 2)
            {
                receiveBuffer[receiveBufferState] = b;
                receiveBufferState++;
                U8 dataLen = receiveBuffer[2];
                if (receiveBufferState == dataLen + HeaderLength + TailLength)
                {
                    StandardExchangePackageSerial sp;
                    FormatErrorEnum fe = sp.readFrom(receiveBuffer, 0, receiveBufferState);
                    if (fe == None)
                    {
                        receiveFrameNum++;
                        if (Enable)
                        {
                            for (int j = 0; j < receiveList.size(); ++j)
                            {
                                receiveList[j]->Do(sp);
                            }
                        }
                    }
                    else
                    {
                        //UNDONE:Error Sum
                    }
                    receiveBufferState = 0;
                }
            }
        }
        return receiveFrameNum;
    }

    void StandardExchangeProtocolSerial::AddReceiveFun(OnReceiveAction *fun)
    {
        this->receiveList.push_back(fun);
    }

    StandardExchangeProtocolSerial::StandardExchangeProtocolSerial()
    {
        this->Enable = true;
        this->receiveBufferState = 0;
        this->S0 = StandardExchangePackageSerial::S0Default;
        this->S1 = StandardExchangePackageSerial::S1Default;
    }
}